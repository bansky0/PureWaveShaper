/*
  ==============================================================================

    Biquad_DFI_LPF.cpp
    Created: 7 Oct 2024 10:18:42am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_II_LPF.h"

// EN: Constructor - Initializes the low-pass filter object.
// ES: Constructor - Inicializa el objeto del filtro de paso bajo.
Biquad_II_LPF::Biquad_II_LPF()
{
}

// EN: Destructor - No dynamic memory cleanup is required.
// ES: Destructor - No se requiere limpieza de memoria dinámica.
Biquad_II_LPF::~Biquad_II_LPF()
{
}

// EN: Prepares the filter by setting the sample rate and updating the filter coefficients.
// ES: Prepara el filtro configurando la frecuencia de muestreo y actualizando los coeficientes del filtro.
void Biquad_II_LPF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

// EN: Processes an audio buffer by applying the low-pass filter to each sample in each channel.
// ES: Procesa un buffer de audio aplicando el filtro de paso bajo a cada muestra en cada canal.
void Biquad_II_LPF::process(juce::AudioBuffer<float>& inBuffer)
{
    int numChannels = inBuffer.getNumChannels(); // EN: Number of audio channels in the buffer. // ES: Número de canales de audio en el buffer.
    int numSamples = inBuffer.getNumSamples();   // EN: Number of samples in the buffer. // ES: Número de muestras en el buffer.

    // EN: Iterate over each channel and process each sample.
    // ES: Itera sobre cada canal y procesa cada muestra.
    for (int channel = 0; channel < numChannels; channel++)
    {
        for (int i = 0; i < numSamples; i++)
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Get the input sample. // ES: Obtiene la muestra de entrada.

            float outSample = processSample(inSample, channel); // EN: Process the sample using the filter. // ES: Procesa la muestra utilizando el filtro.

            inBuffer.setSample(channel, i, outSample); // EN: Write the filtered sample back to the buffer. // ES: Escribe la muestra filtrada de nuevo en el buffer.
        }
    }
}

// EN: Processes a single audio sample for a specific channel using the low-pass filter algorithm.
// ES: Procesa una muestra de audio individual para un canal específico utilizando el algoritmo del filtro de paso bajo.
float Biquad_II_LPF::processSample(float inSample, int channel)
{
    // EN: Compute the intermediate value 'w' for the filter.
    // ES: Calcula el valor intermedio 'w' para el filtro.
    auto w = inSample - a1 * w1[channel] - a2 * w2[channel];

    // EN: Compute the filtered output sample 'y' using the feedforward coefficients.
    // ES: Calcula la muestra de salida filtrada 'y' utilizando los coeficientes de realimentación directa.
    auto y = b0 * w + b1 * w1[channel] + b2 * w2[channel];

    // EN: Update the delay line states for the next sample.
    // ES: Actualiza los estados de la línea de retardo para la siguiente muestra.
    w2[channel] = w1[channel];
    w1[channel] = w;

    return y; // EN: Return the filtered sample. // ES: Devuelve la muestra filtrada.
}

// EN: Sets the cutoff frequency for the filter and updates the coefficients.
// ES: Configura la frecuencia de corte para el filtro y actualiza los coeficientes.
void Biquad_II_LPF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

// EN: Sets the Q factor (resonance) for the filter and updates the coefficients.
// ES: Configura el factor Q (resonancia) para el filtro y actualiza los coeficientes.
void Biquad_II_LPF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

// EN: Updates the filter coefficients based on the current frequency, Q factor, and sample rate.
// ES: Actualiza los coeficientes del filtro según la frecuencia actual, el factor Q y la frecuencia de muestreo.
void Biquad_II_LPF::updateFilter()
{
    // EN: Calculate intermediate values for the filter design.
    // ES: Calcula valores intermedios para el diseño del filtro.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate); // EN: Angular frequency. // ES: Frecuencia angular.
    alpha = sinf(w0) / (2.0f * Q); // EN: Alpha determines the filter's bandwidth. // ES: Alpha determina el ancho de banda del filtro.

    // EN: Calculate the feedforward coefficients.
    // ES: Calcula los coeficientes de realimentación directa.
    b0 = (1.0f - cosf(w0)) / 2.0f;
    b1 = 1.0f - cosf(w0);
    b2 = (1.0f - cosf(w0)) / 2.0f;

    // EN: Calculate the feedback coefficients.
    // ES: Calcula los coeficientes de retroalimentación.
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