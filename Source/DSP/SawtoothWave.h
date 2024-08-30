/*
  ==============================================================================

    SawtoothWave.h
    Created: 29 Aug 2024 4:38:15pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SawtoothWave
{
public:

    void setFrequency(double inFrequecy);

    void prepare(double theSampleRate);

    void process(juce::AudioBuffer<float>& buffer);

	SawtoothWave();
	~SawtoothWave();

private:
    float frequency{ 100.0f };
    float sampleRate{ 44100 };
    float time[2]{};
    float deltaTime[2]{};
};