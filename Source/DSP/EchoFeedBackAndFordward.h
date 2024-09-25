/*
  ==============================================================================

    EchoFeedBackAndFordward.h
    Created: 19 Sep 2024 11:16:08am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class EchoFBF
{
public:

    void setBPM(float BPM);
    void setAmpFordward(float inAmpFordward);
    void setAmpFeedback(float inAmpFeedback);

    void prepare(double theSampleRate);

    void process(juce::AudioBuffer<float>& buffer);

    EchoFBF();
    ~EchoFBF();

private:
    // Variables de retardo (delay)
    int delay = 48000;
    
    float ampFeedback = 0.75f;
    float ampFordward = 0.75f;
    float feedback = 0.5f;

    // Tamaño del buffer circular
    static const int circularBufferSize = 96000;
    float circularBuffer[circularBufferSize][2] = { 0.0f };

    // Punteros de escritura para entrada y salida
    int readerPointer = 0;
    int writterPointer[2]{};
    
    // Parámetros del delay
    float sampleRate = 48000;
    float b0 = 1.0f;
    float bM = 0.5f;
    float aW = 0.7f;
};
