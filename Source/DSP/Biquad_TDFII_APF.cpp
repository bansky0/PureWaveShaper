/*
  ==============================================================================

    Biquad_TDFII_APF.cpp
    Created: 7 Oct 2024 3:59:49pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Biquad_TDFII_APF.h"

Biquad_TDFII_APF::Biquad_TDFII_APF()
{
}

Biquad_TDFII_APF::~Biquad_TDFII_APF()
{
}

void Biquad_TDFII_APF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

void Biquad_TDFII_APF::process(juce::AudioBuffer<float>& inBuffer)
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

float Biquad_TDFII_APF::processSample(float inSample, int channel)
{
    auto y = b0 * inSample + r1[channel];

    r1[channel] = b1 * inSample + (-a1) * y + r2[channel];
    r2[channel] = b2 * inSample + (-a2) * y;

    return y;
}

void Biquad_TDFII_APF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

void Biquad_TDFII_APF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

void Biquad_TDFII_APF::updateFilter()
{
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    b0 = 1.0f - alpha;
    b1 = -2.0f * cosf(w0);
    b2 = 1.0f + alpha;

    a0 = 1.0 + alpha;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha;

    // Normaliza los coeficientes dividiendo por a0
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}