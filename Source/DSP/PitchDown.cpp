/*
  ==============================================================================

    PitchDown.cpp
    Created: 5 Nov 2024 1:03:19pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "PitchDown.h"

void PitchDown::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);
    delay = 0.0f;
    writePosition = 0;

    // Limpiar el buffer de retardo
    std::fill(std::begin(delayBuffer), std::end(delayBuffer), 0.0f);
}

void PitchDown::process(juce::AudioBuffer<float>& buffer)
{
    int numSamples = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels();

    for (int i = 0; i < numSamples; ++i)
    {
        // Calcular delay para esta muestra
        int intDelay = static_cast<int>(floor(delay));       // Parte entera del retardo
        float frac = delay - intDelay;                       // Parte fraccionaria del retardo
        int readPosition = writePosition - intDelay;         // Posición de lectura en el buffer

        // Ajustar readPosition para manejar el buffer circular
        if (readPosition < 0)
            readPosition += bufferSize;

        int nextSampleIndex = (readPosition + 1) % bufferSize;

        for (int channel = 0; channel < numChannels; ++channel)
        {
            float* channelData = buffer.getWritePointer(channel);

            // Interpolación lineal para obtener la muestra con pitch-down
            float delayedSample = (1.0f - frac) * delayBuffer[readPosition] + frac * delayBuffer[nextSampleIndex];

            // Almacenar la muestra actual en el buffer de retardo
            delayBuffer[writePosition] = channelData[i];

            // Escribir la muestra de salida con pitch-down en el canal actual
            channelData[i] = delayedSample;
        }

        // Incrementar el retardo para disminuir el tono
        delay += 0.5f;

        // Mantener el tamaño del retardo en los límites del buffer circular
        if (delay > bufferSize - 1)
            delay -= bufferSize;

        // Actualizar el puntero de escritura de forma circular
        writePosition = (writePosition + 1) % bufferSize;
    }
}