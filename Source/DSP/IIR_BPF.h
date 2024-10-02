/*
  ==============================================================================

    IIR_BPF.h
    Created: 30 Sep 2024 4:05:49pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class IIR_BPF
{
public:
    IIR_BPF();
    ~IIR_BPF();

    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void setCutoffFrequency(float newCutoff);

private:

    void updateFilter(); // Método para actualizar los coeficientes del filtro
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> bpf;
    double sampleRate{};
    float cutoffFrequency{};
    float q{};
    float gain{};
};