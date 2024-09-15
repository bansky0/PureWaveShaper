/*
  ==============================================================================

    WetDry.cpp
    Created: 5 Sep 2024 10:20:06am
    Author:  Jhonatan

  ==============================================================================
*/

#include "WetDry.h"
void WetDry::setDryWet(float inDryWetValue)
{
    dryWet = inDryWetValue/100.0f;
}

void WetDry::process(juce::AudioBuffer<float>& dryBuffer,
                     juce::AudioBuffer<float>& wetBuffer)
{
    for (int channel = 0; channel < dryBuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < dryBuffer.getNumSamples(); i++)
        {
            float wetSample = wetBuffer.getSample(channel,i);
            float drySample = dryBuffer.getSample(channel,i);

            float outSample = drySample * (1.0f - dryWet) + (wetSample * dryWet); //g * dist + (1–g) * in;
            
            wetBuffer.setSample(channel, i, outSample);
        }
    }
}

WetDry::WetDry()
{
}

WetDry::~WetDry()
{
}