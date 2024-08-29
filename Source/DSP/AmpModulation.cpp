/*
  ==============================================================================

    AmpModulation.cpp
    Created: 27 Aug 2024 2:40:42pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "AmpModulation.h"

void AmpModulation::setDepth(float inDepthValue)
{
    depthValue = inDepthValue;
}

void AmpModulation::setSpeed(float inSpeedValue)
{
    speedValue = inSpeedValue;
}

void AmpModulation::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);

    for (int i = 0; i < 2; i++)
    {
        time[i] = 0.0f;
        deltTime[i] = 1.0f / sampleRate;
    }
}
void AmpModulation::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            
            float amplitud = 0.5f * (depthValue / 100.0f);
            float offset = 1.0f - amplitud;
            float phi = 0.0f;
            float f = speedValue;

            float sw = sinf(2.0f * pi * f * time[channel] + phi);

            float mod = (amplitud * sw) + offset;

            float outSample = inSample * mod;

            buffer.setSample(channel, i, outSample);

            time[channel] += deltTime[channel];

            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;
        }
    }
}

AmpModulation::AmpModulation()
{
}

AmpModulation::~AmpModulation()
{
}