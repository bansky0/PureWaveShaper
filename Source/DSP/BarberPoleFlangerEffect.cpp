/*
  ==============================================================================

    BarberPoleFeedback.cpp
    Created: 5 Nov 2024 8:29:25am
    Author:  Jhonatan

  ==============================================================================
*/

#include "BarberpoleFlangerEffect.h"

void BarberpoleFlangerFX::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);
    t = 0.0f;
    ratePercentage = 0.0f;
    targetRatePercentage = 0.0f;
    predelay = 0.0f; // Inicializar el predelay
}

void BarberpoleFlangerFX::setDepth(float inDepth)
{
    depth = inDepth;
}

void BarberpoleFlangerFX::setRate(float inRatePercentage)
{
    targetRatePercentage = juce::jlimit(0.0f, 100.0f, inRatePercentage) / 100.0f;
}

void BarberpoleFlangerFX::setPredelay(float inPredelayMs)
{
    predelay = inPredelayMs * sampleRate / 1000.0f; // Convertir ms a samples
}

float BarberpoleFlangerFX::generateSawtooth(float phase)
{
    return 2.0f * (phase - floorf(phase + 0.5f));
}

void BarberpoleFlangerFX::process(juce::AudioBuffer<float>& buffer)
{
    float old_t = t;
    const float minRateHz = 0.1f;
    const float maxRateHz = 10.0f;

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        t = old_t;
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            auto sample = buffer.getReadPointer(channel)[i];
            ratePercentage = targetRatePercentage;
            float rateHz = minRateHz + ratePercentage * (maxRateHz - minRateHz);
            float phase = rateHz * t;
            float lfoValue = depth * generateSawtooth(phase) + predelay;
            float fracDelay = static_cast<float>(writterPointer[channel]) - lfoValue;
            if (fracDelay < 0) fracDelay += circularBufferSize;

            int intDelay = static_cast<int>(fracDelay);
            float frac = fracDelay - intDelay;
            int nextSampleIndex = intDelay + 1;
            if (nextSampleIndex >= circularBufferSize) nextSampleIndex = 0;

            float delayedSample = (1.0f - frac) * circularBuffer[intDelay][channel] + frac * circularBuffer[nextSampleIndex][channel];
            circularBuffer[writterPointer[channel]][channel] = sample;
            writterPointer[channel]++;
            if (writterPointer[channel] >= circularBufferSize) writterPointer[channel] = 0;

            buffer.getWritePointer(channel)[i] = delayedSample;
            t += 1.0f / sampleRate;
        }
    }
}

BarberpoleFlangerFX::BarberpoleFlangerFX() {}
BarberpoleFlangerFX::~BarberpoleFlangerFX() {}