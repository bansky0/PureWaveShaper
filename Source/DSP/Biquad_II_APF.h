/*
  ==============================================================================

    Biquad_II_APF.h
    Created: 7 Oct 2024 11:58:53am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Biquad_II_APF
{
public:
	Biquad_II_APF();
	~Biquad_II_APF();

    void prepare(double inSampleRate);

    void process(juce::AudioBuffer<float>& inBuffer);
    float processSample(float inSample, int channel);

    void setFrequency(float inFrequency);
    void setQ(float inQ);

    void updateFilter();

private:
    double sampleRate{ 0.0f };

    float w1[2] = { 0.0f };
    float w2[2] = { 0.0f };

    float w0{ 0.0f };
    float alpha{ 0.0f };

    float b0{ 0.0f };
    float b1{ 0.0f };
    float b2{ 0.0f };
    float a0{ 0.0f };
    float a1{ 0.0f };
    float a2{ 0.0f };

    float frequency{ 1000.0f };
    float Q{ 0.707f };
};
