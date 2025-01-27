/*
  ==============================================================================

    CubicDistortion.h
    Created: 2 Sep 2024 9:17:07pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CubicDistortion
{
public:

    // EN: Sets the drive parameter for the cubic distortion effect (range: 0.0 to 1.0).
    // ES: Establece el parámetro de drive para el efecto de distorsión cúbica (rango: 0.0 a 1.0).
    void setCubicDistortionDrive(float inCubicDistortionDriveValue);

    // EN: Processes the audio buffer and applies the cubic distortion effect.
    // ES: Procesa el buffer de audio y aplica el efecto de distorsión cúbica.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the CubicDistortion class.
    // ES: Constructor de la clase CubicDistortion.
    CubicDistortion();

    // EN: Destructor for the CubicDistortion class.
    // ES: Destructor de la clase CubicDistortion.
    ~CubicDistortion();

private:
    float drive = 0.0f; // EN: Drive level for the distortion effect (range: 0-1). | ES: Nivel de drive para el efecto de distorsión (rango: 0-1).
};