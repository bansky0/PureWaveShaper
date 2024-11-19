/*
  ==============================================================================

    VibratoEffect.cpp
    Created: 23 Oct 2024 4:32:52pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "VibratoEffect.h"

void VibratoFX::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);
    t = 0.0f;
    ratePercentage = 0.0f;   // Inicializa el porcentaje de rate
    targetRatePercentage = 0.0f;
}

void VibratoFX::setDepth(float inDepth)
{
    depth = inDepth;
}

void VibratoFX::setRate(float inRate)
{
    // Convierte el rango de entrada de 0 a 100 en un valor entre 0.0 y 1.0
    targetRatePercentage = juce::jlimit(0.0f, 100.0f, inRate) / 100.0f;
}

void VibratoFX::process(juce::AudioBuffer<float>& buffer)
{
    float old_t = t;
    const float minRateHz = 0.1f;  // Frecuencia mínima en Hz
    const float maxRateHz = 10.0f; // Frecuencia máxima en Hz

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        t = old_t;

        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            auto sample = buffer.getReadPointer(channel)[i];

            // Asigna el porcentaje de `rate` y escala a la frecuencia en Hz
            ratePercentage = targetRatePercentage;
            float rateHz = minRateHz + ratePercentage * (maxRateHz - minRateHz);

            // Calcula el LFO para determinar el retardo fraccional
            float lfoValue = (depth / 2.0f) * sin(2.0 * juce::MathConstants<float>::pi * rateHz * t) + depth;

            // Calcular índice fraccional de retardo
            float fracDelay = static_cast<float>(writterPointer[channel]) - lfoValue;
            if (fracDelay < 0) {
                fracDelay += circularBufferSize;
            }

            int intDelay = static_cast<int>(fracDelay);         // Índice entero del retardo
            float frac = fracDelay - intDelay;                  // Parte fraccional para interpolación

            // Índice del siguiente punto para interpolación
            int nextSampleIndex = intDelay + 1;
            if (nextSampleIndex >= circularBufferSize) {
                nextSampleIndex = 0;
            }

            // Interpolación lineal entre las muestras en intDelay y nextSampleIndex
            float delayedSample = (1.0f - frac) * circularBuffer[intDelay][channel] +
                frac * circularBuffer[nextSampleIndex][channel];

            // Escribe la muestra actual en el buffer circular
            circularBuffer[writterPointer[channel]][channel] = sample;

            // Avanza el puntero de escritura en el buffer circular
            writterPointer[channel]++;
            if (writterPointer[channel] >= circularBufferSize) {
                writterPointer[channel] = 0;
            }

            // Escribe la muestra retrasada en el buffer de salida
            buffer.getWritePointer(channel)[i] = delayedSample;

            // Incrementa el tiempo
            t += 1.0f / sampleRate;
        }
    }
}

VibratoFX::VibratoFX()
{
}

VibratoFX::~VibratoFX()
{
}