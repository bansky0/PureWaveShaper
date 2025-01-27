/*
  ==============================================================================

    Biquad_HSF.cpp
    Created: 1 Oct 2024 12:26:59pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_HSF.h"

// EN: Constructor - Initializes the Biquad High-Shelf Filter.
// ES: Constructor - Inicializa el filtro biquad high-shelf.
Biquad_HSF::Biquad_HSF() {}

// EN: Destructor - Cleans up resources used by the filter.
// ES: Destructor - Libera los recursos utilizados por el filtro.
Biquad_HSF::~Biquad_HSF() {}

// EN: Prepares the filter by setting the sample rate and updating the filter coefficients.
// ES: Prepara el filtro configurando la frecuencia de muestreo y actualizando los coeficientes del filtro.
void Biquad_HSF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

// EN: Processes an entire audio buffer, applying the high-shelf filter to each channel and sample.
// ES: Procesa un buffer de audio completo, aplicando el filtro de estante alto a cada canal y muestra.
void Biquad_HSF::process(juce::AudioBuffer<float> inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++) // Iterate through each channel.
    {
        for (int i = 0; i < inBuffer.getNumSamples(); i++) // Iterate through each sample in the channel.
        {
            float inSample = inBuffer.getSample(channel, i); // Get the current sample.

            float outSample = processSample(inSample, channel); // Process the sample using the high-shelf filter.

            inBuffer.setSample(channel, i, outSample); // Write the processed sample back into the buffer.
        }
    }
}

// EN: Processes a single sample for a specific channel using the high-shelf filter coefficients.
// ES: Procesa una sola muestra para un canal específico utilizando los coeficientes del filtro de estante alto.
float Biquad_HSF::processSample(float inSample, int channel)
{
    auto y = (b0 * inSample + b1 * x1[channel] + b2 * x2[channel] + (-a1) * y1[channel] + (-a2) * y2[channel]) * (1.0f / a0);

    // Update the delay lines for the input and output samples.
    x2[channel] = x1[channel];
    x1[channel] = inSample;
    y2[channel] = y1[channel];
    y1[channel] = y;

    return y; // Return the processed output sample.
}

// EN: Sets the cutoff frequency for the high-shelf filter and updates the coefficients.
// ES: Establece la frecuencia de corte para el filtro de estante alto y actualiza los coeficientes.
void Biquad_HSF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

// EN: Sets the quality factor (Q) for the high-shelf filter and updates the coefficients.
// ES: Establece el factor de calidad (Q) para el filtro de estante alto y actualiza los coeficientes.
void Biquad_HSF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

// EN: Sets the gain (boost/cut) for the high-shelf filter and updates the coefficients.
// ES: Establece la ganancia (realce/atenuación) para el filtro de estante alto y actualiza los coeficientes.
void Biquad_HSF::setGain(float inGain)
{
    Gain = inGain;
    updateFilter();
}

// EN: Updates the filter coefficients based on the current parameters (frequency, Q, and gain).
// ES: Actualiza los coeficientes del filtro según los parámetros actuales (frecuencia, Q y ganancia).
void Biquad_HSF::updateFilter()
{
    // EN: Calculate the normalized angular frequency (w0) and bandwidth scaling factor (alpha).
    // ES: Calcula la frecuencia angular normalizada (w0) y el factor de escalado de ancho de banda (alpha).
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    // EN: Convert the gain (dB) to a linear amplitude scaling factor (A).
    // ES: Convierte la ganancia (dB) a un factor de escalado de amplitud lineal (A).
    A = sqrt(powf(10.0f, Gain / 20.0f));

    // EN: Calculate the filter coefficients for a high-shelf filter.
    // ES: Calcula los coeficientes del filtro para un filtro high-shelf.
    b0 = A * ((A + 1.0f) + ((A - 1.0f) * cosf(w0)) + (2.0f * sqrtf(A) * alpha));
    b1 = -2.0f * A * ((A - 1.0f) + ((A + 1.0f) * cosf(w0)));
    b2 = A * ((A + 1.0f) + ((A - 1.0f) * cosf(w0)) - (2.0f * sqrtf(A) * alpha));

    a0 = (A + 1.0f) - ((A - 1.0f) * cosf(w0)) + (2.0f * sqrtf(A) * alpha);
    a1 = 2.0f * ((A - 1.0f) - ((A + 1.0f) * cosf(w0)));
    a2 = (A + 1.0f) - ((A - 1.0f) * cosf(w0)) - (2.0f * sqrtf(A) * alpha);
}