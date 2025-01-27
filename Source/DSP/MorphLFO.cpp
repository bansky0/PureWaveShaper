/*
  ==============================================================================

    MorphLFO.cpp
    Created: 28 Aug 2024 9:52:53am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "MorphLFO.h"

// ES: Configura el valor de la forma de onda (shape) del LFO.
// EN: Sets the waveform shape value of the LFO.
void MorphLfo::setShape(float inShapeValue)
{
    shapeValue = inShapeValue;
}

// ES: Configura el valor de la profundidad (depth) del LFO.
// EN: Sets the depth value of the LFO.
void MorphLfo::setDepth(float inDepthValue)
{
    depthValue = inDepthValue;
}

// ES: Configura la frecuencia del LFO en Hz.
// EN: Sets the frequency of the LFO in Hz.
void MorphLfo::setFrequency(double inFrequency)
{
    frequency = inFrequency;
}

// ES: Inicializa los parámetros internos del LFO en base a la frecuencia de muestreo proporcionada.
// EN: Initializes the LFO's internal parameters based on the provided sample rate.
void MorphLfo::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate); // Almacena la frecuencia de muestreo.

    for (int i = 0; i < 2; i++) // Configura las variables de tiempo y sus incrementos para cada canal.
    {
        time[i] = 0.0f;                   // Inicializa el tiempo a 0 para cada canal.
        deltaTime[i] = 1.0f / sampleRate; // Calcula el incremento temporal por muestra.
    }
}

// ES: Aplica el LFO a un buffer de audio.
// EN: Applies the LFO to an audio buffer.
void MorphLfo::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++) // Recorre todos los canales.
    {
        for (int i = 0; i < buffer.getNumSamples(); i++) // Recorre todas las muestras del canal actual.
        {
            float inSample = buffer.getSample(channel, i); // Obtiene la muestra actual.
            float amplitud = 0.5f * (depthValue / 100.0f); // Calcula la amplitud del LFO según el valor de profundidad.
            float offset = 1.0f - amplitud;                // Calcula el desplazamiento necesario.

            // ES: Genera la forma de onda base del LFO (diente de sierra).
            // EN: Generates the base waveform of the LFO (sawtooth wave).
            float lfo = (2.0f * std::fmod(frequency * time[i] + 0.5f, 1.0f) - 1.0f);

            float newLfo = 0.0f; // Valor modificado del LFO.
            float outSample = 0.0f; // Valor de la muestra procesada.

            // ES: Modifica la forma de onda del LFO según el parámetro de shape.
            // EN: Adjusts the LFO waveform based on the shape parameter.
            if (lfo >= 0)
            {
                newLfo = std::pow(lfo, 1.0f / shapeValue);
            }
            else
            {
                newLfo = -std::pow(std::abs(lfo), 1.0f / shapeValue);
            }

            // ES: Combina la amplitud y el desplazamiento para calcular la modulación final.
            // EN: Combines amplitude and offset to calculate the final modulation.
            float mod = (amplitud * newLfo) + offset;

            // ES: Aplica la modulación a la muestra original.
            // EN: Applies the modulation to the original sample.
            outSample = mod * inSample;

            // ES: Guarda la muestra procesada en el buffer.
            // EN: Stores the processed sample in the buffer.
            buffer.setSample(channel, i, outSample);

            // ES: Incrementa el tiempo para el canal actual.
            // EN: Increments the time for the current channel.
            time[channel] += deltaTime[channel];

            // ES: Reinicia el tiempo si excede 1 (una oscilación completa).
            // EN: Resets the time if it exceeds 1 (a full oscillation).
            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;
        }
    }
}

// ES: Constructor: Inicializa el objeto MorphLfo.
// EN: Constructor: Initializes the MorphLfo object.
MorphLfo::MorphLfo()
{
}

// ES: Destructor: Libera recursos si es necesario.
// EN: Destructor: Frees resources if necessary.
MorphLfo::~MorphLfo()
{
}