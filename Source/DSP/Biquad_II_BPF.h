/*
  ==============================================================================

    Biquad_II_BPF.h
    Created: 7 Oct 2024 12:00:13pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

// EN: The Biquad_II_BPF class represents a second-order band-pass filter (BPF) using the Direct Form II implementation.
// ES: La clase Biquad_II_BPF representa un filtro pasa-banda de segundo orden (BPF) utilizando la implementación en Forma Directa II.
class Biquad_II_BPF
{
public:
    // EN: Constructor - Initializes the Biquad_II_BPF object. 
    // ES: Constructor - Inicializa el objeto Biquad_II_BPF.
    Biquad_II_BPF();

    // EN: Destructor - Cleans up the Biquad_II_BPF object. 
    // ES: Destructor - Limpia el objeto Biquad_II_BPF.
    ~Biquad_II_BPF();

    // EN: Prepares the filter for processing by setting the sample rate and updating the filter coefficients.
    // ES: Prepara el filtro para el procesamiento configurando la frecuencia de muestreo y actualizando los coeficientes del filtro.
    void prepare(double inSampleRate);

    // EN: Processes an audio buffer, applying the filter to each channel and sample.
    // ES: Procesa un buffer de audio, aplicando el filtro a cada canal y muestra.
    void process(juce::AudioBuffer<float>& inBuffer);

    // EN: Processes a single sample through the filter for a specific channel.
    // ES: Procesa una muestra a través del filtro para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the cutoff frequency of the filter and updates the filter coefficients.
    // ES: Establece la frecuencia de corte del filtro y actualiza los coeficientes del filtro.
    void setFrequency(float inFrequency);

    // EN: Sets the quality factor (Q) of the filter and updates the filter coefficients.
    // ES: Establece el factor de calidad (Q) del filtro y actualiza los coeficientes del filtro.
    void setQ(float inQ);

    // EN: Updates the filter coefficients based on the current frequency, Q, and sample rate.
    // ES: Actualiza los coeficientes del filtro según la frecuencia, el Q y la frecuencia de muestreo actuales.
    void updateFilter();

private:
    // EN: Sample rate of the audio processing. // ES: Frecuencia de muestreo del procesamiento de audio.
    double sampleRate{ 0.0f };

    // EN: Delay lines for storing intermediate states for each channel. // ES: Líneas de retardo para almacenar estados intermedios para cada canal.
    float w1[2] = { 0.0f };
    float w2[2] = { 0.0f };

    // EN: Filter coefficients related to the frequency response. // ES: Coeficientes del filtro relacionados con la respuesta en frecuencia.
    float w0{ 0.0f }; // EN: Angular frequency (w0) // ES: Frecuencia angular (w0)
    float alpha{ 0.0f }; // EN: Bandwidth scaling factor (alpha) // ES: Factor de escalado de ancho de banda (alpha)

    // EN: Numerator coefficients of the filter. // ES: Coeficientes del numerador del filtro.
    float b0{ 0.0f };
    float b1{ 0.0f };
    float b2{ 0.0f };

    // EN: Denominator coefficients of the filter. // ES: Coeficientes del denominador del filtro.
    float a0{ 0.0f };
    float a1{ 0.0f };
    float a2{ 0.0f };

    // EN: Frequency and quality factor (Q) of the filter. // ES: Frecuencia y factor de calidad (Q) del filtro.
    float frequency{ 1000.0f };
    float Q{ 0.707f }; // EN: Default Q value for a critically damped filter. // ES: Valor predeterminado de Q para un filtro críticamente amortiguado.
};