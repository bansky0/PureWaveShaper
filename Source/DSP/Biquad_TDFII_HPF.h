/*
  ==============================================================================

    Biquad_TDFII_HPF.h
    Created: 7 Oct 2024 4:01:47pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include "Juceheader.h"

class Biquad_TDFII_HPF
{
public:
    Biquad_TDFII_HPF();
    ~Biquad_TDFII_HPF();

    void prepare(double inSampleRate);

    void process(juce::AudioBuffer<float> inBuffer);
    float processSample(float inSample, int channel);

    void setFrequency(float inFrequency);
    void setQ(float inQ);

    void updateFilter();

private:
    double sampleRate{ 0.0f };

    float r1[2] = { 0.0f };
    float r2[2] = { 0.0f };

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