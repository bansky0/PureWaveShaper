/*
  ==============================================================================

    Biquad_II_APF.cpp
    Created: 7 Oct 2024 11:58:53am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_II_APF.h"

// EN: Constructor - Initializes the All-Pass Filter object.
// ES: Constructor - Inicializa el objeto del filtro All-Pass.
Biquad_II_APF::Biquad_II_APF()
{
}

// EN: Destructor - Cleans up the All-Pass Filter object.
// ES: Destructor - Limpia el objeto del filtro All-Pass.
Biquad_II_APF::~Biquad_II_APF()
{
}

// EN: Prepares the filter for processing by setting the sample rate and updating the coefficients.
// ES: Prepara el filtro para el procesamiento configurando la frecuencia de muestreo y actualizando los coeficientes.
void Biquad_II_APF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

// EN: Processes an audio buffer, applying the All-Pass Filter to all channels and samples.
// ES: Procesa un buffer de audio, aplicando el filtro All-Pass a todos los canales y muestras.
void Biquad_II_APF::process(juce::AudioBuffer<float>& inBuffer)
{
    int numChannels = inBuffer.getNumChannels(); // EN: Number of channels in the buffer. // ES: Número de canales en el buffer.
    int numSamples = inBuffer.getNumSamples();   // EN: Number of samples per channel.   // ES: Número de muestras por canal.

    for (int channel = 0; channel < numChannels; channel++) // EN: Loop through each channel. // ES: Itera sobre cada canal.
    {
        for (int i = 0; i < numSamples; i++) // EN: Loop through each sample. // ES: Itera sobre cada muestra.
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Get the input sample. // ES: Obtiene la muestra de entrada.

            float outSample = processSample(inSample, channel); // EN: Process the sample through the filter. // ES: Procesa la muestra a través del filtro.

            inBuffer.setSample(channel, i, outSample); // EN: Set the processed sample back into the buffer. // ES: Establece la muestra procesada de nuevo en el buffer.
        }
    }
}

// EN: Processes a single audio sample for a specific channel using the All-Pass Filter.
// ES: Procesa una muestra de audio para un canal específico utilizando el filtro All-Pass.
float Biquad_II_APF::processSample(float inSample, int channel)
{
    // EN: Calculate the intermediate state w for the filter.
    // ES: Calcula el estado intermedio w para el filtro.
    auto w = inSample - a1 * w1[channel] - a2 * w2[channel];

    // EN: Calculate the output sample y using the filter coefficients.
    // ES: Calcula la muestra de salida y utilizando los coeficientes del filtro.
    auto y = b0 * w + b1 * w1[channel] + b2 * w2[channel];

    // EN: Update the delay lines for the next sample.
    // ES: Actualiza las líneas de retardo para la siguiente muestra.
    w2[channel] = w1[channel];
    w1[channel] = w;

    return y; // EN: Return the processed sample. // ES: Devuelve la muestra procesada.
}

// EN: Sets the cutoff frequency for the All-Pass Filter and updates the coefficients.
// ES: Establece la frecuencia de corte para el filtro All-Pass y actualiza los coeficientes.
void Biquad_II_APF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

// EN: Sets the quality factor (Q) for the All-Pass Filter and updates the coefficients.
// ES: Establece el factor de calidad (Q) para el filtro All-Pass y actualiza los coeficientes.
void Biquad_II_APF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

// EN: Updates the filter coefficients based on the current frequency, Q, and sample rate.
// ES: Actualiza los coeficientes del filtro según la frecuencia actual, el Q y la frecuencia de muestreo.
void Biquad_II_APF::updateFilter()
{
    // EN: Calculate normalized angular frequency and alpha (bandwidth scaling factor).
    // ES: Calcula la frecuencia angular normalizada y alpha (factor de escala del ancho de banda).
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    // EN: Calculate numerator coefficients for the All-Pass Filter.
    // ES: Calcula los coeficientes del numerador para el filtro All-Pass.
    b0 = 1.0f - alpha;
    b1 = -2.0f * cosf(w0);
    b2 = 1.0f + alpha;

    // EN: Calculate denominator coefficients for the All-Pass Filter.
    // ES: Calcula los coeficientes del denominador para el filtro All-Pass.
    a0 = 1.0f + alpha;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha;

    // EN: Normalize coefficients by dividing them by a0.
    // ES: Normaliza los coeficientes dividiéndolos por a0.
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}