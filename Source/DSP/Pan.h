/*
  ==============================================================================

    Pan.h
    Created: 22 Aug 2024 2:07:46pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Pan
{
public:
	Pan();
	~Pan();

    void setPanValue(float inPanValue);

    void process(juce::AudioBuffer<float>& buffer);

private:
    float pi{ juce::MathConstants<float>::pi };
    float panValue{ juce::MathConstants<float>::pi / 4.0f };

};