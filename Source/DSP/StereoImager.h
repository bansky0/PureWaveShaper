/*
  ==============================================================================

    StereoImager.h
    Created: 31 Aug 2024 11:53:59am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class StereoImager
{
public:
    void setStereoImagerValue(float inStereoImagerWidthValue);
    void process(juce::AudioBuffer<float>& buffer);

	StereoImager();
	~StereoImager();

private:

    float widthValue { 0.0f };
};