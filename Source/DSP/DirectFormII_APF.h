/*
  ==============================================================================

    DirectFormII_APF.h
    Created: 2 Oct 2024 11:20:47am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DirectFormII_APF
{
public:
	DirectFormII_APF();
	~DirectFormII_APF();

    void process(juce::AudioBuffer<float>& inBuffer);
    float processSample(float inSample, int channel);

    void setG(float inG);

private:
    float x1[2] = { 0.0f };
    float y1[2] = { 0.0f };

    float g{ 0.5f };
};

