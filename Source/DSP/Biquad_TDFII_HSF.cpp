/*
  ==============================================================================

    Biquad_TDFII_HSF.cpp
    Created: 7 Oct 2024 4:02:12pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_TDFII_HSF.h"

// EN: Constructor. Initializes the Biquad_TDFII_HSF instance.
// ES: Constructor. Inicializa la instancia de Biquad_TDFII_HSF.
Biquad_TDFII_HSF::Biquad_TDFII_HSF() {}

// EN: Destructor. Cleans up the Biquad_TDFII_HSF instance.
// ES: Destructor. Limpia la instancia de Biquad_TDFII_HSF.
Biquad_TDFII_HSF::~Biquad_TDFII_HSF() {}

// EN: Prepares the filter by setting the sample rate and initializing the filter coefficients.
// ES: Prepara el filtro configurando la frecuencia de muestreo e inicializando los coeficientes del filtro.
void Biquad_TDFII_HSF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate; // EN: Store the input sample rate.
    // ES: Almacena la frecuencia de muestreo proporcionada.
    updateFilter();            // EN: Update filter coefficients.
    // ES: Actualiza los coeficientes del filtro.
}

// EN: Processes the entire audio buffer through the filter.
// ES: Procesa todo el buffer de audio a través del filtro.
void Biquad_TDFII_HSF::process(juce::AudioBuffer<float> inBuffer)
{
    int numChannels = inBuffer.getNumChannels(); // EN: Get the number of channels in the buffer.
    // ES: Obtiene el número de canales en el buffer.
    int numSamples = inBuffer.getNumSamples();   // EN: Get the number of samples in the buffer.
    // ES: Obtiene el número de muestras en el buffer.

// EN: Iterate over each channel and sample in the buffer.
// ES: Itera sobre cada canal y muestra en el buffer.
    for (int channel = 0; channel < numChannels; channel++)
    {
        for (int i = 0; i < numSamples; i++)
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Get the input sample.
            // ES: Obtiene la muestra de entrada.

            float outSample = processSample(inSample, channel); // EN: Process the sample through the filter.
            // ES: Procesa la muestra a través del filtro.

            inBuffer.setSample(channel, i, outSample); // EN: Write the output sample back to the buffer.
            // ES: Escribe la muestra procesada de vuelta al buffer.
        }
    }
}

// EN: Processes a single audio sample for a specific channel using the filter.
// ES: Procesa una única muestra de audio para un canal específico utilizando el filtro.
float Biquad_TDFII_HSF::processSample(float inSample, int channel)
{
    auto y = b0 * inSample + r1[channel]; // EN: Compute the output using the feedforward coefficients.
    // ES: Calcula la salida utilizando los coeficientes de avance.

    r1[channel] = b1 * inSample + (-a1) * y + r2[channel]; // EN: Update the first delay line.
    // ES: Actualiza la primera línea de retardo.
    r2[channel] = b2 * inSample + (-a2) * y;              // EN: Update the second delay line.
    // ES: Actualiza la segunda línea de retardo.

    return y; // EN: Return the processed sample.
    // ES: Devuelve la muestra procesada.
}

// EN: Sets the cutoff frequency for the high shelf filter and updates the coefficients.
// ES: Establece la frecuencia de corte del filtro de estantería alta y actualiza los coeficientes.
void Biquad_TDFII_HSF::setFrequency(float inFrequency)
{
    frequency = inFrequency; // EN: Store the frequency.
    // ES: Almacena la frecuencia.
    updateFilter();          // EN: Update filter coefficients.
    // ES: Actualiza los coeficientes del filtro.
}

// EN: Sets the Q factor (resonance) and updates the coefficients.
// ES: Establece el factor Q (resonancia) y actualiza los coeficientes.
void Biquad_TDFII_HSF::setQ(float inQ)
{
    Q = inQ;        // EN: Store the Q value.
    // ES: Almacena el valor de Q.
    updateFilter(); // EN: Update filter coefficients.
    // ES: Actualiza los coeficientes del filtro.
}

// EN: Sets the gain for the high shelf filter and updates the coefficients.
// ES: Establece la ganancia del filtro de estantería alta y actualiza los coeficientes.
void Biquad_TDFII_HSF::setGain(float inGain)
{
    Gain = inGain;  // EN: Store the gain value.
    // ES: Almacena el valor de ganancia.
    updateFilter(); // EN: Update filter coefficients.
    // ES: Actualiza los coeficientes del filtro.
}

// EN: Updates the filter coefficients based on the current parameters.
// ES: Actualiza los coeficientes del filtro basándose en los parámetros actuales.
void Biquad_TDFII_HSF::updateFilter()
{
    // EN: Calculate the angular frequency (w0) and alpha.
    // ES: Calcula la frecuencia angular (w0) y alpha.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);
    A = sqrt(powf(10.0f, Gain / 20.0f)); // EN: Convert gain from dB to linear amplitude.
    // ES: Convierte la ganancia de dB a amplitud lineal.

// EN: Compute feedforward coefficients for the high shelf filter.
// ES: Calcula los coeficientes de avance para el filtro de estantería alta.
    b0 = A * ((A + 1.0f) + ((A - 1.0f) * cosf(w0)) + (2.0f * sqrtf(A) * alpha));
    b1 = -2.0f * A * ((A - 1.0f) + ((A + 1.0f) * cosf(w0)));
    b2 = A * ((A + 1.0f) + ((A - 1.0f) * cosf(w0)) - (2.0f * sqrtf(A) * alpha));

    // EN: Compute feedback coefficients for the high shelf filter.
    // ES: Calcula los coeficientes de retroalimentación para el filtro de estantería alta.
    a0 = (A + 1.0f) - ((A - 1.0f) * cosf(w0)) + (2.0f * sqrtf(A) * alpha);
    a1 = 2.0f * ((A - 1.0f) - ((A + 1.0f) * cosf(w0)));
    a2 = (A + 1.0f) - ((A - 1.0f) * cosf(w0)) - (2.0f * sqrtf(A) * alpha);

    // EN: Normalize coefficients by dividing all by a0.
    // ES: Normaliza los coeficientes dividiendo todos por a0.
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}
