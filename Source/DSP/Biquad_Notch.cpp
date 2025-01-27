/*
  ==============================================================================

    Biquad_Notch.cpp
    Created: 1 Oct 2024 12:27:30pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_Notch.h"

// EN: Constructor for the Biquad_Notch class.
// ES: Constructor de la clase Biquad_Notch.
Biquad_Notch::Biquad_Notch() {}

// EN: Destructor for the Biquad_Notch class.
// ES: Destructor de la clase Biquad_Notch.
Biquad_Notch::~Biquad_Notch() {}

// EN: Prepares the filter with the provided sample rate and updates coefficients.
// ES: Prepara el filtro con la frecuencia de muestreo proporcionada y actualiza los coeficientes.
void Biquad_Notch::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

// EN: Processes an entire audio buffer by applying the notch filter to each sample.
// ES: Procesa un buffer completo de audio aplicando el filtro notch a cada muestra.
void Biquad_Notch::process(juce::AudioBuffer<float> inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            // EN: Retrieve the current input sample.
            // ES: Obtiene la muestra de entrada actual.
            float inSample = inBuffer.getSample(channel, i);

            // EN: Process the sample through the notch filter.
            // ES: Procesa la muestra a través del filtro notch.
            float outSample = processSample(inSample, channel);

            // EN: Write the processed sample back to the buffer.
            // ES: Escribe la muestra procesada de vuelta al buffer.
            inBuffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Processes a single sample for a specific channel using the notch filter.
// ES: Procesa una sola muestra para un canal específico utilizando el filtro notch.
float Biquad_Notch::processSample(float inSample, int channel)
{
    // EN: Apply the Direct Form II filter equation.
    // ES: Aplica la ecuación del filtro en Forma Directa II.
    auto y = (b0 * inSample + b1 * x1[channel] + b2 * x2[channel] + (-a1) * y1[channel] + (-a2) * y2[channel]) * (1.0f / a0);

    // EN: Update the delay buffers.
    // ES: Actualiza los buffers de retardo.
    x2[channel] = x1[channel];
    x1[channel] = inSample;
    y2[channel] = y1[channel];
    y1[channel] = y;

    return y;
}

// EN: Sets the cutoff frequency of the notch filter and updates the coefficients.
// ES: Establece la frecuencia de corte del filtro notch y actualiza los coeficientes.
void Biquad_Notch::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

// EN: Sets the Q factor (quality factor) of the notch filter and updates the coefficients.
// ES: Establece el factor Q (factor de calidad) del filtro notch y actualiza los coeficientes.
void Biquad_Notch::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

// EN: Updates the filter coefficients based on the current frequency and Q values.
// ES: Actualiza los coeficientes del filtro según los valores actuales de frecuencia y Q.
void Biquad_Notch::updateFilter()
{
    // EN: Calculate angular frequency and bandwidth parameter.
    // ES: Calcula la frecuencia angular y el parámetro de ancho de banda.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    // EN: Set the coefficients for a notch filter.
    // ES: Establece los coeficientes para un filtro notch.
    b0 = 1.0f;                      // EN: b0 coefficient.
                                    // ES: Coeficiente b0.
    b1 = -2.0f * cosf(w0);          // EN: b1 coefficient.
                                    // ES: Coeficiente b1.
    b2 = 1.0f;                      // EN: b2 coefficient.
                                    // ES: Coeficiente b2.

    a0 = 1.0f + alpha;              // EN: a0 coefficient.
                                    // ES: Coeficiente a0.
    a1 = -2.0f * cosf(w0);          // EN: a1 coefficient.
                                    // ES: Coeficiente a1.
    a2 = 1.0f - alpha;              // EN: a2 coefficient.
                                    // ES: Coeficiente a2.
}
