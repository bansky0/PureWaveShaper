/*
  ==============================================================================

    Biquad_TDFII_HSF.h
    Created: 7 Oct 2024 4:02:12pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

// EN: Declaration of the Biquad_TDFII_HSF class, implementing a Biquad High Shelf Filter (HSF) 
// using the Direct Form II Transposed structure.
// ES: Declaración de la clase Biquad_TDFII_HSF, que implementa un filtro High Shelf Biquad (HSF) 
// utilizando la estructura de Forma Directa II Transpuesta.

class Biquad_TDFII_HSF
{
public:
    // EN: Constructor. Initializes the filter instance.
    // ES: Constructor. Inicializa la instancia del filtro.
    Biquad_TDFII_HSF();

    // EN: Destructor. Cleans up the filter instance.
    // ES: Destructor. Limpia la instancia del filtro.
    ~Biquad_TDFII_HSF();

    // EN: Prepares the filter by setting the sample rate and initializing its state.
    // ES: Prepara el filtro configurando la frecuencia de muestreo e inicializando su estado.
    void prepare(double inSampleRate);

    // EN: Processes a full audio buffer through the high shelf filter.
    // ES: Procesa un buffer de audio completo a través del filtro de estantería alta.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single audio sample for a specific channel.
    // ES: Procesa una única muestra de audio para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the cutoff frequency for the high shelf filter.
    // ES: Establece la frecuencia de corte del filtro de estantería alta.
    void setFrequency(float inFrequency);

    // EN: Sets the Q factor (resonance) for the high shelf filter.
    // ES: Establece el factor Q (resonancia) del filtro de estantería alta.
    void setQ(float inQ);

    // EN: Sets the gain for the high shelf filter.
    // ES: Establece la ganancia del filtro de estantería alta.
    void setGain(float inGain);

    // EN: Updates the filter coefficients based on frequency, Q, gain, and sample rate.
    // ES: Actualiza los coeficientes del filtro en función de la frecuencia, Q, ganancia y frecuencia de muestreo.
    void updateFilter();

private:
    // EN: Sample rate for processing audio.
    // ES: Frecuencia de muestreo para procesar audio.
    double sampleRate{ 0.0f };

    // EN: State variables for the filter (per channel).
    // ES: Variables de estado para el filtro (por canal).
    float r1[2] = { 0.0f }; // EN: First delay line for the state variable.
    // ES: Primera línea de retardo para la variable de estado.
    float r2[2] = { 0.0f }; // EN: Second delay line for the state variable.
    // ES: Segunda línea de retardo para la variable de estado.

// EN: Variables for filter coefficient calculations.
// ES: Variables para los cálculos de los coeficientes del filtro.
    float w0{ 0.0f };       // EN: Angular frequency.
    // ES: Frecuencia angular.
    float alpha{ 0.0f };    // EN: Filter bandwidth scaling factor.
    // ES: Factor de escalado del ancho de banda del filtro.

// EN: Coefficients for the filter's transfer function.
// ES: Coeficientes para la función de transferencia del filtro.
    float b0{ 0.0f };       // EN: Feedforward coefficient b0.
    // ES: Coeficiente de avance b0.
    float b1{ 0.0f };       // EN: Feedforward coefficient b1.
    // ES: Coeficiente de avance b1.
    float b2{ 0.0f };       // EN: Feedforward coefficient b2.
    // ES: Coeficiente de avance b2.
    float a0{ 0.0f };       // EN: Feedback coefficient a0.
    // ES: Coeficiente de retroalimentación a0.
    float a1{ 0.0f };       // EN: Feedback coefficient a1.
    // ES: Coeficiente de retroalimentación a1.
    float a2{ 0.0f };       // EN: Feedback coefficient a2.
    // ES: Coeficiente de retroalimentación a2.

// EN: Parameters for the high shelf filter.
// ES: Parámetros del filtro de estantería alta.
    float frequency{ 1000.0f }; // EN: Cutoff frequency in Hz.
    // ES: Frecuencia de corte en Hz.
    float Q{ 0.707f };          // EN: Quality factor controlling the filter's resonance.
    // ES: Factor de calidad que controla la resonancia del filtro.
    float Gain{ 0.0f };         // EN: Gain in decibels.
    // ES: Ganancia en decibelios.
    float A{ 0.0f };            // EN: Linear amplitude derived from gain.
    // ES: Amplitud lineal derivada de la ganancia.
};
