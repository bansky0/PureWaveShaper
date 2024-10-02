/*
  ==============================================================================

    FIR_LPF2.h
    Created: 28 Sep 2024 9:39:51pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FIR_LPF2
{
public:
    FIR_LPF2();
    ~FIR_LPF2();

    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void setCutoffFrequency(float newCutoff); // Método para cambiar la frecuencia de corte


private:
    void updateFilter(); // Método para actualizar los coeficientes del filtro
    juce::dsp::FIR::Filter<float> lowPassFilter; // Filtro FIR LPF
    juce::dsp::FIR::Filter<float> lowPassFilter2;
    juce::dsp::FIR::Coefficients<float>::Ptr coefficients; // Coeficientes del filtro FIR

    double sampleRate; // Frecuencia de muestreo
    float cutoffFrequency; // Frecuencia de corte
};