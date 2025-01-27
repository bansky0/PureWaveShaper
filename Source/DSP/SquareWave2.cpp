/*
  ==============================================================================

    SquareWave2.cpp
    Created: 8 Sep 2024 2:40:00pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "SquareWave2.h"

void SquareWave2::setFrequency(double inFrequency)
{
    frequency = inFrequency;

    // EN: Calculate the new phase increment based on the frequency and sample rate.
    // ES: Calcula el nuevo incremento de fase basado en la frecuencia y la tasa de muestreo.
    if (sampleRate > 0.0f)
    {
        phaseIncrement = frequency / sampleRate;

        // EN: Optional smoothing for transitions between phase increment changes.
        // ES: Suavizado opcional para transiciones entre cambios de incremento de fase.
        // phaseIncrement = 0.9f * phaseIncrement + 0.1f * newPhaseIncrement;
    }
}

void SquareWave2::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);

    // EN: Recalculate the phase increment after setting the sample rate.
    // ES: Recalcula el incremento de fase después de configurar la tasa de muestreo.
    // if (frequency > 0.0f)
    // {
    //     phaseIncrement = 1.0f / (sampleRate / frequency);
    // }

    // EN: Initialize the phase to 0 for each channel.
    // ES: Inicializa la fase en 0 para cada canal.
    // for (int i = 0; i < 2; i++)
    // {
    //     phase[i] = 0.0f;
    // }
}

void SquareWave2::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Iterate over all audio channels.
    // ES: Itera sobre todos los canales de audio.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Process each sample in the current channel.
        // ES: Procesa cada muestra en el canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // EN: Generate a square wave sample using the phase accumulator.
            // ES: Genera una muestra de onda cuadrada usando el acumulador de fase.
            float outSample = (phase[channel] < 0.5f) ? 1.0f : -1.0f;

            // EN: Store the sample value in the audio buffer.
            // ES: Almacena el valor de la muestra en el buffer de audio.
            buffer.setSample(channel, i, outSample);

            // EN: Update the phase accumulator and keep it within the range [0, 1).
            // ES: Actualiza el acumulador de fase y lo mantiene dentro del rango [0, 1).
            phase[channel] += phaseIncrement;
            if (phase[channel] >= 1.0f)
                phase[channel] -= 1.0f;
        }
    }
}

// EN: Constructor for the SquareWave2 class.
// ES: Constructor de la clase SquareWave2.
SquareWave2::SquareWave2()
{
}

// EN: Destructor for the SquareWave2 class.
// ES: Destructor de la clase SquareWave2.
SquareWave2::~SquareWave2()
{
}