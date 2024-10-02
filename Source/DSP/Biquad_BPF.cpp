/*
  ==============================================================================

    Biquad_BPF.cpp
    Created: 1 Oct 2024 12:24:54pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Biquad_BPF.h"

Biquad_BPF::Biquad_BPF() {}

Biquad_BPF::~Biquad_BPF() {}

void Biquad_BPF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

void Biquad_BPF::process(juce::AudioBuffer<float> inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            float inSample = inBuffer.getSample(channel, i);

            float outSample = processSample(inSample, channel);

            inBuffer.setSample(channel, i, outSample);
        }
    }
}

float Biquad_BPF::processSample(float inSample, int channel)
{
    auto y = (b0 * inSample + b1 * x1[channel] + b2 * x2[channel] + (-a1) * y1[channel] + (-a2) * y2[channel]) * (1.0f / a0);

    x2[channel] = x1[channel];
    x1[channel] = inSample;
    y2[channel] = y1[channel];
    y1[channel] = y;

    return y;
}

void Biquad_BPF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

void Biquad_BPF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

void Biquad_BPF::updateFilter()
{
    //calcular componente para un LPF
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    b0 = sinf(w0) / 2.0f;
    b1 = 0.0f;
    b2 = -sinf(w0) / 2.0f;

    a0 = 1.0f + alpha;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha;
}