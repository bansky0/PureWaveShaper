/*
  ==============================================================================

    SawtoothWave.cpp
    Created: 29 Aug 2024 4:38:15pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "SawtoothWave.h"

// EN: Sets the frequency of the sawtooth wave.
// ES: Establece la frecuencia de la onda diente de sierra.
void SawtoothWave::setFrequency(double inFrequency)
{
    frequency = inFrequency;
}

// EN: Prepares the generator by setting the sample rate and initializing phase variables.
// ES: Prepara el generador configurando la frecuencia de muestreo e inicializando las variables de fase.
void SawtoothWave::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);

    // EN: Initialize the time and deltaTime arrays for both channels.
    // ES: Inicializa los arreglos de tiempo y deltaTime para ambos canales.
    for (int i = 0; i < 2; i++)
    {
        time[i] = 0.0f;
        deltaTime[i] = 1.0f / sampleRate;
    }
}

// EN: Generates a sawtooth wave and writes the samples to the audio buffer.
// ES: Genera una onda diente de sierra y escribe las muestras en el búfer de audio.
void SawtoothWave::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Loop through each channel in the buffer.
    // ES: Recorre cada canal en el búfer.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Loop through each sample in the current channel.
        // ES: Recorre cada muestra en el canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float outSample = 0.0f;

            // EN: Calculate the duration of a full wave period.
            // ES: Calcula la duración de un período completo de la onda.
            float fullPeriodTime = 1.0f / frequency;

            // EN: Find the current time position within the wave period.
            // ES: Encuentra la posición de tiempo actual dentro del período de la onda.
            float localTime = fmod(time[channel], fullPeriodTime);

            // EN: Generate the sawtooth wave value normalized to the range [-1, 1].
            // ES: Genera el valor de la onda diente de sierra normalizado al rango [-1, 1].
            outSample = (localTime / fullPeriodTime) * 2.0f - 1.0f;

            // EN: Write the generated sample to the audio buffer.
            // ES: Escribe la muestra generada en el búfer de audio.
            buffer.setSample(channel, i, outSample);

            // EN: Increment the phase time for the channel.
            // ES: Incrementa el tiempo de fase para el canal.
            time[channel] += deltaTime[channel];

            // EN: Reset the time to 0 if it exceeds 1 (one full second).
            // ES: Reinicia el tiempo a 0 si excede 1 (un segundo completo).
            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;
        }
    }
}

// EN: Constructor for the SawtoothWave class. No specific initialization needed.
// ES: Constructor de la clase SawtoothWave. No se necesita inicialización específica.
SawtoothWave::SawtoothWave()
{
}

// EN: Destructor for the SawtoothWave class. No specific cleanup needed.
// ES: Destructor de la clase SawtoothWave. No se necesita limpieza específica.
SawtoothWave::~SawtoothWave()
{
}