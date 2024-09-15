/*
  ==============================================================================

    SineWave2.h
    Created: 8 Sep 2024 12:44:04pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SineWave2
{
public:
    void setFrequency(double inFrequecy);

    void setPhase(double setPhase);

    void prepare(double theSampleRate);

    void process(juce::AudioBuffer<float>& buffer);
    
    SineWave2();
	~SineWave2();

private:
    float sampleRate{ 44100.0f };
    float twoPi{ juce::MathConstants<float>::twoPi };
    float frequency{ 0.0f };
    float phi{ 0.0f };
    float phaseIncrement{};
    float phase[2]{};
};