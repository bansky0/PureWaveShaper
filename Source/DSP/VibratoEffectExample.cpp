/*
  ==============================================================================

    VibratoEffectExample.cpp
    Created: 21 Oct 2024 9:19:16pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "VibratoEffectExample.h"

void VibratoEffect::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);
    t = 0.0f;
}

void VibratoEffect::setDepth(float inDepth)
{
    // Profundidad del vibrato (modulación)
    depth = inDepth;
}

void VibratoEffect::setRate(float inRate)
{
    // Frecuencia de la modulación (LFO)
    rate = inRate;
}

void VibratoEffect::process(juce::AudioBuffer<float>& buffer)
{
    float old_t = t; // Guarda el valor inicial de `t` antes del procesamiento de canales
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        t = old_t;  // Restaura `t` al valor original para cada canal

        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            auto sample = buffer.getReadPointer(channel)[i];

            // Calcula el valor del LFO para determinar el retardo
            float lfoValue = depth / 2.0f * sin(2.0 * juce::MathConstants<float>::pi * rate * t) + depth;

            // Calcula el número de muestras de retardo basado en el LFO
            int delaySamples = static_cast<int>(std::fabs(lfoValue));

            // Calcula la posición de lectura del buffer circular
            readerPointer = writterPointer[channel] - delaySamples;
            if (readerPointer < 0)
            {
                readerPointer += circularBufferSize;
            }

            // Obtiene la muestra retrasada del buffer circular
            auto delayedSample = circularBuffer[readerPointer][channel];

            // Escribe la muestra actual en el buffer circular
            circularBuffer[writterPointer[channel]][channel] = sample;

            // Avanza el puntero de escritura en el buffer circular
            writterPointer[channel]++;
            if (writterPointer[channel] >= circularBufferSize)
            {
                writterPointer[channel] = 0;
            }

            // Escribe la muestra retrasada en el buffer de salida
            buffer.getWritePointer(channel)[i] = delayedSample;

            // Incrementa el tiempo
            t += 1.0f / sampleRate;
        }
    }
}

VibratoEffect::VibratoEffect()
{
}

VibratoEffect::~VibratoEffect()
{
}