/*
  ==============================================================================

    Pan_sqrt_modified.cpp
    Created: 26 Aug 2024 1:26:18pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Pan_sqrt_modified.h"

void PanSqrtModidied::setPanSqrtModidiedValue(float inPanSqrtModidiedValue)
{
    panSqrtModifiedValue = (inPanSqrtModidiedValue / 200.0f) + 0.5f;
}

void PanSqrtModidied::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);

            // Process left channel
            if (channel == 0)
            {
                sample *= powf(1 - panSqrtModifiedValue, 0.75f);
            }
            //Process right channel
            else
            {
                sample *= powf(panSqrtModifiedValue, 0.75f);
            }

            buffer.setSample(channel, i, sample);

        }
    }
}

PanSqrtModidied::PanSqrtModidied()
{
}

PanSqrtModidied::~PanSqrtModidied()
{
}