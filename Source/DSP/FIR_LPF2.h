/*
  ==============================================================================

    FIR_LPF2.h
    Created: 28 Sep 2024 9:39:51pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: FIR_LPF2 class that implements a low-pass filter using a FIR filter structure from JUCE DSP.
//     It provides methods to prepare, process, and update the filter with a configurable cutoff frequency.
// ES: Clase FIR_LPF2 que implementa un filtro de paso bajo utilizando una estructura de filtro FIR de JUCE DSP.
//     Proporciona métodos para preparar, procesar y actualizar el filtro con una frecuencia de corte configurable.
class FIR_LPF2
{
public:
    // EN: Constructor for FIR_LPF2 class. Initializes the filter with default values.
    // ES: Constructor de la clase FIR_LPF2. Inicializa el filtro con valores predeterminados.
    FIR_LPF2();

    // EN: Destructor for FIR_LPF2 class. Cleans up any resources when the filter is no longer needed.
    // ES: Destructor de la clase FIR_LPF2. Limpia los recursos cuando el filtro ya no es necesario.
    ~FIR_LPF2();

    // EN: Prepares the filter by setting up the sample rate, block size, and number of channels.
    //     This is done before processing the audio data to set up the necessary configurations.
    // ES: Prepara el filtro configurando la tasa de muestreo, el tamaño del bloque y el número de canales.
    //     Esto se realiza antes de procesar los datos de audio para configurar las configuraciones necesarias.
    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);

    // EN: Processes the audio buffer by applying the low-pass filter to the audio data.
    //     The processing is done on the provided audio buffer.
    // ES: Procesa el buffer de audio aplicando el filtro de paso bajo a los datos de audio.
    //     El procesamiento se realiza sobre el buffer de audio proporcionado.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Allows the user to change the cutoff frequency of the filter.
    //     This method recalculates the filter coefficients based on the new cutoff frequency.
    // ES: Permite al usuario cambiar la frecuencia de corte del filtro.
    //     Este método recalcula los coeficientes del filtro según la nueva frecuencia de corte.
    void setCutoffFrequency(float newCutoff);

private:
    // EN: Updates the FIR filter coefficients based on the current cutoff frequency and sample rate.
    //     This method is called whenever the cutoff frequency is changed.
    // ES: Actualiza los coeficientes del filtro FIR según la frecuencia de corte actual y la frecuencia de muestreo.
    //     Este método se llama siempre que se cambie la frecuencia de corte.
    void updateFilter();

    // EN: FIR filter instances for the left and right channels.
    // ES: Instancias de filtro FIR para los canales izquierdo y derecho.
    juce::dsp::FIR::Filter<float> lowPassFilter; // Filtro FIR LPF para el canal izquierdo
    juce::dsp::FIR::Filter<float> lowPassFilter2; // Filtro FIR LPF para el canal derecho

    // EN: Pointer to the filter coefficients, which will be updated based on the cutoff frequency.
    // ES: Puntero a los coeficientes del filtro, los cuales se actualizarán según la frecuencia de corte.
    juce::dsp::FIR::Coefficients<float>::Ptr coefficients;

    // EN: The sample rate of the audio signal.
    // ES: La frecuencia de muestreo de la señal de audio.
    double sampleRate;

    // EN: The cutoff frequency for the low-pass filter.
    // ES: La frecuencia de corte para el filtro de paso bajo.
    float cutoffFrequency;
};
