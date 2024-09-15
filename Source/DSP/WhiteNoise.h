/*
  ==============================================================================

    WhiteNoise.h
    Created: 10 Sep 2024 1:12:37pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class WhiteNoise
{
public:
    WhiteNoise();
    ~WhiteNoise();

    void prepare(double theSampleRate);
    void process(juce::AudioBuffer<float>& buffer);

private:
    double sampleRate;
    juce::Random randomGenerator; // Generador de números aleatorios
};