/*
  ==============================================================================

    CubicDistortion.cpp
    Created: 2 Sep 2024 9:17:07pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "CubicDistortion.h"

void CubicDistortion::setCubicDistortionDrive(float inCubicDistortionDriveValue)
{
    drive = inCubicDistortionDriveValue;
}

void CubicDistortion::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            float outSample = 0.0f;
            
            outSample = inSample - (drive * (powf(inSample,3.0f))/3.0f);

            buffer.setSample(channel, i, outSample);
        }
    }
}

CubicDistortion::CubicDistortion()
{
}

CubicDistortion::~CubicDistortion()
{
}