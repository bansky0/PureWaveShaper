/*
  ==============================================================================

    TriangleWave.h
    Created: 28 Aug 2024 5:32:09pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class TriangleWave
{
public:
    void setFrequency(double inFrequecy);

    void prepare(double theSampleRate);

    void process(juce::AudioBuffer<float>& buffer);

	TriangleWave();
	~TriangleWave();

private:
    float frequency{ 100.0f };
    float sampleRate{ 44100 };
    float time[2]{};
    float deltaTime[2]{};
};