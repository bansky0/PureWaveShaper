/*
  ==============================================================================

    Biquad_TDFII_Peaking.cpp
    Created: 7 Oct 2024 4:02:59pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Biquad_TDFII_Peaking.h"

Biquad_TDFII_Peaking::Biquad_TDFII_Peaking() {}

Biquad_TDFII_Peaking::~Biquad_TDFII_Peaking() {}

void Biquad_TDFII_Peaking::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

void Biquad_TDFII_Peaking::process(juce::AudioBuffer<float> inBuffer)
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

float Biquad_TDFII_Peaking::processSample(float inSample, int channel)
{
    auto y = b0 * inSample + r1[channel];

    r1[channel] = b1 * inSample + (-a1) * y + r2[channel];
    r2[channel] = b2 * inSample + (-a2) * y;

    return y;
}

void Biquad_TDFII_Peaking::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

void Biquad_TDFII_Peaking::setGain(float inGain)
{
    Gain = inGain;
    updateFilter();
}

void Biquad_TDFII_Peaking::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

void Biquad_TDFII_Peaking::updateFilter()
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