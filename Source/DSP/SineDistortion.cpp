/*
  ==============================================================================

    SineDistortion.cpp
    Created: 2 Sep 2024 11:03:13pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "SineDistortion.h"

// EN: Sets the intensity of the sine distortion effect.
// ES: Establece la intensidad del efecto de distorsión basada en seno.
void SineDistortion::setSineDistortionValue(float inSineDistortionValue)
{
    distortion = inSineDistortionValue; // EN: Save the distortion value. | ES: Guarda el valor de distorsión.
}

// EN: Applies the sine distortion effect to the audio buffer.
// ES: Aplica el efecto de distorsión basada en seno al buffer de audio.
void SineDistortion::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Loop through all the channels in the audio buffer.
    // ES: Recorre todos los canales del buffer de audio.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Loop through all the samples in the current channel.
        // ES: Recorre todas las muestras en el canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i); // EN: Get the input sample. | ES: Obtiene la muestra de entrada.
            float outSample = 0.0f;                        // EN: Variable to hold the processed sample. | ES: Variable para la muestra procesada.

            // EN: Apply the sine distortion formula.
            // ES: Aplica la fórmula de distorsión basada en seno.
            outSample = sinf(0.5f * pi * inSample * distortion);

            // EN: Save the processed sample back to the buffer.
            // ES: Guarda la muestra procesada de nuevo en el buffer.
            buffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Constructor for the SineDistortion class.
// ES: Constructor de la clase SineDistortion.
SineDistortion::SineDistortion()
{
}

// EN: Destructor for the SineDistortion class.
// ES: Destructor de la clase SineDistortion.
SineDistortion::~SineDistortion()
{
}