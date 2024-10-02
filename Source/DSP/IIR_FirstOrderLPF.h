/*
  ==============================================================================

    IIR_FirstOrderLPF.h
    Created: 30 Sep 2024 11:08:21am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class IIRFirstOrderLPF
{
public:
    IIRFirstOrderLPF();
	~IIRFirstOrderLPF();

    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void setCutoffFrequency(float newCutoff);

private:

    void updateFilter(); // Método para actualizar los coeficientes del filtro
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> foLpf;
    double sampleRate{};
    float cutoffFrequency{};
};