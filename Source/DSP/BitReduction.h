/*
  ==============================================================================

    BitReduction.h
    Created: 4 Sep 2024 10:39:47am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: A class that implements a bit reduction effect for audio processing.
// ES: Una clase que implementa un efecto de reducción de bits para el procesamiento de audio.
class BitReduction
{
public:
    // EN: Constructor. Initializes the BitReduction object.
    // ES: Constructor. Inicializa el objeto BitReduction.
    BitReduction();

    // EN: Destructor. Cleans up any resources used by the BitReduction object.
    // ES: Destructor. Limpia cualquier recurso utilizado por el objeto BitReduction.
    ~BitReduction();

    // EN: Sets the bit depth value for the bit reduction effect.
    // ES: Establece el valor de profundidad de bits para el efecto de reducción de bits.
    void setBitNumberValue(float inBitNumberValue);

    // EN: Processes the audio buffer by applying the bit reduction effect.
    // ES: Procesa el buffer de audio aplicando el efecto de reducción de bits.
    void process(juce::AudioBuffer<float>& buffer);

private:
    // EN: The bit depth value used for the bit reduction effect.
    // ES: El valor de profundidad de bits utilizado para el efecto de reducción de bits.
    float bitNumber{};
};
