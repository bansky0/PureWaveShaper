/*
  ==============================================================================

    Biquad_II_BPF.cpp
    Created: 7 Oct 2024 12:00:13pm
    Author:  Jhonatan López

  ==============================================================================
*/

/*
EN: This implementation represents a second - order band - pass filter using Direct Form II.The coefficients are recalculated whenever the sample rate, frequency, or Q factor changes, ensuring the filter's output matches the desired specifications.
ES : Esta implementación representa un filtro pasa - banda de segundo orden utilizando la Forma Directa II.Los coeficientes se recalculan cada vez que cambian la frecuencia de muestreo, la frecuencia central o el factor Q, asegurando que la salida del filtro coincida con las especificaciones deseadas.
*/

#include "Biquad_II_BPF.h"

// EN: Constructor - Initializes the Biquad_II_BPF object with default values.
// ES: Constructor - Inicializa el objeto Biquad_II_BPF con valores predeterminados.
Biquad_II_BPF::Biquad_II_BPF() {}

// EN: Destructor - Cleans up any resources used by the Biquad_II_BPF object.
// ES: Destructor - Limpia cualquier recurso utilizado por el objeto Biquad_II_BPF.
Biquad_II_BPF::~Biquad_II_BPF() {}

// EN: Prepares the filter for audio processing by setting the sample rate and updating the coefficients.
// ES: Prepara el filtro para el procesamiento de audio configurando la frecuencia de muestreo y actualizando los coeficientes.
void Biquad_II_BPF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate; // EN: Store the sample rate. // ES: Almacena la frecuencia de muestreo.
    updateFilter(); // EN: Update the filter coefficients. // ES: Actualiza los coeficientes del filtro.
}

// EN: Processes an audio buffer, applying the filter to all samples and channels.
// ES: Procesa un buffer de audio, aplicando el filtro a todas las muestras y canales.
void Biquad_II_BPF::process(juce::AudioBuffer<float>& inBuffer)
{
    int numChannels = inBuffer.getNumChannels(); // EN: Get the number of audio channels. // ES: Obtiene el número de canales de audio.
    int numSamples = inBuffer.getNumSamples();  // EN: Get the number of samples per channel. // ES: Obtiene el número de muestras por canal.

    for (int channel = 0; channel < numChannels; channel++) // EN: Loop through each channel. // ES: Itera a través de cada canal.
    {
        for (int i = 0; i < numSamples; i++) // EN: Loop through each sample. // ES: Itera a través de cada muestra.
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Read the input sample. // ES: Lee la muestra de entrada.

            float outSample = processSample(inSample, channel); // EN: Apply the filter to the sample. // ES: Aplica el filtro a la muestra.

            inBuffer.setSample(channel, i, outSample); // EN: Write the filtered sample back to the buffer. // ES: Escribe la muestra filtrada de vuelta al buffer.
        }
    }
}

// EN: Processes a single sample through the filter for a given channel.
// ES: Procesa una muestra única a través del filtro para un canal específico.
float Biquad_II_BPF::processSample(float inSample, int channel)
{
    auto w = inSample - a1 * w1[channel] - a2 * w2[channel]; // EN: Compute the intermediate state for the filter. // ES: Calcula el estado intermedio para el filtro.
    auto y = b0 * w + b1 * w1[channel] + b2 * w2[channel];   // EN: Compute the output sample. // ES: Calcula la muestra de salida.

    w2[channel] = w1[channel]; // EN: Update the delay lines. // ES: Actualiza las líneas de retardo.
    w1[channel] = w;

    return y; // EN: Return the filtered sample. // ES: Retorna la muestra filtrada.
}

// EN: Sets the filter's center frequency and updates the coefficients.
// ES: Establece la frecuencia central del filtro y actualiza los coeficientes.
void Biquad_II_BPF::setFrequency(float inFrequency)
{
    frequency = inFrequency; // EN: Store the new frequency value. // ES: Almacena el nuevo valor de frecuencia.
    updateFilter();          // EN: Recalculate the coefficients. // ES: Recalcula los coeficientes.
}

// EN: Sets the filter's quality factor (Q) and updates the coefficients.
// ES: Establece el factor de calidad (Q) del filtro y actualiza los coeficientes.
void Biquad_II_BPF::setQ(float inQ)
{
    Q = inQ;       // EN: Store the new Q value. // ES: Almacena el nuevo valor de Q.
    updateFilter(); // EN: Recalculate the coefficients. // ES: Recalcula los coeficientes.
}

// EN: Updates the filter coefficients based on the current frequency, Q, and sample rate.
// ES: Actualiza los coeficientes del filtro según la frecuencia, el Q y la frecuencia de muestreo actuales.
void Biquad_II_BPF::updateFilter()
{
    // EN: Calculate the angular frequency (w0) and the bandwidth scaling factor (alpha).
    // ES: Calcula la frecuencia angular (w0) y el factor de escalado de ancho de banda (alpha).
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);

    // EN: Set the coefficients for a band-pass filter (BPF).
    // ES: Establece los coeficientes para un filtro pasa-banda (BPF).
    b0 = sinf(w0) / 2.0f;
    b1 = 0.0f;
    b2 = -sinf(w0) / 2.0f;

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