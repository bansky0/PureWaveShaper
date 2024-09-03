/*
  ==============================================================================

    FullWaveRectification.cpp
    Created: 2 Sep 2024 8:03:38pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "FullWaveRectification.h"

void FullWaveRectification::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            float outSample = 0.0f;

            if (inSample >= 0.0f)
            {
                outSample = inSample;
            }
            else
            {
                outSample = -1.0f * inSample;
            }

            buffer.setSample(channel, i, outSample);
        }
    }
}

FullWaveRectification::FullWaveRectification()
{
}

FullWaveRectification::~FullWaveRectification()
{
}