/*
  ==============================================================================

    Biquad_Peaking.cpp
    Created: 1 Oct 2024 12:25:55pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Biquad_Peaking.h"
Biquad_Peaking::Biquad_Peaking() {}

Biquad_Peaking::~Biquad_Peaking() {}

void Biquad_Peaking::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

void Biquad_Peaking::process(juce::AudioBuffer<float> inBuffer)
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

float Biquad_Peaking::processSample(float inSample, int channel)
{
    auto y = (b0 * inSample + b1 * x1[channel] + b2 * x2[channel] + (-a1) * y1[channel] + (-a2) * y2[channel]) * (1.0f / a0);

    x2[channel] = x1[channel];
    x1[channel] = inSample;
    y2[channel] = y1[channel];
    y1[channel] = y;

    return y;
}

void Biquad_Peaking::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

void Biquad_Peaking::setGain(float inGain)
{
    Gain = inGain;
    updateFilter();
}

void Biquad_Peaking::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

void Biquad_Peaking::updateFilter()
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
}