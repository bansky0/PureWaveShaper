/*
  ==============================================================================

    EchoFeedBackAndFordward.cpp
    Created: 19 Sep 2024 11:16:08am
    Author:  Jhonatan

  ==============================================================================
*/

#include "EchoFeedBackAndFordward.h"
void EchoFBF::prepare(double theSampleRate)
{
    sampleRate = theSampleRate;
}

void  EchoFBF::setBPM(float BPM)
{
    float beatsPerMin = BPM;
    float beatsPerSec = beatsPerMin / 60;
    float secPerBeat = 1 / beatsPerSec;
    float noteDiv = 1;
    auto timeSec = noteDiv * secPerBeat;
    delay = static_cast<int>(std::floor(timeSec * sampleRate));
}

void EchoFBF::setAmpFordward(float inAmpFordward)
{
    bM = inAmpFordward;
}

void EchoFBF::setAmpFeedback(float inAmpFeedback)
{
    aW = inAmpFeedback;
}

void EchoFBF::process(juce::AudioBuffer<float>& buffer)
{
    auto outputCircularBuffer = 0.0f;

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            if (delay >= 1)
            {
                auto currentSample = buffer.getReadPointer(channel)[i];

                // Obtener la posición para x[n - dM] (entrada retrasada)
                int readerPointerInput = writterPointer[channel] - delay;
                if (readerPointerInput < 0)
                {
                    readerPointerInput += circularBufferSize;
                }
                float delayedInputSample = circularBuffer[readerPointerInput][channel];  // x[n - dM]

                // Obtener la posición para y[n - dW] (salida retrasada)
                int readerPointerOutput = writterPointer[channel] - (delay/2);
                if (readerPointerOutput < 0)
                {
                    readerPointerOutput += circularBufferSize;
                }
                float delayedOutputSample = circularBuffer[readerPointerOutput][channel]; // y[n - dW]

                // Aplicar la fórmula:
                // y[n] = b0⋅x[n] + bM⋅x[n−dM] − aW⋅y[n−dW]
                float outputSample = b0 * currentSample +
                    bM * delayedInputSample -
                    aW * delayedOutputSample;

                // Guardar la salida en el buffer circular
                circularBuffer[writterPointer[channel]][channel] = outputSample;

                writterPointer[channel]++;
                if (writterPointer[channel] >= circularBufferSize)
                {
                    writterPointer[channel] = 0;
                }

                // Escribir la salida en el buffer de audio
                buffer.getWritePointer(channel)[i] = outputSample;
            }
        }
    }
}


EchoFBF::EchoFBF()
{
}

EchoFBF::~EchoFBF()
{
}