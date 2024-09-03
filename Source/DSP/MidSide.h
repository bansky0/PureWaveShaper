/*
  ==============================================================================

    MidSide.h
    Created: 31 Aug 2024 9:53:26am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MidSide
{
public:
    //void setMidSideValue(bool inMidSideValue);
    void process(juce::AudioBuffer<float>& buffer);

	MidSide();
	~MidSide();

private:

};