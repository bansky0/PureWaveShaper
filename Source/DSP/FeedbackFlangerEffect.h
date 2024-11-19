/*
  ==============================================================================

    FeedbackFlangerEffect.h
    Created: 30 Oct 2024 4:35:30pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>

class FeedbackFlangerFX
{
public:
    FeedbackFlangerFX();
    ~FeedbackFlangerFX();

    void prepare(double theSampleRate);
    void setDepth(float inDepth);
    void setRate(float inRatePercentage);
    void setPredelay(float inPredelayMs);
    void setFeedback(float inFeedback);
    void process(juce::AudioBuffer<float>& buffer);

private:
    float sampleRate;
    float t;
    float depth;
    float ratePercentage;
    float targetRatePercentage;
    float predelay;
    float feedback;
    static const int circularBufferSize = 48000; // Tamaño del buffer circular
    float circularBuffer[circularBufferSize][2]; // Buffer circular estéreo
    int writterPointer[2] = { 0, 0 };            // Punteros de escritura para cada canal
};