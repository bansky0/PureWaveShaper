/*
  ==============================================================================

    SineDistortion.h
    Created: 2 Sep 2024 11:03:13pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class to apply sine-based distortion to an audio buffer.
// ES: Clase para aplicar distorsión basada en seno a un buffer de audio.
class SineDistortion
{
public:
    // EN: Sets the distortion intensity. Accepts a value from 1 to 4.
    // ES: Configura la intensidad de la distorsión. Acepta un valor de 1 a 4.
    void setSineDistortionValue(float inSineDistortionValue);

    // EN: Applies the sine distortion effect to the audio buffer.
    // ES: Aplica el efecto de distorsión basada en seno al buffer de audio.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor.
    // ES: Constructor.
    SineDistortion();

    // EN: Destructor.
    // ES: Destructor.
    ~SineDistortion();

private:
    // EN: The distortion intensity value (ranges from 1 to 4).
    // ES: Valor de intensidad de la distorsión (rango de 1 a 4).
    float distortion = 0.0f;

    // EN: Constant representing the value of pi.
    // ES: Constante que representa el valor de pi.
    float pi{ juce::MathConstants<float>::pi };
};