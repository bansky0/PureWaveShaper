/*
  ==============================================================================

    SimpleDelay3.h
    Created: 19 Sep 2024 1:00:10pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SimpleDelay3
{
public:
	SimpleDelay3();
	~SimpleDelay3();

    void setTimeDelay(float delayTime);
    void prepare(double theSampleRate, int samplesPerBlock, juce::dsp::ProcessSpec& spec, int numbChannels);

    void process(juce::AudioBuffer<float>& buffer);

private:
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> myDelay{98000};
    double sampleRate{ 0.0 };
    float delay{}; //delay in samples
};