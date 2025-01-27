/*
  ==============================================================================

    Biquad_BPF2.cpp
    Created: 1 Oct 2024 12:25:06pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_BPF2.h" 

// EN: Constructor - Initializes the Biquad_BPF2 class with default parameters.
// ES: Constructor - Inicializa la clase Biquad_BPF2 con parámetros predeterminados.
Biquad_BPF2::Biquad_BPF2() {}

// EN: Destructor - Cleans up any resources used by the Biquad_BPF2 class.
// ES: Destructor - Limpia cualquier recurso utilizado por la clase Biquad_BPF2.
Biquad_BPF2::~Biquad_BPF2() {}

// EN: Prepares the filter for processing by setting the sample rate and updating the coefficients.
// ES: Prepara el filtro para el procesamiento configurando la frecuencia de muestreo y actualizando los coeficientes.
void Biquad_BPF2::prepare(double inSampleRate)
{
    sampleRate = inSampleRate; // EN: Store the sample rate. ES: Almacena la frecuencia de muestreo.
    updateFilter(); // EN: Update the filter coefficients with the current frequency and Q. ES: Actualiza los coeficientes del filtro con la frecuencia y Q actuales.
}

// EN: Processes an entire audio buffer by applying the band-pass filter to each sample.
// ES: Procesa un buffer de audio completo aplicando el filtro de paso banda a cada muestra.
void Biquad_BPF2::process(juce::AudioBuffer<float> inBuffer)
{
    // EN: Iterate through each channel in the audio buffer.
    // ES: Itera por cada canal en el buffer de audio.
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        // EN: Iterate through each sample in the channel.
        // ES: Itera por cada muestra en el canal.
        for (int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Get the input sample. ES: Obtiene la muestra de entrada.

            float outSample = processSample(inSample, channel); // EN: Apply the filter to the sample. ES: Aplica el filtro a la muestra.

            inBuffer.setSample(channel, i, outSample); // EN: Set the filtered sample back in the buffer. ES: Establece la muestra filtrada de vuelta en el buffer.
        }
    }
}

// EN: Processes a single audio sample for a given channel using the band-pass filter.
// ES: Procesa una sola muestra de audio para un canal dado usando el filtro de paso banda.
float Biquad_BPF2::processSample(float inSample, int channel)
{
    // EN: Compute the output sample using the biquad filter equation.
    // ES: Calcula la muestra de salida usando la ecuación del filtro biquad.
    auto y = (b0 * inSample + b1 * x1[channel] + b2 * x2[channel] + (-a1) * y1[channel] + (-a2) * y2[channel]) * (1.0f / a0);

    // EN: Update the delay lines for input samples.
    // ES: Actualiza las líneas de retardo para las muestras de entrada.
    x2[channel] = x1[channel];
    x1[channel] = inSample;

    // EN: Update the delay lines for output samples.
    // ES: Actualiza las líneas de retardo para las muestras de salida.
    y2[channel] = y1[channel];
    y1[channel] = y;

    return y; // EN: Return the filtered output sample. ES: Devuelve la muestra de salida filtrada.
}

// EN: Sets the center frequency of the band-pass filter and updates the coefficients.
// ES: Establece la frecuencia central del filtro de paso banda y actualiza los coeficientes.
void Biquad_BPF2::setFrequency(float inFrequency)
{
    frequency = inFrequency; // EN: Store the new frequency. ES: Almacena la nueva frecuencia.
    updateFilter(); // EN: Update the filter coefficients. ES: Actualiza los coeficientes del filtro.
}

// EN: Sets the quality factor (Q) of the band-pass filter and updates the coefficients.
// ES: Establece el factor de calidad (Q) del filtro de paso banda y actualiza los coeficientes.
void Biquad_BPF2::setQ(float inQ)
{
    Q = inQ; // EN: Store the new Q value. ES: Almacena el nuevo valor de Q.
    updateFilter(); // EN: Update the filter coefficients. ES: Actualiza los coeficientes del filtro.
}

// EN: Updates the filter coefficients based on the current frequency and Q values.
// ES: Actualiza los coeficientes del filtro según los valores actuales de frecuencia y Q.
void Biquad_BPF2::updateFilter()
{
    // EN: Calculate the normalized angular frequency and bandwidth scaling factor.
    // ES: Calcula la frecuencia angular normalizada y el factor de escalado de ancho de banda.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    // EN: Compute the coefficients for a band-pass filter.
    // ES: Calcula los coeficientes para un filtro de paso banda.
    b0 = alpha;                // EN: Proportional to the bandwidth. ES: Proporcional al ancho de banda.
    b1 = 0.0f;                 // EN: No first-order term in feedforward. ES: Sin término de primer orden en la alimentación directa.
    b2 = -alpha;               // EN: Opposite sign to b0. ES: Signo opuesto a b0.

    a0 = 1.0 + alpha;          // EN: Normalization term for feedback. ES: Término de normalización para retroalimentación.
    a1 = -2.0f * cosf(w0);     // EN: Relates to the filter's center frequency. ES: Relacionado con la frecuencia central del filtro.
    a2 = 1.0f - alpha;         // EN: Opposite sign to alpha in feedback. ES: Signo opuesto a alpha en retroalimentación.
}