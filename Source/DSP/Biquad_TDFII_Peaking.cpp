/*
  ==============================================================================

    Biquad_TDFII_Peaking.cpp
    Created: 7 Oct 2024 4:02:59pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_TDFII_Peaking.h"

// EN: Constructor for the Peaking EQ filter. Initializes the object.
// ES: Constructor para el filtro de ecualización de pico. Inicializa el objeto.
Biquad_TDFII_Peaking::Biquad_TDFII_Peaking() {}

// EN: Destructor for the Peaking EQ filter. Cleans up resources.
// ES: Destructor para el filtro de ecualización de pico. Libera los recursos.
Biquad_TDFII_Peaking::~Biquad_TDFII_Peaking() {}

// EN: Prepares the filter by setting the sample rate and updating the filter coefficients.
// ES: Prepara el filtro configurando la frecuencia de muestreo y actualizando los coeficientes del filtro.
void Biquad_TDFII_Peaking::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

// EN: Processes an entire audio buffer through the peaking EQ filter, channel by channel and sample by sample.
// ES: Procesa un buffer completo de audio a través del filtro de ecualización de pico, canal por canal y muestra por muestra.
void Biquad_TDFII_Peaking::process(juce::AudioBuffer<float> inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            // EN: Retrieve the input sample.
            // ES: Obtiene la muestra de entrada.
            float inSample = inBuffer.getSample(channel, i);

            // EN: Process the sample using the peaking EQ filter.
            // ES: Procesa la muestra usando el filtro de ecualización de pico.
            float outSample = processSample(inSample, channel);

            // EN: Set the processed sample back into the buffer.
            // ES: Guarda la muestra procesada en el buffer.
            inBuffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Processes a single sample using the Transposed Direct Form II algorithm.
// ES: Procesa una única muestra usando el algoritmo de Forma Directa Transpuesta II.
float Biquad_TDFII_Peaking::processSample(float inSample, int channel)
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

// EN: Sets the center frequency of the peaking filter and updates the coefficients.
// ES: Configura la frecuencia central del filtro de pico y actualiza los coeficientes.
void Biquad_TDFII_Peaking::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

// EN: Sets the gain (boost or cut) of the peaking filter and updates the coefficients.
// ES: Configura la ganancia (aumento o reducción) del filtro de pico y actualiza los coeficientes.
void Biquad_TDFII_Peaking::setGain(float inGain)
{
    Gain = inGain;
    updateFilter();
}

// EN: Sets the Q factor (quality factor) of the peaking filter and updates the coefficients.
// ES: Configura el factor Q (factor de calidad) del filtro de pico y actualiza los coeficientes.
void Biquad_TDFII_Peaking::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

// EN: Updates the filter coefficients based on the current frequency, gain, Q factor, and sample rate.
// ES: Actualiza los coeficientes del filtro basándose en la frecuencia, la ganancia, el factor Q y la frecuencia de muestreo actuales.
void Biquad_TDFII_Peaking::updateFilter()
{
    // EN: Calculate angular frequency, alpha, and the amplitude gain factor A.
    // ES: Calcula la frecuencia angular, alpha y el factor de ganancia de amplitud A.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);
    A = sqrt(powf(10.0f, Gain / 20.0f));

    // EN: Set the coefficients for a peaking EQ filter.
    // ES: Configura los coeficientes para un filtro de ecualización de pico.
    b0 = 1.0f + alpha * A;
    b1 = -2.0f * cosf(w0);
    b2 = 1.0f - alpha * A;

    a0 = 1.0 + alpha / A;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha / A;

    // EN: Normalize the coefficients by dividing all of them by a0.
    // ES: Normaliza los coeficientes dividiendo todos ellos por a0.
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}
