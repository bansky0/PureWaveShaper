/*
  ==============================================================================

    DutyCicleWave.h
    Created: 9 Sep 2024 1:03:43pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DutyCicleWave
{
public:

    void setFrequency(double inFrequency);
    void setDutyCycle(float inDutyCycle);
    void prepare(double theSampleRate);

    void process(juce::AudioBuffer<float>& buffer);

	DutyCicleWave();
	~DutyCicleWave();

private:
    float frequency{ 0.0f };
    float sampleRate{ 44100 };
    float phaseIncrement{};
    float phase[2]{};
    float dutyCycle{};//0-100%
};
