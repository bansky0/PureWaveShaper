/*
  ==============================================================================

    SimpleDelay2.h
    Created: 17 Sep 2024 3:41:36pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SimpleDelay2
{
public:

    void setBPM(float BPM);
    void setAmpDelay(float inAmpDelay);
    void setFeedback(float inFeedback);

    void prepare(double theSampleRate);

    void process(juce::AudioBuffer<float>& buffer);

    SimpleDelay2();
    ~SimpleDelay2();

private:
    float sampleRate = 48000;
    int delay = 48000;
    float ampDelay = 0.75f;
    float feedback = 0.5f;
    static const int circularBufferSize = 96000;
    float circularBuffer[circularBufferSize][2] = { 0.0f };
    int readerPointer = 0;
    int writterPointer[2]{};
};
