/*
  ==============================================================================

    IIR_LPF.h
    Created: 30 Sep 2024 1:13:35pm
    Author:  Jhonatan López
    Notes: somes distortion 300hz an lower values. some glitchs in veryhig frequencies.
  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class definition for a low-pass IIR filter (IIR_LPF).
//     This filter allows frequencies below the cutoff frequency to pass and attenuates frequencies above it.
// ES: Definición de clase para un filtro pasa bajos IIR (IIR_LPF).
//     Este filtro permite que pasen las frecuencias por debajo de la frecuencia de corte y atenúa las frecuencias por encima de ella.
class IIR_LPF
{
public:
    // EN: Constructor for the IIR_LPF class. Initializes the filter object.
    // ES: Constructor para la clase IIR_LPF. Inicializa el objeto del filtro.
    IIR_LPF();

    // EN: Destructor for the IIR_LPF class. Cleans up resources when the object is destroyed.
    // ES: Destructor para la clase IIR_LPF. Libera los recursos cuando el objeto es destruido.
    ~IIR_LPF();

    // EN: Prepares the low-pass filter with the given sample rate, block size, and number of channels.
    //     Sets up the filter to be ready for processing audio.
    // ES: Prepara el filtro pasa bajos con la frecuencia de muestreo, tamaño de bloque y número de canales proporcionados.
    //     Configura el filtro para estar listo para procesar audio.
    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);

    // EN: Processes the given audio buffer with the low-pass filter.
    //     This method modifies the buffer by applying the filter to the audio data.
    // ES: Procesa el búfer de audio proporcionado con el filtro pasa bajos.
    //     Este método modifica el búfer aplicando el filtro a los datos de audio.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Sets the cutoff frequency for the low-pass filter.
    //     The cutoff frequency determines the point at which the filter starts attenuating higher frequencies.
    // ES: Establece la frecuencia de corte para el filtro pasa bajos.
    //     La frecuencia de corte determina el punto en el que el filtro comienza a atenuar las frecuencias altas.
    void setCutoffFrequency(float newCutoff);

private:
    // EN: Updates the filter coefficients based on the current sample rate and cutoff frequency.
    //     This method is used to adjust the filter's behavior when the cutoff frequency changes.
    // ES: Actualiza los coeficientes del filtro según la frecuencia de muestreo y la frecuencia de corte actuales.
    //     Este método se utiliza para ajustar el comportamiento del filtro cuando cambia la frecuencia de corte.
    void updateFilter();

    // EN: The low-pass filter object, which is a duplicator of the IIR filter with the given coefficients.
    //     This filter will process the audio data according to the coefficients.
    // ES: El objeto filtro pasa bajos, que es un duplicador del filtro IIR con los coeficientes dados.
    //     Este filtro procesará los datos de audio según los coeficientes.
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> foApf;

    // EN: The sample rate used for processing the audio. It is required to compute the filter coefficients.
    // ES: La frecuencia de muestreo utilizada para procesar el audio. Es necesaria para calcular los coeficientes del filtro.
    double sampleRate{};

    // EN: The cutoff frequency of the low-pass filter. It determines which frequencies will pass through the filter.
    // ES: La frecuencia de corte del filtro pasa bajos. Determina qué frecuencias pasarán a través del filtro.
    float cutoffFrequency{};
};