/*
  ==============================================================================

    Pan_linear.cpp
    Created: 22 Aug 2024 6:20:09pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Pan_linear.h"

void PanLinear::setPanLinearValue(float inPanLinearValue)
{
    panLinearValue = (inPanLinearValue / 200.0f) + 0.5f;
}

void PanLinear::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);

            // Process left channel
            if (channel == 0)
            {
                sample *= 1.0f - panLinearValue;
            }
            //Process right channel
            else
            {
                sample *= panLinearValue;
            }

            buffer.setSample(channel, i, sample);
        }
    }
}
PanLinear::PanLinear()
{
}

PanLinear::~PanLinear()
{
}