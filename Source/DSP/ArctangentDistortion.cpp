/*
  ==============================================================================

    ArctangentDistortion.cpp
    Created: 2 Sep 2024 10:08:57pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "ArctangentDistortion.h"
void ArctangentDistortion::setArctangentDistortionDrive(float inArctangentDistortionDriveValue)
{
    alpha = inArctangentDistortionDriveValue;
}

void ArctangentDistortion::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            float outSample = 0.0f;

            outSample = (2.0f / pi) * atanf(inSample * alpha);

            buffer.setSample(channel, i, outSample);
        }
    }
}

ArctangentDistortion::ArctangentDistortion()
{
}

ArctangentDistortion::~ArctangentDistortion()
{
}