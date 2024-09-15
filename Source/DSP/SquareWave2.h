/*
  ==============================================================================

    SquareWave2.h
    Created: 8 Sep 2024 2:40:00pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SquareWave2
{
public:
    void setFrequency(double inFrequency);

    void prepare(double theSampleRate);

    void process(juce::AudioBuffer<float>& buffer);

    SquareWave2();
    ~SquareWave2();

private:
    float frequency{ 0.0f };
    float sampleRate{ 44100 };
    float phaseIncrement{};
    float phase[2]{};
};