/*
  ==============================================================================

    ArctangentDistortion.cpp
    Created: 2 Sep 2024 10:08:57pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "ArctangentDistortion.h"

// EN: Sets the drive level for the arctangent distortion effect.
// ES: Configura el nivel de "drive" para el efecto de distorsión de arco tangente.
void ArctangentDistortion::setArctangentDistortionDrive(float inArctangentDistortionDriveValue)
{
    alpha = inArctangentDistortionDriveValue;
}

// EN: Processes the audio buffer, applying the arctangent distortion effect.
// ES: Procesa el buffer de audio, aplicando el efecto de distorsión de arco tangente.
void ArctangentDistortion::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Iterate through each audio channel in the buffer.
    // ES: Itera a través de cada canal de audio en el buffer.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Iterate through each audio sample in the current channel.
        // ES: Itera a través de cada muestra de audio en el canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // EN: Get the current input sample from the buffer.
            // ES: Obtiene la muestra de entrada actual del buffer.
            float inSample = buffer.getSample(channel, i);

            // EN: Initialize the output sample.
            // ES: Inicializa la muestra de salida.
            float outSample = 0.0f;

            // EN: Apply the arctangent distortion formula.
            // ES: Aplica la fórmula de distorsión de arco tangente.
            outSample = (2.0f / pi) * atanf(inSample * alpha);

            // EN: Write the processed sample back to the buffer.
            // ES: Escribe la muestra procesada de vuelta al buffer.
            buffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Constructor for the ArctangentDistortion class.
// ES: Constructor de la clase ArctangentDistortion.
ArctangentDistortion::ArctangentDistortion()
{
}

// EN: Destructor for the ArctangentDistortion class.
// ES: Destructor de la clase ArctangentDistortion.
ArctangentDistortion::~ArctangentDistortion()
{
}