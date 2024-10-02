/*
  ==============================================================================

    Biquad_Peaking.h
    Created: 1 Oct 2024 12:25:55pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class Biquad_Peaking
{
public:
    Biquad_Peaking();
    ~Biquad_Peaking();

    void prepare(double inSampleRate);

    void process(juce::AudioBuffer<float> inBuffer);
    float processSample(float inSample, int channel);

    void setFrequency(float inFrequency);
    void setGain(float inGain);
    void setQ(float inQ);

    void updateFilter();

private:
    double sampleRate{ 0.0f };

    float x1[2] = { 0.0f };
    float x2[2] = { 0.0f };
    float y1[2] = { 0.0f };
    float y2[2] = { 0.0f };

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
    float Gain{ 0.0f };
    float A{ 0.0f };
};