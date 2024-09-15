/*
  ==============================================================================

    WhiteNoise.cpp
    Created: 10 Sep 2024 1:12:37pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "WhiteNoise.h"

void WhiteNoise::prepare(double theSampleRate)
{
    sampleRate = theSampleRate;
}

void WhiteNoise::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // Generar un valor aleatorio entre -1.0f y 1.0f
            float outSample = randomGenerator.nextFloat() * 2.0f - 1.0f;

            // Asignar el valor generado al buffer
            buffer.setSample(channel, i, outSample);
        }
    }
}

WhiteNoise::WhiteNoise()
{
}

WhiteNoise::~WhiteNoise()
{
}