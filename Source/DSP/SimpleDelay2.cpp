/*
  ==============================================================================

    SimpleDelay2.cpp
    Created: 17 Sep 2024 3:41:36pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "SimpleDelay2.h"
void SimpleDelay2::prepare(double theSampleRate)
{
    sampleRate = theSampleRate;
}

void  SimpleDelay2::setBPM(float BPM)
{
    float beatsPerMin = BPM;
    float beatsPerSec = beatsPerMin / 60;
    float secPerBeat = 1 / beatsPerSec;
    float noteDiv = 1;
    auto timeSec = noteDiv * secPerBeat;
    delay = static_cast<int>(std::floor(timeSec * sampleRate));
}

void SimpleDelay2::setAmpDelay(float inAmpDelay)
{
    ampDelay = inAmpDelay;
}

void SimpleDelay2::setFeedback(float inFeedback)
{
    feedback = inFeedback/100.0f; // Configura el valor del feedback
}

void SimpleDelay2::process(juce::AudioBuffer<float>& buffer)
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

                circularBuffer[writterPointer[channel]][channel] = sample + (outputCircularBuffer * feedback); //Eliminar feedback y outputcircu;ar buffersi se quiere fordward

                writterPointer[channel]++;
                if (writterPointer[channel] >= circularBufferSize)
                {
                    writterPointer[channel] = 0;
                }
                auto out = sample - (outputCircularBuffer * ampDelay);// cambair signo a + fordward.

                buffer.getWritePointer(channel)[i] = out;
            }
        }
    }
}


SimpleDelay2::SimpleDelay2()
{
}

SimpleDelay2::~SimpleDelay2()
{
}