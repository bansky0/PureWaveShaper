/*
  ==============================================================================

    FIR_HPF.h
    Created: 27 Sep 2024 8:52:32am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: FIR_LPF class defines a low-pass FIR filter. It provides methods to set the cutoff frequency,
// initialize the filter based on the sample rate and block size, and process an audio buffer.
// ES: La clase FIR_LPF define un filtro FIR de paso bajo. Proporciona métodos para establecer la frecuencia de corte,
// inicializar el filtro según la tasa de muestreo y el tamaño del bloque, y procesar un buffer de audio.
class FIR_LPF
{
public:

    // EN: Constructor of the FIR_LPF class, initializes the filter with default values.
    // ES: Constructor de la clase FIR_LPF, inicializa el filtro con valores predeterminados.
    FIR_LPF();

    // EN: Destructor of the FIR_LPF class, cleans up resources when the filter is no longer needed.
    // ES: Destructor de la clase FIR_LPF, limpia los recursos cuando el filtro ya no se necesita.
    ~FIR_LPF();

    // EN: Method to update the cutoff frequency of the low-pass filter.
    // ES: Método para actualizar la frecuencia de corte del filtro de paso bajo.
    void setCutoffFrequency(float newCutoff);

    // EN: Prepares the filter by setting the sample rate, block size, and number of channels.
    //     This is done before the filtering process to configure the filter correctly.
    // ES: Prepara el filtro estableciendo la tasa de muestreo, el tamaño del bloque y el número de canales.
    //     Esto se hace antes del proceso de filtrado para configurar el filtro correctamente.
    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);

    // EN: Processes the audio buffer using the low-pass filter.
    //     Applies the filter to the audio data contained in the buffer.
    // ES: Procesa el buffer de audio utilizando el filtro de paso bajo.
    //     Aplica el filtro a los datos de audio contenidos en el buffer.
    void process(juce::AudioBuffer<float>& buffer);

private:
    // EN: Low-pass filter objects used for processing the audio signal.
    // ES: Objetos de filtro de paso bajo utilizados para procesar la señal de audio.
    juce::dsp::FIR::Filter<float> lowPassFilter; // Filtro FIR LPF
    juce::dsp::FIR::Filter<float> lowPassFilter2; // Filtro FIR LPF adicional (posiblemente para redundancia o diferentes configuraciones)

    // EN: Coefficients of the FIR filter, used to define the filter characteristics.
    // ES: Coeficientes del filtro FIR, utilizados para definir las características del filtro.
    juce::dsp::FIR::Coefficients<float>::Ptr coefficients; // Coeficientes del filtro FIR

    // EN: The cutoff frequency of the low-pass filter, initially set to 20,000 Hz (the upper limit of human hearing).
    // ES: La frecuencia de corte del filtro de paso bajo, inicialmente establecida en 20,000 Hz (el límite superior de la audición humana).
    float cutoffFrequency = 20000.0f;

    // EN: The sample rate of the audio system. This is used to calculate filter coefficients and set up the filter.
    // ES: La tasa de muestreo del sistema de audio. Se usa para calcular los coeficientes del filtro y configurar el filtro.
    double sampleRate{};

    // EN: Updates the filter coefficients based on the current cutoff frequency and sample rate.
    // ES: Actualiza los coeficientes del filtro según la frecuencia de corte y la tasa de muestreo actuales.
    void updateFilter();
};

