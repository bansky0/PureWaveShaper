/*
  ==============================================================================

    IIR_PeakFilter.h
    Created: 30 Sep 2024 6:28:09pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class IIR_PeakF
{
public:
    IIR_PeakF();
    ~IIR_PeakF();

    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void setCutoffFrequency(float newCutoff);
    void setQ(float newQ);
    void setGain(float newGain);
private:

    void updateFilter(); // Método para actualizar los coeficientes del filtro
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> notch;
    double sampleRate{};
    float cutoffFrequency{};
    float q{};
    float gain{};
};