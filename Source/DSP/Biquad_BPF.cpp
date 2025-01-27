/*
  ==============================================================================

    Biquad_BPF.cpp
    Created: 1 Oct 2024 12:24:54pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_BPF.h"

// EN: Constructor - Initializes the Biquad_BPF class with default values.
// ES: Constructor - Inicializa la clase Biquad_BPF con valores predeterminados.
Biquad_BPF::Biquad_BPF() {}

// EN: Destructor - Cleans up any resources used by the Biquad_BPF class.
// ES: Destructor - Limpia cualquier recurso usado por la clase Biquad_BPF.
Biquad_BPF::~Biquad_BPF() {}

// EN: Prepares the filter for processing by setting the sample rate and updating the coefficients.
// ES: Prepara el filtro para el procesamiento estableciendo la frecuencia de muestreo y actualizando los coeficientes.
void Biquad_BPF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate; // EN: Set the sample rate. ES: Establece la frecuencia de muestreo.
    updateFilter(); // EN: Update the filter coefficients. ES: Actualiza los coeficientes del filtro.
}

// EN: Processes the audio buffer by applying the band-pass filter to each sample.
// ES: Procesa el buffer de audio aplicando el filtro de paso banda a cada muestra.
void Biquad_BPF::process(juce::AudioBuffer<float> inBuffer)
{
    // EN: Iterate over each channel in the buffer.
    // ES: Iterar sobre cada canal en el buffer.
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        // EN: Iterate over each sample in the current channel.
        // ES: Iterar sobre cada muestra en el canal actual.
        for (int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Get the input sample. ES: Obtener la muestra de entrada.

            float outSample = processSample(inSample, channel); // EN: Process the sample through the filter. ES: Procesar la muestra a través del filtro.

            inBuffer.setSample(channel, i, outSample); // EN: Set the processed sample back to the buffer. ES: Establecer la muestra procesada de vuelta en el buffer.
        }
    }
}

// EN: Processes a single audio sample by applying the filter equation and updates the delay line.
// ES: Procesa una sola muestra de audio aplicando la ecuación del filtro y actualiza la línea de retardo.
float Biquad_BPF::processSample(float inSample, int channel)
{
    // EN: Apply the difference equation of the band-pass filter.
    // ES: Aplicar la ecuación diferencial del filtro de paso banda.
    auto y = (b0 * inSample + b1 * x1[channel] + b2 * x2[channel]
        + (-a1) * y1[channel] + (-a2) * y2[channel]) * (1.0f / a0);

    // EN: Update the delay line for the input and output samples.
    // ES: Actualizar la línea de retardo para las muestras de entrada y salida.
    x2[channel] = x1[channel];
    x1[channel] = inSample;
    y2[channel] = y1[channel];
    y1[channel] = y;

    return y; // EN: Return the processed sample. ES: Retornar la muestra procesada.
}

// EN: Sets the filter's center frequency and updates the coefficients.
// ES: Establece la frecuencia central del filtro y actualiza los coeficientes.
void Biquad_BPF::setFrequency(float inFrequency)
{
    frequency = inFrequency; // EN: Set the frequency. ES: Establecer la frecuencia.
    updateFilter(); // EN: Update the filter coefficients. ES: Actualizar los coeficientes del filtro.
}

// EN: Sets the quality factor (Q) of the filter and updates the coefficients.
// ES: Establece el factor de calidad (Q) del filtro y actualiza los coeficientes.
void Biquad_BPF::setQ(float inQ)
{
    Q = inQ; // EN: Set the Q factor. ES: Establecer el factor Q.
    updateFilter(); // EN: Update the filter coefficients. ES: Actualizar los coeficientes del filtro.
}

// EN: Updates the coefficients of the band-pass filter based on the frequency and Q values.
// ES: Actualiza los coeficientes del filtro de paso banda según los valores de frecuencia y Q.
void Biquad_BPF::updateFilter()
{
    // EN: Calculate the normalized angular frequency (w0) and alpha based on the sample rate, frequency, and Q.
    // ES: Calcular la frecuencia angular normalizada (w0) y alpha basado en la frecuencia de muestreo, la frecuencia y el Q.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    // EN: Coefficients for the band-pass filter.
    // ES: Coeficientes para el filtro de paso banda.
    b0 = sinf(w0) / 2.0f;    // EN: Numerator coefficient for the current stage. ES: Coeficiente del numerador para la etapa actual.
    b1 = 0.0f;               // EN: Numerator coefficient for the previous stage. ES: Coeficiente del numerador para la etapa anterior.
    b2 = -sinf(w0) / 2.0f;   // EN: Numerator coefficient for two stages back. ES: Coeficiente del numerador para dos etapas atrás.

    a0 = 1.0f + alpha;       // EN: Denominator coefficient for the current stage. ES: Coeficiente del denominador para la etapa actual.
    a1 = -2.0f * cosf(w0);   // EN: Denominator coefficient for the previous stage. ES: Coeficiente del denominador para la etapa anterior.
    a2 = 1.0f - alpha;       // EN: Denominator coefficient for two stages back. ES: Coeficiente del denominador para dos etapas atrás.
}
