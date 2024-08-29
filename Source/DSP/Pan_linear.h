/*
  ==============================================================================

    Pan_linear.h
    Created: 22 Aug 2024 6:20:09pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PanLinear
{
public:
	PanLinear();
	~PanLinear();

    void setPanLinearValue(float inPanLinearValue);

    void process(juce::AudioBuffer<float>& buffer);

private:
    float panLinearValue{};

};

