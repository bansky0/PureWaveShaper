/*
  ==============================================================================

    ImpulseTrain.cpp
    Created: 10 Sep 2024 11:13:07am
    Author:  Jhonatan

  ==============================================================================
*/

#include "ImpulseTrain.h"

void ImpulseTrain::setFrequency(double inFrequency)
{
    frequency = inFrequency;
    // Recalcular el incremento de fase en función de la frecuencia
    if (sampleRate > 0.0f)
    {
        phaseIncrement = 1.0f / (sampleRate / frequency);
    }
}

void ImpulseTrain::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);
}

void ImpulseTrain::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float outSample;
            // Si la fase es 0 (inicio de un ciclo), generar un impulso
            if (phase[channel] < phaseIncrement)
            {
                outSample = 1.0f; // Impulso
            }
            else
            {
                outSample = 0.0f; // De lo contrario, es cero
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
ImpulseTrain::ImpulseTrain()
{
}

ImpulseTrain::~ImpulseTrain()
{
}