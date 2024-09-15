/*
  ==============================================================================

    SquareWave2.cpp
    Created: 8 Sep 2024 2:40:00pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "SquareWave2.h"

void SquareWave2::setFrequency(double inFrequency)
{
    frequency = inFrequency;

    // Calcula el nuevo incremento de fase
    if (sampleRate > 0.0f)
    {
        phaseIncrement = frequency / sampleRate;

        // To create a smoth transition betwwen values
        //phaseIncrement = 0.9f * phaseIncrement + 0.1f * newPhaseIncrement;
    }
}

void SquareWave2::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);

    // Recalcular el incremento de fase después de establecer la frecuencia de muestreo
    //if (frequency > 0.0f)
    //{
    //    phaseIncrement = 1.0f / (sampleRate / frequency);
    //}

    // Inicializar la fase a 0 para cada canal
    //for (int i = 0; i < 2; i++)
    //{
    //    phase[i] = 0.0f;
    //}
}

void SquareWave2::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // Calcular el valor de la onda cuadrada usando el acumulador de fase
            float outSample = (phase[channel] < 0.5f) ? 1.0f : -1.0f;

            // Guardar el valor en el buffer
            buffer.setSample(channel, i, outSample);
            
            // Actualizar la fase y mantenerla dentro del rango [0, 1)
            phase[channel] += phaseIncrement;
            if (phase[channel] >= 1.0f)
                phase[channel] -= 1.0f;
        }
    }
}

SquareWave2::SquareWave2()
{
}

SquareWave2::~SquareWave2()
{
}