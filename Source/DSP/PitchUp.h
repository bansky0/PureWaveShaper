/*
  ==============================================================================

    PitchUp.h
    Created: 5 Nov 2024 4:21:53pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PitchUp
{
public:
    PitchUp() {}
    ~PitchUp() {}

    void prepare(double theSampleRate);
    void process(juce::AudioBuffer<float>& buffer);

private:
    float sampleRate{48000};
    float delay{0}; // Retardo en muestras
    static const int bufferSize = 48000; // Tamaño del buffer circular (2 segundos a 48 kHz)
    float delayBuffer[bufferSize]; // Buffer de retardo circular
    int writePosition{0}; // Posición de escritura en el buffer
};