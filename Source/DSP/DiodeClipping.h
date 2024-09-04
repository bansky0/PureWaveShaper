/*
  ==============================================================================

    DiodeClipping.h
    Created: 3 Sep 2024 4:46:15pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DiodeClipping
{
public:

    void process(juce::AudioBuffer<float>& buffer);

	DiodeClipping();
	~DiodeClipping();

private:
    float Vt = 0.0253f;// thermal voltage
    float eta = 1.68f;// emission coefficient
    float Is = .105f;// saturation current
};
