/*
  ==============================================================================

    Biquad_II_HSF.cpp
    Created: 7 Oct 2024 11:59:38am
    Author:  Jhonatan

  ==============================================================================
*/

#include "Biquad_II_HSF.h"
Biquad_II_HSF::Biquad_II_HSF() {}

Biquad_II_HSF::~Biquad_II_HSF() {}

void Biquad_II_HSF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

void Biquad_II_HSF::process(juce::AudioBuffer<float> inBuffer)
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

float Biquad_II_HSF::processSample(float inSample, int channel)
{
    auto w = inSample - a1 * w1[channel] - a2 * w2[channel];
    auto y = b0 * w + b1 * w1[channel] + b2 * w2[channel];

    w2[channel] = w1[channel];
    w1[channel] = w;

    return y;
}

void Biquad_II_HSF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

void Biquad_II_HSF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}
void Biquad_II_HSF::setGain(float inGain)
{
    Gain = inGain;
    updateFilter();
}
void Biquad_II_HSF::updateFilter()
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
