/*
  ==============================================================================

    IIR_Notch.h
    Created: 30 Sep 2024 6:27:34pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class IIR_Notch
{
public:
    IIR_Notch();
    ~IIR_Notch();

    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void setCutoffFrequency(float newCutoff);

private:

    void updateFilter(); // Método para actualizar los coeficientes del filtro
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> notch;
    double sampleRate{};
    float cutoffFrequency{};
};