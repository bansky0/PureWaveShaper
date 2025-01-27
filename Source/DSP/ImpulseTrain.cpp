/*
  ==============================================================================

    ImpulseTrain.cpp
    Created: 10 Sep 2024 11:13:07am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "ImpulseTrain.h"

// ES: Establece la frecuencia del tren de impulsos
// EN: Sets the frequency of the impulse train.
void ImpulseTrain::setFrequency(double inFrequency)
{
    frequency = inFrequency;

    // ES: Recalcula el incremento de fase basado en la frecuencia y la tasa de muestreo
    // EN: Recalculates the phase increment based on frequency and sample rate.
    if (sampleRate > 0.0f)
    {
        phaseIncrement = 1.0f / (sampleRate / frequency);
    }
}

// ES: Prepara el tren de impulsos con una tasa de muestreo específica
// EN: Prepares the impulse train with a specific sample rate.
void ImpulseTrain::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);
}

// ES: Procesa un buffer de audio y genera el tren de impulsos
// EN: Processes an audio buffer and generates the impulse train.
void ImpulseTrain::process(juce::AudioBuffer<float>& buffer)
{
    // ES: Itera sobre los canales de audio
    // EN: Iterates over audio channels.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // ES: Itera sobre las muestras en el buffer
        // EN: Iterates over the samples in the buffer.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float outSample;

            // ES: Genera un impulso al inicio de cada ciclo (fase cercana a 0)
            // EN: Generates an impulse at the start of each cycle (phase close to 0).
            if (phase[channel] < phaseIncrement)
            {
                outSample = 1.0f;   // ES: Impulso
                                    // EN: Impulse
            }
            else
            {
                outSample = 0.0f;   // ES: Resto del ciclo es 0
                                    // EN: Rest of the cycle is 0.
            }

            // ES: Escribe la muestra generada en el buffer de audio
            // EN: Writes the generated sample to the audio buffer.
            buffer.setSample(channel, i, outSample);

            // ES: Actualiza la fase y la mantiene dentro del rango [0, 1)
            // EN: Updates the phase and keeps it within the range [0, 1).
            phase[channel] += phaseIncrement;
            if (phase[channel] >= 1.0f)
                phase[channel] -= 1.0f;
        }
    }
}

// ES: Constructor de la clase
// EN: Class constructor.
ImpulseTrain::ImpulseTrain()
{
}

// ES: Destructor de la clase
// EN: Class destructor.
ImpulseTrain::~ImpulseTrain()
{
}