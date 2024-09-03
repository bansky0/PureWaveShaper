/*
  ==============================================================================

    Infiniteclip.cpp
    Created: 2 Sep 2024 6:29:56pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Infiniteclip.h"

void InfiniteClip::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel,i);
            float outSample = 0.0f;

            if (inSample>=0)
            {
                outSample = inSample;
            }
            else
            {
                outSample = 0;
            }

            buffer.setSample(channel, i,outSample);
        }
    }
}

InfiniteClip::InfiniteClip()
{
}

InfiniteClip::~InfiniteClip()
{
}