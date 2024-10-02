/*
  ==============================================================================

    IIR_FirstOrderHPF.h
    Created: 30 Sep 2024 11:56:09am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class IIRFirstOrderHPF
{
public:
    IIRFirstOrderHPF();
    ~IIRFirstOrderHPF();

    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void setCutoffFrequency(float newCutoff);

private:

    void updateFilter(); // Método para actualizar los coeficientes del filtro
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> foHpf;
    double sampleRate{};
    float cutoffFrequency{};
};