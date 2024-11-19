/*
  ==============================================================================

    ModulatedDelay.cpp
    Created: 13 Nov 2024 3:29:42pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "ModulatedDelay.h"

ModulatedDelay::ModulatedDelay()
{
}

ModulatedDelay::~ModulatedDelay()
{
}
void ModulatedDelay::prepare(double theSampleRate)
{
    sampleRate = theSampleRate;
}
void ModulatedDelay::setDelay(float newDelayInSamples)
{
    delay = std::floor(newDelayInSamples * sampleRate);
    delayInt = static_cast<int>(delay);            // Parte entera
    delayFrac = delay - delayInt;                  // Parte fraccional
}

void ModulatedDelay::pushSample(int channel, float sample)
{
    if (channel >= 0 && channel < buffer.size())  // Asegura que el canal est� dentro de los l�mites
    {
        buffer[channel][writeIndex[channel]] = sample;  // Escribe en el buffer correspondiente
        writeIndex[channel] = (writeIndex[channel] + 1) % maxDelaySamples; // Avanza el �ndice
    }
}

float ModulatedDelay::popSample(int channel)
{
    if (channel >= 0 && channel < buffer.size())  // Asegura que el canal est� dentro de los l�mites
    {
        int readIndex1 = (writeIndex[channel] - delayInt + maxDelaySamples) % maxDelaySamples; // �ndice de lectura 1
        int readIndex2 = (readIndex1 + 1) % maxDelaySamples; // �ndice de lectura 2 para interpolaci�n

        // Interpolaci�n lineal entre los dos valores
        return (1.0f - delayFrac) * buffer[channel][readIndex1] + delayFrac * buffer[channel][readIndex2];
    }
    return 0.0f;  // Si el canal no es v�lido, retorna 0
}

void ModulatedDelay::process(juce::AudioBuffer<float>& inputBuffer)
{
    const int numChannels = inputBuffer.getNumChannels();
    const int numSamples = inputBuffer.getNumSamples();

    // Asegura que el n�mero de buffers es igual al n�mero de canales
    if (buffer.size() != numChannels)
    {
        buffer.resize(numChannels, std::vector<float>(maxDelaySamples, 0.0f)); // Redimensiona el buffer
        writeIndex.resize(numChannels, 0);  // Redimensiona los �ndices de escritura
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