/*
  ==============================================================================

    EchoFeedBackAndFordward2.cpp
    Created: 20 Sep 2024 1:29:43pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "EchoFeedBackAndFordward2.h"

void EchoFBF2::prepare(double theSampleRate, int totalNumChannels)
{
    sampleRate = theSampleRate;
    circularBufferInput.resize(circularBufferSize, std::vector<float>(totalNumChannels, 0.0f));
    circularBufferOutput.resize(circularBufferSize, std::vector<float>(totalNumChannels, 0.0f));

    // Inicializar los punteros
    for (int i = 0; i < numChannels; i++) 
    {
        writterPointerInput[i] = 0;
        writterPointerOutput[i] = 0;
    }
}

void EchoFBF2::setBPM(float BPM)
{
    float beatsPerMin = BPM;
    float beatsPerSec = beatsPerMin / 60.0f;
    float secPerBeat = 1.0f / beatsPerSec;
    float noteDiv = 1.0f; // Esto podría ser ajustable para diferentes subdivisiones
    auto timeSec = noteDiv * secPerBeat;

    delayM = static_cast<int>(std::floor(timeSec * sampleRate));
}

void EchoFBF2::setBPMOutput(float BPM)
{
    float beatsPerMin = BPM;
    float beatsPerSec = beatsPerMin / 60.0f;
    float secPerBeat = 1.0f / beatsPerSec;
    float noteDiv = 1.0f; // También podría ajustarse para diferentes subdivisiones
    auto timeSec = noteDiv * secPerBeat;

    delayW = static_cast<int>(std::floor(timeSec * sampleRate));
}

void EchoFBF2::setAmpFordward(float inAmpFordward)
{
    bM = inAmpFordward;  // bM en la ecuación
}

void EchoFBF2::setAmpFeedback(float inAmpFeedback)
{
    aW = inAmpFeedback;  // aW en la ecuación
}

void EchoFBF2::setFeedback(float inFeedback)
{
    feedback = inFeedback / 100.0f; // Configura el valor del feedback
}

void EchoFBF2::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            if (delayM >= 1 && delayW >= 1)
            {
                auto sampleInput = buffer.getReadPointer(channel)[i];
                
                // Lógica para el buffer circular de entrada (x[n - dM])
                int readerPointerInput = writterPointerInput[channel] - delayM;
                if (readerPointerInput < 0)
                    readerPointerInput += circularBufferSize;

                float delayedSampleInput = circularBufferInput[readerPointerInput][channel];
                
                // Lógica para el buffer circular de salida (y[n - dW])
                int readerPointerOutput = writterPointerOutput[channel] - delayW;
                if (readerPointerOutput < 0)
                    readerPointerOutput += circularBufferSize;

                float delayedSampleOutput = circularBufferOutput[readerPointerOutput][channel];
                
                // Aplicar la ecuación y[n] = b0 * x[n] + bM * x[n - dM] - aW * y[n - dW]
                float output = b0 * sampleInput + bM * delayedSampleInput - aW * delayedSampleOutput;

                // Guardar en el buffer circular de entrada y salida
                circularBufferInput[writterPointerInput[channel]][channel] = sampleInput + delayedSampleInput * feedback;
                circularBufferOutput[writterPointerOutput[channel]][channel] = output;

                // Avanzar los punteros de escritura
                writterPointerInput[channel]++;
                if (writterPointerInput[channel] >= circularBufferSize)
                    writterPointerInput[channel] = 0;
                 
                writterPointerOutput[channel]++;
                if (writterPointerOutput[channel] >= circularBufferSize)
                    writterPointerOutput[channel] = 0;

                // Escribir la salida procesada en el buffer
                buffer.getWritePointer(channel)[i] = output;                
            }
        }
    }
}

EchoFBF2::EchoFBF2()
{
}

EchoFBF2::~EchoFBF2()
{
}
