/*
  ==============================================================================

    Infiniteclip.h
    Created: 2 Sep 2024 6:29:56pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class InfiniteClip
{
public:

    void process(juce::AudioBuffer<float>& buffer);

	InfiniteClip();
	~InfiniteClip();

private:

};