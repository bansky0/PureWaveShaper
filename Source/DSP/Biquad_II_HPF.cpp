/*
  ==============================================================================

    Biquad_II_HPF.cpp
    Created: 7 Oct 2024 11:58:20am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_II_HPF.h"

// EN: Constructor - Initializes the class, no specific setup needed here.
// ES: Constructor - Inicializa la clase, no se requiere configuración específica aquí.
Biquad_II_HPF::Biquad_II_HPF() {}

// EN: Destructor - Cleans up the class, no dynamic allocation to handle.
// ES: Destructor - Limpia la clase, no hay asignación dinámica que manejar.
Biquad_II_HPF::~Biquad_II_HPF() {}

// EN: Sets the sample rate and updates the filter coefficients accordingly.
// ES: Configura la frecuencia de muestreo y actualiza los coeficientes del filtro en consecuencia.
void Biquad_II_HPF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter(); // EN: The filter needs to be updated because its coefficients depend on the sample rate.
    // ES: El filtro necesita actualizarse porque sus coeficientes dependen de la frecuencia de muestreo.
}

// EN: Processes an audio buffer, applying the high-pass filter to all samples and channels.
// ES: Procesa un buffer de audio, aplicando el filtro pasa altos a todas las muestras y canales.
void Biquad_II_HPF::process(juce::AudioBuffer<float>& inBuffer)
{
    int numChannels = inBuffer.getNumChannels();
    int numSamples = inBuffer.getNumSamples();

    // EN: Loop through all channels and samples.
    // ES: Itera a través de todos los canales y muestras.
    for (int channel = 0; channel < numChannels; channel++)
    {
        for (int i = 0; i < numSamples; i++)
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Get the input sample. // ES: Obtiene la muestra de entrada.

            float outSample = processSample(inSample, channel); // EN: Process the sample. // ES: Procesa la muestra.

            inBuffer.setSample(channel, i, outSample); // EN: Set the processed sample back into the buffer. // ES: Guarda la muestra procesada de vuelta en el buffer.
        }
    }
}

// EN: Processes a single audio sample for a specific channel using the high-pass filter.
// ES: Procesa una muestra de audio específica para un canal usando el filtro pasa altos.
float Biquad_II_HPF::processSample(float inSample, int channel)
{
    // EN: Calculate intermediate variable `w` and output `y`.
    // ES: Calcula la variable intermedia `w` y la salida `y`.
    auto w = inSample - a1 * w1[channel] - a2 * w2[channel];
    auto y = b0 * w + b1 * w1[channel] + b2 * w2[channel];

    // EN: Update delay lines.
    // ES: Actualiza las líneas de retardo.
    w2[channel] = w1[channel];
    w1[channel] = w;

    return y; // EN: Return the filtered sample. // ES: Retorna la muestra filtrada.
}

// EN: Sets the cutoff frequency for the high-pass filter and updates the coefficients.
// ES: Configura la frecuencia de corte para el filtro pasa altos y actualiza los coeficientes.
void Biquad_II_HPF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

// EN: Sets the Q factor (resonance) for the high-pass filter and updates the coefficients.
// ES: Configura el factor Q (resonancia) para el filtro pasa altos y actualiza los coeficientes.
void Biquad_II_HPF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

// EN: Updates the filter coefficients based on the current frequency, Q factor, and sample rate.
// ES: Actualiza los coeficientes del filtro según la frecuencia, el factor Q y la frecuencia de muestreo actuales.
void Biquad_II_HPF::updateFilter()
{
    // EN: Calculate coefficients for a high-pass filter.
    // ES: Calcula los coeficientes para un filtro pasa altos.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    // EN: Coefficients based on standard biquad high-pass filter formula.
    // ES: Coeficientes basados en la fórmula estándar de biquad para filtro pasa altos.
    b0 = (1.0f + cosf(w0)) / 2.0f;
    b1 = -(1.0f + cosf(w0)); // EN: Note - This implementation differs from standard tables. // ES: Nota - Esta implementación difiere de las tablas estándar.
    b2 = (1.0f + cosf(w0)) / 2.0f;

    a0 = 1.0f + alpha;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha;

    // EN: Normalize coefficients by dividing by `a0`.
    // ES: Normaliza los coeficientes dividiéndolos por `a0`.
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}