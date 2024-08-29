/*
  ==============================================================================

    Pan_sineLaw_modified.h
    Created: 26 Aug 2024 1:26:44pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PanSineLawModified
{
public:
    PanSineLawModified();
    ~PanSineLawModified();

    void setPanSineLawModifiedValue(float inPanSineLawModifiedValue);

    void process(juce::AudioBuffer<float>& buffer);

private:
    float panSineLawModifiedValue{};
    float pi{ juce::MathConstants<float>::pi };
};
