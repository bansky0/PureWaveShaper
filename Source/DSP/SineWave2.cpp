/*
  ==============================================================================

    SineWave2.cpp
    Created: 8 Sep 2024 12:44:04pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "SineWave2.h"

// EN: Sets the frequency of the sine wave and updates the phase increment based on the current sample rate.
// ES: Establece la frecuencia de la onda seno y actualiza el incremento de fase basado en la tasa de muestreo actual.
void SineWave2::setFrequency(double inFrequency)
{
    frequency = inFrequency;
    // EN: Calculate the phase increment using the formula: 2π * frequency / sampleRate.
    // ES: Calcula el incremento de fase usando la fórmula: 2π * frecuencia / tasa de muestreo.
    phaseIncrement = twoPi * frequency / sampleRate;
}

// EN: Sets the initial phase offset of the sine wave.
// ES: Establece el desplazamiento de fase inicial de la onda seno.
void SineWave2::setPhase(double setPhase)
{
    phi = setPhase;
}

// EN: Prepares the sine wave generator with a given sample rate.
// ES: Prepara el generador de onda seno con una tasa de muestreo dada.
void SineWave2::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);

    // EN: Initialize the phase for each channel to 0.
    // ES: Inicializa la fase para cada canal en 0.
    for (int i = 0; i < 2; i++)
    {
        phase[i] = 0.0f;
    }
}

// EN: Processes the audio buffer, generating a sine wave for each sample in each channel.
// ES: Procesa el buffer de audio, generando una onda seno para cada muestra en cada canal.
void SineWave2::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Loop through all the channels in the buffer.
    // ES: Itera a través de todos los canales del buffer.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Loop through all the samples in the current channel.
        // ES: Itera a través de todas las muestras del canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // EN: Calculate the sine wave value using the current phase and phase offset (phi).
            // ES: Calcula el valor de la onda seno usando la fase actual y el desplazamiento de fase (phi).
            float outSample = sinf(phase[channel] + phi);

            // EN: Write the sine wave value to the buffer at the current sample index.
            // ES: Escribe el valor de la onda seno en el buffer en el índice de muestra actual.
            buffer.setSample(channel, i, outSample);

            // EN: Update the phase for the channel and wrap it to stay within [0, 2π].
            // ES: Actualiza la fase del canal y la ajusta para mantenerse dentro del rango [0, 2π].
            phase[channel] += phaseIncrement;

            if (phase[channel] >= twoPi)
                phase[channel] -= twoPi; // EN: Wrap phase to avoid overflow. | ES: Ajusta la fase para evitar desbordamientos.
        }
    }
}

// EN: Constructor for the SineWave2 class.
// ES: Constructor de la clase SineWave2.
SineWave2::SineWave2()
{
}

// EN: Destructor for the SineWave2 class.
// ES: Destructor de la clase SineWave2.
SineWave2::~SineWave2()
{
}