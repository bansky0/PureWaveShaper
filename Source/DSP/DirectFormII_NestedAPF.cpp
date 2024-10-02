/*
  ==============================================================================

    DirectFormII_NestedAPF.cpp
    Created: 2 Oct 2024 4:44:56pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "DirectFormII_NestedAPF.h"

DirectFormII_NestedAPF::DirectFormII_NestedAPF()
{
}

DirectFormII_NestedAPF::~DirectFormII_NestedAPF()
{
}

void DirectFormII_NestedAPF::process(juce::AudioBuffer<float>& inBuffer)
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

float DirectFormII_NestedAPF::processSample(float inSample, int channel)
{
    auto w1 = inSample + (-g1 * prevW2[channel]);
    auto w2 = prevW1[channel];
    auto v = w2 + (-g2 * prevV[channel]);
    auto y = g2 * prevV[channel] + inSample;
    
    prevW1[channel] = w1;
    prevW2[channel] = w2;
    prevV[channel] = v;

    return y;
}
void DirectFormII_NestedAPF::setG(float inG1, float inG2)
{
    g1 = inG1;
    g2 = inG2;
}