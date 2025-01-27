/*
  ==============================================================================

    Biquad_II_HSF.cpp
    Created: 7 Oct 2024 11:59:38am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Biquad_II_HSF.h"

// EN: Constructor - No additional initialization is required as all members are initialized in the class definition.
// ES: Constructor - No se requiere inicialización adicional ya que todos los miembros se inicializan en la definición de la clase.
Biquad_II_HSF::Biquad_II_HSF() {}

// EN: Destructor - No special cleanup is necessary since no dynamic memory is used.
// ES: Destructor - No se requiere limpieza especial ya que no se utiliza memoria dinámica.
Biquad_II_HSF::~Biquad_II_HSF() {}

// EN: Prepares the filter by setting the sample rate and updating the filter coefficients.
// ES: Prepara el filtro configurando la frecuencia de muestreo y actualizando los coeficientes del filtro.
void Biquad_II_HSF::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;
    updateFilter(); // EN: Ensure coefficients reflect the current sample rate. // ES: Asegura que los coeficientes reflejen la frecuencia de muestreo actual.
}

// EN: Processes the input audio buffer by applying the high-shelf filter to each sample.
// ES: Procesa el buffer de audio de entrada aplicando el filtro de estantería alta a cada muestra.
void Biquad_II_HSF::process(juce::AudioBuffer<float> inBuffer)
{
    int numChannels = inBuffer.getNumChannels(); // EN: Number of channels in the buffer. // ES: Número de canales en el buffer.
    int numSamples = inBuffer.getNumSamples();  // EN: Number of samples per channel. // ES: Número de muestras por canal.

    // EN: Iterate over each channel.
    // ES: Iterar sobre cada canal.
    for (int channel = 0; channel < numChannels; channel++)
    {
        // EN: Iterate over each sample in the channel.
        // ES: Iterar sobre cada muestra del canal.
        for (int i = 0; i < numSamples; i++)
        {
            float inSample = inBuffer.getSample(channel, i); // EN: Get the input sample. // ES: Obtener la muestra de entrada.

            float outSample = processSample(inSample, channel); // EN: Process the sample through the filter. // ES: Procesar la muestra a través del filtro.

            inBuffer.setSample(channel, i, outSample); // EN: Set the filtered sample back in the buffer. // ES: Colocar la muestra filtrada de nuevo en el buffer.
        }
    }
}

// EN: Processes a single sample for the given channel using the high-shelf filter.
// ES: Procesa una muestra única para el canal dado utilizando el filtro de estantería alta.
float Biquad_II_HSF::processSample(float inSample, int channel)
{
    // EN: Compute the intermediate value 'w' and the output 'y'.
    // ES: Calcular el valor intermedio 'w' y la salida 'y'.
    auto w = inSample - a1 * w1[channel] - a2 * w2[channel];
    auto y = b0 * w + b1 * w1[channel] + b2 * w2[channel];

    // EN: Update the delay lines.
    // ES: Actualizar las líneas de retardo.
    w2[channel] = w1[channel];
    w1[channel] = w;

    return y; // EN: Return the filtered sample. // ES: Devolver la muestra filtrada.
}

// EN: Sets the cutoff frequency and updates the filter coefficients.
// ES: Configura la frecuencia de corte y actualiza los coeficientes del filtro.
void Biquad_II_HSF::setFrequency(float inFrequency)
{
    frequency = inFrequency;
    updateFilter();
}

// EN: Sets the Q factor (resonance) and updates the filter coefficients.
// ES: Configura el factor Q (resonancia) y actualiza los coeficientes del filtro.
void Biquad_II_HSF::setQ(float inQ)
{
    Q = inQ;
    updateFilter();
}

// EN: Sets the gain for the high-shelf filter and updates the coefficients.
// ES: Configura la ganancia para el filtro de estantería alta y actualiza los coeficientes.
void Biquad_II_HSF::setGain(float inGain)
{
    Gain = inGain;
    updateFilter();
}

// EN: Recalculates the filter coefficients based on the current parameters and sample rate.
// ES: Recalcula los coeficientes del filtro según los parámetros actuales y la frecuencia de muestreo.
void Biquad_II_HSF::updateFilter()
{
    // EN: Compute intermediate values for the filter design.
    // ES: Calcular valores intermedios para el diseño del filtro.
    w0 = (juce::MathConstants<float>::twoPi * frequency) / static_cast<float>(sampleRate);
    alpha = sinf(w0) / (2.0f * Q);
    A = sqrt(powf(10.0f, Gain / 20.0f)); // EN: Compute linear gain from dB. // ES: Calcular la ganancia lineal a partir de los dB.

    // EN: Compute numerator coefficients.
    // ES: Calcular los coeficientes del numerador.
    b0 = A * ((A + 1.0f) + ((A - 1.0f) * cosf(w0)) + (2.0f * sqrtf(A) * alpha));
    b1 = -2.0f * A * ((A - 1.0f) + ((A + 1.0f) * cosf(w0)));
    b2 = A * ((A + 1.0f) + ((A - 1.0f) * cosf(w0)) - (2.0f * sqrtf(A) * alpha));

    // EN: Compute denominator coefficients.
    // ES: Calcular los coeficientes del denominador.
    a0 = (A + 1.0f) - ((A - 1.0f) * cosf(w0)) + (2.0f * sqrtf(A) * alpha);
    a1 = 2.0f * ((A - 1.0f) - ((A + 1.0f) * cosf(w0)));
    a2 = (A + 1.0f) - ((A - 1.0f) * cosf(w0)) - (2.0f * sqrtf(A) * alpha);

    // EN: Normalize the coefficients by dividing them by a0.
    // ES: Normalizar los coeficientes dividiéndolos por a0.
    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}
