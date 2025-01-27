/*
  ==============================================================================

    Biquad_TDFII_LSF.cpp
    Created: 7 Oct 2024 4:02:00pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_TDFII_LSF.h"

// EN: Constructor. Initializes the Low Shelf Filter object.
// ES: Constructor. Inicializa el objeto del filtro de estantería baja.
Biquad_TDFII_LSF::Biquad_TDFII_LSF() {}

// EN: Destructor. Cleans up the Low Shelf Filter object.
// ES: Destructor. Libera los recursos del objeto del filtro de estantería baja.
Biquad_TDFII_LSF::~Biquad_TDFII_LSF() {}

// EN: Prepares the filter for processing by setting the sample rate and updating the filter coefficients.
// ES: Prepara el filtro para procesar, configurando la frecuencia de muestreo y actualizando los coeficientes del filtro.
void Biquad_TDFII_LSF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter();
}

// EN: Processes an entire audio buffer through the Low Shelf Filter.
// ES: Procesa un buffer completo de audio a través del filtro de estantería baja.
void Biquad_TDFII_LSF::process(juce::AudioBuffer<float> inBuffer)
{
    int numChannels = inBuffer.getNumChannels(); // EN: Get the number of channels. / ES: Obtiene el número de canales.
    int numSamples = inBuffer.getNumSamples();   // EN: Get the number of samples. / ES: Obtiene el número de muestras.

    // EN: Loop through each channel and each sample to apply the filter.
    // ES: Itera por cada canal y muestra para aplicar el filtro.
    for (int channel = 0; channel < numChannels; channel++)
    {
        for (int i = 0; i < numSamples; i++)
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Get the current input sample. / ES: Obtiene la muestra de entrada actual.

            float outSample = processSample(inSample, channel); // EN: Process the sample through the filter. / ES: Procesa la muestra con el filtro.

            inBuffer.setSample(channel, i, outSample); // EN: Store the filtered sample back in the buffer. / ES: Almacena la muestra filtrada de nuevo en el buffer.
        }
    }
}

// EN: Processes a single sample for a specific channel using the filter's equations.
// ES: Procesa una única muestra para un canal específico usando las ecuaciones del filtro.
float Biquad_TDFII_LSF::processSample(float inSample, int channel)
{
    auto y = b0 * inSample + r1[channel]; // EN: Calculate the filtered output. / ES: Calcula la salida filtrada.

    r1[channel] = b1 * inSample + (-a1) * y + r2[channel]; // EN: Update the first delay register. / ES: Actualiza el primer registro de retardo.
    r2[channel] = b2 * inSample + (-a2) * y;              // EN: Update the second delay register. / ES: Actualiza el segundo registro de retardo.

    return y; // EN: Return the filtered output. / ES: Devuelve la salida filtrada.
}

// EN: Sets the cutoff frequency of the filter and updates the coefficients.
// ES: Configura la frecuencia de corte del filtro y actualiza los coeficientes.
void Biquad_TDFII_LSF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

// EN: Sets the Q factor (resonance) of the filter and updates the coefficients.
// ES: Configura el factor Q (resonancia) del filtro y actualiza los coeficientes.
void Biquad_TDFII_LSF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

// EN: Sets the gain of the filter in decibels and updates the coefficients.
// ES: Configura la ganancia del filtro en decibelios y actualiza los coeficientes.
void Biquad_TDFII_LSF::setGain(float inGain)
{
    Gain = inGain;
    updateFilter();
}

// EN: Updates the filter coefficients based on the frequency, Q factor, and gain parameters.
// ES: Actualiza los coeficientes del filtro basándose en los parámetros de frecuencia, factor Q y ganancia.
void Biquad_TDFII_LSF::updateFilter()
{
    // EN: Calculate intermediate values for the filter's equations.
    // ES: Calcula valores intermedios para las ecuaciones del filtro.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);
    A = sqrt(powf(10.0f, Gain / 20.0f)); // EN: Convert gain to linear amplitude. / ES: Convierte la ganancia a amplitud lineal.

    // EN: Calculate the feedforward coefficients (b0, b1, b2).
    // ES: Calcula los coeficientes de avance (b0, b1, b2).
    b0 = A * ((A + 1.0f) - ((A - 1.0f) * cosf(w0)) + (2.0f * sqrtf(A) * alpha));
    b1 = 2.0f * A * ((A - 1.0f) - ((A + 1.0f) * cosf(w0)));
    b2 = A * ((A + 1.0f) - ((A - 1.0f) * cosf(w0)) - (2.0f * sqrtf(A) * alpha));

    // EN: Calculate the feedback coefficients (a0, a1, a2).
    // ES: Calcula los coeficientes de retroalimentación (a0, a1, a2).
    a0 = (A + 1.0f) + ((A - 1.0f) * cosf(w0)) + (2.0f * sqrtf(A) * alpha);
    a1 = -2.0f * ((A - 1.0f) + ((A + 1.0f) * cosf(w0)));
    a2 = (A + 1.0f) + ((A - 1.0f) * cosf(w0)) - (2.0f * sqrtf(A) * alpha);

    // EN: Normalize the coefficients by dividing each by a0.
    // ES: Normaliza los coeficientes dividiendo cada uno por a0.
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}
