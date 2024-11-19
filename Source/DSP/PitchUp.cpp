/*
  ==============================================================================

    PitchUp.cpp
    Created: 5 Nov 2024 4:21:53pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "PitchUp.h"

void PitchUp::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);
    delay = static_cast<float>(bufferSize); // Inicializa con el tamaño del buffer
    writePosition = 0;

    // Limpiar el buffer de retardo
    std::fill(std::begin(delayBuffer), std::end(delayBuffer), 0.0f);
}

void PitchUp::process(juce::AudioBuffer<float>& buffer)
{
    int numSamples = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels();

    for (int i = 0; i < numSamples; ++i)
    {
        for (int channel = 0; channel < numChannels; ++channel)
        {
            float* channelData = buffer.getWritePointer(channel);

            // Calcular delay para esta muestra
            int intDelay = static_cast<int>(floorf(delay)); // Parte entera del retardo
            float frac = delay - intDelay; // Parte fraccionaria del retardo
            int readPosition = writePosition - intDelay; // Posición de lectura en el buffer

            // Ajustar readPosition para manejar el buffer circular
            if (readPosition < 0)
                readPosition += bufferSize;

            int nextSampleIndex = (readPosition + 1) % bufferSize;

            // Interpolación lineal para obtener la muestra con pitch-up
            float delayedSample = (1.0f - frac) * delayBuffer[readPosition] + frac * delayBuffer[nextSampleIndex];

            // Almacenar la muestra actual en el buffer de retardo
            delayBuffer[writePosition] = channelData[i];

            // Escribir la muestra de salida con pitch-up en el canal actual
            channelData[i] = delayedSample;
        }

        // Incrementar el puntero de escritura de forma circular
        if (++writePosition >= bufferSize)
            writePosition = 0;

        // Disminuir el retardo para aumentar el tono
        delay -= 1.0f;

        // Mantener el tamaño del retardo en los límites del buffer circular
        if (delay < 0)
            delay += bufferSize;
    }
}
