/*
  ==============================================================================

    FIR_HPF.h
    Created: 27 Sep 2024 8:52:32am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FIR_LPF
{
public:
    
    FIR_LPF();
	~FIR_LPF();
    void setCutoffFrequency(float newCutoff);  // Método para actualizar la frecuencia de corte

    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);
    
    void process(juce::AudioBuffer<float>& buffer);

private:
    //juce::dsp::ProcessorDuplicator<juce::dsp::FIR::Filter<float>, juce::dsp::FIR::Coefficients<float>> firLpf;
    juce::dsp::FIR::Filter<float> lowPassFilter; // Filtro FIR LPF
    juce::dsp::FIR::Filter<float> lowPassFilter2; // Filtro FIR LPF
    juce::dsp::FIR::Coefficients<float>::Ptr coefficients; // Coeficientes del filtro FIR

    float cutoffFrequency = 20000.0f;  // Frecuencia de corte inicial
    double sampleRate{};
    void updateFilter();

        /*std::array<juce::dsp::IIR::Filter<float>, 2> hpf;
    typename juce::dsp::FIR::Coefficients<float>::Ptr hpfCoeficientes;*/

    //juce::dsp::ProcessorDuplicator<juce::dsp::FIR::Filter<float>, juce::dsp::FIR::Coefficients<float>> hpf;

    /*juce::dsp::StateVariableTPTFilter<float> hpf;*/

};
