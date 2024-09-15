/*
  ==============================================================================

    SawtoothWave2.cpp
    Created: 9 Sep 2024 1:04:43pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "SawtoothWave2.h"

void SawtoothWave2::setFrequency(double inFrequecy)
{
    frequency = inFrequecy;
    
    if (sampleRate > 0.0f)
    {
        phaseIncrement = 1.0f / (sampleRate / frequency);
    }
}

void SawtoothWave2::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);
}

void SawtoothWave2::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float outSample = 0.0f;

            outSample = 2.0f * phase[channel] - 1.0f;

            buffer.setSample(channel, i, outSample);

            phase[channel] += phaseIncrement;

            if (phase[channel] >= 1.0f)
                phase[channel] = 0.0f;
        }
    }
}

SawtoothWave2::SawtoothWave2()
{
}

SawtoothWave2::~SawtoothWave2()
{
}