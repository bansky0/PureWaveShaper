/*
  ==============================================================================

    Pan.cpp
    Created: 22 Aug 2024 2:07:46pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Pan.h"

Pan::Pan()
{
}

Pan::~Pan()
{
}

void Pan::setPanValue(float inPanValue)
{
    // Normaliza el valor en el rango de 0 a 1
    float normalizedValue = (inPanValue + 100.0f) / 200.0f;

    // Mapea el valor normalizado al rango de 0 a pi/2
    float outputValue = normalizedValue * (pi / 2.0f);

    panValue = outputValue;
}

void Pan::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);
            // Process left channel
            if (channel == 0)
            {
                sample *= sqrtf(((pi/2.0f)- panValue)*(2.0f/pi)*(cosf(panValue)));
            }
            //Process right channel
            else
            {
                sample *= sqrtf(panValue * (2.0f / pi) * sinf(panValue));
            }
            
            buffer.setSample(channel, i, sample);
        }
    }
}