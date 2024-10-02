/*
  ==============================================================================

    IIR_LPF.h
    Created: 30 Sep 2024 1:13:35pm
    Author:  Jhonatan
    Notes: somes distortion 300hz an lower values. some glitchs in veryhig frequencies.
  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class IIR_LPF
{
public:
    IIR_LPF();
    ~IIR_LPF();

    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void setCutoffFrequency(float newCutoff);

private:

    void updateFilter(); // Método para actualizar los coeficientes del filtro
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> foApf;
    double sampleRate{};
    float cutoffFrequency{};
};