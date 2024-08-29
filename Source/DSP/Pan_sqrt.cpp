/*
  ==============================================================================

    Pan_sqrt.cpp
    Created: 26 Aug 2024 11:09:35am
    Author:  Jhonatan

  ==============================================================================
*/

#include "Pan_sqrt.h"

void PanSqrt::setPanSqrtValue(float inPanSqrtValue) 
{
    panSqrtValue = (inPanSqrtValue / 200.0f) + 0.5f;
}

void PanSqrt::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);

            // Process left channel
            if (channel == 0)
            {
                sample *= sqrtf(1.0f - panSqrtValue);
            }
            //Process right channel
            else
            {
                sample *= sqrtf(panSqrtValue);
            }

            buffer.setSample(channel, i, sample);

        }
    }
}

PanSqrt::PanSqrt()
{
}

PanSqrt::~PanSqrt()
{
}