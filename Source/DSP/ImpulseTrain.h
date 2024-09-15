/*
  ==============================================================================

    ImpulseTrain.h
    Created: 10 Sep 2024 11:13:07am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ImpulseTrain
{
public:
    void setFrequency(double inFrequency);
    void prepare(double theSampleRate);
    void process(juce::AudioBuffer<float>& buffer);

	ImpulseTrain();
	~ImpulseTrain();

private:
    float phase[2]{ 0.0f, 0.0f };    // Fase por canal
    float phaseIncrement = 0.0f;    // Incremento de fase para controlar el ciclo de la onda
    float sampleRate = 44100.0f;
    float frequency = 440.0f;       // Frecuencia del tren de impulsos
};