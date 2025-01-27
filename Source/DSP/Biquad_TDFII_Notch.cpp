/*
  ==============================================================================

    Biquad_TDFII_Notch.cpp
    Created: 7 Oct 2024 4:02:43pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_TDFII_Notch.h"

// EN: Constructor for the Notch Filter. Initializes the object.
// ES: Constructor para el filtro de muesca. Inicializa el objeto.
Biquad_TDFII_Notch::Biquad_TDFII_Notch() {}

// EN: Destructor for the Notch Filter. Cleans up resources.
// ES: Destructor para el filtro de muesca. Libera los recursos.
Biquad_TDFII_Notch::~Biquad_TDFII_Notch() {}

// EN: Prepares the filter by setting the sample rate and updating filter coefficients.
// ES: Prepara el filtro configurando la frecuencia de muestreo y actualizando los coeficientes del filtro.
void Biquad_TDFII_Notch::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

// EN: Processes an entire audio buffer through the notch filter, channel by channel and sample by sample.
// ES: Procesa un buffer completo de audio a través del filtro de muesca, canal por canal y muestra por muestra.
void Biquad_TDFII_Notch::process(juce::AudioBuffer<float> inBuffer)
{
    int numChannels = inBuffer.getNumChannels(); // EN: Number of channels. / ES: Número de canales.
    int numSamples = inBuffer.getNumSamples();   // EN: Number of samples per channel. / ES: Número de muestras por canal.

    for (int channel = 0; channel < numChannels; channel++)
    {
        for (int i = 0; i < numSamples; i++)
        {
            // EN: Retrieve the input sample.
            // ES: Obtiene la muestra de entrada.
            float inSample = inBuffer.getSample(channel, i);

            // EN: Process the sample using the notch filter.
            // ES: Procesa la muestra usando el filtro de muesca.
            float outSample = processSample(inSample, channel);

            // EN: Set the processed sample back into the buffer.
            // ES: Guarda la muestra procesada en el buffer.
            inBuffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Processes a single sample using the Transposed Direct Form II algorithm.
// ES: Procesa una única muestra usando el algoritmo de Forma Directa Transpuesta II.
float Biquad_TDFII_Notch::processSample(float inSample, int channel)
{
    // EN: Calculate the output sample using the biquad filter equation.
    // ES: Calcula la muestra de salida usando la ecuación del filtro Biquad.
    auto y = b0 * inSample + r1[channel];

    // EN: Update the delay buffers.
    // ES: Actualiza los buffers de retardo.
    r1[channel] = b1 * inSample + (-a1) * y + r2[channel];
    r2[channel] = b2 * inSample + (-a2) * y;

    return y;
}

// EN: Sets the cutoff frequency of the notch filter and updates the coefficients.
// ES: Configura la frecuencia de corte del filtro de muesca y actualiza los coeficientes.
void Biquad_TDFII_Notch::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

// EN: Sets the Q factor (resonance) of the notch filter and updates the coefficients.
// ES: Configura el factor Q (resonancia) del filtro de muesca y actualiza los coeficientes.
void Biquad_TDFII_Notch::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

// EN: Updates the filter coefficients based on the current frequency, Q factor, and sample rate.
// ES: Actualiza los coeficientes del filtro basándose en la frecuencia actual, el factor Q y la frecuencia de muestreo.
void Biquad_TDFII_Notch::updateFilter()
{
    // EN: Calculate angular frequency and alpha (bandwidth parameter).
    // ES: Calcula la frecuencia angular y alpha (parámetro de ancho de banda).
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    // EN: Set the coefficients for a notch filter.
    // ES: Configura los coeficientes para un filtro de muesca.
    b0 = 1.0f;
    b1 = -2.0f * cosf(w0);
    b2 = 1.0f;

    a0 = 1.0 + alpha;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha;

    // EN: Normalize the coefficients by dividing all of them by a0.
    // ES: Normaliza los coeficientes dividiendo todos ellos por a0.
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}
