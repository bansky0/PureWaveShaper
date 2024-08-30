/*
  ==============================================================================

    MorphWave.h
    Created: 30 Aug 2024 11:25:40am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MorphWave
{
public:

    void setShape(float inShapeValue);
    void setFrequency(double inFrequecy);
    void prepare(double theSampleRate);
    void process(juce::AudioBuffer<float>& buffer);

    MorphWave();
	~MorphWave();

private:
    float shapeValue{ 0.0f };//Values 0-10
    float frequency{ 100.0f };//0-20
    float sampleRate{ 44100 };
    float time[2]{};
    float deltaTime[2]{};

};
