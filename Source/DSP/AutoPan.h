/*
  ==============================================================================

    AutoPan.h
    Created: 30 Aug 2024 12:13:48pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AutoPan
{
public:
    void setDepth(float inDepthValue);
    void setSpeed(float inSpeedValue);

    void prepare(double theSampleRate);

    void process(juce::AudioBuffer<float>& buffer);

	AutoPan();
	~AutoPan();

private:
    float pi{ juce::MathConstants<float>::pi };
    float time[2];
    float deltTime[2];
    float sampleRate{ 44100.0f };

    //Tremolo parameters
    float depthValue{ 0 };//0-100
    float speedValue{ 5.0 };//0-20

};

