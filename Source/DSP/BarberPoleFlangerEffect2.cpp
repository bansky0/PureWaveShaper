/*
  ==============================================================================

    BarberPoleFlangerEffect2.cpp
    Created: 5 Nov 2024 9:52:36am
    Author:  Jhonatan

  ==============================================================================
*/

#include "BarberPoleFlangerEffect2.h"

void BarberpoleFlanger2FX::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);
    t = 0.0f;
    ratePercentage = 0.0f;
    targetRatePercentage = 0.0f;
    predelay = 0.0f; // Inicializar el predelay
}

void BarberpoleFlanger2FX::setDepth(float inDepth)
{
    depth = inDepth;
}

void BarberpoleFlanger2FX::setRate(float inRatePercentage)
{
    targetRatePercentage = juce::jlimit(0.0f, 100.0f, inRatePercentage) / 100.0f;
}

void BarberpoleFlanger2FX::setPredelay(float inPredelayMs)
{
    predelay = inPredelayMs * sampleRate / 1000.0f; // Convertir ms a samples
}

float BarberpoleFlanger2FX::generateSawtooth(float phase)
{
    return 2.0f * (phase - floorf(phase + 0.5f));
}

void BarberpoleFlanger2FX::process(juce::AudioBuffer<float>& buffer)
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
            float lfoValue1 = depth * generateSawtooth(phase) + predelay;
            float lfoValue2 = depth * generateSawtooth(phase + juce::MathConstants<float>::pi) + predelay;

            float fracDelay1 = static_cast<float>(writterPointer1[channel]) - lfoValue1;
            float fracDelay2 = static_cast<float>(writterPointer2[channel]) - lfoValue2;

            if (fracDelay1 < 0) fracDelay1 += circularBufferSize;
            if (fracDelay2 < 0) fracDelay2 += circularBufferSize;

            int intDelay1 = static_cast<int>(fracDelay1);
            int intDelay2 = static_cast<int>(fracDelay2);
            float frac1 = fracDelay1 - intDelay1;
            float frac2 = fracDelay2 - intDelay2;

            int nextSampleIndex1 = intDelay1 + 1;
            int nextSampleIndex2 = intDelay2 + 1;

            if (nextSampleIndex1 >= circularBufferSize) nextSampleIndex1 = 0;
            if (nextSampleIndex2 >= circularBufferSize) nextSampleIndex2 = 0;

            float delayedSample1 = (1.0f - frac1) * circularBuffer1[intDelay1][channel] + frac1 * circularBuffer1[nextSampleIndex1][channel];
            float delayedSample2 = (1.0f - frac2) * circularBuffer2[intDelay2][channel] + frac2 * circularBuffer2[nextSampleIndex2][channel];

            // Almacenar la muestra actual en los buffers circulares
            circularBuffer1[writterPointer1[channel]][channel] = sample;
            circularBuffer2[writterPointer2[channel]][channel] = sample;

            writterPointer1[channel]++;
            if (writterPointer1[channel] >= circularBufferSize) writterPointer1[channel] = 0;

            writterPointer2[channel]++;
            if (writterPointer2[channel] >= circularBufferSize) writterPointer2[channel] = 0;

            // Calcular la muestra de salida combinada utilizando la interpolación
            float outputSample = crossfade1[channel] * delayedSample1 + crossfade2[channel] * delayedSample2;

            // Escribir la muestra de salida en el buffer
            buffer.getWritePointer(channel)[i] = outputSample;

            // Incrementar el tiempo
            t += 1.0f / sampleRate;
        }
    }
}

BarberpoleFlanger2FX::BarberpoleFlanger2FX() {}
BarberpoleFlanger2FX::~BarberpoleFlanger2FX() {}
