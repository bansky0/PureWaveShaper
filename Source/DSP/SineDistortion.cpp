/*
  ==============================================================================

    SineDistortion.cpp
    Created: 2 Sep 2024 11:03:13pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "SineDistortion.h"

void SineDistortion::setSineDistortionValue(float inSineDistortionValue)
{
    distortion = inSineDistortionValue;
}

void SineDistortion::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            float outSample = 0.0f;

            outSample = sinf(0.5f * pi * inSample * distortion);

            buffer.setSample(channel, i, outSample);
        }
    }
}

SineDistortion::SineDistortion()
{
}

SineDistortion::~SineDistortion()
{
}