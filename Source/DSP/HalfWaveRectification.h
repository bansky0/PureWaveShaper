/*
  ==============================================================================

    HalfWaveRectification.h
    Created: 2 Sep 2024 7:13:47pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class HalfWaveRectification
{
public:

    void process(juce::AudioBuffer<float>& buffer);

	HalfWaveRectification();
	~HalfWaveRectification();

private:

};