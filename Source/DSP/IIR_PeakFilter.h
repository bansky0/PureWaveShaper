/*
  ==============================================================================

    IIR_PeakFilter.h
    Created: 30 Sep 2024 6:28:09pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: This class implements an IIR peak filter, allowing control of cutoff frequency, Q factor, and gain.
// ES: Esta clase implementa un filtro pico IIR, permitiendo el control de la frecuencia de corte, el factor Q y la ganancia.
class IIR_PeakF
{
public:
    // EN: Constructor. Initializes the filter object.
    // ES: Constructor. Inicializa el objeto del filtro.
    IIR_PeakF();

    // EN: Destructor. Cleans up resources used by the filter.
    // ES: Destructor. Libera los recursos utilizados por el filtro.
    ~IIR_PeakF();

    // EN: Prepares the filter for audio processing. Sets sample rate, block size, and number of channels.
    //     This must be called before using the filter.
    // ES: Prepara el filtro para el procesamiento de audio. Configura la frecuencia de muestreo, el tamaño del bloque y el número de canales.
    //     Esto debe llamarse antes de usar el filtro.
    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);

    // EN: Processes an audio buffer through the peak filter. Applies the filter in place.
    // ES: Procesa un búfer de audio a través del filtro pico. Aplica el filtro directamente en el búfer.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Sets the cutoff frequency of the peak filter. Updates the filter coefficients.
    // ES: Establece la frecuencia de corte del filtro pico. Actualiza los coeficientes del filtro.
    void setCutoffFrequency(float newCutoff);

    // EN: Sets the Q factor of the peak filter. Updates the filter coefficients.
    // ES: Establece el factor Q del filtro pico. Actualiza los coeficientes del filtro.
    void setQ(float newQ);

    // EN: Sets the gain of the peak filter. Updates the filter coefficients.
    // ES: Establece la ganancia del filtro pico. Actualiza los coeficientes del filtro.
    void setGain(float newGain);

private:
    // EN: Updates the filter coefficients based on the current parameters (cutoff frequency, Q factor, and gain).
    // ES: Actualiza los coeficientes del filtro en función de los parámetros actuales (frecuencia de corte, factor Q y ganancia).
    void updateFilter();

    // EN: The filter processor that manages the IIR filter and its coefficients.
    // ES: El procesador del filtro que gestiona el filtro IIR y sus coeficientes.
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> notch;

    // EN: The sample rate of the audio system.
    // ES: La frecuencia de muestreo del sistema de audio.
    double sampleRate{};

    // EN: The cutoff frequency of the peak filter.
    // ES: La frecuencia de corte del filtro pico.
    float cutoffFrequency{};

    // EN: The Q factor of the peak filter, which controls the bandwidth.
    // ES: El factor Q del filtro pico, que controla el ancho de banda.
    float q{};

    // EN: The gain of the peak filter, measured in decibels.
    // ES: La ganancia del filtro pico, medida en decibelios.
    float gain{};
};