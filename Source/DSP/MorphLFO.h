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
    void setShape(float inShapeValue);
    void setDepth(float inDepthValue);
    void setFrequency(double inFrequecy);
    void prepare(double theSampleRate);
    void process(juce::AudioBuffer<float>& buffer);

	MorphLfo();
	~MorphLfo();

private:
    float shapeValue{ 0.0f };//Values 0-10
    float frequency{ 100.0f };//0-20
    float depthValue{ 1.0f }; //0-100
    float sampleRate{ 44100 };
    float time[2]{};
    float deltaTime[2]{};

};