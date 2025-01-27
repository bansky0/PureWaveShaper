/*
  ==============================================================================

    Biquad_HPF.cpp
    Created: 1 Oct 2024 12:18:03pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_HPF.h"

// EN: Constructor - Initializes the High-Pass Filter (HPF).
// ES: Constructor - Inicializa el filtro pasa altos (HPF).
Biquad_HPF::Biquad_HPF() {}

// EN: Destructor - Cleans up any resources used by the HPF.
// ES: Destructor - Limpia cualquier recurso utilizado por el HPF.
Biquad_HPF::~Biquad_HPF() {}

// EN: Prepares the filter by setting the sample rate and updating the coefficients.
// ES: Prepara el filtro configurando la frecuencia de muestreo y actualizando los coeficientes.
void Biquad_HPF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter(); // EN: Updates coefficients as they depend on the sample rate.
    // ES: Actualiza los coeficientes ya que dependen de la frecuencia de muestreo.
}

// EN: Processes an entire audio buffer, applying the high-pass filter to all channels and samples.
// ES: Procesa un buffer de audio completo, aplicando el filtro pasa altos a todos los canales y muestras.
void Biquad_HPF::process(juce::AudioBuffer<float> inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++) // EN: Iterate over channels. ES: Itera sobre los canales.
    {
        for (int i = 0; i < inBuffer.getNumSamples(); i++) // EN: Iterate over samples. ES: Itera sobre las muestras.
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Retrieve input sample. ES: Obtiene la muestra de entrada.

            float outSample = processSample(inSample, channel); // EN: Process the sample. ES: Procesa la muestra.

            inBuffer.setSample(channel, i, outSample); // EN: Store the processed sample back. ES: Guarda la muestra procesada.
        }
    }
}

// EN: Processes a single sample for a specific channel using the HPF coefficients.
// ES: Procesa una sola muestra para un canal específico usando los coeficientes del HPF.
float Biquad_HPF::processSample(float inSample, int channel)
{
    auto y = (b0 * inSample + b1 * x1[channel] + b2 * x2[channel] + (-a1) * y1[channel] + (-a2) * y2[channel])
        * (1.0f / a0); // EN: Compute the output using the Biquad equation. ES: Calcula la salida usando la ecuación Biquad.

    // EN: Update the delay lines for input and output samples.
    // ES: Actualiza las líneas de retardo para las muestras de entrada y salida.
    x2[channel] = x1[channel];
    x1[channel] = inSample;
    y2[channel] = y1[channel];
    y1[channel] = y;

    return y; // EN: Return the filtered output. ES: Devuelve la salida filtrada.
}

// EN: Sets the cutoff frequency for the HPF and updates the filter coefficients.
// ES: Establece la frecuencia de corte del HPF y actualiza los coeficientes del filtro.
void Biquad_HPF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter(); // EN: Update coefficients for the new frequency. ES: Actualiza los coeficientes para la nueva frecuencia.
}

// EN: Sets the quality factor (Q) for the HPF and updates the filter coefficients.
// ES: Establece el factor de calidad (Q) del HPF y actualiza los coeficientes del filtro.
void Biquad_HPF::setQ(float inQ)
{
    Q = inQ;
    updateFilter(); // EN: Update coefficients for the new Q value. ES: Actualiza los coeficientes para el nuevo valor de Q.
}

// EN: Updates the filter coefficients based on the current sample rate, frequency, and Q.
// ES: Actualiza los coeficientes del filtro según la frecuencia de muestreo, frecuencia y Q actuales.
void Biquad_HPF::updateFilter()
{
    // EN: Compute angular frequency (w0) and bandwidth scaling factor (alpha).
    // ES: Calcula la frecuencia angular (w0) y el factor de escalado de ancho de banda (alpha).
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    // EN: Calculate feedforward coefficients for a high-pass filter.
    // ES: Calcula los coeficientes de alimentación directa para un filtro pasa altos.
    b0 = (1.0f + cosf(w0)) / 2.0f;
    b1 = -(1.0f + cosf(w0)); // EN: Note: The formula deviates slightly from standard implementations.
    // ES: Nota: La fórmula difiere ligeramente de las implementaciones estándar.
    b2 = (1.0f + cosf(w0)) / 2.0f;

    // EN: Calculate feedback coefficients for a high-pass filter.
    // ES: Calcula los coeficientes de retroalimentación para un filtro pasa altos.
    a0 = 1.0f + alpha;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha;
}

