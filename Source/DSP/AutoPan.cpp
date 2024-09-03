/*
  ==============================================================================

    AutoPan.cpp
    Created: 30 Aug 2024 12:13:48pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "AutoPan.h"
void AutoPan::setDepth(float inDepthValue)
{
    depthValue = inDepthValue;//(inDepthValue / 200.0f) + 0.5;

}
void AutoPan::setSpeed(float inSpeedValue)
{
    speedValue = inSpeedValue;

}
void AutoPan::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);

    for (int i = 0; i < 2; i++)
    {
        time[i] = 0.0f;
        deltTime[i] = 1.0f / sampleRate;
    }
}
void AutoPan::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);

            float amplitud = 0.5f * (depthValue / 100.0f);
            float offset = 1.0f - amplitud;
            float phi = 0.0f;
            float f = speedValue;

            float sw = sinf(2.0f * pi * f * time[channel] + phi); //100 * sinf(2 * pi * f * time[channel]);

            float mod = (amplitud * sw) + offset;


            // Process left channel
            if (channel == 0)
            {
                sample *= powf(1 - mod, 0.75f);
            }
            //Process right channel
            else
            {
                sample *= powf(mod, 0.75f);
            }

            buffer.setSample(channel, i, sample);

            time[channel] += deltTime[channel];

            if (time[channel] >= 1.0f)
                time[channel] = 0.0f;
        }
    }
}

AutoPan::AutoPan()
{
}

AutoPan::~AutoPan()
{
}