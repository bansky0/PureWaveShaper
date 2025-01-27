/*
  ==============================================================================

    CubicDistortion.cpp
    Created: 2 Sep 2024 9:17:07pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "CubicDistortion.h"

// EN: Sets the drive parameter for the cubic distortion effect.
// ES: Establece el parámetro de drive para el efecto de distorsión cúbica.
void CubicDistortion::setCubicDistortionDrive(float inCubicDistortionDriveValue)
{
    drive = inCubicDistortionDriveValue;
}

// EN: Processes the audio buffer and applies the cubic distortion effect.
// ES: Procesa el buffer de audio y aplica el efecto de distorsión cúbica.
void CubicDistortion::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Iterate through each audio channel in the buffer.
    // ES: Itera a través de cada canal de audio en el buffer.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Iterate through each audio sample in the current channel.
        // ES: Itera a través de cada muestra de audio en el canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // EN: Get the current sample value.
            // ES: Obtiene el valor de la muestra actual.
            float inSample = buffer.getSample(channel, i);

            // EN: Apply the cubic distortion formula to the sample.
            // ES: Aplica la fórmula de distorsión cúbica a la muestra.
            float outSample = 0.0f;
            outSample = inSample - (drive * (powf(inSample, 3.0f)) / 3.0f);

            // EN: Set the processed sample value back into the buffer.
            // ES: Establece el valor de la muestra procesada de nuevo en el buffer.
            buffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Constructor for the CubicDistortion class.
// ES: Constructor de la clase CubicDistortion.
CubicDistortion::CubicDistortion()
{
}

// EN: Destructor for the CubicDistortion class.
// ES: Destructor de la clase CubicDistortion.
CubicDistortion::~CubicDistortion()
{
}