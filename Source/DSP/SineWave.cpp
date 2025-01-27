/*
  ==============================================================================

    SineWave.cpp
    Created: 28 Aug 2024 11:32:36am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "SineWave.h"

// EN: Sets the frequency of the sine wave in Hz.
// ES: Establece la frecuencia de la onda seno en Hz.
void SineWave::setFrequency(double inFrequency)
{
    frequency = inFrequency;
}

// EN: Sets the initial phase of the sine wave.
// ES: Establece la fase inicial de la onda seno.
void SineWave::setPhase(double setPhase)
{
    phi = setPhase;
}

// EN: Prepares the sine wave generator with the specified sample rate.
// ES: Prepara el generador de onda seno con la tasa de muestreo especificada.
void SineWave::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate); // EN: Set the sample rate. | ES: Configura la tasa de muestreo.

    // EN: Initialize time and deltaTime for each channel.
    // ES: Inicializa time y deltaTime para cada canal.
    for (int i = 0; i < 2; i++)
    {
        time[i] = 0.0f;               // EN: Reset the time for the channel. | ES: Reinicia el tiempo para el canal.
        deltaTime[i] = 1.0f / sampleRate; // EN: Compute the phase increment per sample. | ES: Calcula el incremento de fase por muestra.
    }
}

// EN: Processes the buffer to generate the sine wave signal.
// ES: Procesa el buffer para generar la señal de onda seno.
void SineWave::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++) // EN: Loop through each channel. | ES: Recorre cada canal.
    {
        for (int i = 0; i < buffer.getNumSamples(); i++) // EN: Loop through each sample. | ES: Recorre cada muestra.
        {
            // EN: Generate the sine wave sample with frequency, time, and phase.
            // ES: Genera la muestra de onda seno con frecuencia, tiempo y fase.
            float outSample = sinf(twoPi * frequency * time[channel] + phi);

            // EN: Set the generated sample into the buffer.
            // ES: Coloca la muestra generada en el buffer.
            buffer.setSample(channel, i, outSample);

            // EN: Increment the time for the current channel.
            // ES: Incrementa el tiempo para el canal actual.
            time[channel] += deltaTime[channel];

            // EN: Wrap the time value to avoid overflow.
            // ES: Ajusta el valor de tiempo para evitar desbordamientos.
            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;
        }
    }
}

// EN: Constructor for the SineWave class. Initializes default values.
// ES: Constructor de la clase SineWave. Inicializa valores por defecto.
SineWave::SineWave()
{
}

// EN: Destructor for the SineWave class. Releases any allocated resources (if any).
// ES: Destructor de la clase SineWave. Libera recursos asignados (si los hubiera).
SineWave::~SineWave()
{
}