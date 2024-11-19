/*
  ==============================================================================

    BarberPoleFlangerEffect2.h
    Created: 5 Nov 2024 9:52:36am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <vector>

class BarberpoleFlanger2FX
{
public:
    BarberpoleFlanger2FX();
    ~BarberpoleFlanger2FX();

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
    float circularBuffer1[circularBufferSize][2]; // Buffer circular estéreo 1
    float circularBuffer2[circularBufferSize][2]; // Buffer circular estéreo 2
    int writterPointer1[2] = { 0, 0 };            // Punteros de escritura para cada canal en buffer 1
    int writterPointer2[2] = { 0, 0 };            // Punteros de escritura para cada canal en buffer 2
    static constexpr float crossfade1[2] = { 0.8f, 0.2f };
    static constexpr float crossfade2[2] = { 0.2f, 0.8f };

    float generateSawtooth(float phase);
};