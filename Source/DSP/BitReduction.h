/*
  ==============================================================================

    BitReduction.h
    Created: 4 Sep 2024 10:39:47am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class BitReduction
{
public:
    void setBitNumberValue(float inBitNumberValue);

    void process(juce::AudioBuffer<float>& buffer);

	BitReduction();
	~BitReduction();

private:
    float bitNumber{};
};
