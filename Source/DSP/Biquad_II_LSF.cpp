/*
  ==============================================================================

    Biquad_II_LSF.cpp
    Created: 7 Oct 2024 11:59:16am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_II_LSF.h"

// EN: Constructor - No additional initialization is required as all members are initialized in the class definition.
// ES: Constructor - No se requiere inicialización adicional ya que todos los miembros se inicializan en la definición de la clase.
Biquad_II_LSF::Biquad_II_LSF() {}

// EN: Destructor - Cleans up any resources allocated by the class.
// ES: Destructor - Limpia cualquier recurso asignado por la clase.
Biquad_II_LSF::~Biquad_II_LSF() {}

// EN: Prepares the filter with the given sample rate and updates the filter coefficients.
// ES: Prepara el filtro con la frecuencia de muestreo dada y actualiza los coeficientes del filtro.
void Biquad_II_LSF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter(); // EN: Updates the filter coefficients based on the sample rate. 
    // ES: Actualiza los coeficientes del filtro en función de la frecuencia de muestreo.
}

// EN: Processes the entire audio buffer, applying the filter to each sample.
// ES: Procesa el buffer de audio completo, aplicando el filtro a cada muestra.
void Biquad_II_LSF::process(juce::AudioBuffer<float> inBuffer)
{
    int numChannels = inBuffer.getNumChannels();
    int numSamples = inBuffer.getNumSamples();

    // EN: Loops through all the channels and samples in the buffer and applies the filter.
    // ES: Recorre todos los canales y muestras en el buffer y aplica el filtro.
    for (int channel = 0; channel < numChannels; channel++)
    {
        for (int i = 0; i < numSamples; i++)
        {
            // EN: Retrieves the current sample from the buffer.
            // ES: Obtiene la muestra actual del buffer.
            float inSample = inBuffer.getSample(channel, i);

            // EN: Processes the sample using the filter and stores the output.
            // ES: Procesa la muestra utilizando el filtro y almacena el resultado.
            float outSample = processSample(inSample, channel);

            // EN: Sets the processed sample back into the buffer.
            // ES: Coloca la muestra procesada de nuevo en el buffer.
            inBuffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Processes a single sample of audio for the specified channel.
// ES: Procesa una sola muestra de audio para el canal especificado.
float Biquad_II_LSF::processSample(float inSample, int channel)
{
    // EN: Computes the input to the filter (w) based on the previous states.
    // ES: Calcula la entrada al filtro (w) en función de los estados previos.
    auto w = inSample - a1 * w1[channel] - a2 * w2[channel];

    // EN: Computes the output of the filter (y) using the current input and previous states.
    // ES: Calcula la salida del filtro (y) usando la entrada actual y los estados previos.
    auto y = b0 * w + b1 * w1[channel] + b2 * w2[channel];

    // EN: Updates the previous states for the next sample.
    // ES: Actualiza los estados previos para la siguiente muestra.
    w2[channel] = w1[channel];
    w1[channel] = w;

    return y; // EN: Returns the processed sample.
    // ES: Retorna la muestra procesada.
}

// EN: Sets the frequency of the filter and updates the filter coefficients.
// ES: Establece la frecuencia del filtro y actualiza los coeficientes del filtro.
void Biquad_II_LSF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter(); // EN: Updates the filter coefficients with the new frequency.
    // ES: Actualiza los coeficientes del filtro con la nueva frecuencia.
}

// EN: Sets the quality factor (Q) of the filter and updates the filter coefficients.
// ES: Establece el factor de calidad (Q) del filtro y actualiza los coeficientes del filtro.
void Biquad_II_LSF::setQ(float inQ)
{
    Q = inQ;
    updateFilter(); // EN: Updates the filter coefficients with the new Q value.
    // ES: Actualiza los coeficientes del filtro con el nuevo valor de Q.
}

// EN: Sets the gain of the filter and updates the filter coefficients.
// ES: Establece la ganancia del filtro y actualiza los coeficientes del filtro.
void Biquad_II_LSF::setGain(float inGain)
{
    Gain = inGain;
    updateFilter(); // EN: Updates the filter coefficients with the new gain value.
    // ES: Actualiza los coeficientes del filtro con el nuevo valor de ganancia.
}

// EN: Updates the filter coefficients based on the current frequency, Q, and gain.
// ES: Actualiza los coeficientes del filtro según la frecuencia, Q y ganancia actuales.
void Biquad_II_LSF::updateFilter()
{
    // EN: Calculates the angular frequency (w0) for the filter based on the sample rate.
    // ES: Calcula la frecuencia angular (w0) para el filtro en función de la frecuencia de muestreo.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);

    // EN: Calculates the alpha parameter used for coefficient calculations.
    // ES: Calcula el parámetro alpha utilizado para el cálculo de coeficientes.
    alpha = sinf(w0) / (2.0f * Q);

    // EN: Calculates the 'A' value for gain adjustments.
    // ES: Calcula el valor 'A' para los ajustes de ganancia.
    A = sqrt(powf(10.0f, Gain / 20.0f));

    // EN: Computes the filter coefficients (b0, b1, b2, a0, a1, a2) based on the frequency, Q, and gain.
    // ES: Calcula los coeficientes del filtro (b0, b1, b2, a0, a1, a2) en función de la frecuencia, Q y ganancia.
    b0 = A * ((A + 1.0f) - ((A - 1.0f) * cosf(w0)) + (2.0f * sqrtf(A) * alpha));
    b1 = 2.0f * A * ((A - 1.0f) - ((A + 1.0f) * cosf(w0)));
    b2 = A * ((A + 1.0f) - ((A - 1.0f) * cosf(w0)) - (2.0f * sqrtf(A) * alpha));

    a0 = (A + 1.0f) + ((A - 1.0f) * cosf(w0)) + (2.0f * sqrtf(A) * alpha);
    a1 = -2.0f * ((A - 1.0f) + ((A + 1.0f) * cosf(w0)));
    a2 = (A + 1.0f) + ((A - 1.0f) * cosf(w0)) - (2.0f * sqrtf(A) * alpha);

    // EN: Normalizes the coefficients by dividing them by a0.
    // ES: Normaliza los coeficientes dividiéndolos por a0.
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}
