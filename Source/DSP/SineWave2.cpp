/*
  ==============================================================================

    SineWave2.cpp
    Created: 8 Sep 2024 12:44:04pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "SineWave2.h"

void SineWave2::setFrequency(double inFrequency)
{
    frequency = inFrequency;
    // Calculamos el incremento de fase con la frecuencia actual
    phaseIncrement = twoPi * frequency / sampleRate;
}

void SineWave2::setPhase(double setPhase)
{
    phi = setPhase;
}

void SineWave2::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);
    //phaseIncrement = twoPi * frequency / sampleRate;

    // Inicializamos la fase a 0 para cada canal
    for (int i = 0; i < 2; i++)
    {
        phase[i] = 0.0f;
    }
}

void SineWave2::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // Calculamos la salida de la onda senoidal usando la fase actual
            float outSample = sinf(phase[channel] + phi);

            // Guardamos el valor en el buffer
            buffer.setSample(channel, i, outSample);

            // Actualizamos la fase y la mantenemos dentro del rango [0, 2π]
            phase[channel] += phaseIncrement;

            if (phase[channel] >= twoPi)
                phase[channel] -= twoPi;
        }
    }
}

SineWave2::SineWave2()
{
}

SineWave2::~SineWave2()
{
}