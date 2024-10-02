/*
  ==============================================================================

    IIR_FirstOrderAPF.h
    Created: 30 Sep 2024 12:55:31pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class IIRFirstOrderAPF
{
public:
    IIRFirstOrderAPF();
    ~IIRFirstOrderAPF();

    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void setCutoffFrequency(float newCutoff);

private:

    void updateFilter(); // Método para actualizar los coeficientes del filtro
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> foApf;
    double sampleRate{};
    float cutoffFrequency{};
};