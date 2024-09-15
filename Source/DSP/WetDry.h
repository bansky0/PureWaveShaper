/*
  ==============================================================================

    WetDry.h
    Created: 5 Sep 2024 10:20:06am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class WetDry
{
public:
    void setDryWet(float inDryWetValue);

    void process(juce::AudioBuffer<float>& dryBuffer, 
                 juce::AudioBuffer<float>& wetBuffer);

	WetDry();
	~WetDry();

private:
    float dryWet{0.0f};
};