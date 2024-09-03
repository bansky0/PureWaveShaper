/*
  ==============================================================================

    FullWaveRectification.h
    Created: 2 Sep 2024 8:03:38pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FullWaveRectification
{
public:

    void process(juce::AudioBuffer<float>& buffer);

	FullWaveRectification();
	~FullWaveRectification();

private:

};