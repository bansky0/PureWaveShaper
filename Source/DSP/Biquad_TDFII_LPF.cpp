/*
  ==============================================================================

    Biquad_TDFII_LPF.cpp
    Created: 7 Oct 2024 3:18:16pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_TDFII_LPF.h"

// EN: Constructor. Initializes the low-pass filter instance.
// ES: Constructor. Inicializa la instancia del filtro de paso bajo.
Biquad_TDFII_LPF::Biquad_TDFII_LPF()
{
}

// EN: Destructor. Cleans up any allocated resources (if applicable).
// ES: Destructor. Libera cualquier recurso asignado (si aplica).
Biquad_TDFII_LPF::~Biquad_TDFII_LPF()
{
}

// EN: Prepares the filter by setting the sample rate and updating the filter coefficients.
// ES: Prepara el filtro configurando la frecuencia de muestreo y actualizando los coeficientes del filtro.
void Biquad_TDFII_LPF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

// EN: Processes an entire audio buffer through the low-pass filter.
// ES: Procesa un buffer completo de audio a través del filtro de paso bajo.
void Biquad_TDFII_LPF::process(juce::AudioBuffer<float>& inBuffer)
{
    int numChannels = inBuffer.getNumChannels(); // EN: Get the number of channels in the buffer.
    // ES: Obtiene el número de canales en el buffer.
    int numSamples = inBuffer.getNumSamples();   // EN: Get the number of samples per channel.
    // ES: Obtiene el número de muestras por canal.

// EN: Loop through each channel and sample, applying the filter to each sample.
// ES: Recorre cada canal y muestra, aplicando el filtro a cada muestra.
    for (int channel = 0; channel < numChannels; channel++)
    {
        for (int i = 0; i < numSamples; i++)
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Read the input sample.
            // ES: Lee la muestra de entrada.

            float outSample = processSample(inSample, channel); // EN: Process the sample through the filter.
            // ES: Procesa la muestra a través del filtro.

            inBuffer.setSample(channel, i, outSample); // EN: Write the processed sample back to the buffer.
            // ES: Escribe la muestra procesada de nuevo en el buffer.
        }
    }
}

// EN: Processes a single sample for a specific channel using the low-pass filter equations.
// ES: Procesa una única muestra para un canal específico utilizando las ecuaciones del filtro de paso bajo.
float Biquad_TDFII_LPF::processSample(float inSample, int channel)
{
    auto y = b0 * inSample + r1[channel]; // EN: Calculate the output sample using the filter equation.
    // ES: Calcula la muestra de salida utilizando la ecuación del filtro.

// EN: Update the delay lines with the current input and output samples.
// ES: Actualiza las líneas de retardo con las muestras de entrada y salida actuales.
    r1[channel] = b1 * inSample + (-a1) * y + r2[channel];
    r2[channel] = b2 * inSample + (-a2) * y;

    return y; // EN: Return the filtered output sample.
    // ES: Retorna la muestra filtrada de salida.
}

// EN: Sets the cutoff frequency of the filter and updates the coefficients.
// ES: Establece la frecuencia de corte del filtro y actualiza los coeficientes.
void Biquad_TDFII_LPF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

// EN: Sets the Q factor (resonance) of the filter and updates the coefficients.
// ES: Establece el factor Q (resonancia) del filtro y actualiza los coeficientes.
void Biquad_TDFII_LPF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

// EN: Updates the filter coefficients based on the current sample rate, frequency, and Q factor.
// ES: Actualiza los coeficientes del filtro basándose en la frecuencia de muestreo, frecuencia y factor Q actuales.
void Biquad_TDFII_LPF::updateFilter()
{
    // EN: Calculate intermediate values for the filter coefficients.
    // ES: Calcula valores intermedios para los coeficientes del filtro.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate); // EN: Angular frequency.
    // ES: Frecuencia angular.
    alpha = sinf(w0) / (2.0f * Q); // EN: Filter slope and bandwidth.
    // ES: Pendiente y ancho de banda del filtro.

// EN: Calculate the feedforward coefficients (b0, b1, b2).
// ES: Calcula los coeficientes de avance (b0, b1, b2).
    b0 = (1.0f - cosf(w0)) / 2.0f;
    b1 = 1.0f - cosf(w0);
    b2 = (1.0f - cosf(w0)) / 2.0f;

    // EN: Calculate the feedback coefficients (a0, a1, a2).
    // ES: Calcula los coeficientes de retroalimentación (a0, a1, a2).
    a0 = 1.0f + alpha;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha;

    // EN: Normalize the coefficients by dividing each by a0.
    // ES: Normaliza los coeficientes dividiendo cada uno por a0.
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}
