/*
  ==============================================================================

    VibratoEffect.h
    Created: 23 Oct 2024 4:32:52pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class VibratoFX
{
public:

    void setDepth(float inDepth);
    void setRate(float inRate);

    void prepare(double theSampleRate);

    void process(juce::AudioBuffer<float>& buffer);

    VibratoFX();
    ~VibratoFX();

private:
    float sampleRate = 48000;
    int delay = 1000;
    float depth = 0.0f;
    float ratePercentage = 0.0f;
    float targetRatePercentage{};
    float t = 0.0f;
    static const int circularBufferSize = 1000;
    float circularBuffer[circularBufferSize][2] = { 0.0f };
    int readerPointer = 0;
    int writterPointer[2]{};
};
