/*
  ==============================================================================

    IIR_FirstOrderLPF.h
    Created: 30 Sep 2024 11:08:21am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: The IIRFirstOrderLPF class represents a first-order low-pass filter (LPF) 
//     that can be prepared with specific settings, processed with audio data, and adjusted with a cutoff frequency.
//     The filter uses IIR (Infinite Impulse Response) coefficients for efficient processing.
// ES: La clase IIRFirstOrderLPF representa un filtro pasa-bajos de primer orden (LPF)
//     que puede prepararse con configuraciones específicas, procesarse con datos de audio y ajustarse con una frecuencia de corte.
//     El filtro usa coeficientes IIR (Respuesta al Impulso Infinita) para un procesamiento eficiente.
class IIRFirstOrderLPF
{
public:
    // EN: Constructor of the IIRFirstOrderLPF class. Initializes the object.
    // ES: Constructor de la clase IIRFirstOrderLPF. Inicializa el objeto.
    IIRFirstOrderLPF();

    // EN: Destructor of the IIRFirstOrderLPF class. Cleans up resources when the object is destroyed.
    // ES: Destructor de la clase IIRFirstOrderLPF. Limpia los recursos cuando el objeto es destruido.
    ~IIRFirstOrderLPF();

    // EN: Prepares the filter with the given sample rate, block size, and number of channels.
    //     This method sets up the filter state and prepares it for processing.
    // ES: Prepara el filtro con la frecuencia de muestreo, el tamaño del bloque y el número de canales proporcionados.
    //     Este método configura el estado del filtro y lo prepara para el procesamiento.
    void prepare(double inSampleRate, int inSamplesPerBlock, int inChannels);

    // EN: Processes the audio buffer by applying the low-pass filter.
    //     This method modifies the buffer in place with the filtered audio.
    // ES: Procesa el búfer de audio aplicando el filtro pasa-bajos.
    //     Este método modifica el búfer directamente con el audio filtrado.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Sets the cutoff frequency of the filter and recalculates the filter coefficients.
    //     The filter will allow frequencies below this threshold and attenuate higher ones.
    // ES: Establece la frecuencia de corte del filtro y recalcula los coeficientes del filtro.
    //     El filtro permitirá las frecuencias por debajo de este umbral y atenuará las más altas.
    void setCutoffFrequency(float newCutoff);

private:

    // EN: Updates the filter coefficients based on the current sample rate and cutoff frequency.
    //     This method is called whenever the cutoff frequency changes.
    // ES: Actualiza los coeficientes del filtro según la frecuencia de muestreo y la frecuencia de corte actuales.
    //     Este método se llama cada vez que cambia la frecuencia de corte.
    void updateFilter();

    // EN: A ProcessorDuplicator that handles both the filter and its coefficients.
    //     It stores the filter state and applies the coefficients to process the audio.
    // ES: Un ProcessorDuplicator que maneja tanto el filtro como sus coeficientes.
    //     Almacena el estado del filtro y aplica los coeficientes para procesar el audio.
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> foLpf;

    // EN: The sample rate of the audio signal, used for coefficient calculations.
    // ES: La frecuencia de muestreo de la señal de audio, utilizada para los cálculos de coeficientes.
    double sampleRate{};

    // EN: The cutoff frequency of the filter, which determines the point at which frequencies will be attenuated.
    //     Frequencies below this value will pass through, and higher frequencies will be filtered out.
    // ES: La frecuencia de corte del filtro, que determina el punto en el que las frecuencias serán atenuadas.
    //     Las frecuencias por debajo de este valor pasarán, y las frecuencias más altas serán filtradas.
    float cutoffFrequency{};
};