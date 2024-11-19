/*
  ==============================================================================

    BarberPoleFeedback.h
    Created: 5 Nov 2024 8:29:25am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class BarberpoleFlangerFX
{
public:
    BarberpoleFlangerFX();
    ~BarberpoleFlangerFX();

    void prepare(double theSampleRate);
    void setDepth(float inDepth);
    void setRate(float inRatePercentage);
    void setPredelay(float inPredelayMs);
    void process(juce::AudioBuffer<float>& buffer);

private:
    float sampleRate;
    float t;
    float depth;
    float ratePercentage;
    float targetRatePercentage;
    float predelay;
    static const int circularBufferSize = 48000; // Tamaño del buffer circular
    float circularBuffer[circularBufferSize][2]; // Buffer circular estéreo
    int writterPointer[2] = { 0, 0 };            // Punteros de escritura para cada canal

    float generateSawtooth(float phase);
};