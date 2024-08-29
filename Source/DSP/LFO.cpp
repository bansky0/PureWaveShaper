/*
  ==============================================================================

    LFO.cpp
    Created: 27 Aug 2024 10:39:40am
    Author:  Jhonatan

  ==============================================================================
*/

#include "LFO.h"


void LFO::setLFOValue(float inRateValue)
{
    frecuency = inRateValue;
}

void LFO::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);

    for (int i = 0; i < 2; i++)
    {
        time[i] = 0.0f;
        deltaTime[i] = 1.0f / sampleRate;
    }
}
void LFO::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            //y=0.5*sin(2*pi*ft)+0.5
            float sinValue = (0.5f * sinf(twoPi * frecuency * time[channel])) + 0.5f;

            float outSample = inSample * sinValue;

            buffer.setSample(channel, i, outSample);

            time[channel] += deltaTime[channel];

            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;
        }
    }
}

LFO::LFO()
{
}

LFO::~LFO()
{
}
