/*
  ==============================================================================

    Pan_sqrt_modified.h
    Created: 26 Aug 2024 1:26:18pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PanSqrtModidied
{
public:
    PanSqrtModidied();
    ~PanSqrtModidied();

    void setPanSqrtModidiedValue(float inPanSqrtModidiedValue);

    void process(juce::AudioBuffer<float>& buffer);

private:
    float panSqrtModifiedValue{};
};