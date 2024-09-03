/*
  ==============================================================================

    SineDistortion.h
    Created: 2 Sep 2024 11:03:13pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SineDistortion
{
public:
    void setSineDistortionValue(float inSineDistortionValue);

    void process(juce::AudioBuffer<float>& buffer);

	SineDistortion();
	~SineDistortion();

private:
    float distortion = 0.0f;
    float pi{ juce::MathConstants<float>::pi };

};
