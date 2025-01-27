/*
  ==============================================================================

    ChorusEffect.cpp
    Created: 30 Oct 2024 3:21:25pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "ChorusEffect.h"

// EN: Prepares the chorus effect by initializing sample rate and key variables.
// ES: Prepara el efecto de chorus inicializando la frecuencia de muestreo y las variables clave.
void ChorusFX::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate); // EN: Store the sample rate. / ES: Almacena la frecuencia de muestreo.
    t = 0.0f;                                       // EN: Initialize the LFO time variable. / ES: Inicializa la variable de tiempo del LFO.
    ratePercentage = 0.0f;                          // EN: Initialize modulation rate percentage. / ES: Inicializa el porcentaje de modulación.
    targetRatePercentage = 0.0f;                    // EN: Initialize the target modulation rate. / ES: Inicializa la velocidad de modulación objetivo.
    predelay = 0.0f;                                // EN: Initialize pre-delay. / ES: Inicializa el pre-delay.
}

// EN: Sets the depth of the modulation effect.
// ES: Ajusta la profundidad del efecto de modulación.
void ChorusFX::setDepth(float inDepth)
{
    depth = inDepth; // EN: Store the depth value. / ES: Almacena el valor de profundidad.
}

// EN: Sets the target modulation rate percentage, ensuring it is within 0% to 100%.
// ES: Ajusta el porcentaje objetivo de la velocidad de modulación, asegurándose de que esté entre 0% y 100%.
void ChorusFX::setRate(float inRatePercentage)
{
    targetRatePercentage = juce::jlimit(0.0f, 100.0f, inRatePercentage) / 100.0f; // EN: Normalize to a range of 0 to 1. / ES: Normaliza al rango de 0 a 1.
}

// EN: Sets the pre-delay in milliseconds and converts it to samples.
// ES: Ajusta el pre-delay en milisegundos y lo convierte a muestras.
void ChorusFX::setPredelay(float inPredelayMs)
{
    predelay = inPredelayMs * sampleRate / 1000.0f; // EN: Convert milliseconds to samples. / ES: Convierte milisegundos a muestras.
}

// EN: Processes the audio buffer, applying the chorus effect.
// ES: Procesa el buffer de audio aplicando el efecto de chorus.
void ChorusFX::process(juce::AudioBuffer<float>& buffer)
{
    float old_t = t; // EN: Store the previous LFO time to synchronize between channels. / ES: Almacena el tiempo anterior del LFO para sincronizar entre canales.
    const float minRateHz = 0.1f; // EN: Minimum modulation rate in Hz. / ES: Velocidad mínima de modulación en Hz.
    const float maxRateHz = 10.0f; // EN: Maximum modulation rate in Hz. / ES: Velocidad máxima de modulación en Hz.

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        t = old_t; // EN: Reset the LFO time for the current channel. / ES: Reinicia el tiempo del LFO para el canal actual.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            auto sample = buffer.getReadPointer(channel)[i]; // EN: Read the current sample. / ES: Lee la muestra actual.
            ratePercentage = targetRatePercentage; // EN: Update the modulation rate. / ES: Actualiza la velocidad de modulación.

            // EN: Compute the modulation rate in Hz.
            // ES: Calcula la velocidad de modulación en Hz.
            float rateHz = minRateHz + ratePercentage * (maxRateHz - minRateHz);

            // EN: Calculate the LFO value based on depth and rate.
            // ES: Calcula el valor del LFO basado en la profundidad y la velocidad.
            float lfoValue = (depth / 2.0f) * sin(2.0 * juce::MathConstants<float>::pi * rateHz * t) + depth;

            // EN: Compute fractional delay including pre-delay.
            // ES: Calcula el retardo fraccional incluyendo el pre-delay.
            float fracDelay = static_cast<float>(writterPointer[channel]) - lfoValue - predelay;

            // EN: Wrap the delay index if it goes negative.
            // ES: Ajusta el índice de retardo si es negativo.
            if (fracDelay < 0)
                fracDelay += circularBufferSize;

            int intDelay = static_cast<int>(fracDelay); // EN: Extract integer part of the delay. / ES: Extrae la parte entera del retardo.
            float frac = fracDelay - intDelay; // EN: Extract fractional part. / ES: Extrae la parte fraccional.
            int nextSampleIndex = intDelay + 1; // EN: Compute the index for the next sample. / ES: Calcula el índice de la siguiente muestra.
            if (nextSampleIndex >= circularBufferSize)
                nextSampleIndex = 0;

            // EN: Interpolate between two delayed samples.
            // ES: Interpola entre dos muestras retardadas.
            float delayedSample = (1.0f - frac) * circularBuffer[intDelay][channel] + frac * circularBuffer[nextSampleIndex][channel];

            // EN: Store the current sample in the circular buffer.
            // ES: Almacena la muestra actual en el buffer circular.
            circularBuffer[writterPointer[channel]][channel] = sample;

            // EN: Increment and wrap the write pointer.
            // ES: Incrementa y ajusta el puntero de escritura.
            writterPointer[channel]++;
            if (writterPointer[channel] >= circularBufferSize)
                writterPointer[channel] = 0;

            // EN: Write the processed sample to the output buffer.
            // ES: Escribe la muestra procesada en el buffer de salida.
            buffer.getWritePointer(channel)[i] = delayedSample;

            // EN: Increment the LFO time.
            // ES: Incrementa el tiempo del LFO.
            t += 1.0f / sampleRate;
        }
    }
}

// EN: Constructor for the ChorusFX class.
// ES: Constructor de la clase ChorusFX.
ChorusFX::ChorusFX() {}

// EN: Destructor for the ChorusFX class.
// ES: Destructor de la clase ChorusFX.
ChorusFX::~ChorusFX() {}
