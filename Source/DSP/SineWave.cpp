/*
  ==============================================================================

    SineWave.cpp
    Created: 28 Aug 2024 11:32:36am
    Author:  Jhonatan

  ==============================================================================
*/

#include "SineWave.h"

void SineWave::setFrequency(double inFrequecy)
{
    frequency = inFrequecy;
}

void SineWave::setPhase(double setPhase)
{
    phi = setPhase;
}

void SineWave::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);

    for (int i = 0; i < 2; i++)
    {
        time[i] = 0.0f;
        deltaTime[i] = 1.0f / sampleRate;
    }
}

void SineWave::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float outSample = sinf(twoPi * frequency * time[channel] + phi);

            buffer.setSample(channel, i, outSample);

            time[channel] += deltaTime[channel];
            
            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;
        }
    }
}

SineWave::SineWave()
{
}

SineWave::~SineWave()
{
}