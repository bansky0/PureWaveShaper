/*
  ==============================================================================

    ExponentialDistortion.cpp
    Created: 3 Sep 2024 12:32:28pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "ExponentialDistortion.h"

void ExponentialDistortion::setExponentialDistortionValue(float inExponentialDistortionValue)
{
    gain = inExponentialDistortionValue;
}

void ExponentialDistortion::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            float processedSample = 0.0f;
            float outSample = 0.0f;
            
            if (inSample >= 0.0f)
            {
                processedSample = (1 - expf(-fabs(gain * inSample)));
            }
            else if (inSample<0.0f)
            {
                processedSample = -(1 - expf(-fabs(gain * inSample)));
            }
            
            outSample =  processedSample;

            buffer.setSample(channel, i, outSample);
        }
    }
}

ExponentialDistortion::ExponentialDistortion()
{
}

ExponentialDistortion::~ExponentialDistortion()
{
}