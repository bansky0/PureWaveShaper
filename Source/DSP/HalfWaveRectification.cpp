/*
  ==============================================================================

    HalfWaveRectification.cpp
    Created: 2 Sep 2024 7:13:47pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "HalfWaveRectification.h"

void HalfWaveRectification::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            float outSample = 0.0f;

            if (inSample >= 0)
            {
                outSample = 1;
            }
            else
            {
                outSample = -1;
            }

            buffer.setSample(channel, i, outSample);
        }
    }
}

HalfWaveRectification::HalfWaveRectification()
{
}

HalfWaveRectification::~HalfWaveRectification()
{
}