/*
  ==============================================================================

    Biquad_TDFII_HPF.cpp
    Created: 7 Oct 2024 4:01:47pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_TDFII_HPF.h"

// EN: Constructor for the Biquad_TDFII_HPF class. Initializes the filter object.
// ES: Constructor de la clase Biquad_TDFII_HPF. Inicializa el objeto del filtro.
Biquad_TDFII_HPF::Biquad_TDFII_HPF() {}

// EN: Destructor for the Biquad_TDFII_HPF class.
// ES: Destructor de la clase Biquad_TDFII_HPF.
Biquad_TDFII_HPF::~Biquad_TDFII_HPF() {}

// EN: Prepares the filter by setting the sample rate and updating the filter coefficients.
// ES: Prepara el filtro configurando la frecuencia de muestreo y actualizando los coeficientes del filtro.
void Biquad_TDFII_HPF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter(); // EN: Update required because filter coefficients depend on the sample rate. 
    // ES: Actualización necesaria porque los coeficientes del filtro dependen de la frecuencia de muestreo.
}

// EN: Processes an entire audio buffer through the high-pass filter.
// ES: Procesa un buffer de audio completo a través del filtro pasa altos.
void Biquad_TDFII_HPF::process(juce::AudioBuffer<float> inBuffer)
{
    int numChannels = inBuffer.getNumChannels(); // EN: Get number of channels in the buffer.
    // ES: Obtiene el número de canales en el buffer.
    int numSamples = inBuffer.getNumSamples();   // EN: Get number of samples per channel.
    // ES: Obtiene el número de muestras por canal.

    for (int channel = 0; channel < numChannels; channel++)
    {
        for (int i = 0; i < numSamples; i++)
        {
            // EN: Retrieve the input sample from the buffer.
            // ES: Recupera la muestra de entrada del buffer.
            float inSample = inBuffer.getSample(channel, i);

            // EN: Process the sample through the filter.
            // ES: Procesa la muestra a través del filtro.
            float outSample = processSample(inSample, channel);

            // EN: Store the processed sample back into the buffer.
            // ES: Almacena la muestra procesada de nuevo en el buffer.
            inBuffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Processes a single audio sample for a specific channel using the high-pass filter algorithm.
// ES: Procesa una única muestra de audio para un canal específico utilizando el algoritmo del filtro pasa altos.
float Biquad_TDFII_HPF::processSample(float inSample, int channel)
{
    // EN: Compute the output sample using the Direct Form II Transposed algorithm.
    // ES: Calcula la muestra de salida utilizando el algoritmo de Forma Directa II Transpuesta.
    auto y = b0 * inSample + r1[channel];

    // EN: Update the filter's state variables for the current channel.
    // ES: Actualiza las variables de estado del filtro para el canal actual.
    r1[channel] = b1 * inSample + (-a1) * y + r2[channel];
    r2[channel] = b2 * inSample + (-a2) * y;

    return y;
}

// EN: Sets the cutoff frequency of the high-pass filter and updates the coefficients.
// ES: Establece la frecuencia de corte del filtro pasa altos y actualiza los coeficientes.
void Biquad_TDFII_HPF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

// EN: Sets the Q factor (resonance) of the high-pass filter and updates the coefficients.
// ES: Establece el factor Q (resonancia) del filtro pasa altos y actualiza los coeficientes.
void Biquad_TDFII_HPF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

// EN: Updates the filter coefficients based on the current frequency, Q, and sample rate.
// ES: Actualiza los coeficientes del filtro en función de la frecuencia, Q y frecuencia de muestreo actuales.
void Biquad_TDFII_HPF::updateFilter()
{
    // EN: Calculate coefficients for the High-Pass Filter (HPF).
    // ES: Calcula los coeficientes para el filtro pasa altos (HPF).
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    // EN: Feedforward coefficients for HPF.
    // ES: Coeficientes de avance para el HPF.
    b0 = (1.0f + cosf(w0)) / 2.0f;
    b1 = -(1.0f + cosf(w0)); // EN: Note that this implementation differs from common reference tables.
    // ES: Nota que esta implementación difiere de las tablas de referencia comunes.
    b2 = (1.0f + cosf(w0)) / 2.0f;

    // EN: Feedback coefficients for HPF.
    // ES: Coeficientes de retroalimentación para el HPF.
    a0 = 1.0f + alpha;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha;

    // EN: Normalize the coefficients by dividing by a0.
    // ES: Normaliza los coeficientes dividiendo por a0.
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}
