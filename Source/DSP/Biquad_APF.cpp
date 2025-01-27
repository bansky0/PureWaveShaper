/*
  ==============================================================================

    Biquad_APF.cpp
    Created: 1 Oct 2024 12:25:34pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_APF.h"

// EN: Constructor for the Biquad All-Pass Filter class.
// ES: Constructor para la clase de filtro Biquad All-Pass.
Biquad_APF::Biquad_APF() {}

// EN: Destructor for the Biquad All-Pass Filter class.
// ES: Destructor para la clase de filtro Biquad All-Pass.
Biquad_APF::~Biquad_APF() {}

// EN: Prepares the filter with the specified sample rate.
// ES: Prepara el filtro con la frecuencia de muestreo especificada.
void Biquad_APF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter(); // EN: Updates filter coefficients. ES: Actualiza los coeficientes del filtro.
}

// EN: Processes an audio buffer and applies the filter to each sample.
// ES: Procesa un buffer de audio y aplica el filtro a cada muestra.
void Biquad_APF::process(juce::AudioBuffer<float> inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++) // EN: Iterate through each audio channel. ES: Iterar por cada canal de audio.
    {
        for (int i = 0; i < inBuffer.getNumSamples(); i++) // EN: Iterate through each sample in the channel. ES: Iterar por cada muestra en el canal.
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Get the current input sample. ES: Obtener la muestra de entrada actual.

            float outSample = processSample(inSample, channel); // EN: Process the sample using the filter. ES: Procesar la muestra usando el filtro.

            inBuffer.setSample(channel, i, outSample); // EN: Store the processed sample back into the buffer. ES: Almacenar la muestra procesada de nuevo en el buffer.
        }
    }
}

// EN: Processes a single audio sample and applies the filter formula.
// ES: Procesa una sola muestra de audio y aplica la fórmula del filtro.
float Biquad_APF::processSample(float inSample, int channel)
{
    // EN: Calculate the output sample using the Biquad filter equation.
    // ES: Calcular la muestra de salida usando la ecuación del filtro Biquad.
    auto y = (b0 * inSample + b1 * x1[channel] + b2 * x2[channel] + (-a1) * y1[channel] + (-a2) * y2[channel]) * (1.0f / a0);

    // EN: Update the delay line values for input and output.
    // ES: Actualizar los valores de la línea de retardo para entrada y salida.
    x2[channel] = x1[channel];
    x1[channel] = inSample;
    y2[channel] = y1[channel];
    y1[channel] = y;

    return y; // EN: Return the processed sample. ES: Devolver la muestra procesada.
}

// EN: Sets the center frequency of the filter.
// ES: Establece la frecuencia central del filtro.
void Biquad_APF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter(); // EN: Update the filter coefficients. ES: Actualizar los coeficientes del filtro.
}

// EN: Sets the quality factor (Q) of the filter.
// ES: Establece el factor de calidad (Q) del filtro.
void Biquad_APF::setQ(float inQ)
{
    Q = inQ;
    updateFilter(); // EN: Update the filter coefficients. ES: Actualizar los coeficientes del filtro.
}

// EN: Updates the filter coefficients based on frequency and Q.
// ES: Actualiza los coeficientes del filtro según la frecuencia y el Q.
void Biquad_APF::updateFilter()
{
    // EN: Calculate the normalized angular frequency (w0) and alpha value.
    // ES: Calcular la frecuencia angular normalizada (w0) y el valor de alpha.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    // EN: Calculate the numerator coefficients (b0, b1, b2) for the filter.
    // ES: Calcular los coeficientes del numerador (b0, b1, b2) para el filtro.
    b0 = 1.0f - alpha;
    b1 = -2.0f * cosf(w0);
    b2 = 1.0f + alpha;

    // EN: Calculate the denominator coefficients (a0, a1, a2) for the filter.
    // ES: Calcular los coeficientes del denominador (a0, a1, a2) para el filtro.
    a0 = 1.0 + alpha;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha;
}