/*
  ==============================================================================

    SineWave.h
    Created: 28 Aug 2024 11:32:36am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SineWave
{
public:
    void setFrequency(double inFrequecy);

    void setPhase(double setPhase);

    void prepare(double theSampleRate);

    void process(juce::AudioBuffer<float>& buffer);


	SineWave();
	~SineWave();
private:
    float sampleRate{ 44100.0f };
    float twoPi{ juce::MathConstants<float>::twoPi };
    float time[2] {};
    float deltaTime[2]{};
    float frequency{ 0.0f };
    float phi{0.0f};
};

