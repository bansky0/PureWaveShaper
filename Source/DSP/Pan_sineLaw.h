/*
  ==============================================================================

    Pan_sineLaw.h
    Created: 26 Aug 2024 12:08:48pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PanSineLaw
{
public:
	PanSineLaw();
	~PanSineLaw();

    void setPanSineLawValue(float inPanSineLawValue);

    void process(juce::AudioBuffer<float>& buffer);

private:
    float panSineLawValue{};
    float pi{ juce::MathConstants<float>::pi };
};

