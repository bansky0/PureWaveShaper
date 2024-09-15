/*
  ==============================================================================

    Subtraction.h
    Created: 11 Sep 2024 2:32:06pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Subtraction
{
public:

    void setFrequency1(float inFreqOsc1);
    void setAmplitud1(float inAmp1);
    void setFrequency2(float inFreqOsc2);
    void setAmplitud2(float inAmp1);

    void prepare(double theSampleRate);
    void process(juce::AudioBuffer<float>& buffer);

	Subtraction();
	~Subtraction();

private:
    float osc1{};
    float amp1{};
    float osc2{};
    float amp2{};
    double sampleRate{};
    float twoPi{ juce::MathConstants<float>::twoPi };
    float phaseIncrement1{};
    float phaseIncrement2{};
    float phase1[2]{};
    float phase2[2]{};
};