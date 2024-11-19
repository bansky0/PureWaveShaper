/*
  ==============================================================================

    PitchDown.h
    Created: 5 Nov 2024 1:03:19pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PitchDown
{
public:
    PitchDown() {}
    ~PitchDown() {}

    void prepare(double sampleRate);
    void process(juce::AudioBuffer<float>& buffer);

private:
    float sampleRate;
    float delay;                      // Retardo fraccionario
    static const int bufferSize = 48000 * 2; // Buffer de 2 segundos a 48kHz
    float delayBuffer[bufferSize];     // Buffer circular
    int writePosition = 0;             // Puntero de escritura
    float t;
};