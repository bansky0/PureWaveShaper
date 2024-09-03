/*
  ==============================================================================

    HardClip.h
    Created: 2 Sep 2024 8:43:08pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class HardClip
{
public:
    void setHardClipThresh(float inHardClipThreshValue);

    void process(juce::AudioBuffer<float>& buffer);

	HardClip();
	~HardClip();

private:
    float thresh = 0.0f;
};