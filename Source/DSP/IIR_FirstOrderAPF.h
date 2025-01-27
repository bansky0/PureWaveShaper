/*
  ==============================================================================

    IIR_FirstOrderAPF.h
    Created: 30 Sep 2024 12:55:31pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once 
#include <JuceHeader.h>

// EN: IIRFirstOrderAPF class is a first-order all-pass filter implementation using JUCE DSP.
//     It processes audio signals by applying the filter and allows setting and updating its cutoff frequency.
// ES: La clase IIRFirstOrderAPF es una implementación de un filtro pasapaso de primer orden utilizando JUCE DSP.
//     Procesa señales de audio aplicando el filtro y permite configurar y actualizar su frecuencia de corte.

class IIRFirstOrderAPF
{
public:
    // EN: Constructor for the IIRFirstOrderAPF class, initializes the object.
    // ES: Constructor para la clase IIRFirstOrderAPF, inicializa el objeto.
    IIRFirstOrderAPF();

    // EN: Destructor for the IIRFirstOrderAPF class, cleans up resources.
    // ES: Destructor para la clase IIRFirstOrderAPF, limpia los recursos.
    ~IIRFirstOrderAPF();

    // EN: Prepares the filter with the sample rate, block size, and number of channels.
    //     This method initializes the filter coefficients based on the incoming parameters.
    // ES: Prepara el filtro con la frecuencia de muestreo, el tamaño del bloque y el número de canales.
    //     Este método inicializa los coeficientes del filtro según los parámetros entrantes.
    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);

    // EN: Processes the audio buffer using the first-order all-pass filter.
    //     The method applies the filter to the audio buffer in place.
    // ES: Procesa el búfer de audio utilizando el filtro pasapaso de primer orden.
    //     El método aplica el filtro al búfer de audio en el lugar.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Sets the cutoff frequency for the filter and updates its coefficients.
    // ES: Establece la frecuencia de corte para el filtro y actualiza sus coeficientes.
    void setCutoffFrequency(float newCutoff);

private:
    // EN: Updates the filter coefficients based on the cutoff frequency.
    //     This method is used to recalculate the filter state whenever the cutoff frequency changes.
    // ES: Actualiza los coeficientes del filtro según la frecuencia de corte.
    //     Este método se utiliza para recalcular el estado del filtro cada vez que cambia la frecuencia de corte.
    void updateFilter();

    // EN: An instance of the JUCE filter processor duplicator, which is used to apply the IIR filter.
    //     It manages the filter state and coefficients for processing audio.
    // ES: Una instancia del duplicador de procesadores de filtros JUCE, que se utiliza para aplicar el filtro IIR.
    //     Gestiona el estado y los coeficientes del filtro para procesar audio.
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> foApf;

    // EN: The sample rate of the audio signal.
    // ES: La frecuencia de muestreo de la señal de audio.
    double sampleRate{};

    // EN: The cutoff frequency for the filter, which defines the frequency response.
    // ES: La frecuencia de corte para el filtro, que define la respuesta en frecuencia.
    float cutoffFrequency{};
};