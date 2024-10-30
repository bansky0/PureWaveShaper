/*
  ==============================================================================

    Biquad_II_Peaking.cpp
    Created: 7 Oct 2024 2:37:56pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Biquad_II_Peaking.h"
Biquad_II_Peaking::Biquad_II_Peaking() {}

Biquad_II_Peaking::~Biquad_II_Peaking() {}

void Biquad_II_Peaking::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

void Biquad_II_Peaking::process(juce::AudioBuffer<float> inBuffer)
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

float Biquad_II_Peaking::processSample(float inSample, int channel)
{
    auto w = inSample - a1 * w1[channel] - a2 * w2[channel];
    auto y = b0 * w + b1 * w1[channel] + b2 * w2[channel];

    w2[channel] = w1[channel];
    w1[channel] = w;

    return y;
}

void Biquad_II_Peaking::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

void Biquad_II_Peaking::setGain(float inGain)
{
    Gain = inGain;
    updateFilter();
}

void Biquad_II_Peaking::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

void Biquad_II_Peaking::updateFilter()
{
    //calcular componente
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);
    A = sqrt(powf(10.0f, Gain / 20.0f));

    b0 = 1.0f + alpha * A;
    b1 = -2.0f * cosf(w0);
    b2 = 1.0f - alpha * A;

    a0 = 1.0 + alpha / A;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha / A;

    // Normaliza los coeficientes dividiendo por a0
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}