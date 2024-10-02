/*
  ==============================================================================

    DirectFormII_NestedAPF.h
    Created: 2 Oct 2024 4:44:56pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DirectFormII_NestedAPF
{
public:
	DirectFormII_NestedAPF();
	~DirectFormII_NestedAPF();

    void process(juce::AudioBuffer<float>& inBuffer);
    float processSample(float inSample, int channel);

    void setG(float inG1, float inG2);
private:
    float prevV[2] = { 0.0f };
    float prevW1[2] = { 0.0f };
    float prevW2[2] = { 0.0f };

    float g1{ 0.5f };
    float g2{ 0.5f };
};