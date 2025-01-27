/*
  ==============================================================================

    SquareWave.cpp
    Created: 28 Aug 2024 2:25:56pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "SquareWave.h"

// EN: Sets the frequency of the square wave.
// ES: Establece la frecuencia de la onda cuadrada.
void SquareWave::setFrequency(double inFrequency)
{
    frequency = inFrequency;
}

// EN: Prepares the square wave generator by initializing the sample rate and time parameters.
// ES: Prepara el generador de onda cuadrada inicializando la tasa de muestreo y los parámetros de tiempo.
void SquareWave::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);

    // EN: Initialize the time and deltaTime for each channel.
    // ES: Inicializa los valores de tiempo y deltaTime para cada canal.
    for (int i = 0; i < 2; i++)
    {
        time[i] = 0.0f;
        deltaTime[i] = 1.0f / sampleRate;
    }
}

// EN: Processes the audio buffer and fills it with a square wave signal.
// ES: Procesa el buffer de audio y lo llena con una señal de onda cuadrada.
void SquareWave::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // EN: Calculate the total period and half period of the square wave.
            // ES: Calcula el período total y el medio período de la onda cuadrada.
            float fullPeriodTime = 1.0f / frequency;       // EN: Duration of one full period. | ES: Duración de un período completo.
            float halfPeriodTime = fullPeriodTime / 2.0f;  // EN: Duration of half the period. | ES: Duración de medio período.

            // EN: Calculate the current time position within the current period.
            // ES: Calcula la posición de tiempo actual dentro del período actual.
            float localTime = fmod(time[channel], fullPeriodTime);

            float outSample = 0.0f;

            // EN: Determine the output sample value based on the current time in the period.
            // ES: Determina el valor de la muestra de salida basado en el tiempo actual en el período.
            if (localTime < halfPeriodTime)
                outSample = 1.0f;  // EN: Positive part of the square wave. | ES: Parte positiva de la onda cuadrada.
            else
                outSample = 0.0f;  // EN: Negative part of the square wave. | ES: Parte negativa de la onda cuadrada.

            // EN: Write the output sample to the buffer.
            // ES: Escribe la muestra de salida en el buffer.
            buffer.setSample(channel, i, outSample);

            // EN: Increment the time for the current channel.
            // ES: Incrementa el tiempo para el canal actual.
            time[channel] += deltaTime[channel];

            // EN: Reset the time if it exceeds 1.0 to keep it within a valid range.
            // ES: Reinicia el tiempo si excede 1.0 para mantenerlo dentro de un rango válido.
            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;
        }
    }
}

// EN: Constructor for the SquareWave class.
// ES: Constructor de la clase SquareWave.
SquareWave::SquareWave()
{
}

// EN: Destructor for the SquareWave class.
// ES: Destructor de la clase SquareWave.
SquareWave::~SquareWave()
{
}