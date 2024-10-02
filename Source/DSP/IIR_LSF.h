/*
  ==============================================================================

    IIR_LSF.h
    Created: 30 Sep 2024 1:53:16pm
    Author:  Jhonatan

    notes: values for Q 0.1f, 2.0f, 0.707f. Values for gain 0.1f, 3.0f, 1.0f +6db aprox.
  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class IIR_LSF
{
public:
    IIR_LSF();
    ~IIR_LSF();

    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void setCutoffFrequency(float newCutoff);
    void setQ(float newQ);
    void setGain(float newGain);

private:

    void updateFilter(); // Método para actualizar los coeficientes del filtro
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> foApf;
    double sampleRate{};
    float cutoffFrequency{};
    float q{};
    float gain{};
};