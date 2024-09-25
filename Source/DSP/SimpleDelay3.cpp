/*
  ==============================================================================

    SimpleDelay3.cpp
    Created: 19 Sep 2024 1:00:10pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "SimpleDelay3.h"

void SimpleDelay3::prepare(double theSampleRate, int samplesPerBlock, juce::dsp::ProcessSpec& spec, int numChannels)
{
    spec.sampleRate = theSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = numChannels;

    myDelay.reset();
    myDelay.prepare(spec);
    myDelay.setDelay(48000);
    //myDelay.setMaximumDelayInSamples(96000);

    sampleRate = theSampleRate;
}

void SimpleDelay3::setTimeDelay(float delayTime)
{
    delay = static_cast<int>(std::floor(delayTime * sampleRate));
    myDelay.setDelay(delay);
    DBG(delay);
}


void SimpleDelay3::process(juce::AudioBuffer<float>& buffer)
{

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        auto* inSamples = buffer.getReadPointer(channel);
        auto* outSamples = buffer.getWritePointer(channel);

        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float delayedSample = myDelay.popSample(channel);
            //float inDelay = inSamples[i] + (0.75 * delayedSample);
            myDelay.pushSample(channel, inSamples[i]);
            outSamples[i] = inSamples[i] + delayedSample;
        }
    }
}


SimpleDelay3::SimpleDelay3()
{
}

SimpleDelay3::~SimpleDelay3()
{
}