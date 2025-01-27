/*
  ==============================================================================

    IIR_Notch.h
    Created: 30 Sep 2024 6:27:34pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class declaration for IIR_Notch, which implements a notch filter using JUCE's DSP module.
//     A notch filter is used to attenuate frequencies in a narrow band around the cutoff frequency.
// ES: Declaración de la clase IIR_Notch, que implementa un filtro notch utilizando el módulo DSP de JUCE.
//     Un filtro notch se utiliza para atenuar frecuencias en una banda estrecha alrededor de la frecuencia de corte.

class IIR_Notch
{
public:
    // EN: Constructor for the IIR_Notch class. Initializes the filter object but does not configure it yet.
    // ES: Constructor de la clase IIR_Notch. Inicializa el objeto del filtro, pero aún no lo configura.
    IIR_Notch();

    // EN: Destructor for the IIR_Notch class. Cleans up resources when the object is destroyed.
    // ES: Destructor de la clase IIR_Notch. Libera los recursos cuando se destruye el objeto.
    ~IIR_Notch();

    // EN: Prepares the filter with the given sample rate, block size, and number of channels.
    //     This method must be called before processing any audio.
    // ES: Prepara el filtro con la frecuencia de muestreo, el tamaño del bloque y el número de canales especificados.
    //     Este método debe ser llamado antes de procesar cualquier audio.
    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);

    // EN: Processes the audio buffer by applying the notch filter. Modifies the buffer in place.
    // ES: Procesa el búfer de audio aplicando el filtro notch. Modifica el búfer en su lugar.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Sets the cutoff frequency for the notch filter. This frequency determines the center of the attenuation band.
    //     After setting the frequency, the filter coefficients are updated.
    // ES: Establece la frecuencia de corte para el filtro notch. Esta frecuencia determina el centro de la banda de atenuación.
    //     Después de establecer la frecuencia, los coeficientes del filtro se actualizan.
    void setCutoffFrequency(float newCutoff);

private:
    // EN: Updates the filter coefficients based on the current cutoff frequency.
    //     This method recalculates the filter to reflect any changes in the cutoff frequency.
    // ES: Actualiza los coeficientes del filtro según la frecuencia de corte actual.
    //     Este método recalcula el filtro para reflejar cualquier cambio en la frecuencia de corte.
    void updateFilter();

    // EN: Notch filter implementation using JUCE's ProcessorDuplicator, which combines the filter and its coefficients.
    // ES: Implementación del filtro notch utilizando el ProcessorDuplicator de JUCE, que combina el filtro y sus coeficientes.
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> notch;

    // EN: Sample rate used for filter calculations.
    // ES: Frecuencia de muestreo utilizada para los cálculos del filtro.
    double sampleRate{};

    // EN: Cutoff frequency for the notch filter.
    // ES: Frecuencia de corte para el filtro notch.
    float cutoffFrequency{};
};
