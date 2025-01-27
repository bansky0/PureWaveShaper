/*
  ==============================================================================

    VibratoEffectExample.cpp
    Created: 21 Oct 2024 9:19:16pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "VibratoEffectExample.h"

// EN: Prepares the vibrato effect by setting the sample rate and resetting the time variable.
// ES: Prepara el efecto de vibrato configurando la tasa de muestreo y reiniciando la variable de tiempo.
void VibratoEffect::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate); // Configura la tasa de muestreo.
    t = 0.0f; // Reinicia la variable de tiempo.
}

// EN: Sets the depth of the vibrato effect.
// ES: Configura la profundidad del efecto de vibrato.
void VibratoEffect::setDepth(float inDepth)
{
    depth = inDepth; // Profundidad de la modulación (amplitud del LFO).
}

// EN: Sets the frequency of the vibrato effect (LFO rate).
// ES: Configura la frecuencia del efecto de vibrato (velocidad del LFO).
void VibratoEffect::setRate(float inRate)
{
    rate = inRate; // Frecuencia del LFO en Hz.
}

// EN: Processes the audio buffer to apply the vibrato effect using a circular buffer and LFO modulation.
// ES: Procesa el buffer de audio para aplicar el efecto de vibrato utilizando un buffer circular y modulación con LFO.
void VibratoEffect::process(juce::AudioBuffer<float>& buffer)
{
    float old_t = t; // EN: Save the initial time value for consistent LFO phase across channels.
    // ES: Guarda el valor inicial de `t` para mantener la fase del LFO consistente entre canales.

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        t = old_t; // EN: Restore the original time for each channel.
        // ES: Restaura el tiempo original para cada canal.

        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            auto sample = buffer.getReadPointer(channel)[i]; // EN: Get the current input sample.
            // ES: Obtiene la muestra actual de entrada.

// EN: Calculate the LFO value for delay modulation.
// ES: Calcula el valor del LFO para la modulación del retardo.
            float lfoValue = depth / 2.0f * sin(2.0 * juce::MathConstants<float>::pi * rate * t) + depth;

            // EN: Calculate the delay in samples based on the LFO.
            // ES: Calcula el número de muestras de retardo basado en el LFO.
            int delaySamples = static_cast<int>(std::fabs(lfoValue));

            // EN: Calculate the read position in the circular buffer.
            // ES: Calcula la posición de lectura en el buffer circular.
            readerPointer = writterPointer[channel] - delaySamples;
            if (readerPointer < 0)
            {
                readerPointer += circularBufferSize; // EN: Wrap around if the pointer goes negative.
                // ES: Ajusta el puntero si se vuelve negativo.
            }

            // EN: Get the delayed sample from the circular buffer.
            // ES: Obtiene la muestra retrasada del buffer circular.
            auto delayedSample = circularBuffer[readerPointer][channel];

            // EN: Write the current input sample into the circular buffer.
            // ES: Escribe la muestra actual en el buffer circular.
            circularBuffer[writterPointer[channel]][channel] = sample;

            // EN: Advance the write pointer in the circular buffer.
            // ES: Avanza el puntero de escritura en el buffer circular.
            writterPointer[channel]++;
            if (writterPointer[channel] >= circularBufferSize)
            {
                writterPointer[channel] = 0; // EN: Wrap around if the pointer exceeds the buffer size.
                // ES: Ajusta el puntero si excede el tamaño del buffer.
            }

            // EN: Write the delayed sample to the output buffer.
            // ES: Escribe la muestra retrasada en el buffer de salida.
            buffer.getWritePointer(channel)[i] = delayedSample;

            // EN: Increment the time variable for the LFO.
            // ES: Incrementa la variable de tiempo para el LFO.
            t += 1.0f / sampleRate;
        }
    }
}

// EN: Constructor. Initializes the vibrato effect.
// ES: Constructor. Inicializa el efecto de vibrato.
VibratoEffect::VibratoEffect()
{
}

// EN: Destructor. Cleans up resources if necessary.
// ES: Destructor. Limpia recursos si es necesario.
VibratoEffect::~VibratoEffect()
{
}