/*
  ==============================================================================

    DutyCicleWave.cpp
    Created: 9 Sep 2024 1:03:43pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "DutyCicleWave.h"
void DutyCicleWave::setFrequency(double inFrequency)
{
    frequency = inFrequency;

    if (sampleRate > 0.0f)
    {
        phaseIncrement = 1.0f / (sampleRate / frequency);
    }
}

void DutyCicleWave::setDutyCycle(float inDutyCycle)
{
    // Asegúrate de que el ciclo de trabajo esté en el rango [0.0, 1.0]
    dutyCycle = inDutyCycle/100.f;
}

void DutyCicleWave::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);
}

void DutyCicleWave::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // Calcular el valor de la onda cuadrada usando el acumulador de fase
            float fullPeriodTime = 1.0f / frequency;
            float halfPeriodTime = fullPeriodTime * dutyCycle;
            float localTime = fmod(phase[channel] * fullPeriodTime, fullPeriodTime);
            float outSample = (localTime < halfPeriodTime) ? 1.0f : -1.0f;

            // Guardar el valor en el buffer
            buffer.setSample(channel, i, outSample);

            // Actualizar la fase y mantenerla dentro del rango [0, 1)
            phase[channel] += phaseIncrement;
            if (phase[channel] >= 1.0f)
                phase[channel] -= 1.0f;
        }
    }
}

DutyCicleWave::DutyCicleWave()
{
}

DutyCicleWave::~DutyCicleWave()
{
}