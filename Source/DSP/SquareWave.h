/*
  ==============================================================================

    SquareWave.h
    Created: 28 Aug 2024 2:25:56pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SquareWave
{
public:
    void setFrequency(double inFrequecy);

    void prepare(double theSampleRate);

    void process(juce::AudioBuffer<float>& buffer);

	SquareWave();
	~SquareWave();

private:
    float frequency{ 0.0f };
    float sampleRate{ 44100 };
    float time[2]{};
    float deltaTime[2]{};
};