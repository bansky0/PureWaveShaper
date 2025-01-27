/*
  ==============================================================================

    Biquad_LPF.cpp
    Created: 1 Oct 2024 12:17:44pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_LPF.h"

// Constructor - Initializes the low-pass filter object.
// Constructor - Inicializa el objeto del filtro pasa bajos.
Biquad_LPF::Biquad_LPF() {}

// Destructor - No dynamic memory cleanup is required.
// Destructor - No se requiere limpieza de memoria dinámica.
Biquad_LPF::~Biquad_LPF() {}

// EN: Prepares the low-pass filter by setting the sample rate and updating the filter coefficients.
// ES: Prepara el filtro pasa bajos configurando la frecuencia de muestreo y actualizando los coeficientes del filtro.
void Biquad_LPF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate; // Set the sample rate.
    updateFilter(); // Update the filter coefficients based on the sample rate and current parameters.
}

// EN: Processes an audio buffer by applying the low-pass filter to each sample in each channel.
// ES: Procesa un buffer de audio aplicando el filtro pasa bajos a cada muestra en cada canal.
void Biquad_LPF::process(juce::AudioBuffer<float> inBuffer)
{
    // Iterate over each channel of the audio buffer.
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        // Iterate over each sample in the channel.
        for (int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            // Get the current sample.
            float inSample = inBuffer.getSample(channel, i);

            // Process the sample through the filter.
            float outSample = processSample(inSample, channel);

            // Set the processed sample back into the buffer.
            inBuffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Processes a single audio sample for a specific channel using the low-pass filter algorithm.
// ES: Procesa una muestra de audio individual para un canal específico utilizando el algoritmo del filtro pasa bajos.
float Biquad_LPF::processSample(float inSample, int channel)
{
    // EN: Filter equation: y[n] = (b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] - a1 * y[n-1] - a2 * y[n-2]) / a0
    // ES: Ecuación del filtro: y[n] = (b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] - a1 * y[n-1] - a2 * y[n-2]) / a0
    auto y = (b0 * inSample + b1 * x1[channel] + b2 * x2[channel] + (-a1) * y1[channel] + (-a2) * y2[channel]) * (1.0f / a0);

    // EN: Update the delay line states for the next sample.
    // ES: Actualiza los estados de la línea de retardo para la siguiente muestra.
    x2[channel] = x1[channel];
    x1[channel] = inSample;
    y2[channel] = y1[channel];
    y1[channel] = y;

    // EN: Return the processed output sample.
    // ES: Devuelve la muestra de salida procesada.
    return y;
}

// EN: Sets the cutoff frequency for the filter and updates the filter coefficients.
// ES: Configura la frecuencia de corte para el filtro y actualiza los coeficientes.
void Biquad_LPF::setFrequency(float inFrequency)
{
    frequency = inFrequency; // Set the cutoff frequency.
    updateFilter(); // Update the filter coefficients based on the new frequency.
}

// EN: Sets the Q factor (resonance) for the filter and updates the filter coefficients.
// ES: Configura el factor Q (resonancia) para el filtro y actualiza los coeficientes.
void Biquad_LPF::setQ(float inQ)
{
    Q = inQ; // Set the Q factor.
    updateFilter(); // Update the filter coefficients based on the new Q value.
}

// EN: Updates the filter coefficients based on the current frequency, Q factor, and sample rate.
// ES: Actualiza los coeficientes del filtro según la frecuencia, el factor Q y la frecuencia de muestreo actuales.
void Biquad_LPF::updateFilter()
{
    // EN: Calculate the angular frequency (w0) and alpha (bandwidth).
    // ES: Calcula la frecuencia angular (w0) y alpha (ancho de banda).
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q); // Alpha is used to control the bandwidth of the filter.

    // EN: Calculate the filter coefficients based on the low-pass filter design.
    // ES: Calcula los coeficientes del filtro basados en el diseño de filtro pasa bajos.
    b0 = (1.0f - cosf(w0)) / 2.0f; // Coefficient for current sample.
    b1 = 1.0f - cosf(w0);          // Coefficient for previous sample (x[n-1]).
    b2 = (1.0f - cosf(w0)) / 2.0f; // Coefficient for two previous samples (x[n-2]).

    // EN: Calculate the feedback coefficients for the filter.
    // ES: Calcula los coeficientes de retroalimentación para el filtro.
    a0 = 1.0f + alpha;            // Normalization factor.
    a1 = -2.0f * cosf(w0);        // Feedback coefficient for previous sample (y[n-1]).
    a2 = 1.0f - alpha;            // Feedback coefficient for two previous samples (y[n-2]).

    // EN: Normalize the feedforward and feedback coefficients by dividing by a0.
    // ES: Normaliza los coeficientes de realimentación directa y retroalimentación dividiendo por a0.
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}
