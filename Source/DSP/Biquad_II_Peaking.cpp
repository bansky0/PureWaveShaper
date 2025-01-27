/*
  ==============================================================================

    Biquad_II_Peaking.cpp
    Created: 7 Oct 2024 2:37:56pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_II_Peaking.h"

// EN: Constructor - Initializes the Biquad_II_Peaking filter with default values.
//     This is where the filter is instantiated but no actual computation happens here.
// ES: Constructor - Inicializa el filtro Biquad_II_Peaking con valores predeterminados.
//     Aquí se instancia el filtro, pero no ocurre ningún cálculo real.
Biquad_II_Peaking::Biquad_II_Peaking() {}

// EN: Destructor - Cleans up any resources when the filter object is destroyed.
//     This implementation does not require specific cleanup but can be added if needed.
// ES: Destructor - Limpia los recursos cuando el objeto del filtro es destruido.
//     Esta implementación no requiere limpieza específica, pero se puede agregar si es necesario.
Biquad_II_Peaking::~Biquad_II_Peaking() {}

// EN: Prepares the filter for processing by setting the sample rate and updating the filter coefficients.
//     The sample rate is used for filter calculation and must be set before processing audio.
// ES: Prepara el filtro para el procesamiento estableciendo la frecuencia de muestreo y actualizando los coeficientes del filtro.
//     La frecuencia de muestreo se utiliza para el cálculo del filtro y debe ser establecida antes de procesar el audio.
void Biquad_II_Peaking::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;  // Store the sample rate for future filter updates.
    updateFilter();  // Update the filter coefficients based on the new sample rate.
}

// EN: Processes an entire audio buffer, applying the filter to each sample in each channel.
//     It loops over all channels and samples of the buffer to apply the filtering process.
// ES: Procesa todo el buffer de audio, aplicando el filtro a cada muestra en cada canal.
//     Recorre todos los canales y muestras del buffer para aplicar el proceso de filtrado.
void Biquad_II_Peaking::process(juce::AudioBuffer<float> inBuffer)
{
    // EN: Loop through each channel of the audio buffer.
    // ES: Recorrer cada canal del buffer de audio.
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        // EN: Loop through each sample in the current channel.
        // ES: Recorrer cada muestra en el canal actual.
        for (int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            float inSample = inBuffer.getSample(channel, i);  // Get the current sample.

            // EN: Process the sample using the processSample function and filter coefficients.
            //     The processed sample is returned as the output.
            // ES: Procesa la muestra usando la función processSample y los coeficientes del filtro.
            //     La muestra procesada se devuelve como salida.
            float outSample = processSample(inSample, channel);

            // EN: Set the processed sample back to the buffer.
            // ES: Establecer la muestra procesada de nuevo en el buffer.
            inBuffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Processes a single sample for a specific channel using the peaking filter formula.
//     This computes the filter output based on the current sample and filter state variables.
//     It updates the internal state (w1, w2) for the next sample.
// ES: Procesa una sola muestra para un canal específico usando la fórmula del filtro de pico.
//     Calcula la salida del filtro basada en la muestra actual y las variables de estado del filtro.
//     Actualiza el estado interno (w1, w2) para la siguiente muestra.
float Biquad_II_Peaking::processSample(float inSample, int channel)
{
    // EN: Calculate the intermediate variable w using the previous filter states (w1, w2).
    //     This is the difference equation for the filter.
    // ES: Calcular la variable intermedia w usando los estados anteriores del filtro (w1, w2).
    //     Esta es la ecuación en diferencia del filtro.
    auto w = inSample - a1 * w1[channel] - a2 * w2[channel];

    // EN: Calculate the output sample (y) based on the filter's coefficients and the intermediate variable w.
    //     The output sample is computed using the filter's difference equation.
    // ES: Calcular la muestra de salida (y) basada en los coeficientes del filtro y la variable intermedia w.
    //     La muestra de salida se calcula usando la ecuación en diferencia del filtro.
    auto y = b0 * w + b1 * w1[channel] + b2 * w2[channel];

    // EN: Update the filter state for the next sample (w1, w2).
    // ES: Actualizar el estado del filtro para la siguiente muestra (w1, w2).
    w2[channel] = w1[channel];
    w1[channel] = w;

    // EN: Return the processed output sample.
    // ES: Devolver la muestra de salida procesada.
    return y;
}

// EN: Sets the frequency of the peaking filter and updates the filter coefficients accordingly.
//     The frequency is used to calculate the angular frequency (w0), which is a key part of the filter design.
// ES: Establece la frecuencia del filtro de pico y actualiza los coeficientes del filtro en consecuencia.
//     La frecuencia se utiliza para calcular la frecuencia angular (w0), que es una parte clave del diseño del filtro.
void Biquad_II_Peaking::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();  // Update filter coefficients based on the new frequency.
}

// EN: Sets the gain of the peaking filter and updates the filter coefficients accordingly.
//     The gain controls the amount of boost or cut at the given frequency (in dB).
// ES: Establece la ganancia del filtro de pico y actualiza los coeficientes del filtro en consecuencia.
//     La ganancia controla la cantidad de aumento o corte en la frecuencia dada (en dB).
void Biquad_II_Peaking::setGain(float inGain)
{
    Gain = inGain;
    updateFilter();  // Update filter coefficients based on the new gain value.
}

// EN: Sets the Q factor of the peaking filter and updates the filter coefficients accordingly.
//     The Q factor determines the bandwidth of the filter, with higher Q values resulting in a narrower peak.
 // ES: Establece el factor Q del filtro de pico y actualiza los coeficientes del filtro en consecuencia.
//     El factor Q determina el ancho de banda del filtro, con valores más altos de Q resultando en un pico más estrecho.
void Biquad_II_Peaking::setQ(float inQ)
{
    Q = inQ;
    updateFilter();  // Update filter coefficients based on the new Q factor.
}

// EN: Calculates and updates the filter coefficients based on the current frequency, gain, and Q factor.
//     This function uses the standard biquad filter formula to compute the coefficients, normalizing them by a0.
//     The gain (A) is also used to scale the coefficients for the peaking filter effect.
// ES: Calcula y actualiza los coeficientes del filtro en función de la frecuencia, ganancia y factor Q actuales.
//     Esta función utiliza la fórmula estándar del filtro biquad para calcular los coeficientes, normalizándolos por a0.
//     La ganancia (A) también se utiliza para escalar los coeficientes para el efecto de pico del filtro.
void Biquad_II_Peaking::updateFilter()
{
    // EN: Calculate the angular frequency (w0) based on the sample rate and frequency.
    //     Calculate alpha for the filter resonance.
    //     Calculate the gain factor (A) from the gain in dB.
    // ES: Calcular la frecuencia angular (w0) en función de la frecuencia de muestreo y la frecuencia.
    //     Calcular alpha para la resonancia del filtro.
    //     Calcular el factor de ganancia (A) a partir de la ganancia en dB.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);
    A = sqrt(powf(10.0f, Gain / 20.0f));  // Convert gain from dB to linear scale.

    // EN: Calculate the filter coefficients (b0, b1, b2, a0, a1, a2) based on frequency, Q, and A.
    //     These coefficients define the filter's behavior.
    // ES: Calcular los coeficientes del filtro (b0, b1, b2, a0, a1, a2) en función de la frecuencia, Q y A.
    //     Estos coeficientes definen el comportamiento del filtro.
    b0 = 1.0f + alpha * A;
    b1 = -2.0f * cosf(w0);
    b2 = 1.0f - alpha * A;

    a0 = 1.0 + alpha / A;
    a1 = -2.0f * cosf(w0);
    a2 = 1.0f - alpha / A;

    // EN: Normalize the coefficients by dividing by a0.
    // ES: Normalizar los coeficientes dividiendo por a0.
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}