/*
  ==============================================================================

    TriangleWave2.h
    Created: 9 Sep 2024 3:56:59pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class TriangleWave2
{
public:

    void setFrequency(double inFrequecy);
    void setWidth(float inWidth);
    void prepare(double theSampleRate);

    void process(juce::AudioBuffer<float>& buffer);

	TriangleWave2();
	~TriangleWave2();

private:
    float sampleRate{};
    float frequency{ 44100.0f };
    float phaseIncrement{};
    float width{};
    float phase[2]{};
};