/*
  ==============================================================================

    Pan_sineLaw_modified.cpp
    Created: 26 Aug 2024 1:26:44pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Pan_sineLaw_modified.h"

void PanSineLawModified::setPanSineLawModifiedValue(float inPanSineLawModifiedValue)
{
    panSineLawModifiedValue = (inPanSineLawModifiedValue/200.0f)+0.5;
}

void PanSineLawModified::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);

            // Process left channel
            if (channel == 0)
            {
                sample *= sqrtf((1- panSineLawModifiedValue) * sinf((1.0f - panSineLawModifiedValue) * (pi / 2.0f)));
            }
            //Process right channel
            else
            {
                sample *= sqrtf(panSineLawModifiedValue * sinf(panSineLawModifiedValue * (pi / 2.0f)));
            }

            buffer.setSample(channel, i, sample);
        }
    }
}


PanSineLawModified::PanSineLawModified()
{
}

PanSineLawModified::~PanSineLawModified()
{
}