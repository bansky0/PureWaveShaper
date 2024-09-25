/*
  ==============================================================================

    SimpleDelay.h
    Created: 17 Sep 2024 1:08:03pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SimpleDelay
{
public:
    void prepare(double theSampleRate);

    void setDelay(float delayTime);

    void process(juce::AudioBuffer<float>& buffer);

	SimpleDelay();
	~SimpleDelay();

private:
    int delay = 48000;
    float sampleRate = 48000;
    static const int circularBufferSize = 96000;
    float circularBuffer[circularBufferSize][2] = {0.0f};
    int readerPointer = 0;
    int writterPointer[2]{};
};
