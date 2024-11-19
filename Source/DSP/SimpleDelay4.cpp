/*
  ==============================================================================

    SimpleDelay4.cpp
    Created: 14 Nov 2024 1:48:52pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "SimpleDelay4.h"

SimpleDelay4::SimpleDelay4(){}

SimpleDelay4::~SimpleDelay4(){}

void SimpleDelay4::prepare(double theSampleRate)
{
    sampleRate = theSampleRate;
}
void SimpleDelay4::setDelay(float newDelayInSamples)
{
    delay = std::floor(newDelayInSamples * sampleRate);
    delayInt = static_cast<int>(delay);            // Parte entera
    delayFrac = delay - delayInt;                  // Parte fraccional
}

void SimpleDelay4::pushSample(int channel, float sample)
{
    if (channel >= 0 && channel < buffer.size())  // Asegura que el canal está dentro de los límites
    {
        buffer[channel][writeIndex[channel]] = sample;  // Escribe en el buffer correspondiente
        writeIndex[channel] = (writeIndex[channel] + 1) % maxDelaySamples; // Avanza el índice
    }
}

float SimpleDelay4::popSample(int channel)
{
    if (channel >= 0 && channel < buffer.size())  // Asegura que el canal está dentro de los límites
    {
        int readIndex1 = (writeIndex[channel] - delayInt + maxDelaySamples) % maxDelaySamples; // Índice de lectura 1
        int readIndex2 = (readIndex1 + 1) % maxDelaySamples; // Índice de lectura 2 para interpolación

        // Interpolación lineal entre los dos valores
        return (1.0f - delayFrac) * buffer[channel][readIndex1] + delayFrac * buffer[channel][readIndex2];
    }
    return 0.0f;  // Si el canal no es válido, retorna 0
}

void SimpleDelay4::process(juce::AudioBuffer<float>& inputBuffer)
{
    const int numChannels = inputBuffer.getNumChannels();
    const int numSamples = inputBuffer.getNumSamples();

    // Asegura que el número de buffers es igual al número de canales
    if (buffer.size() != numChannels)
    {
        buffer.resize(numChannels, std::vector<float>(maxDelaySamples, 0.0f)); // Redimensiona el buffer
        writeIndex.resize(numChannels, 0);  // Redimensiona los índices de escritura
    }

    // Procesa cada canal de manera independiente
    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto* channelData = inputBuffer.getWritePointer(channel);
        for (int i = 0; i < numSamples; ++i)
        {
            float inputSample = channelData[i];
            pushSample(channel, inputSample); // Inserta el sample en el buffer de delay del canal
            float delayedSample = popSample(channel); // Obtiene el sample con delay
            channelData[i] = delayedSample; // Sustituye el sample original por el sample con delay
        }
    }
}