/*
  ==============================================================================

    Biquad_TDFII_HPF.h
    Created: 7 Oct 2024 4:01:47pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include "Juceheader.h"

// EN: Class representing a High-Pass Filter (HPF) using the Transposed Direct Form II structure.
// ES: Clase que representa un filtro pasa altos (HPF) utilizando la estructura de Forma Directa Transpuesta II.
class Biquad_TDFII_HPF
{
public:
    // EN: Constructor for the Biquad_TDFII_HPF class.
    // ES: Constructor de la clase Biquad_TDFII_HPF.
    Biquad_TDFII_HPF();

    // EN: Destructor for the Biquad_TDFII_HPF class.
    // ES: Destructor de la clase Biquad_TDFII_HPF.
    ~Biquad_TDFII_HPF();

    // EN: Prepares the filter with the given sample rate.
    // ES: Prepara el filtro con la frecuencia de muestreo proporcionada.
    void prepare(double inSampleRate);

    // EN: Processes an entire audio buffer through the high-pass filter.
    // ES: Procesa un buffer de audio completo a través del filtro pasa altos.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single audio sample for a specific channel.
    // ES: Procesa una única muestra de audio para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the cutoff frequency of the high-pass filter.
    // ES: Establece la frecuencia de corte del filtro pasa altos.
    void setFrequency(float inFrequency);

    // EN: Sets the Q factor (resonance) of the high-pass filter.
    // ES: Establece el factor Q (resonancia) del filtro pasa altos.
    void setQ(float inQ);

    // EN: Updates the filter coefficients based on the current frequency, Q, and sample rate.
    // ES: Actualiza los coeficientes del filtro en función de la frecuencia, Q y frecuencia de muestreo actuales.
    void updateFilter();

private:
    // EN: The sample rate of the audio processing system.
    // ES: La frecuencia de muestreo del sistema de procesamiento de audio.
    double sampleRate{ 0.0f };

    // EN: Filter state variables for feedback paths, one for each channel.
    // ES: Variables de estado del filtro para las trayectorias de retroalimentación, una para cada canal.
    float r1[2] = { 0.0f };
    float r2[2] = { 0.0f };

    // EN: Intermediate filter calculations.
    // ES: Cálculos intermedios del filtro.
    float w0{ 0.0f };    // EN: Angular frequency (normalized). ES: Frecuencia angular (normalizada).
    float alpha{ 0.0f }; // EN: Filter bandwidth parameter. ES: Parámetro de ancho de banda del filtro.

    // EN: Coefficients of the filter.
    // ES: Coeficientes del filtro.
    float b0{ 0.0f }; // EN: Feedforward coefficient b0. ES: Coeficiente de avance b0.
    float b1{ 0.0f }; // EN: Feedforward coefficient b1. ES: Coeficiente de avance b1.
    float b2{ 0.0f }; // EN: Feedforward coefficient b2. ES: Coeficiente de avance b2.
    float a0{ 0.0f }; // EN: Feedback coefficient a0. ES: Coeficiente de retroalimentación a0.
    float a1{ 0.0f }; // EN: Feedback coefficient a1. ES: Coeficiente de retroalimentación a1.
    float a2{ 0.0f }; // EN: Feedback coefficient a2. ES: Coeficiente de retroalimentación a2.

    // EN: User-defined filter parameters.
    // ES: Parámetros del filtro definidos por el usuario.
    float frequency{ 1000.0f }; // EN: Cutoff frequency in Hz. ES: Frecuencia de corte en Hz.
    float Q{ 0.707f };          // EN: Q factor (quality factor). ES: Factor Q (factor de calidad).
};
