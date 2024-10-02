/*
  ==============================================================================

    Biquad_HSF.cpp
    Created: 1 Oct 2024 12:26:59pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "Biquad_HSF.h"
Biquad_HSF::Biquad_HSF() {}

Biquad_HSF::~Biquad_HSF() {}

void Biquad_HSF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

void Biquad_HSF::process(juce::AudioBuffer<float> inBuffer)
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

float Biquad_HSF::processSample(float inSample, int channel)
{
    auto y = (b0 * inSample + b1 * x1[channel] + b2 * x2[channel] + (-a1) * y1[channel] + (-a2) * y2[channel]) * (1.0f / a0);

    x2[channel] = x1[channel];
    x1[channel] = inSample;
    y2[channel] = y1[channel];
    y1[channel] = y;

    return y;
}

void Biquad_HSF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

void Biquad_HSF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}
void Biquad_HSF::setGain(float inGain)
{
    Gain = inGain;
    updateFilter();
}
void Biquad_HSF::updateFilter()
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
}
