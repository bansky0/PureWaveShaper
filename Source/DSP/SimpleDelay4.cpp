/*
  ==============================================================================

    SimpleDelay4.cpp
    Created: 14 Nov 2024 1:48:52pm
    Author:  Jhonatan

  ==============================================================================
*/

#include "SimpleDelay4.h"

// Constructor
SimpleDelay4::SimpleDelay4() {}

// Destructor
SimpleDelay4::~SimpleDelay4() {}

// EN: Prepares the delay system by setting the sample rate.
// ES: Prepara el sistema de delay configurando la frecuencia de muestreo.
void SimpleDelay4::prepare(double theSampleRate)
{
    sampleRate = theSampleRate; // Configura la frecuencia de muestreo.
}

// EN: Sets the delay time in samples. It calculates the integer and fractional parts of the delay.
// ES: Configura el tiempo de delay en samples. Calcula la parte entera y fraccional del delay.
void SimpleDelay4::setDelay(float newDelayInSamples)
{
    delay = std::floor(newDelayInSamples * sampleRate); // Convierte el tiempo de delay a samples.
    delayInt = static_cast<int>(delay);                // Obtiene la parte entera del delay.
    delayFrac = delay - delayInt;                      // Calcula la parte fraccional del delay.
}

// EN: Adds a sample to the delay buffer for the specified channel.
// ES: Agrega una muestra al buffer de delay para el canal especificado.
void SimpleDelay4::pushSample(int channel, float sample)
{
    if (channel >= 0 && channel < buffer.size()) // Asegura que el canal está dentro de los límites.
    {
        buffer[channel][writeIndex[channel]] = sample; // Escribe la muestra en el buffer correspondiente.
        writeIndex[channel] = (writeIndex[channel] + 1) % maxDelaySamples; // Avanza el índice de escritura circularmente.
    }
}

// EN: Retrieves a delayed sample from the buffer for the specified channel.
// ES: Obtiene una muestra con delay desde el buffer para el canal especificado.
float SimpleDelay4::popSample(int channel)
{
    if (channel >= 0 && channel < buffer.size()) // Asegura que el canal está dentro de los límites.
    {
        int readIndex1 = (writeIndex[channel] - delayInt + maxDelaySamples) % maxDelaySamples; // Índice de lectura principal.
        int readIndex2 = (readIndex1 + 1) % maxDelaySamples; // Índice de lectura para interpolación.

        // EN: Performs linear interpolation between the two closest samples.
        // ES: Realiza una interpolación lineal entre las dos muestras más cercanas.
        return (1.0f - delayFrac) * buffer[channel][readIndex1] + delayFrac * buffer[channel][readIndex2];
    }
    return 0.0f; // EN: Returns 0 if the channel is invalid. ES: Retorna 0 si el canal es inválido.
}

// EN: Processes the audio buffer, applying the delay effect to all channels and samples.
// ES: Procesa el buffer de audio, aplicando el efecto de delay a todos los canales y muestras.
void SimpleDelay4::process(juce::AudioBuffer<float>& inputBuffer)
{
    const int numChannels = inputBuffer.getNumChannels(); // Número de canales en el buffer de entrada.
    const int numSamples = inputBuffer.getNumSamples();   // Número de samples por canal.

    // EN: Ensures the delay buffer matches the number of channels in the input buffer.
    // ES: Asegura que el buffer de delay coincida con el número de canales del buffer de entrada.
    if (buffer.size() != numChannels)
    {
        buffer.resize(numChannels, std::vector<float>(maxDelaySamples, 0.0f)); // Redimensiona el buffer de delay.
        writeIndex.resize(numChannels, 0); // Redimensiona los índices de escritura.
    }

    // EN: Processes each channel independently.
    // ES: Procesa cada canal de manera independiente.
    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto* channelData = inputBuffer.getWritePointer(channel); // Obtiene un puntero a los datos del canal.
        for (int i = 0; i < numSamples; ++i)
        {
            float inputSample = channelData[i];     // Muestra de entrada actual.
            pushSample(channel, inputSample);       // Inserta la muestra en el buffer de delay.
            float delayedSample = popSample(channel); // Obtiene la muestra con delay.
            channelData[i] = delayedSample;         // Sustituye la muestra original por la muestra con delay.
        }
    }
}