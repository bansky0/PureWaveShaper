/*
  ==============================================================================

    TriangleWave.cpp
    Created: 28 Aug 2024 5:32:09pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "TriangleWave.h"

// EN: Sets the frequency of the triangle wave.
// ES: Establece la frecuencia de la onda triangular.
void TriangleWave::setFrequency(double inFrequency)
{
    frequency = inFrequency;
}

// EN: Prepares the triangle wave generator by setting the sample rate and initializing time and deltaTime arrays for each channel.
// ES: Prepara el generador de onda triangular configurando la tasa de muestreo e inicializando los arreglos time y deltaTime para cada canal.
void TriangleWave::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate); // EN: Set the sample rate. | ES: Configura la tasa de muestreo.

    for (int i = 0; i < 2; i++) // EN: Initialize time and deltaTime for stereo channels. | ES: Inicializa time y deltaTime para los canales estéreo.
    {
        time[i] = 0.0f;               // EN: Reset the time accumulator. | ES: Reinicia el acumulador de tiempo.
        deltaTime[i] = 1.0f / sampleRate; // EN: Calculate the time increment per sample. | ES: Calcula el incremento de tiempo por muestra.
    }
}

// EN: Processes the audio buffer to generate a triangle wave for each sample.
// ES: Procesa el buffer de audio para generar una onda triangular para cada muestra.
void TriangleWave::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++) // EN: Iterate over channels. | ES: Itera sobre los canales.
    {
        for (int i = 0; i < buffer.getNumSamples(); i++) // EN: Iterate over samples. | ES: Itera sobre las muestras.
        {
            float res = 0.0f; // EN: Placeholder (unused). | ES: Variable auxiliar (no utilizada).
            float fullPeriodTime = 1.0f / frequency; // EN: Calculate the period of the triangle wave. | ES: Calcula el período de la onda triangular.
            float localTime = fmod(time[channel], fullPeriodTime); // EN: Wrap time to the period of the wave. | ES: Ajusta el tiempo al período de la onda.
            float outSample = 0.0f; // EN: Output sample value. | ES: Valor de la muestra de salida.

            float value = localTime / fullPeriodTime; // EN: Normalize local time to a range [0, 1]. | ES: Normaliza el tiempo local al rango [0, 1].

            // EN: Generate the triangle wave based on the normalized value.
            // ES: Genera la onda triangular en función del valor normalizado.
            if (value < 0.25f) // EN: First rising section. | ES: Primera sección ascendente.
            {
                outSample = value * 4.0f;
            }
            else if (value < 0.75f) // EN: Descending section. | ES: Sección descendente.
            {
                outSample = 2.0f - (value * 4.0f);
            }
            else // EN: Second rising section. | ES: Segunda sección ascendente.
            {
                outSample = value * 4.0f - 4.0f;
            }

            buffer.setSample(channel, i, outSample); // EN: Write the sample to the buffer. | ES: Escribe la muestra en el buffer.

            time[channel] += deltaTime[channel]; // EN: Increment time for the current channel. | ES: Incrementa el tiempo para el canal actual.

            if (time[channel] >= 1.0f) // EN: Reset time if it exceeds 1 second. | ES: Reinicia el tiempo si excede 1 segundo.
                time[channel] = 0.0f;
        }
    }
}

// EN: Constructor initializes the TriangleWave object.
// ES: El constructor inicializa el objeto TriangleWave.
TriangleWave::TriangleWave()
{
}

// EN: Destructor cleans up the TriangleWave object.
// ES: El destructor limpia el objeto TriangleWave.
TriangleWave::~TriangleWave()
{
}
