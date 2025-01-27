/*
  ==============================================================================

    Biquad_TDFII_APF.cpp
    Created: 7 Oct 2024 3:59:49pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_TDFII_APF.h"

// EN: Constructor for the Biquad_TDFII_APF class.
// ES: Constructor de la clase Biquad_TDFII_APF.
Biquad_TDFII_APF::Biquad_TDFII_APF()
{
}

// EN: Destructor for the Biquad_TDFII_APF class.
// ES: Destructor de la clase Biquad_TDFII_APF.
Biquad_TDFII_APF::~Biquad_TDFII_APF()
{
}

// EN: Initializes the filter with the provided sample rate and updates the coefficients.
// ES: Inicializa el filtro con la frecuencia de muestreo proporcionada y actualiza los coeficientes.
void Biquad_TDFII_APF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

// EN: Processes the entire audio buffer through the filter, applying the filter to each sample.
// ES: Procesa el buffer completo de audio a través del filtro, aplicando el filtro a cada muestra.
void Biquad_TDFII_APF::process(juce::AudioBuffer<float>& inBuffer)
{
    int numChannels = inBuffer.getNumChannels(); // EN: Number of audio channels.
    // ES: Número de canales de audio.
    int numSamples = inBuffer.getNumSamples();   // EN: Number of samples in the buffer.
    // ES: Número de muestras en el buffer.

    for (int channel = 0; channel < numChannels; channel++) // EN: Iterate through each channel.
        // ES: Iterar por cada canal.
    {
        for (int i = 0; i < numSamples; i++) // EN: Iterate through each sample.
            // ES: Iterar por cada muestra.
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Get the input sample.
            // ES: Obtener la muestra de entrada.

            float outSample = processSample(inSample, channel); // EN: Process the sample through the filter.
            // ES: Procesar la muestra a través del filtro.

            inBuffer.setSample(channel, i, outSample); // EN: Set the processed sample back into the buffer.
            // ES: Colocar la muestra procesada de nuevo en el buffer.
        }
    }
}

// EN: Processes a single sample for a specific channel using the Transposed Direct Form II structure.
// ES: Procesa una muestra individual para un canal específico utilizando la estructura de Forma Directa Transpuesta II.
float Biquad_TDFII_APF::processSample(float inSample, int channel)
{
    auto y = b0 * inSample + r1[channel]; // EN: Calculate the current output sample.
    // ES: Calcular la muestra de salida actual.

// EN: Update the internal state variables for the next iteration.
// ES: Actualizar las variables de estado internas para la siguiente iteración.
    r1[channel] = b1 * inSample + (-a1) * y + r2[channel];
    r2[channel] = b2 * inSample + (-a2) * y;

    return y; // EN: Return the filtered output sample.
    // ES: Devolver la muestra de salida filtrada.
}

// EN: Sets the filter's center frequency and updates the coefficients.
// ES: Establece la frecuencia central del filtro y actualiza los coeficientes.
void Biquad_TDFII_APF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

// EN: Sets the filter's Q factor (resonance) and updates the coefficients.
// ES: Establece el factor Q (resonancia) del filtro y actualiza los coeficientes.
void Biquad_TDFII_APF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

// EN: Updates the filter coefficients based on the current frequency, Q factor, and sample rate.
// ES: Actualiza los coeficientes del filtro según la frecuencia actual, el factor Q y la frecuencia de muestreo.
void Biquad_TDFII_APF::updateFilter()
{
    // EN: Calculate angular frequency and alpha (a parameter related to bandwidth).
    // ES: Calcular la frecuencia angular y alpha (un parámetro relacionado con el ancho de banda).
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    // EN: Calculate the filter coefficients for the all-pass filter.
    // ES: Calcular los coeficientes del filtro para el filtro pasa todo.
    b0 = 1.0f - alpha;
    b1 = -2.0f * cosf(w0);
    b2 = 1.0f + alpha;

    a0 = 1.0 + alpha;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha;

    // EN: Normalize the coefficients by dividing them by a0.
    // ES: Normalizar los coeficientes dividiéndolos por a0.
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}