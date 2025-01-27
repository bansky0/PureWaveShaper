/*
  ==============================================================================

    IIR_BPF.h
    Created: 30 Sep 2024 4:05:49pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class definition for an IIR Band-Pass Filter (BPF).
// ES: Definición de la clase para un filtro pasabanda (BPF) IIR.
class IIR_BPF
{
public:
    // EN: Constructor for the IIR_BPF class.
    // ES: Constructor para la clase IIR_BPF.
    IIR_BPF();

    // EN: Destructor for the IIR_BPF class.
    // ES: Destructor para la clase IIR_BPF.
    ~IIR_BPF();

    // EN: Prepares the filter for audio processing by setting sample rate, block size, and number of channels.
    // ES: Prepara el filtro para el procesamiento de audio configurando la frecuencia de muestreo, el tamaño de bloque y el número de canales.
    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);

    // EN: Processes the audio buffer through the band-pass filter.
    // ES: Procesa el búfer de audio a través del filtro pasabanda.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Sets the cutoff frequency for the filter.
    // ES: Establece la frecuencia de corte para el filtro.
    void setCutoffFrequency(float newCutoff);

private:
    // EN: Updates the filter coefficients based on the current settings.
    // ES: Actualiza los coeficientes del filtro según la configuración actual.
    void updateFilter();

    // EN: Band-pass filter object that duplicates the state and coefficients.
    // ES: Objeto de filtro pasabanda que duplica el estado y los coeficientes.
    juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>,
        juce::dsp::IIR::Coefficients<float>> bpf;

    // EN: The sample rate of the audio signal.
    // ES: La frecuencia de muestreo de la señal de audio.
    double sampleRate{};

    // EN: The cutoff frequency for the band-pass filter.
    // ES: La frecuencia de corte para el filtro pasabanda.
    float cutoffFrequency{};

    // EN: The quality factor (Q) of the filter, defining the sharpness of the passband.
    // ES: El factor de calidad (Q) del filtro, que define la nitidez de la banda de paso.
    float q{};

    // EN: The gain applied within the passband.
    // ES: La ganancia aplicada dentro de la banda de paso.
    float gain{};
};
