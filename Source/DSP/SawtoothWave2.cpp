/*
  ==============================================================================

    SawtoothWave2.cpp
    Created: 9 Sep 2024 1:04:43pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "SawtoothWave2.h"

// EN: Sets the frequency of the sawtooth wave and calculates the phase increment based on the sample rate.
// ES: Establece la frecuencia de la onda diente de sierra y calcula el incremento de fase basado en la frecuencia de muestreo.
void SawtoothWave2::setFrequency(double inFrequency)
{
    frequency = inFrequency;

    // EN: Ensure the sample rate is valid before calculating the phase increment.
    // ES: Asegura que la frecuencia de muestreo sea válida antes de calcular el incremento de fase.
    if (sampleRate > 0.0f)
    {
        // EN: Calculate phase increment: the fraction of the wave to advance per sample.
        // ES: Calcula el incremento de fase: la fracción de la onda que avanza por muestra.
        phaseIncrement = 1.0f / (sampleRate / frequency);
    }
}

// EN: Prepares the generator by setting the sample rate.
// ES: Prepara el generador configurando la frecuencia de muestreo.
void SawtoothWave2::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);
}

// EN: Processes the audio buffer by generating a sawtooth wave for each sample and channel.
// ES: Procesa el búfer de audio generando una onda diente de sierra para cada muestra y canal.
void SawtoothWave2::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++) // EN: Loop through channels. | ES: Iterar a través de los canales.
    {
        for (int i = 0; i < buffer.getNumSamples(); i++) // EN: Loop through samples. | ES: Iterar a través de las muestras.
        {
            float outSample = 0.0f;

            // EN: Generate the sawtooth waveform by scaling the phase value to [-1.0, 1.0].
            // ES: Genera la onda diente de sierra escalando el valor de fase a [-1.0, 1.0].
            outSample = 2.0f * phase[channel] - 1.0f;

            // EN: Write the generated sample into the buffer.
            // ES: Escribe la muestra generada en el búfer.
            buffer.setSample(channel, i, outSample);

            // EN: Increment the phase for the current channel.
            // ES: Incrementa la fase para el canal actual.
            phase[channel] += phaseIncrement;

            // EN: Wrap the phase back to 0.0 if it exceeds 1.0 (cyclic behavior).
            // ES: Reinicia la fase a 0.0 si excede 1.0 (comportamiento cíclico).
            if (phase[channel] >= 1.0f)
                phase[channel] = 0.0f;
        }
    }
}

// EN: Constructor for the SawtoothWave2 class (no additional setup required here).
// ES: Constructor de la clase SawtoothWave2 (no requiere configuración adicional aquí).
SawtoothWave2::SawtoothWave2()
{
}

// EN: Destructor for the SawtoothWave2 class (no cleanup required here).
// ES: Destructor de la clase SawtoothWave2 (no se requiere limpieza aquí).
SawtoothWave2::~SawtoothWave2()
{
}