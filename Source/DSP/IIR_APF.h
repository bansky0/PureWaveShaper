/*
  ==============================================================================

    IIR_APF.h
    Created: 30 Sep 2024 1:14:09pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class for implementing an Infinite Impulse Response (IIR) All-Pass Filter (APF).
// ES: Clase para implementar un filtro de fase total (APF) de respuesta infinita al impulso (IIR).
class IIR_APF
{
public:
    // EN: Constructor. Initializes the IIR_APF object.
    // ES: Constructor. Inicializa el objeto IIR_APF.
    IIR_APF();

    // EN: Destructor. Cleans up any allocated resources.
    // ES: Destructor. Limpia cualquier recurso asignado.
    ~IIR_APF();

    // EN: Prepares the filter for processing by setting the sample rate, block size, and number of channels.
    // ES: Prepara el filtro para el procesamiento estableciendo la frecuencia de muestreo, el tamaño del bloque y el número de canales.
    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);

    // EN: Processes an audio buffer through the all-pass filter.
    // ES: Procesa un búfer de audio a través del filtro de fase total.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Sets the cutoff frequency of the filter and updates the coefficients accordingly.
    // ES: Establece la frecuencia de corte del filtro y actualiza los coeficientes en consecuencia.
    void setCutoffFrequency(float newCutoff);

private:
    // EN: Updates the filter coefficients based on the current cutoff frequency.
    // ES: Actualiza los coeficientes del filtro según la frecuencia de corte actual.
    void updateFilter();

    // EN: A JUCE DSP processor duplicator for managing IIR filter coefficients and processing.
    // ES: Un duplicador de procesadores de DSP de JUCE para gestionar los coeficientes del filtro IIR y su procesamiento.
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> foApf;

    // EN: The sample rate of the audio being processed.
    // ES: La frecuencia de muestreo del audio que se está procesando.
    double sampleRate{};

    // EN: The cutoff frequency of the filter in Hz.
    // ES: La frecuencia de corte del filtro en Hz.
    float cutoffFrequency{};
};