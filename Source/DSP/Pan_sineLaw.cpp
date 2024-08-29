/*
  ==============================================================================

    Pan_sineLaw.cpp
    Created: 26 Aug 2024 12:08:48pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Pan_sineLaw.h"

void PanSineLaw::setPanSineLawValue(float inPanSineLawValue)
{
    panSineLawValue = (inPanSineLawValue / 200.0f) + 0.5f;
}

void PanSineLaw::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);

            // Process left channel
            if (channel == 0)
            {
                sample *= sinf((1.0f - panSineLawValue) * (pi / 2.0f));
            }
            //Process right channel
            else
            {
                sample *= sinf(panSineLawValue *(pi/2.0f));
            }

            buffer.setSample(channel, i, sample);
        }
    }
}


PanSineLaw::PanSineLaw()
{
}

PanSineLaw::~PanSineLaw()
{
}