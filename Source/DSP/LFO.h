/*
  ==============================================================================

    LFO.h
    Created: 27 Aug 2024 10:39:40am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class LFO
{
public:
	LFO();
	~LFO();

    void setLFOValue(float inRateValue);

    void prepare(double theSampleRate);
    void process(juce::AudioBuffer<float>& buffer);
private:
    //y=0.5sin(2*pi*ft)+0.5
    float sampleRate{ 44100.0f };
    float twoPi{ juce::MathConstants<float>::twoPi };
    float frecuency{ 0 };
    float time[2];
    float deltaTime[2];
};