/*
  ==============================================================================

    MorphLFO.h
    Created: 28 Aug 2024 9:52:53am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MorphLfo
{
public:
    void set(float inShapeValue);

    void prepare(double theSampleRate);
    void process(juce::AudioBuffer<float>& buffer);

	MorphLfo();
	~MorphLfo();

private:
    float shapeValue{ 0 };//Values 0-10
};