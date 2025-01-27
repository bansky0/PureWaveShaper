/*
  ==============================================================================

    IIR_HPF.h
    Created: 29 Sep 2024 8:49:51pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: IIR_HPF class represents an IIR high-pass filter that processes audio signals.
//     It allows setting a cutoff frequency and applying the filter to an audio buffer.
// ES: La clase IIR_HPF representa un filtro pasa-altos IIR que procesa señales de audio.
//     Permite establecer una frecuencia de corte y aplicar el filtro a un búfer de audio.
class IIR_HPF
{
public:
    // EN: Default constructor for the IIR_HPF class.
    // ES: Constructor por defecto para la clase IIR_HPF.
    IIR_HPF();

    // EN: Destructor for the IIR_HPF class.
    // ES: Destructor para la clase IIR_HPF.
    ~IIR_HPF();

    // EN: Prepares the filter with the provided sample rate, block size, and number of channels.
    //     This method initializes the filter with the given specifications.
    //     The filter is ready to process audio once this method is called.
    // ES: Prepara el filtro con la frecuencia de muestreo, el tamaño del bloque y el número de canales proporcionados.
    //     Este método inicializa el filtro con las especificaciones dadas.
    //     El filtro estará listo para procesar el audio una vez que se llame a este método.
    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);

    // EN: Processes the audio buffer by applying the high-pass filter.
    //     This method modifies the buffer in place with the filtered audio.
    // ES: Procesa el búfer de audio aplicando el filtro pasa-altos.
    //     Este método modifica el búfer directamente con el audio filtrado.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Sets the cutoff frequency for the high-pass filter.
    //     The cutoff frequency determines the threshold below which frequencies will be attenuated.
    // ES: Establece la frecuencia de corte para el filtro pasa-altos.
    //     La frecuencia de corte determina el umbral por debajo del cual se atenuarán las frecuencias.
    void setCutoffFrequency(float newCutoff);

private:
    // EN: Updates the filter coefficients based on the current sample rate and cutoff frequency.
    //     This method is used to recalculate the filter's behavior when the cutoff frequency changes.
    // ES: Actualiza los coeficientes del filtro según la frecuencia de muestreo y la frecuencia de corte actuales.
    //     Este método se utiliza para recalcular el comportamiento del filtro cuando cambia la frecuencia de corte.
    void updateFilter();

    // EN: A ProcessorDuplicator that holds both the filter instance and its coefficients.
    //     This is responsible for processing the audio with the IIR high-pass filter.
    // ES: Un ProcessorDuplicator que contiene tanto la instancia del filtro como sus coeficientes.
    //     Este se encarga de procesar el audio con el filtro pasa-altos IIR.
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> hpf;

    // EN: Stores the sample rate for the audio processing.
    // ES: Almacena la frecuencia de muestreo para el procesamiento de audio.
    double sampleRate{};

    // EN: Stores the cutoff frequency for the high-pass filter.
    // ES: Almacena la frecuencia de corte para el filtro pasa-altos.
    float cutoffFrequency{};
};