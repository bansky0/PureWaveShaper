/*
  ==============================================================================

    HardClip.cpp
    Created: 2 Sep 2024 8:43:08pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "HardClip.h"

void HardClip::setHardClipThresh(float inHardClipThreshValue)
{
    thresh = juce::Decibels::decibelsToGain(inHardClipThreshValue);
}

void HardClip::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            float outSample = 0.0f;
            if (inSample >= thresh)
            {
                outSample = thresh;
            }
            else if (inSample <= -thresh)
            {
                outSample = -thresh;
            }
            else
            {
                outSample = inSample;
            }

            buffer.setSample(channel, i, outSample);
        }
    }
}

HardClip::HardClip()
{
}

HardClip::~HardClip()
{
}