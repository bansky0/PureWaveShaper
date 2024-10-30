/*
  ==============================================================================

    Biquad_II_APF.cpp
    Created: 7 Oct 2024 11:58:53am
    Author:  Jhonatan

  ==============================================================================
*/

#include "Biquad_II_APF.h"

Biquad_II_APF::Biquad_II_APF()
{
}

Biquad_II_APF::~Biquad_II_APF()
{
}

void Biquad_II_APF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

void Biquad_II_APF::process(juce::AudioBuffer<float>& inBuffer)
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

float Biquad_II_APF::processSample(float inSample, int channel)
{
    auto w = inSample - a1 * w1[channel] - a2 * w2[channel];
    auto y = b0 * w + b1 * w1[channel] + b2 * w2[channel];

    w2[channel] = w1[channel];
    w1[channel] = w;

    return y;
}

void Biquad_II_APF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

void Biquad_II_APF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

void Biquad_II_APF::updateFilter()
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