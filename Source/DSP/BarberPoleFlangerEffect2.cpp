/*
  ==============================================================================

    BarberPoleFlangerEffect2.cpp
    Created: 5 Nov 2024 9:52:36am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "BarberPoleFlangerEffect2.h"

// EN: Initializes the effect with the given sample rate.
// ES: Inicializa el efecto con la frecuencia de muestreo proporcionada.
void BarberpoleFlanger2FX::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate);
    t = 0.0f; // EN: Reset LFO time. | ES: Reinicia el tiempo del LFO.
    ratePercentage = 0.0f; // EN: Initialize the LFO rate as 0%. | ES: Inicializa la velocidad del LFO en 0%.
    targetRatePercentage = 0.0f; // EN: Set the target LFO rate to 0%. | ES: Establece la velocidad objetivo del LFO en 0%.
    predelay = 0.0f; // EN: Initialize the predelay. | ES: Inicializar el predelay.
}

// EN: Sets the depth of the Barberpole Flanger effect.
// ES: Establece la profundidad del efecto Barberpole Flanger.
void BarberpoleFlanger2FX::setDepth(float inDepth)
{
    depth = inDepth;
}

// EN: Sets the target LFO rate, limiting it to a range of 0% to 100%.
// ES: Establece la velocidad objetivo del LFO, limitándola a un rango de 0% a 100%.
void BarberpoleFlanger2FX::setRate(float inRatePercentage)
{
    targetRatePercentage = juce::jlimit(0.0f, 100.0f, inRatePercentage) / 100.0f;
}

// EN: Configures the predelay time in milliseconds, converting it to samples.
// ES: Configura el tiempo de predelay en milisegundos, convirtiéndolo a muestras.
void BarberpoleFlanger2FX::setPredelay(float inPredelayMs)
{
    predelay = inPredelayMs * sampleRate / 1000.0f;
}

// EN: Generates a sawtooth waveform based on the input phase.
// ES: Genera una onda de diente de sierra basada en la fase de entrada.
float BarberpoleFlanger2FX::generateSawtooth(float phase)
{
    return 2.0f * (phase - floorf(phase + 0.5f));
}

// EN: Processes the audio buffer to apply the Barberpole Flanger effect.
// ES: Procesa el buffer de audio para aplicar el efecto Barberpole Flanger.
void BarberpoleFlanger2FX::process(juce::AudioBuffer<float>& buffer)
{
    float old_t = t; // EN: Save the current LFO time. | ES: Guarda el tiempo actual del LFO.
    const float minRateHz = 0.1f; // EN: Minimum LFO frequency in Hz. | ES: Frecuencia mínima del LFO en Hz.
    const float maxRateHz = 10.0f; // EN: Maximum LFO frequency in Hz. | ES: Frecuencia máxima del LFO en Hz.

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        t = old_t;
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            auto sample = buffer.getReadPointer(channel)[i];

            // EN: Calculate the LFO rate based on the current rate percentage.
            // ES: Calcula la velocidad del LFO basada en el porcentaje actual.
            ratePercentage = targetRatePercentage;
            float rateHz = minRateHz + ratePercentage * (maxRateHz - minRateHz);
            float phase = rateHz * t;

            // EN: Generate two LFO values for the two circular buffers.
            // ES: Genera dos valores de LFO para los dos buffers circulares.
            float lfoValue1 = depth * generateSawtooth(phase) + predelay;
            float lfoValue2 = depth * generateSawtooth(phase + juce::MathConstants<float>::pi) + predelay;

            // EN: Calculate fractional delays for both LFO values.
            // ES: Calcula los retrasos fraccionales para ambos valores de LFO.
            float fracDelay1 = static_cast<float>(writterPointer1[channel]) - lfoValue1;
            float fracDelay2 = static_cast<float>(writterPointer2[channel]) - lfoValue2;

            if (fracDelay1 < 0) fracDelay1 += circularBufferSize;
            if (fracDelay2 < 0) fracDelay2 += circularBufferSize;

            int intDelay1 = static_cast<int>(fracDelay1);
            int intDelay2 = static_cast<int>(fracDelay2);
            float frac1 = fracDelay1 - intDelay1;
            float frac2 = fracDelay2 - intDelay2;

            int nextSampleIndex1 = intDelay1 + 1;
            int nextSampleIndex2 = intDelay2 + 1;

            if (nextSampleIndex1 >= circularBufferSize) nextSampleIndex1 = 0;
            if (nextSampleIndex2 >= circularBufferSize) nextSampleIndex2 = 0;

            // EN: Retrieve interpolated samples from the circular buffers.
            // ES: Recupera muestras interpoladas de los buffers circulares.
            float delayedSample1 = (1.0f - frac1) * circularBuffer1[intDelay1][channel] + frac1 * circularBuffer1[nextSampleIndex1][channel];
            float delayedSample2 = (1.0f - frac2) * circularBuffer2[intDelay2][channel] + frac2 * circularBuffer2[nextSampleIndex2][channel];

            // EN: Store the current sample in the circular buffers.
            // ES: Almacena la muestra actual en los buffers circulares.
            circularBuffer1[writterPointer1[channel]][channel] = sample;
            circularBuffer2[writterPointer2[channel]][channel] = sample;

            writterPointer1[channel]++;
            if (writterPointer1[channel] >= circularBufferSize) writterPointer1[channel] = 0;

            writterPointer2[channel]++;
            if (writterPointer2[channel] >= circularBufferSize) writterPointer2[channel] = 0;

            // EN: Compute the combined output sample using crossfade.
            // ES: Calcula la muestra de salida combinada utilizando crossfade.
            float outputSample = crossfade1[channel] * delayedSample1 + crossfade2[channel] * delayedSample2;

            // EN: Write the output sample to the buffer.
            // ES: Escribe la muestra de salida en el buffer.
            buffer.getWritePointer(channel)[i] = outputSample;

            // EN: Increment the LFO time.
            // ES: Incrementa el tiempo del LFO.
            t += 1.0f / sampleRate;
        }
    }
}

// EN: Constructor for BarberpoleFlanger2FX.
// ES: Constructor para BarberpoleFlanger2FX.
BarberpoleFlanger2FX::BarberpoleFlanger2FX() {}

// EN: Destructor for BarberpoleFlanger2FX.
// ES: Destructor para BarberpoleFlanger2FX.
BarberpoleFlanger2FX::~BarberpoleFlanger2FX() {}