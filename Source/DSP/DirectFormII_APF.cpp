/*
  ==============================================================================

    DirectFormII_APF.cpp
    Created: 2 Oct 2024 11:20:47am
    Author:  Jhonatan

  ==============================================================================
*/

#include "DirectFormII_APF.h"
DirectFormII_APF::DirectFormII_APF()
{
}

DirectFormII_APF::~DirectFormII_APF()
{
}

void DirectFormII_APF::process(juce::AudioBuffer<float>& inBuffer)
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

float DirectFormII_APF::processSample(float inSample, int channel)
{
    auto y = g * inSample + (-g) * y1[channel] + x1[channel];

    x1[channel] = inSample;
    y1[channel] = y;

    return y;
}
void DirectFormII_APF::setG(float inG)
{
    g = inG;
}