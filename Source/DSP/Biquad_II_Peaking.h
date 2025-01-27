/*
  ==============================================================================

    Biquad_II_Peaking.h
    Created: 7 Oct 2024 2:37:56pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

// EN: This class implements a Biquad peaking filter, which can be used for audio processing tasks
//     like equalization. It allows setting frequency, gain, and quality factor (Q) and updates
//     the filter coefficients accordingly.
// ES: Esta clase implementa un filtro biquad de pico, que se puede usar para tareas de procesamiento
//     de audio como ecualización. Permite establecer la frecuencia, ganancia y el factor de calidad (Q)
//     y actualiza los coeficientes del filtro en consecuencia.
class Biquad_II_Peaking
{
public:
    // EN: Constructor - Initializes the filter with default values.
    // ES: Constructor - Inicializa el filtro con valores predeterminados.
    Biquad_II_Peaking();

    // EN: Destructor - Cleans up any resources when the object is destroyed.
    // ES: Destructor - Limpia los recursos cuando el objeto es destruido.
    ~Biquad_II_Peaking();

    // EN: Prepares the filter by setting the sample rate and updating the filter coefficients.
    //     The sample rate is required to calculate the filter parameters and update them accordingly.
    // ES: Prepara el filtro estableciendo la frecuencia de muestreo y actualizando los coeficientes del filtro.
    //     La frecuencia de muestreo es necesaria para calcular los parámetros del filtro y actualizarlos en consecuencia.
    void prepare(double inSampleRate);

    // EN: Processes an entire audio buffer, applying the filter to each sample of each channel.
    //     It iterates over all channels and samples in the buffer to apply the filter.
    // ES: Procesa todo el buffer de audio, aplicando el filtro a cada muestra de cada canal.
    //     Itera sobre todos los canales y muestras del buffer para aplicar el filtro.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single sample for a specific channel by applying the peaking filter.
    //     This function calculates the filter output based on the current sample and the filter state.
    // ES: Procesa una sola muestra para un canal específico aplicando el filtro de pico.
    //     Esta función calcula la salida del filtro basada en la muestra actual y el estado del filtro.
    float processSample(float inSample, int channel);

    // EN: Sets the frequency of the peaking filter and updates the filter coefficients accordingly.
    //     After changing the frequency, the filter coefficients are updated to reflect the new frequency.
    // ES: Establece la frecuencia del filtro de pico y actualiza los coeficientes del filtro en consecuencia.
    //     Después de cambiar la frecuencia, los coeficientes del filtro se actualizan para reflejar la nueva frecuencia.
    void setFrequency(float inFrequency);

    // EN: Sets the gain of the peaking filter and updates the filter coefficients accordingly.
    //     Gain controls the amount of boost or cut at the given frequency.
    // ES: Establece la ganancia del filtro de pico y actualiza los coeficientes del filtro en consecuencia.
    //     La ganancia controla la cantidad de aumento o corte en la frecuencia dada.
    void setGain(float inGain);

    // EN: Sets the quality factor (Q) of the peaking filter and updates the filter coefficients accordingly.
    //     The quality factor controls the bandwidth of the filter, with higher values leading to narrower bandwidth.
    // ES: Establece el factor de calidad (Q) del filtro de pico y actualiza los coeficientes del filtro en consecuencia.
    //     El factor de calidad controla el ancho de banda del filtro, siendo valores más altos de Q más estrechos.
    void setQ(float inQ);

    // EN: Updates the filter coefficients based on the current frequency, gain, and Q factor.
    //     The filter coefficients (b0, b1, b2, a0, a1, a2) are calculated based on the frequency, Q, and gain.
    //     The coefficients are normalized by dividing by a0.
    // ES: Actualiza los coeficientes del filtro en función de la frecuencia, ganancia y factor Q actuales.
    //     Los coeficientes del filtro (b0, b1, b2, a0, a1, a2) se calculan en función de la frecuencia, Q y ganancia.
    //     Los coeficientes se normalizan dividiendo por a0.
    void updateFilter();

private:
    // EN: The sample rate of the audio signal, required to calculate filter parameters.
    // ES: La frecuencia de muestreo de la señal de audio, necesaria para calcular los parámetros del filtro.
    double sampleRate{ 0.0f };

    // EN: Internal state variables used for the filtering process (w1, w2).
    // ES: Variables de estado internas utilizadas en el proceso de filtrado (w1, w2).
    float w1[2] = { 0.0f };
    float w2[2] = { 0.0f };

    // EN: Filter parameters used to calculate the filter coefficients.
    //     w0 is the angular frequency, alpha is used for calculating filter resonance.
    // ES: Parámetros del filtro utilizados para calcular los coeficientes del filtro.
    //     w0 es la frecuencia angular, alpha se usa para calcular la resonancia del filtro.
    float w0{ 0.0f };
    float alpha{ 0.0f };

    // EN: Coefficients of the filter. These are calculated based on frequency, Q, and gain.
    //     b0, b1, b2 are the numerator coefficients and a0, a1, a2 are the denominator coefficients.
    // ES: Coeficientes del filtro. Estos se calculan en función de la frecuencia, Q y ganancia.
    //     b0, b1, b2 son los coeficientes del numerador y a0, a1, a2 son los coeficientes del denominador.
    float b0{ 0.0f };
    float b1{ 0.0f };
    float b2{ 0.0f };
    float a0{ 0.0f };
    float a1{ 0.0f };
    float a2{ 0.0f };

    // EN: The frequency, Q, and Gain parameters of the filter, which control its behavior.
    // ES: La frecuencia, Q y ganancia del filtro, que controlan su comportamiento.
    float frequency{ 1000.0f };  // Default frequency is 1000 Hz.
    float Q{ 0.707f };  // Default Q value is 0.707 (a standard value for peaking filters).
    float Gain{ 0.0f }; // Default Gain is 0 dB (no gain or cut).
    float A{ 0.0f };    // Internal parameter that is calculated based on Gain.
};
