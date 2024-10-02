/*
  ==============================================================================

    Convolution.cpp
    Created: 26 Sep 2024 10:28:16am
    Author:  Jhonatan

  ==============================================================================
*/

#include "Convolution.h"

void Convolution::prepare(double inSampleRate, int inSamplesPerblock, int inNumChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerblock;
    spec.numChannels = inNumChannels;

    convolution.reset();
    convolution.prepare(spec);

    convolution.loadImpulseResponse(BinaryData::Taylor_314ce__DPA_4011_wav, BinaryData::Taylor_314ce__DPA_4011_wavSize,
                                juce::dsp::Convolution::Stereo::yes, 
                                juce::dsp::Convolution::Trim::yes,
                                0,
                                juce::dsp::Convolution::Normalise::yes);
}
void Convolution::process(juce::AudioBuffer<float> inBuffer) 
{
    juce::dsp::AudioBlock<float> block(inBuffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    convolution.process(context);
}

Convolution::Convolution()
{
}

Convolution::~Convolution()
{
}