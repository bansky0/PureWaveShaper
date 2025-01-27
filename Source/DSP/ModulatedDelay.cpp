/*
  ==============================================================================

    ModulatedDelay.cpp
    Created: 13 Nov 2024 3:29:42pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "ModulatedDelay.h"

// ES: Constructor: Inicializa la clase, pero no realiza ninguna acción específica al inicio.
// EN: Constructor: Initializes the class but does not perform any specific action initially.
ModulatedDelay::ModulatedDelay()
{
}

// ES: Destructor: Libera recursos utilizados, aunque en este caso no se requiere una limpieza explícita.
// EN: Destructor: Frees resources, although no explicit cleanup is required here.
ModulatedDelay::~ModulatedDelay()
{
}

// ES: Configura la frecuencia de muestreo para el efecto.
// EN: Sets the sample rate for the effect.
void ModulatedDelay::prepare(double theSampleRate)
{
    sampleRate = theSampleRate; // ES: Guarda la frecuencia de muestreo proporcionada.
}

// ES: Configura el valor del delay en muestras, separándolo en parte entera y fraccional.
// EN: Sets the delay value in samples, separating it into integer and fractional parts.
void ModulatedDelay::setDelay(float newDelayInSamples)
{
    delay = std::floor(newDelayInSamples * sampleRate); // Convierte el tiempo de delay en muestras.
    delayInt = static_cast<int>(delay);                // Parte entera del delay.
    delayFrac = delay - delayInt;                      // Parte fraccional del delay.
}

// ES: Inserta una muestra en el buffer circular correspondiente al canal especificado.
// EN: Inserts a sample into the circular buffer for the specified channel.
void ModulatedDelay::pushSample(int channel, float sample)
{
    if (channel >= 0 && channel < buffer.size()) // Comprueba que el canal es válido.
    {
        buffer[channel][writeIndex[channel]] = sample; // Escribe la muestra en el índice actual del buffer.
        writeIndex[channel] = (writeIndex[channel] + 1) % maxDelaySamples; // Actualiza el índice circularmente.
    }
}

// ES: Obtiene una muestra del buffer correspondiente al canal, aplicando interpolación si es necesario.
// EN: Retrieves a sample from the buffer for the specified channel, applying interpolation if needed.
float ModulatedDelay::popSample(int channel)
{
    if (channel >= 0 && channel < buffer.size()) // Comprueba que el canal es válido.
    {
        // Calcula los índices de lectura para la interpolación.
        int readIndex1 = (writeIndex[channel] - delayInt + maxDelaySamples) % maxDelaySamples;
        int readIndex2 = (readIndex1 + 1) % maxDelaySamples;

        // Aplica interpolación lineal entre las dos muestras adyacentes.
        return (1.0f - delayFrac) * buffer[channel][readIndex1] + delayFrac * buffer[channel][readIndex2];
    }
    return 0.0f; // Si el canal no es válido, retorna 0 como valor por defecto.
}

// ES: Procesa un buffer de audio completo, aplicando el efecto de delay a cada canal.
// EN: Processes an entire audio buffer, applying the delay effect to each channel.
void ModulatedDelay::process(juce::AudioBuffer<float>& inputBuffer)
{
    const int numChannels = inputBuffer.getNumChannels(); // Número de canales del buffer.
    const int numSamples = inputBuffer.getNumSamples();   // Número de muestras en el buffer.

    // Comprueba si el número de buffers coincide con el número de canales y redimensiona si es necesario.
    if (buffer.size() != numChannels)
    {
        // Crea un buffer de delay para cada canal y lo inicializa con ceros.
        buffer.resize(numChannels, std::vector<float>(maxDelaySamples, 0.0f));

        // Ajusta el tamaño del vector de índices de escritura para cada canal.
        writeIndex.resize(numChannels, 0);
    }

    // Procesa cada canal de audio de manera independiente.
    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto* channelData = inputBuffer.getWritePointer(channel); // Obtiene el puntero de escritura para el canal.

        for (int i = 0; i < numSamples; ++i)
        {
            float inputSample = channelData[i]; // Obtiene la muestra original.

            // Inserta la muestra en el buffer circular.
            pushSample(channel, inputSample);

            // Extrae la muestra con delay aplicada.
            float delayedSample = popSample(channel);

            // Sustituye la muestra original con la muestra procesada (con delay).
            channelData[i] = delayedSample;
        }
    }
}