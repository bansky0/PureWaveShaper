/*
  ==============================================================================

    PiceWiseOverdrive.cpp
    Created: 3 Sep 2024 1:43:52pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "PiceWiseOverdrive.h"

//void PiceWiseOverdrive::setPiceWiseOverdriveValue(float inPiceWiseOverdriveValue)
//{
//
//}

void PiceWiseOverdrive::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float inSample = buffer.getSample(channel, i);
            float absValue = std::abs(inSample);
            float processedSample = 0.0f;
            float outSample = 0.0f;

            if (absValue <= 1.0f/3.0f)
            {
                processedSample = 2.0f * inSample;
            }
            else if (absValue > 2.0f / 3.0f)
            {
                processedSample = inSample>= 0.0f ? 1.0f : -1.0f;
            }
            else
            {
                float signValue = inSample >= 0.0f ? 1.0f : -1.0f;
                processedSample = signValue * (3.0f - std::pow(2.0f - 3.0f * absValue, 2)) / 3.0f;
                    //inSample * (3.0f - powf((2.0f - 3.0f * fabs(inSample)), 2.0f) / (3.0f * fabs(inSample)));
            }

            outSample = processedSample;

            buffer.setSample(channel, i, outSample);
        }
    }
}

PiceWiseOverdrive::PiceWiseOverdrive()
{
}

PiceWiseOverdrive::~PiceWiseOverdrive()
{
}