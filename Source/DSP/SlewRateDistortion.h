/*
  ==============================================================================

    SlewRateDistortion.h
    Created: 8 Oct 2024 3:00:37pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SlewRateDistortion
{
public:
	SlewRateDistortion();
	~SlewRateDistortion();

    void prepare(double inSampleRate);

    void process(juce::AudioBuffer<float>& buffer);
    float processSample(float inSample, int channel);

    void setMaxFreq(float inSlewDistortionValue);
    
    void updateSlewRate();

private:
    double sampleRate{ 44100 };
    float maxFreq{};

    float y1[2] = { 0.0f };
    float delta[2] = { 0.0f };

    float Ts = 0.0;         // Período de muestreo
    float peak = 1.0;       // Valor pico
    float slewRate = 0.2;   // Tasa de cambio máxima
    float slope = 0.0;      // Pendiente de la tasa de cambio
    float preSample{};
    
    //std::vector<float> prevOut = 0.0;    // Muestra anterior para la retroalimentación
};
