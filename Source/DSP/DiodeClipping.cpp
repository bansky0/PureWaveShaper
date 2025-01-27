/*
  ==============================================================================

    DiodeClipping.cpp
    Created: 3 Sep 2024 4:46:15pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "DiodeClipping.h"

// EN: Applies the diode clipping effect to an audio buffer.
// ES: Aplica el efecto de recorte de diodo a un buffer de audio.
void DiodeClipping::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Iterate over each channel in the buffer.
    // ES: Iterar sobre cada canal en el buffer.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Iterate over each sample in the current channel.
        // ES: Iterar sobre cada muestra en el canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // EN: Read the input sample from the buffer.
            // ES: Leer la muestra de entrada desde el buffer.
            float inSample = buffer.getSample(channel, i);

            // EN: Initialize variables for processed and output samples.
            // ES: Inicializar variables para las muestras procesadas y de salida.
            float processedSample = 0.0f;
            float outSample = 0.0f;

            // EN: Apply the diode clipping formula using the diode equation:
            //     I = Is * (exp(V / (eta * Vt)) - 1), where V is proportional to the input sample.
            // ES: Aplicar la fórmula de recorte de diodo utilizando la ecuación del diodo:
            //     I = Is * (exp(V / (eta * Vt)) - 1), donde V es proporcional a la muestra de entrada.
            processedSample = Is * (expf((0.1f * inSample) / (eta * Vt)) - 1);

            // EN: Set the processed sample as the output sample.
            // ES: Establecer la muestra procesada como la muestra de salida.
            outSample = processedSample;

            // EN: Write the output sample back to the buffer.
            // ES: Escribir la muestra de salida de vuelta al buffer.
            buffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Constructor for the DiodeClipping class.
// ES: Constructor de la clase DiodeClipping.
DiodeClipping::DiodeClipping()
{
}

// EN: Destructor for the DiodeClipping class.
// ES: Destructor de la clase DiodeClipping.
DiodeClipping::~DiodeClipping()
{
}