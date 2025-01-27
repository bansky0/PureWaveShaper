/*
  ==============================================================================

    ModulatedDelay.h
    Created: 13 Nov 2024 3:29:42pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <vector>

// ES: Clase ModulatedDelay: Implementa un efecto de delay modulado con soporte para múltiples canales.
// EN: ModulatedDelay class: Implements a modulated delay effect with support for multiple channels.
class ModulatedDelay
{
public:
    // ES: Constructor: Inicializa los valores por defecto de la clase.
    // EN: Constructor: Initializes the default values of the class.
    ModulatedDelay();

    // ES: Destructor: Libera recursos utilizados por la clase.
    // EN: Destructor: Frees resources used by the class.
    ~ModulatedDelay();

    // ES: Configura el valor de sample rate para los cálculos.
    // EN: Configures the sample rate value for calculations.
    void prepare(double theSampleRate);

    // ES: Configura el delay en muestras, soportando valores fraccionales.
    // EN: Sets the delay in samples, supporting fractional values.
    void setDelay(float newDelayInSamples);

    // ES: Agrega una muestra al buffer para el canal especificado.
    // EN: Adds a sample to the buffer for the specified channel.
    void pushSample(int channel, float sample);

    // ES: Extrae una muestra del buffer aplicando el delay configurado.
    // EN: Retrieves a sample from the buffer applying the configured delay.
    float popSample(int channel);

    // ES: Procesa un buffer de audio aplicando el efecto de delay.
    // EN: Processes an audio buffer, applying the delay effect.
    void process(juce::AudioBuffer<float>& buffer);

private:
    double sampleRate{};                  // ES: Tasa de muestreo (samples por segundo).
                                          // EN: Sample rate (samples per second).

    static constexpr int maxDelaySamples = 48000; // ES: Máximo delay permitido en muestras.
                                                  // EN: Maximum allowed delay in samples.

    std::vector<int> writeIndex;         // ES: Índices de escritura para cada canal en el buffer circular.
                                         // EN: Write indices for each channel in the circular buffer.

    float delay{};                       // ES: Valor total del delay en muestras (incluye parte entera y fraccional).
                                         // EN: Total delay value in samples (includes integer and fractional parts).

    int delayInt{};                      // ES: Parte entera del valor de delay.
                                         // EN: Integer part of the delay value.

    float delayFrac{};                   // ES: Parte fraccional del valor de delay.
                                         // EN: Fractional part of the delay value.

    std::vector<std::vector<float>> buffer; // ES: Buffer de delay circular, con un buffer para cada canal.
                                            // EN: Circular delay buffer, with one buffer for each channel.
};
