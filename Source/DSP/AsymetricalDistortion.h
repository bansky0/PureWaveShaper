/*
  ==============================================================================

    AsymetricalDistortion.h
    Created: 4 Sep 2024 1:26:39pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AsymetricalDistortion
{
public:
    void setDCValue(float inDCValue);

    void process(juce::AudioBuffer<float>& buffer);

	AsymetricalDistortion();
	~AsymetricalDistortion();

private:
    float pi{ juce::MathConstants<float>::pi };
    float dc = {};//-0.7 to 0.7, 0 no distortion. Negative values cut down wave.
};