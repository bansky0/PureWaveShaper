/*
  ==============================================================================

    AsymetricalDistortion.cpp
    Created: 4 Sep 2024 1:26:39pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "AsymetricalDistortion.h"
void AsymetricalDistortion::setDCValue(float inDCValue)
{
    dc = inDCValue;
}

void AsymetricalDistortion::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            float x = inSample + dc;
            float outSample = 0.0f;

            if (std::abs(x) > 1.0f)
            {
                x = std::copysign(1.0f, x);
            }

            float outSample1 = x - (1.0f / 5.0f) * powf(x, 5.0f);//(2.0f / pi) * atanf(x*10.0f);//

            outSample = outSample1 - dc;
            buffer.setSample(channel, i, outSample);
        }
    }
}

AsymetricalDistortion::AsymetricalDistortion()
{
}

AsymetricalDistortion::~AsymetricalDistortion()
{
}