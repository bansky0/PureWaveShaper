/*
  ==============================================================================

    VibratoEffect.cpp
    Created: 23 Oct 2024 4:32:52pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "VibratoEffect.h"

// EN: Prepares the vibrato effect by setting the sample rate and initializing variables.
// ES: Prepara el efecto de vibrato configurando la tasa de muestreo e inicializando variables.
void VibratoFX::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate); // Establece la tasa de muestreo.
    t = 0.0f;                                       // Reinicia el tiempo.
    ratePercentage = 0.0f;                          // Inicializa el porcentaje de velocidad.
    targetRatePercentage = 0.0f;                    // Inicializa el valor objetivo del porcentaje de velocidad.
}

// EN: Sets the depth of the vibrato effect.
// ES: Establece la profundidad del efecto de vibrato.
void VibratoFX::setDepth(float inDepth)
{
    depth = inDepth; // Configura la amplitud de la modulación del delay.
}

// EN: Sets the vibrato rate as a percentage of the frequency range.
// ES: Establece la velocidad del vibrato como un porcentaje del rango de frecuencia.
void VibratoFX::setRate(float inRate)
{
    // EN: Clamps the input range to [0, 100] and scales it to [0.0, 1.0].
    // ES: Limita el rango de entrada a [0, 100] y lo escala a [0.0, 1.0].
    targetRatePercentage = juce::jlimit(0.0f, 100.0f, inRate) / 100.0f;
}

// EN: Processes the audio buffer to apply the vibrato effect.
// ES: Procesa el buffer de audio para aplicar el efecto de vibrato.
void VibratoFX::process(juce::AudioBuffer<float>& buffer)
{
    float old_t = t; // Almacena el valor anterior de tiempo para los canales.
    const float minRateHz = 0.1f;  // EN: Minimum frequency in Hz. | ES: Frecuencia mínima en Hz.
    const float maxRateHz = 10.0f; // EN: Maximum frequency in Hz. | ES: Frecuencia máxima en Hz.

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        t = old_t; // Reinicia el tiempo para cada canal.

        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            auto sample = buffer.getReadPointer(channel)[i]; // Obtiene la muestra actual.

            // EN: Assigns the target rate and scales it to the frequency range.
            // ES: Asigna el porcentaje de velocidad objetivo y lo escala al rango de frecuencia.
            ratePercentage = targetRatePercentage;
            float rateHz = minRateHz + ratePercentage * (maxRateHz - minRateHz);

            // EN: Calculates the LFO to determine the fractional delay.
            // ES: Calcula el LFO para determinar el retardo fraccional.
            float lfoValue = (depth / 2.0f) * sin(2.0 * juce::MathConstants<float>::pi * rateHz * t) + depth;

            // EN: Calculates the fractional delay index.
            // ES: Calcula el índice de retardo fraccional.
            float fracDelay = static_cast<float>(writterPointer[channel]) - lfoValue;
            if (fracDelay < 0) {
                fracDelay += circularBufferSize; // Ajusta el índice si es negativo.
            }

            int intDelay = static_cast<int>(fracDelay); // Parte entera del retardo.
            float frac = fracDelay - intDelay;          // Parte fraccional para interpolación.

            // EN: Calculates the next sample index for interpolation.
            // ES: Calcula el índice de la siguiente muestra para la interpolación.
            int nextSampleIndex = intDelay + 1;
            if (nextSampleIndex >= circularBufferSize) {
                nextSampleIndex = 0; // Ajusta si se excede el tamaño del buffer circular.
            }

            // EN: Performs linear interpolation between the delayed samples.
            // ES: Realiza una interpolación lineal entre las muestras retrasadas.
            float delayedSample = (1.0f - frac) * circularBuffer[intDelay][channel] +
                frac * circularBuffer[nextSampleIndex][channel];

            // EN: Writes the current sample into the circular buffer.
            // ES: Escribe la muestra actual en el buffer circular.
            circularBuffer[writterPointer[channel]][channel] = sample;

            // EN: Advances the write pointer in the circular buffer.
            // ES: Avanza el puntero de escritura en el buffer circular.
            writterPointer[channel]++;
            if (writterPointer[channel] >= circularBufferSize) {
                writterPointer[channel] = 0; // Reinicia si alcanza el límite del buffer.
            }

            // EN: Writes the delayed sample to the output buffer.
            // ES: Escribe la muestra retrasada en el buffer de salida.
            buffer.getWritePointer(channel)[i] = delayedSample;

            // EN: Increments the time variable.
            // ES: Incrementa la variable de tiempo.
            t += 1.0f / sampleRate;
        }
    }
}

// EN: Constructor for VibratoFX.
// ES: Constructor de VibratoFX.
VibratoFX::VibratoFX()
{
}

// EN: Destructor for VibratoFX.
// ES: Destructor de VibratoFX.
VibratoFX::~VibratoFX()
{
}