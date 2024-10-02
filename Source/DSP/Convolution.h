/*
  ==============================================================================

    Convolution.h
    Created: 26 Sep 2024 10:28:16am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Convolution
{
public:

    void prepare(double inSampleRate, int inSamplesPerblock, int inNumChannels);
    void process(juce::AudioBuffer<float> inBuffer);

	Convolution();
	~Convolution();

private:
    juce::dsp::Convolution convolution;
};

