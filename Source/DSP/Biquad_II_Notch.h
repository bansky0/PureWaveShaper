/*
  ==============================================================================

    Biquad_II_Notch.h
    Created: 7 Oct 2024 2:37:19pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

// EN: This class implements a notch filter using the Biquad II filter structure.
// ES: Esta clase implementa un filtro notch utilizando la estructura de filtro Biquad II.
class Biquad_II_Notch
{
public:
    // EN: Default constructor. Initializes filter parameters to default values.
    // ES: Constructor por defecto. Inicializa los parámetros del filtro con valores predeterminados.
    Biquad_II_Notch();

    // EN: Destructor. Cleans up any resources when the object is destroyed.
    // ES: Destructor. Limpia cualquier recurso cuando el objeto es destruido.
    ~Biquad_II_Notch();

    // EN: Prepares the filter by setting the sample rate and updating the filter coefficients.
    // ES: Prepara el filtro estableciendo la frecuencia de muestreo y actualizando los coeficientes del filtro.
    void prepare(double inSampleRate);

    // EN: Processes the entire audio buffer by applying the filter to each sample.
    // ES: Procesa el buffer de audio completo aplicando el filtro a cada muestra.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single sample of audio for a specific channel.
    // ES: Procesa una sola muestra de audio para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the frequency of the notch filter and updates the filter coefficients.
    // ES: Establece la frecuencia del filtro notch y actualiza los coeficientes del filtro.
    void setFrequency(float inFrequency);

    // EN: Sets the quality factor (Q) of the notch filter and updates the filter coefficients.
    // ES: Establece el factor de calidad (Q) del filtro notch y actualiza los coeficientes del filtro.
    void setQ(float inQ);

    // EN: Updates the filter coefficients based on the current frequency and Q.
    // ES: Actualiza los coeficientes del filtro en función de la frecuencia y el Q actuales.
    void updateFilter();

private:
    // EN: Sample rate of the audio signal, used to calculate filter coefficients.
    // ES: Frecuencia de muestreo de la señal de audio, utilizada para calcular los coeficientes del filtro.
    double sampleRate{ 0.0f };

    // EN: Internal state variables used in the filter calculations.
    // ES: Variables de estado internas utilizadas en los cálculos del filtro.
    float w1[2] = { 0.0f };
    float w2[2] = { 0.0f };

    // EN: Angular frequency (w0) and alpha value used in the notch filter calculation.
    // ES: Frecuencia angular (w0) y valor alpha utilizados en el cálculo del filtro notch.
    float w0{ 0.0f };
    float alpha{ 0.0f };

    // EN: Filter coefficients for the notch filter.
    // ES: Coeficientes del filtro para el filtro notch.
    float b0{ 0.0f };
    float b1{ 0.0f };
    float b2{ 0.0f };
    float a0{ 0.0f };
    float a1{ 0.0f };
    float a2{ 0.0f };

    // EN: Frequency and Q factor for the notch filter, defaulting to 1000 Hz and 0.707 respectively.
    // ES: Frecuencia y factor Q para el filtro notch, con valores predeterminados de 1000 Hz y 0.707 respectivamente.
    float frequency{ 1000.0f };
    float Q{ 0.707f };
};
