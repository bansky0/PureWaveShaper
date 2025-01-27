/*
  ==============================================================================

    Biquad_II_Notch.cpp
    Created: 7 Oct 2024 2:37:19pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_II_Notch.h"

// EN: Constructor - Initializes the object, no additional setup is needed.
// ES: Constructor - Inicializa el objeto, no se necesita configuración adicional.
Biquad_II_Notch::Biquad_II_Notch() {}

// EN: Destructor - Cleans up any resources when the object is destroyed.
// ES: Destructor - Limpia los recursos cuando el objeto es destruido.
Biquad_II_Notch::~Biquad_II_Notch() {}

// EN: Prepares the filter by setting the sample rate and updating the filter coefficients.
//     The sample rate is required to calculate the filter parameters and update them accordingly.
// ES: Prepara el filtro estableciendo la frecuencia de muestreo y actualizando los coeficientes del filtro.
//     La frecuencia de muestreo es necesaria para calcular los parámetros del filtro y actualizarlos en consecuencia.
void Biquad_II_Notch::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter(); // Updates the filter coefficients after setting the sample rate.
}

// EN: Processes the entire audio buffer, applying the filter to each sample of each channel.
//     It iterates over all channels and samples in the buffer to apply the filter.
// ES: Procesa todo el buffer de audio, aplicando el filtro a cada muestra de cada canal.
//     Itera sobre todos los canales y muestras del buffer para aplicar el filtro.
void Biquad_II_Notch::process(juce::AudioBuffer<float> inBuffer)
{
    int numChannels = inBuffer.getNumChannels(); // Number of channels in the buffer.
    int numSamples = inBuffer.getNumSamples();   // Number of samples in the buffer.

    // EN: Iterate over each channel.
    // ES: Itera sobre cada canal.
    for (int channel = 0; channel < numChannels; channel++)
    {
        // EN: Iterate over each sample in the current channel.
        // ES: Itera sobre cada muestra en el canal actual.
        for (int i = 0; i < numSamples; i++)
        {
            float inSample = inBuffer.getSample(channel, i); // Get the input sample.

            float outSample = processSample(inSample, channel); // Process the sample with the filter.

            inBuffer.setSample(channel, i, outSample); // Set the processed sample back into the buffer.
        }
    }
}

// EN: Processes a single sample for a specific channel by applying the notch filter.
//     This function calculates the filter output based on the current sample and the filter state.
 // ES: Procesa una sola muestra para un canal específico aplicando el filtro notch.
//     Esta función calcula la salida del filtro basada en la muestra actual y el estado del filtro.
float Biquad_II_Notch::processSample(float inSample, int channel)
{
    // EN: Calculate the internal state variable (w) based on the input sample and previous states.
    // ES: Calcula la variable de estado interna (w) basada en la muestra de entrada y los estados previos.
    auto w = inSample - a1 * w1[channel] - a2 * w2[channel];

    // EN: Calculate the output sample (y) based on the filter coefficients and the internal state.
    // ES: Calcula la muestra de salida (y) basada en los coeficientes del filtro y el estado interno.
    auto y = b0 * w + b1 * w1[channel] + b2 * w2[channel];

    // EN: Update the internal state variables for the next sample.
    // ES: Actualiza las variables de estado internas para la siguiente muestra.
    w2[channel] = w1[channel];
    w1[channel] = w;

    return y; // Return the processed output sample.
}

// EN: Sets the frequency of the notch filter and updates the filter coefficients accordingly.
//     After changing the frequency, the filter coefficients are updated to reflect the new frequency.
// ES: Establece la frecuencia del filtro notch y actualiza los coeficientes del filtro en consecuencia.
//     Después de cambiar la frecuencia, los coeficientes del filtro se actualizan para reflejar la nueva frecuencia.
void Biquad_II_Notch::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter(); // Update the filter coefficients after changing the frequency.
}

// EN: Sets the quality factor (Q) of the notch filter and updates the filter coefficients accordingly.
//     The quality factor controls the width of the notch (filtering effect).
// ES: Establece el factor de calidad (Q) del filtro notch y actualiza los coeficientes del filtro en consecuencia.
//     El factor de calidad controla el ancho del notch (efecto de filtrado).
void Biquad_II_Notch::setQ(float inQ)
{
    Q = inQ;
    updateFilter(); // Update the filter coefficients after changing the Q factor.
}

// EN: Updates the filter coefficients based on the current frequency and Q factor.
//     The filter coefficients (b0, b1, b2, a0, a1, a2) are calculated based on the frequency and Q.
//     The coefficients are normalized by dividing by a0.
// ES: Actualiza los coeficientes del filtro en función de la frecuencia y el factor Q actuales.
//     Los coeficientes del filtro (b0, b1, b2, a0, a1, a2) se calculan en función de la frecuencia y el Q.
//     Los coeficientes se normalizan dividiendo por a0.
void Biquad_II_Notch::updateFilter()
{
    // EN: Calculate angular frequency (w0) and alpha based on the frequency and sample rate.
    //     w0 is the angular frequency and alpha is used in the filter coefficient calculation.
    // ES: Calcula la frecuencia angular (w0) y alpha en función de la frecuencia y la frecuencia de muestreo.
    //     w0 es la frecuencia angular y alpha se utiliza en el cálculo de los coeficientes del filtro.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    // EN: Calculate the filter coefficients based on w0 and alpha.
    //     These coefficients define the behavior of the notch filter.
    // ES: Calcula los coeficientes del filtro en función de w0 y alpha.
    //     Estos coeficientes definen el comportamiento del filtro notch.
    b0 = 1.0f;
    b1 = -2.0f * cosf(w0);
    b2 = 1.0f;

    a0 = 1.0 + alpha;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha;

    // EN: Normalize the coefficients by dividing by a0 to ensure the filter is correctly scaled.
    // ES: Normaliza los coeficientes dividiendo por a0 para asegurar que el filtro esté correctamente escalado.
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}