/*
  ==============================================================================

    SlewRateDistortion.cpp
    Created: 8 Oct 2024 3:00:37pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "SlewRateDistortion.h"

SlewRateDistortion::SlewRateDistortion()
{
}

SlewRateDistortion::~SlewRateDistortion()
{
}

void SlewRateDistortion::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    Ts = 1.0 / sampleRate;
}
void SlewRateDistortion::process(juce::AudioBuffer<float>& buffer)
{
    int numChannels = buffer.getNumChannels();
    int numSamples = buffer.getNumSamples();

    for (int channel = 0; channel < numChannels; channel++)
    {
        for (int i = 0; i < numSamples; i++)
        {
            float inSample = buffer.getSample(channel, i);

            float outSample = processSample(inSample, channel);

            buffer.setSample(channel, i, outSample);
        }
    }
}

float SlewRateDistortion::processSample(float inSample, int channel)
{
    delta[channel] = inSample - y1[channel];

    if (delta[channel] > slope)
    {
        delta[channel] = slope;
    }
    else if (delta[channel] < -slope)
    {
        delta[channel] = -slope;
    }

    auto y = y1[channel] + delta[channel];


    y1[channel] = inSample;

    return y;
}


void SlewRateDistortion::setMaxFreq(float inMaxFreq)
{
    maxFreq = inMaxFreq;
    updateSlewRate();
}

void SlewRateDistortion::updateSlewRate()
{
    slewRate = maxFreq * 2.0 * juce::MathConstants<double>::pi * peak;
    slope = slewRate * Ts;
}