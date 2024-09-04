/*
  ==============================================================================

    BitReduction.cpp
    Created: 4 Sep 2024 10:39:47am
    Author:  Jhonatan

  ==============================================================================
*/

#include "BitReduction.h"

void BitReduction::setBitNumberValue(float inBitNumberValue)
{
    bitNumber= inBitNumberValue;
}

void BitReduction::process(juce::AudioBuffer<float>& buffer)
{
    float ampValue = powf(2.0f, bitNumber);
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            float preIn = 0.5f * inSample + 0.5f;
            float scaleIn = ampValue * preIn;
            float roundIn = roundf(scaleIn);
            float preOut = roundIn / ampValue;
            float outSample = 2.0 * preOut - 1;
            buffer.setSample(channel, i, outSample);
        }
    }
}

BitReduction::BitReduction()
{
}

BitReduction::~BitReduction()
{
}