/*
  ==============================================================================

    PitchShifter.h
    Created: 5 Nov 2024 5:17:44pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PitchShift
{
public:
    PitchShift();
    ~PitchShift();

    void prepare(double sampleRate);
    void setSemitones(int semitones);
    void process(juce::AudioBuffer<float>& buffer);

private:
    float sampleRate{};
    float delay{};
    float delayRate{};
    static const int bufferSize = 96000; // Tamaño del buffer circular
    float delayBuffer[bufferSize];       // Buffer circular
    int writePosition{};                   // Puntero de escritura

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PitchShift)
};