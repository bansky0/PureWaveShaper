/*
  ==============================================================================

    DiodeClipping.cpp
    Created: 3 Sep 2024 4:46:15pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "DiodeClipping.h"

void DiodeClipping::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            float processedSample = 0.0f;
            float outSample = 0.0f;

            processedSample = Is*(expf((0.1*inSample)/(eta*Vt))-1);

            outSample = processedSample;

            buffer.setSample(channel, i, outSample);
        }
    }
}

DiodeClipping::DiodeClipping()
{
}

DiodeClipping::~DiodeClipping()
{
}