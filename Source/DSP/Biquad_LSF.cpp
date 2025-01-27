/*
  ==============================================================================

    Biquad_LSF.cpp
    Created: 1 Oct 2024 12:26:41pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_LSF.h"

// EN: Constructor for the biquad low-shelving filter (LSF).
// ES: Constructor para el filtro biquad de tipo shelving bajo (LSF).
Biquad_LSF::Biquad_LSF() {}

// EN: Destructor for cleaning up resources.
// ES: Destructor para limpiar los recursos.
Biquad_LSF::~Biquad_LSF() {}

// EN: Prepares the filter by setting the sample rate and updating filter coefficients.
// ES: Prepara el filtro configurando la frecuencia de muestreo y actualizando los coeficientes del filtro.
void Biquad_LSF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter(); // EN: Update coefficients based on the current settings.
                    // ES: Actualiza los coeficientes según la configuración actual.
}

// EN: Processes an audio buffer by applying the filter to all samples in all channels.
// ES: Procesa un buffer de audio aplicando el filtro a todas las muestras en todos los canales.
void Biquad_LSF::process(juce::AudioBuffer<float> inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++) // EN: Loop through each channel.
                                                                          // ES: Recorre cada canal.
    {
        for (int i = 0; i < inBuffer.getNumSamples(); i++) // EN: Loop through each sample in the channel.
                                                           // ES: Recorre cada muestra en el canal.
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Get the current sample.
                                                             // ES: Obtiene la muestra actual.

            float outSample = processSample(inSample, channel); // EN: Process the sample through the filter.
                                                                // ES: Procesa la muestra a través del filtro.

            inBuffer.setSample(channel, i, outSample); // EN: Write the processed sample back to the buffer.
                                                       // ES: Escribe la muestra procesada de vuelta en el buffer.
        }
    }
}

// EN: Processes a single audio sample for a specific channel.
// ES: Procesa una muestra de audio individual para un canal específico.
float Biquad_LSF::processSample(float inSample, int channel)
{
    auto y = (b0 * inSample + b1 * x1[channel] + b2 * x2[channel] + (-a1) * y1[channel] + (-a2) * y2[channel]) * (1.0f / a0);

    // EN: Update delay states for the filter.
    // ES: Actualiza los estados de retardo del filtro.
    x2[channel] = x1[channel]; // EN: Shift x[n-2] to x[n-1].
                               // ES: Desplaza x[n-2] a x[n-1].
    x1[channel] = inSample;    // EN: Set current input as x[n].
                               // ES: Establece la entrada actual como x[n].
    y2[channel] = y1[channel]; // EN: Shift y[n-2] to y[n-1].
                               // ES: Desplaza y[n-2] a y[n-1].
    y1[channel] = y;           // EN: Set current output as y[n].
                               // ES: Establece la salida actual como y[n].

    return y; // EN: Return the processed sample.
              // ES: Devuelve la muestra procesada.
}

// EN: Sets the cutoff frequency for the filter.
// ES: Establece la frecuencia de corte para el filtro.
void Biquad_LSF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter(); // EN: Update coefficients to reflect the new frequency.
                    // ES: Actualiza los coeficientes para reflejar la nueva frecuencia.
}

// EN: Sets the Q factor (resonance) for the filter.
// ES: Establece el factor Q (resonancia) para el filtro.
void Biquad_LSF::setQ(float inQ)
{
    Q = inQ;
    updateFilter(); // EN: Update coefficients to reflect the new Q value.
                    // ES: Actualiza los coeficientes para reflejar el nuevo valor de Q.
}

// EN: Sets the gain for the shelving filter.
// ES: Establece la ganancia para el filtro shelving.
void Biquad_LSF::setGain(float inGain)
{
    Gain = inGain;
    updateFilter(); // EN: Update coefficients to reflect the new gain.
                    // ES: Actualiza los coeficientes para reflejar la nueva ganancia.
}

// EN: Updates the filter coefficients based on the current frequency, Q, and gain.
// ES: Actualiza los coeficientes del filtro según la frecuencia, Q y ganancia actuales.
void Biquad_LSF::updateFilter()
{
    // EN: Calculate intermediate variables for the filter coefficients.
    // ES: Calcula las variables intermedias para los coeficientes del filtro.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate); // EN: Angular frequency.
                                                                                           // ES: Frecuencia angular.
    alpha = sinf(w0) / (2.0f * Q);  // EN: Bandwidth factor.
                                    // ES: Factor de ancho de banda.
    A = sqrt(powf(10.0f, Gain / 20.0f)); // EN: Convert dB gain to linear scale.
                                         // ES: Convierte la ganancia en dB a escala lineal.

// EN: Calculate filter coefficients for the LSF.
// ES: Calcula los coeficientes del filtro para el LSF.
    b0 = A * ((A + 1.0f) - ((A - 1.0f) * cosf(w0)) + (2.0f * sqrtf(A) * alpha));
    b1 = 2.0f * A * ((A - 1.0f) - ((A + 1.0f) * cosf(w0)));
    b2 = A * ((A + 1.0f) - ((A - 1.0f) * cosf(w0)) - (2.0f * sqrtf(A) * alpha));

    a0 = (A + 1.0f) + ((A - 1.0f) * cosf(w0)) + (2.0f * sqrtf(A) * alpha);
    a1 = -2.0f * ((A - 1.0f) + ((A + 1.0f) * cosf(w0)));
    a2 = (A + 1.0f) + ((A - 1.0f) * cosf(w0)) - (2.0f * sqrtf(A) * alpha);
}