/*
  ==============================================================================

    SawtoothWave2.h
    Created: 9 Sep 2024 1:04:43pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SawtoothWave2
{
public:
    void setFrequency(double inFrequecy);

    void prepare(double theSampleRate);

    void process(juce::AudioBuffer<float>& buffer);

	SawtoothWave2();
	~SawtoothWave2();

private:
    float frequency{ 100.0f };
    float sampleRate{ 44100 };
    float phaseIncrement{};
    float phase[2]{};
};