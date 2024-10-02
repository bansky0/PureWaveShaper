/*
  ==============================================================================

    IIR_HPF.h
    Created: 29 Sep 2024 8:49:51pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class IIR_HPF
{
public:
    IIR_HPF();
	~IIR_HPF();

    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void setCutoffFrequency(float newCutoff);

private:
    void updateFilter(); // Método para actualizar los coeficientes del filtro
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> hpf;
    double sampleRate{};
    float cutoffFrequency{};
};
