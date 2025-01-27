/*
  ==============================================================================

    SlewRateDistortion.cpp
    Created: 8 Oct 2024 3:00:37pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "SlewRateDistortion.h"

// EN: Constructor for the SlewRateDistortion class.
// ES: Constructor de la clase SlewRateDistortion.
SlewRateDistortion::SlewRateDistortion()
{
}

// EN: Destructor for the SlewRateDistortion class.
// ES: Destructor de la clase SlewRateDistortion.
SlewRateDistortion::~SlewRateDistortion()
{
}

// EN: Prepares the distortion processor by setting the sample rate and calculating the sampling period.
// ES: Prepara el procesador de distorsión configurando la tasa de muestreo y calculando el período de muestreo.
void SlewRateDistortion::prepare(double inSampleRate)
{
    sampleRate = inSampleRate;      // EN: Set the sample rate. | ES: Configura la tasa de muestreo.
    Ts = 1.0 / sampleRate;          // EN: Calculate the sampling period (1/sampleRate). | ES: Calcula el período de muestreo (1/tasa de muestreo).
}

// EN: Processes the entire audio buffer by applying slew rate distortion to each sample.
// ES: Procesa todo el buffer de audio aplicando distorsión por tasa de cambio a cada muestra.
void SlewRateDistortion::process(juce::AudioBuffer<float>& buffer)
{
    int numChannels = buffer.getNumChannels(); // EN: Get the number of audio channels. | ES: Obtiene el número de canales de audio.
    int numSamples = buffer.getNumSamples();   // EN: Get the number of samples per channel. | ES: Obtiene el número de muestras por canal.

    for (int channel = 0; channel < numChannels; channel++) // EN: Loop through all channels. | ES: Bucle a través de todos los canales.
    {
        for (int i = 0; i < numSamples; i++) // EN: Loop through all samples in the channel. | ES: Bucle a través de todas las muestras del canal.
        {
            float inSample = buffer.getSample(channel, i);   // EN: Get the current sample. | ES: Obtiene la muestra actual.

            float outSample = processSample(inSample, channel); // EN: Apply the slew rate distortion to the sample. | ES: Aplica la distorsión por tasa de cambio a la muestra.

            buffer.setSample(channel, i, outSample); // EN: Write the processed sample back to the buffer. | ES: Escribe la muestra procesada de nuevo en el buffer.
        }
    }
}

// EN: Processes a single sample with slew rate distortion for a specific channel.
// ES: Procesa una sola muestra con distorsión por tasa de cambio para un canal específico.
float SlewRateDistortion::processSample(float inSample, int channel)
{
    // EN: Calculate the difference between the current input sample and the previous output sample.
    // ES: Calcula la diferencia entre la muestra de entrada actual y la muestra de salida previa.
    delta[channel] = inSample - y1[channel];

    // EN: Limit the change (delta) to the maximum positive or negative slope.
    // ES: Limita el cambio (delta) a la pendiente máxima positiva o negativa.
    if (delta[channel] > slope)
    {
        delta[channel] = slope;
    }
    else if (delta[channel] < -slope)
    {
        delta[channel] = -slope;
    }

    // EN: Calculate the output by adding the limited change (delta) to the previous output.
    // ES: Calcula la salida sumando el cambio limitado (delta) a la salida previa.
    auto y = y1[channel] + delta[channel];

    // EN: Update the previous output sample for the next calculation.
    // ES: Actualiza la muestra de salida previa para el siguiente cálculo.
    y1[channel] = inSample;

    return y; // EN: Return the processed sample. | ES: Devuelve la muestra procesada.
}

// EN: Sets the maximum frequency for the slew rate distortion and updates the internal parameters.
// ES: Establece la frecuencia máxima para la distorsión por tasa de cambio y actualiza los parámetros internos.
void SlewRateDistortion::setMaxFreq(float inMaxFreq)
{
    maxFreq = inMaxFreq; // EN: Set the maximum frequency. | ES: Establece la frecuencia máxima.
    updateSlewRate();    // EN: Update the slew rate parameters. | ES: Actualiza los parámetros de tasa de cambio.
}

// EN: Updates the slew rate and slope based on the maximum frequency and sample rate.
// ES: Actualiza la tasa de cambio y la pendiente basada en la frecuencia máxima y la tasa de muestreo.
void SlewRateDistortion::updateSlewRate()
{
    // EN: Calculate the maximum slew rate based on the max frequency and a full-scale signal peak.
    // ES: Calcula la tasa de cambio máxima basada en la frecuencia máxima y un pico de señal a escala completa.
    slewRate = maxFreq * 2.0 * juce::MathConstants<double>::pi * peak;

    // EN: Calculate the slope (rate of change per sample) based on the slew rate and sample period.
    // ES: Calcula la pendiente (tasa de cambio por muestra) basada en la tasa de cambio y el período de muestreo.
    slope = slewRate * Ts;
}