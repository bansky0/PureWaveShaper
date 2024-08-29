/*
  ==============================================================================

    Pan_sqrt.h
    Created: 26 Aug 2024 11:09:35am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PanSqrt
{
public:
	PanSqrt();
	~PanSqrt();

    void setPanSqrtValue(float inPanSqrtValue);

    void process(juce::AudioBuffer<float>& buffer);

private:
    float panSqrtValue{};
};