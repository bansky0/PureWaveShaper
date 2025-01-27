/*
  ==============================================================================

    Biquad_TDFII_BPF.cpp
    Created: 7 Oct 2024 4:01:29pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_TDFII_BPF.h"

// EN: Constructor for the Biquad_TDFII_BPF class.
// ES: Constructor de la clase Biquad_TDFII_BPF.
Biquad_TDFII_BPF::Biquad_TDFII_BPF()
{
}

// EN: Destructor for the Biquad_TDFII_BPF class.
// ES: Destructor de la clase Biquad_TDFII_BPF.
Biquad_TDFII_BPF::~Biquad_TDFII_BPF()
{
}

// EN: Prepares the filter by setting the sample rate and updating the filter coefficients.
// ES: Prepara el filtro configurando la frecuencia de muestreo y actualizando los coeficientes del filtro.
void Biquad_TDFII_BPF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

// EN: Processes an entire audio buffer, applying the band-pass filter to all channels and samples.
// ES: Procesa un buffer de audio completo, aplicando el filtro pasa banda a todos los canales y muestras.
void Biquad_TDFII_BPF::process(juce::AudioBuffer<float>& inBuffer)
{
    int numChannels = inBuffer.getNumChannels();
    int numSamples = inBuffer.getNumSamples();

    // EN: Loop through each channel.
    // ES: Itera sobre cada canal.
    for (int channel = 0; channel < numChannels; channel++)
    {
        // EN: Loop through each sample in the channel.
        // ES: Itera sobre cada muestra en el canal.
        for (int i = 0; i < numSamples; i++)
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Get the input sample. ES: Obtiene la muestra de entrada.
            float outSample = processSample(inSample, channel); // EN: Process the sample through the filter. ES: Procesa la muestra a través del filtro.
            inBuffer.setSample(channel, i, outSample); // EN: Set the filtered sample in the buffer. ES: Asigna la muestra filtrada al buffer.
        }
    }
}

// EN: Processes a single sample for a specific channel using the filter equations.
// ES: Procesa una muestra individual para un canal específico utilizando las ecuaciones del filtro.
float Biquad_TDFII_BPF::processSample(float inSample, int channel)
{
    auto y = b0 * inSample + r1[channel]; // EN: Compute the output sample. ES: Calcula la muestra de salida.

    // EN: Update the filter's internal states for feedback and feedforward paths.
    // ES: Actualiza los estados internos del filtro para las trayectorias de retroalimentación y avance.
    r1[channel] = b1 * inSample + (-a1) * y + r2[channel];
    r2[channel] = b2 * inSample + (-a2) * y;

    return y; // EN: Return the filtered sample. ES: Devuelve la muestra filtrada.
}

// EN: Sets the center frequency of the band-pass filter and updates the coefficients.
// ES: Establece la frecuencia central del filtro pasa banda y actualiza los coeficientes.
void Biquad_TDFII_BPF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

// EN: Sets the Q factor (resonance) of the band-pass filter and updates the coefficients.
// ES: Establece el factor Q (resonancia) del filtro pasa banda y actualiza los coeficientes.
void Biquad_TDFII_BPF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

// EN: Updates the filter coefficients based on the current sample rate, frequency, and Q factor.
// ES: Actualiza los coeficientes del filtro según la frecuencia de muestreo, frecuencia y factor Q actuales.
void Biquad_TDFII_BPF::updateFilter()
{
    // EN: Calculate intermediate parameters for the filter equations.
    // ES: Calcula parámetros intermedios para las ecuaciones del filtro.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    // EN: Coefficients for a band-pass filter.
    // ES: Coeficientes para un filtro pasa banda.
    b0 = sinf(w0) / 2.0f; // EN: Feedforward coefficient b0 for band-pass behavior. ES: Coeficiente de avance b0 para el comportamiento pasa banda.
    b1 = 0.0f;            // EN: Feedforward coefficient b1. ES: Coeficiente de avance b1.
    b2 = -sinf(w0) / 2.0f;// EN: Feedforward coefficient b2 for band-pass behavior. ES: Coeficiente de avance b2 para el comportamiento pasa banda.

    a0 = 1.0f + alpha;    // EN: Feedback coefficient a0. ES: Coeficiente de retroalimentación a0.
    a1 = -2.0f * cosf(w0);// EN: Feedback coefficient a1. ES: Coeficiente de retroalimentación a1.
    a2 = 1.0f - alpha;    // EN: Feedback coefficient a2. ES: Coeficiente de retroalimentación a2.

    // EN: Normalize coefficients to ensure filter stability and correct scaling.
    // ES: Normaliza los coeficientes para garantizar la estabilidad del filtro y el escalado correcto.
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}