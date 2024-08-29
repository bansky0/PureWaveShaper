/*
  ==============================================================================

    SquareWave.cpp
    Created: 28 Aug 2024 2:25:56pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "SquareWave.h"
void SquareWave::setFrequency(double inFrequecy)
{
    frequency = inFrequecy;
}

void SquareWave::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);

    for (int i = 0; i < 2; i++)
    {
        time[i] = 0.0f;
        deltaTime[i] = 1.0f / sampleRate;
    }
}

void SquareWave::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float fullPeriodTime = 1.0f / frequency;
            float halfPeriodTime = fullPeriodTime / 2.0f;
            float localTime = fmod(time[channel], fullPeriodTime);
            float outSample = 0.0f;

            if (localTime < halfPeriodTime)
                outSample = 1.0f;
            else
                outSample = 0.0f;
            buffer.setSample(channel, i, outSample);

            time[channel] += deltaTime[channel];

            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;

        }
    }

}

SquareWave::SquareWave()
{
}

SquareWave::~SquareWave()
{
}