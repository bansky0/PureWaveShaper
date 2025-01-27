/*
  ==============================================================================

    WhiteNoise.cpp
    Created: 10 Sep 2024 1:12:37pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "WhiteNoise.h"

// EN: Prepares the WhiteNoise generator by setting the sample rate.
// ES: Prepara el generador de ruido blanco configurando la tasa de muestreo.
void WhiteNoise::prepare(double theSampleRate)
{
    sampleRate = theSampleRate;
}

// EN: Fills the audio buffer with white noise samples.
// ES: Llena el buffer de audio con muestras de ruido blanco.
void WhiteNoise::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Loop through each channel in the audio buffer.
    // ES: Iterar a través de cada canal en el buffer de audio.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Loop through each sample in the current channel.
        // ES: Iterar a través de cada muestra en el canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // EN: Generate a random value between -1.0f and 1.0f.
            // ES: Generar un valor aleatorio entre -1.0f y 1.0f.
            float outSample = randomGenerator.nextFloat() * 2.0f - 1.0f;

            // EN: Assign the generated value to the buffer.
            // ES: Asignar el valor generado al buffer.
            buffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Constructor. Initializes the WhiteNoise object.
// ES: Constructor. Inicializa el objeto WhiteNoise.
WhiteNoise::WhiteNoise()
{
}

// EN: Destructor. Cleans up the WhiteNoise object.
// ES: Destructor. Libera el objeto WhiteNoise.
WhiteNoise::~WhiteNoise()
{
}