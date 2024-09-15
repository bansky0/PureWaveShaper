/*
  ==============================================================================

    TriangleWave2.cpp
    Created: 9 Sep 2024 3:56:59pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "TriangleWave2.h"

void TriangleWave2::setFrequency(double inFrequecy)
{
    frequency = inFrequecy;
    
    if (sampleRate > 0.0f)
    {
        phaseIncrement = frequency / sampleRate;
    }
}
void TriangleWave2::setWidth(float inWidth)
{
    width = inWidth;
}
void TriangleWave2::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);
}

void TriangleWave2::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float outSample = 0.0f;

            // Generar la onda triangular con width ajustable
            if (phase[channel] < width)
            {
                // Primera mitad de la onda
                outSample = (phase[channel] / width) * 2.0f - 1.0f;
            }
            else
            {
                // Segunda mitad de la onda
                outSample = ((phase[channel] - width) / (1.0f - width)) * -2.0f + 1.0f;
            }

            // Guardar el valor en el buffer
            buffer.setSample(channel, i, outSample);

            // Actualizar la fase y mantenerla dentro del rango [0, 1)
            phase[channel] += phaseIncrement;
            if (phase[channel] >= 1.0f)
                phase[channel] -= 1.0f;
        }
    }
}

TriangleWave2::TriangleWave2()
{
}

TriangleWave2::~TriangleWave2()
{
}