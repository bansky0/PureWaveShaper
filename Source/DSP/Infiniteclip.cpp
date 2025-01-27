/*
  ==============================================================================

    Infiniteclip.cpp
    Created: 2 Sep 2024 6:29:56pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Infiniteclip.h"

// ES: Método que procesa un buffer de audio y aplica una lógica de "clipping infinito".
// EN: Method that processes an audio buffer and applies "infinite clipping" logic.
void InfiniteClip::process(juce::AudioBuffer<float>& buffer)
{
    // ES: Iterar sobre cada canal de audio en el buffer.
    // EN: Iterate over each audio channel in the buffer.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // ES: Iterar sobre cada muestra en el canal actual.
        // EN: Iterate over each sample in the current channel.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // ES: Obtener el valor de la muestra actual.
            // EN: Get the value of the current sample.
            float inSample = buffer.getSample(channel, i);
            float outSample = 0.0f; // Inicializar la muestra de salida.
            // EN: Initialize the output sample.

            // ES: Aplicar la lógica de clipping infinito:
            // Si el valor de entrada es mayor o igual a 0, mantenerlo;
            // de lo contrario, establecerlo en 0.
            // EN: Apply infinite clipping logic:
            // If the input value is greater than or equal to 0, keep it;
            // otherwise, set it to 0.
            if (inSample >= 0)
            {
                outSample = inSample;
            }
            else
            {
                outSample = 0;
            }

            // ES: Establecer el valor procesado en el buffer de salida.
            // EN: Set the processed value in the output buffer.
            buffer.setSample(channel, i, outSample);
        }
    }
}

// ES: Constructor de la clase InfiniteClip.
// EN: Constructor for the InfiniteClip class.
InfiniteClip::InfiniteClip()
{
}

// ES: Destructor de la clase InfiniteClip.
// EN: Destructor for the InfiniteClip class.
InfiniteClip::~InfiniteClip()
{
}