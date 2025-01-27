/*
  ==============================================================================

    MorphWave.cpp
    Created: 30 Aug 2024 11:25:40am
    Author:  Jhonatan López
    Notes: This code generates a configurable waveform that can be used as an LFO, 
    base oscillator for synthesis, or modulator in audio effects such as vibrato, tremolo, or chorus.

  ==============================================================================
*/

#include "MorphWave.h"

// ES: Configura el valor de la forma de onda (shape) que define la curvatura de la señal generada.
// EN: Sets the waveform shape value, which defines the curvature of the generated signal.
void MorphWave::setShape(float inShapeValue)
{
    shapeValue = inShapeValue;
}

// ES: Configura la frecuencia del oscilador en Hz.
// EN: Sets the oscillator frequency in Hz.
void MorphWave::setFrequency(double inFrequency)
{
    frequency = inFrequency;
}

// ES: Inicializa los parámetros del oscilador en función de la frecuencia de muestreo proporcionada.
// EN: Initializes the oscillator parameters based on the provided sample rate.
void MorphWave::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate); // Almacena la frecuencia de muestreo como un valor de coma flotante.

    for (int i = 0; i < 2; i++) // Inicializa los valores de tiempo y sus incrementos para cada canal.
    {
        time[i] = 0.0f;                   // Inicializa el tiempo a 0 para el canal actual.
        deltaTime[i] = 1.0f / sampleRate; // Calcula el incremento de tiempo por muestra.
    }
}

// ES: Genera una forma de onda modulada y la escribe en el buffer de audio.
// EN: Generates a modulated waveform and writes it to the audio buffer.
void MorphWave::process(juce::AudioBuffer<float>& buffer)
{
    // Recorre todos los canales del buffer de audio.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // Procesa todas las muestras del canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // ES: Genera una onda de diente de sierra como base.
            // EN: Generates a sawtooth wave as the base waveform.
            float osc = (2.0f * std::fmod(frequency * time[i] + 0.5f, 1.0f) - 1.0f);

            float newWave = 0.0f; // Almacena la forma de onda modificada.
            float outSample = 0.0f; // Almacena la muestra de salida.

            // ES: Ajusta la forma de la onda según el valor de shapeValue.
            // EN: Adjusts the waveform shape based on the shapeValue parameter.
            if (osc >= 0)
            {
                newWave = std::pow(osc, 1.0f / shapeValue);
            }
            else
            {
                newWave = -std::pow(std::abs(osc), 1.0f / shapeValue);
            }

            // ES: La muestra de salida es simplemente la forma de onda modificada.
            // EN: The output sample is simply the modified waveform.
            outSample = newWave;

            // ES: Escribe la muestra procesada en el buffer.
            // EN: Writes the processed sample to the buffer.
            buffer.setSample(channel, i, outSample);

            // ES: Incrementa el tiempo del canal actual.
            // EN: Increments the time for the current channel.
            time[channel] += deltaTime[channel];

            // ES: Reinicia el tiempo si excede 1 (un ciclo completo).
            // EN: Resets the time if it exceeds 1 (a full cycle).
            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;
        }
    }
}

// ES: Constructor: Inicializa el objeto MorphWave.
// EN: Constructor: Initializes the MorphWave object.
MorphWave::MorphWave()
{
}

// ES: Destructor: Libera recursos si fuera necesario.
// EN: Destructor: Frees resources if needed.
MorphWave::~MorphWave()
{
}