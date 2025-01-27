/*
  ==============================================================================

    IIR_FirstOrderHPF.h
    Created: 30 Sep 2024 11:56:09am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: This class implements a first-order high-pass filter using JUCE's DSP module.
//     It allows for preparing the filter, processing audio, and adjusting the cutoff frequency.
// ES: Esta clase implementa un filtro pasa-altos de primer orden utilizando el módulo DSP de JUCE.
//     Permite preparar el filtro, procesar audio y ajustar la frecuencia de corte.

class IIRFirstOrderHPF
{
public:
    // EN: Constructor of the IIRFirstOrderHPF class. Initializes the object.
    // ES: Constructor de la clase IIRFirstOrderHPF. Inicializa el objeto.
    IIRFirstOrderHPF();

    // EN: Destructor of the IIRFirstOrderHPF class. Cleans up resources when the object is destroyed.
    // ES: Destructor de la clase IIRFirstOrderHPF. Limpia los recursos cuando el objeto es destruido.
    ~IIRFirstOrderHPF();

    // EN: Prepares the filter with the given sample rate, block size, and number of channels.
    //     This method sets up the filter state based on the provided specifications.
    // ES: Prepara el filtro con la frecuencia de muestreo, el tamaño del bloque y el número de canales proporcionados.
    //     Este método configura el estado del filtro según las especificaciones proporcionadas.
    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);

    // EN: Processes the audio buffer by applying the first-order high-pass filter.
    //     The filter is applied in place, modifying the buffer directly.
    // ES: Procesa el búfer de audio aplicando el filtro pasa-altos de primer orden.
    //     El filtro se aplica en el lugar, modificando directamente el búfer.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Sets the cutoff frequency of the filter and updates the filter coefficients accordingly.
    //     This method is called when the cutoff frequency needs to be changed.
    // ES: Establece la frecuencia de corte del filtro y actualiza los coeficientes del filtro en consecuencia.
    //     Este método se llama cuando se necesita cambiar la frecuencia de corte.
    void setCutoffFrequency(float newCutoff);

private:
    // EN: Updates the filter coefficients based on the current sample rate and cutoff frequency.
    //     This method recalculates the filter state whenever the cutoff frequency is changed.
    // ES: Actualiza los coeficientes del filtro según la frecuencia de muestreo y la frecuencia de corte actuales.
    //     Este método recalcula el estado del filtro cada vez que cambia la frecuencia de corte.
    void updateFilter();

    // EN: The filter object that performs the high-pass filtering using IIR filter coefficients.
    //     The ProcessorDuplicator handles the filter processing.
    // ES: El objeto del filtro que realiza el filtrado pasa-altos utilizando coeficientes de filtro IIR.
    //     El ProcessorDuplicator maneja el procesamiento del filtro.
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> foHpf;

    // EN: The sample rate of the audio processing system.
    //     This value is used to calculate the filter coefficients.
    // ES: La frecuencia de muestreo del sistema de procesamiento de audio.
    //     Este valor se utiliza para calcular los coeficientes del filtro.
    double sampleRate{};

    // EN: The cutoff frequency for the high-pass filter.
    //     This frequency determines the point at which the filter begins to attenuate low frequencies.
    // ES: La frecuencia de corte para el filtro pasa-altos.
    //     Esta frecuencia determina el punto en el que el filtro comienza a atenuar las frecuencias bajas.
    float cutoffFrequency{};
};