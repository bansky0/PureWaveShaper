/*
  ==============================================================================

    TriangleWave.cpp
    Created: 28 Aug 2024 5:32:09pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "TriangleWave.h"
void TriangleWave::setFrequency(double inFrequency)
{
    frequency = inFrequency;
}

void TriangleWave::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);

    for (int i = 0; i < 2; i++)
    {
        time[i] = 0.0f;
        deltaTime[i] = 1.0f / sampleRate;
    }
}

void TriangleWave::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float res = 0.0f;
            float fullPeriodTime = 1.0f / frequency;
            float localTime = fmod(time[channel], fullPeriodTime);
            float outSample = 0.0f;

            float value = localTime / fullPeriodTime;

            if (value < 0.25f)
            {
                outSample = value * 4.0f;
            }
            else if (value < 0.75f)
            {
                outSample = 2.0f - (value * 4.0f);
            }
            else
            {
                outSample = value * 4.0f - 4.0f;
            }

            buffer.setSample(channel, i, outSample);

            time[channel] += deltaTime[channel];

            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;
            
        }
    }
}

TriangleWave::TriangleWave()
{
}

TriangleWave::~TriangleWave()
{
}