/*
  ==============================================================================

    Biquad_Peaking.cpp
    Created: 1 Oct 2024 12:25:55pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_Peaking.h"

// EN: Constructor for the Biquad_Peaking class.
// ES: Constructor de la clase Biquad_Peaking.
Biquad_Peaking::Biquad_Peaking() {}

// EN: Destructor for the Biquad_Peaking class.
// ES: Destructor de la clase Biquad_Peaking.
Biquad_Peaking::~Biquad_Peaking() {}

// EN: Prepares the filter with the specified sample rate and updates the filter coefficients.
// ES: Prepara el filtro con la frecuencia de muestreo especificada y actualiza los coeficientes del filtro.
void Biquad_Peaking::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter(); // EN: Update the filter coefficients based on the initial parameters.
                    // ES: Actualiza los coeficientes del filtro según los parámetros iniciales.
}

// EN: Processes an entire audio buffer by applying the peaking filter to each sample.
// ES: Procesa un buffer completo de audio aplicando el filtro peaking a cada muestra.
void Biquad_Peaking::process(juce::AudioBuffer<float> inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++) // EN: Iterate over all channels.
                                                                          // ES: Itera sobre todos los canales.
    {
        for (int i = 0; i < inBuffer.getNumSamples(); i++) // EN: Iterate over all samples in the buffer.
                                                           // ES: Itera sobre todas las muestras en el buffer.
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Get the input sample.
                                                             // ES: Obtiene la muestra de entrada.

            float outSample = processSample(inSample, channel); // EN: Process the sample through the filter.
                                                                // ES: Procesa la muestra a través del filtro.

            inBuffer.setSample(channel, i, outSample); // EN: Write the processed sample back into the buffer.
                                                       // ES: Escribe la muestra procesada de vuelta en el buffer.
        }
    }
}

// EN: Processes a single sample of audio for the specified channel.
// ES: Procesa una única muestra de audio para el canal especificado.
float Biquad_Peaking::processSample(float inSample, int channel)
{
    // EN: Compute the filter output using the difference equation.
    // ES: Calcula la salida del filtro usando la ecuación en diferencias.
    auto y = (b0 * inSample + b1 * x1[channel] + b2 * x2[channel] + (-a1) * y1[channel] + (-a2) * y2[channel]) * (1.0f / a0);

    // EN: Update the delay buffers.
    // ES: Actualiza los buffers de retardo.
    x2[channel] = x1[channel];
    x1[channel] = inSample;
    y2[channel] = y1[channel];
    y1[channel] = y;

    return y; // EN: Return the filtered output sample.
              // ES: Devuelve la muestra de salida filtrada.
}

// EN: Sets the center frequency of the peaking filter and updates the filter coefficients.
// ES: Establece la frecuencia central del filtro peaking y actualiza los coeficientes del filtro.
void Biquad_Peaking::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter(); // EN: Update the filter coefficients after changing the frequency.
                    // ES: Actualiza los coeficientes del filtro después de cambiar la frecuencia.
}

// EN: Sets the gain (boost/cut) of the peaking filter and updates the filter coefficients.
// ES: Establece la ganancia (boost/cut) del filtro peaking y actualiza los coeficientes del filtro.
void Biquad_Peaking::setGain(float inGain)
{
    Gain = inGain;
    updateFilter(); // EN: Update the filter coefficients after changing the gain.
                    // ES: Actualiza los coeficientes del filtro después de cambiar la ganancia.
}

// EN: Sets the Q factor (quality factor) of the peaking filter and updates the filter coefficients.
// ES: Establece el factor Q (factor de calidad) del filtro peaking y actualiza los coeficientes del filtro.
void Biquad_Peaking::setQ(float inQ)
{
    Q = inQ;
    updateFilter(); // EN: Update the filter coefficients after changing the Q factor.
                    // ES: Actualiza los coeficientes del filtro después de cambiar el factor Q.
}

// EN: Updates the filter coefficients based on the current frequency, gain, and Q factor.
// ES: Actualiza los coeficientes del filtro según la frecuencia, ganancia y factor Q actuales.
void Biquad_Peaking::updateFilter()
{
    // EN: Calculate intermediate values for the coefficients.
    // ES: Calcula valores intermedios para los coeficientes.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate); // EN: Angular frequency.
                                                                                           // ES: Frecuencia angular.
    alpha = sinf(w0) / (2.0f * Q); // EN: Bandwidth parameter.
                                   // ES: Parámetro de ancho de banda.
    A = sqrt(powf(10.0f, Gain / 20.0f)); // EN: Convert gain in dB to linear amplitude.
                                         // ES: Convierte la ganancia en dB a amplitud lineal.

// EN: Calculate feedforward coefficients.
// ES: Calcula los coeficientes de realimentación directa.
    b0 = 1.0f + alpha * A;
    b1 = -2.0f * cosf(w0);
    b2 = 1.0f - alpha * A;

    // EN: Calculate feedback coefficients.
    // ES: Calcula los coeficientes de retroalimentación.
    a0 = 1.0 + alpha / A;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha / A;
}