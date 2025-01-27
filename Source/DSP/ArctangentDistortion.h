/*
  ==============================================================================

    ArctangentDistortion.h
    Created: 2 Sep 2024 10:08:57pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class ArctangentDistortion: Implements a simple distortion effect based on the arctangent function.
// ES: Clase ArctangentDistortion: Implementa un efecto de distorsión simple basado en la función arco tangente.

class ArctangentDistortion
{
public:
    // EN: Sets the drive level for the arctangent distortion. Accepts values in the range of 1-10.
    // ES: Configura el nivel de "drive" para la distorsión de arco tangente. Acepta valores en el rango de 1-10.
    void setArctangentDistortionDrive(float inArctangentDistortionDriveValue);

    // EN: Processes the audio buffer to apply the arctangent distortion effect.
    // ES: Procesa el buffer de audio para aplicar el efecto de distorsión de arco tangente.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the ArctangentDistortion class.
    // ES: Constructor de la clase ArctangentDistortion.
    ArctangentDistortion();

    // EN: Destructor for the ArctangentDistortion class.
    // ES: Destructor de la clase ArctangentDistortion.
    ~ArctangentDistortion();

private:
    // EN: Mathematical constant Pi, used in the distortion formula.
    // ES: Constante matemática Pi, utilizada en la fórmula de distorsión.
    float pi{ juce::MathConstants<float>::pi };

    // EN: Drive parameter for the distortion, determines the amount of effect applied.
    // ES: Parámetro de "drive" para la distorsión, determina la cantidad de efecto aplicado.
    float alpha{}; // Range: 1-10
};