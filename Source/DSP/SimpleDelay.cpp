/*
  ==============================================================================

    SimpleDelay.cpp
    Created: 17 Sep 2024 1:08:03pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "SimpleDelay.h"
void SimpleDelay::prepare(double theSampleRate)
{
    sampleRate = theSampleRate;
}

void SimpleDelay::setDelay(float inDelay)
{
    //delay = delayTime; //se debe cambair si quiero que el valor de entrada sea mi samplerate.
    delay = static_cast<int>(std::floor(inDelay * sampleRate));
   // auto delay2 = delayTime * sampleRate;
    //DBG(inDelay);
}

void SimpleDelay::process(juce::AudioBuffer<float>& buffer)
{
    auto outputCircularBuffer = 0.0f;

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            if (delay >= 1)
            {
                auto sample = buffer.getReadPointer(channel)[i];
                
                readerPointer = writterPointer[channel] - delay;
                if (readerPointer < 0)
                {
                    readerPointer += circularBufferSize;
                }
                outputCircularBuffer = circularBuffer[readerPointer][channel];

                circularBuffer[writterPointer[channel]][channel] = sample;

                writterPointer[channel]++;
                if (writterPointer[channel] >= circularBufferSize)
                {
                    writterPointer[channel] = 0;    
                }
                auto out = sample + outputCircularBuffer;

                buffer.getWritePointer(channel)[i] = out;
            }
        }
    }
}


SimpleDelay::SimpleDelay()
{
}

SimpleDelay::~SimpleDelay()
{
}