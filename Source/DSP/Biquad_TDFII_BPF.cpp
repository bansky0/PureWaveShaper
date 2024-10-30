/*
  ==============================================================================

    Biquad_TDFII_BPF.cpp
    Created: 7 Oct 2024 4:01:29pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Biquad_TDFII_BPF.h"
Biquad_TDFII_BPF::Biquad_TDFII_BPF()
{
}

Biquad_TDFII_BPF::~Biquad_TDFII_BPF()
{
}

void Biquad_TDFII_BPF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

void Biquad_TDFII_BPF::process(juce::AudioBuffer<float>& inBuffer)
{
    int numChannels = inBuffer.getNumChannels();
    int numSamples = inBuffer.getNumSamples();

    for (int channel = 0; channel < numChannels; channel++)
    {
        for (int i = 0; i < numSamples; i++)
        {
            float inSample = inBuffer.getSample(channel, i);

            float outSample = processSample(inSample, channel);

            inBuffer.setSample(channel, i, outSample);
        }
    }
}

float Biquad_TDFII_BPF::processSample(float inSample, int channel)
{
    auto y = b0 * inSample + r1[channel];

    r1[channel] = b1 * inSample + (-a1) * y + r2[channel];
    r2[channel] = b2 * inSample + (-a2) * y;

    return y;
}

void Biquad_TDFII_BPF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

void Biquad_TDFII_BPF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

void Biquad_TDFII_BPF::updateFilter()
{
    //calcular componente para un BPF
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    b0 = sinf(w0) / 2.0f;
    b1 = 0.0f;
    b2 = -sinf(w0) / 2.0f;

    a0 = 1.0f + alpha;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha;

    // Normaliza los coeficientes dividiendo por a0
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}