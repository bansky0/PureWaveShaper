/*
  ==============================================================================

    Biquad_TDFII_HSF.cpp
    Created: 7 Oct 2024 4:02:12pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Biquad_TDFII_HSF.h"
Biquad_TDFII_HSF::Biquad_TDFII_HSF() {}

Biquad_TDFII_HSF::~Biquad_TDFII_HSF() {}

void Biquad_TDFII_HSF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

void Biquad_TDFII_HSF::process(juce::AudioBuffer<float> inBuffer)
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

float Biquad_TDFII_HSF::processSample(float inSample, int channel)
{
    auto y = b0 * inSample + r1[channel];

    r1[channel] = b1 * inSample + (-a1) * y + r2[channel];
    r2[channel] = b2 * inSample + (-a2) * y;

    return y;
}

void Biquad_TDFII_HSF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

void Biquad_TDFII_HSF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}
void Biquad_TDFII_HSF::setGain(float inGain)
{
    Gain = inGain;
    updateFilter();
}
void Biquad_TDFII_HSF::updateFilter()
{
    //calcular componente
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);
    A = sqrt(powf(10.0f, Gain / 20.0f));

    b0 = A * ((A + 1.0f) + ((A - 1.0f) * cosf(w0)) + (2.0f * sqrtf(A) * alpha));
    b1 = -2.0f * A * ((A - 1.0f) + ((A + 1.0f) * cosf(w0)));
    b2 = A * ((A + 1.0f) + ((A - 1.0f) * cosf(w0)) - (2.0f * sqrtf(A) * alpha));

    a0 = (A + 1.0f) - ((A - 1.0f) * cosf(w0)) + (2.0f * sqrtf(A) * alpha);
    a1 = 2.0f * ((A - 1.0f) - ((A + 1.0f) * cosf(w0)));
    a2 = (A + 1.0f) - ((A - 1.0f) * cosf(w0)) - (2.0f * sqrtf(A) * alpha);
    // Normaliza los coeficientes dividiendo por a0
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}
