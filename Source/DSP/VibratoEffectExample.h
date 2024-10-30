/*
  ==============================================================================

    VibratoEffectExample.h
    Created: 21 Oct 2024 9:19:16pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <vector>

class VibratoEffect
{
public:
    VibratoEffect();
    ~VibratoEffect();

    void prepare(double sampleRate);
    //void setBPM(float BPM);
    void setRate(float rateHz);  // Configura la frecuencia del LFO
    void setDepth(float depthSamples);  // Configura la profundidad en muestras
    void process(juce::AudioBuffer<float>& buffer);

private:
    double sampleRate = 48000;
    int delaySamples = 1000;  // Máximo retardo en muestras
    float rate = 4;    // Frecuencia del LFO en Hz
    float depth = 75;  // Profundidad en muestras
    float t = 0.0f;
    int currentSample = 0;
    float lfoPhase = 0.0f;
    static const int circularBufferSize = 1000;
    float circularBuffer[circularBufferSize][2] = { 0.0f };
    int readerPointer = 0;
    int writterPointer[2] = { 0, 0 };
};
