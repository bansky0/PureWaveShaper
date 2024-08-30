/*
  ==============================================================================

    SawtoothWave.cpp
    Created: 29 Aug 2024 4:38:15pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "SawtoothWave.h"
void SawtoothWave::setFrequency(double inFrequecy)
{
    frequency = inFrequecy;
}

void SawtoothWave::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);

    for (int i = 0; i < 2; i++)
    {
        time[i] = 0.0f;
        deltaTime[i] = 1.0f / sampleRate;
    }
}

void SawtoothWave::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float outSample = 0.0f;

            float fullPeriodTime = 1.0f / frequency;
            float localTime = fmod(time[channel], fullPeriodTime);

            outSample = (localTime / fullPeriodTime) * 2.0f - 1.0f;

            buffer.setSample(channel, i, outSample);

            time[channel] += deltaTime[channel];

            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;
        }
    }
}

SawtoothWave::SawtoothWave()
{
}

SawtoothWave::~SawtoothWave()
{
}