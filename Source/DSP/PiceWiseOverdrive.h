/*
  ==============================================================================

    PiceWiseOverdrive.h
    Created: 3 Sep 2024 1:43:52pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PiceWiseOverdrive
{
public:

    //void setPiceWiseOverdriveValue(float inPiceWiseOverdriveValue);

    void process(juce::AudioBuffer<float>& buffer);

	PiceWiseOverdrive();
	~PiceWiseOverdrive();

private:

};
