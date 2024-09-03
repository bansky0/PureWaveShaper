/*
  ==============================================================================

    ExponentialDistortion.h
    Created: 3 Sep 2024 12:32:28pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ExponentialDistortion
{
public:

    void setExponentialDistortionValue(float inExponentialDistortionValue);

    void process(juce::AudioBuffer<float>& buffer);

	ExponentialDistortion();
	~ExponentialDistortion();

private:
    float gain = 0.0f; //1-10
};