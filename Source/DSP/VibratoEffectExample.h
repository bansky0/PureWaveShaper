/*
  ==============================================================================

    VibratoEffectExample.h
    Created: 21 Oct 2024 9:19:16pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <vector>

// EN: Class implementing a vibrato effect using a circular buffer and LFO modulation.
// ES: Clase que implementa un efecto de vibrato utilizando un buffer circular y modulación con LFO.
class VibratoEffect
{
public:
    // EN: Constructor. Initializes the effect.
    // ES: Constructor. Inicializa el efecto.
    VibratoEffect();

    // EN: Destructor. Cleans up any resources used by the effect.
    // ES: Destructor. Limpia los recursos utilizados por el efecto.
    ~VibratoEffect();

    // EN: Prepares the vibrato effect with the given sample rate.
    // ES: Prepara el efecto de vibrato con la tasa de muestreo proporcionada.
    void prepare(double sampleRate);

    // EN: Sets the frequency of the LFO in Hz.
    // ES: Configura la frecuencia del LFO en Hz.
    void setRate(float rateHz);

    // EN: Sets the depth of the vibrato in samples.
    // ES: Configura la profundidad del vibrato en muestras.
    void setDepth(float depthSamples);

    // EN: Processes the audio buffer to apply the vibrato effect.
    // ES: Procesa el buffer de audio para aplicar el efecto de vibrato.
    void process(juce::AudioBuffer<float>& buffer);

private:
    // EN: The sample rate of the audio signal.
    // ES: La tasa de muestreo de la señal de audio.
    double sampleRate = 48000;

    // EN: Maximum delay in samples for the circular buffer.
    // ES: Retardo máximo en muestras para el buffer circular.
    int delaySamples = 1000;

    // EN: Frequency of the LFO in Hz.
    // ES: Frecuencia del LFO en Hz.
    float rate = 4;

    // EN: Depth of the vibrato in samples.
    // ES: Profundidad del vibrato en muestras.
    float depth = 75;

    // EN: Current time for the LFO phase.
    // ES: Tiempo actual para la fase del LFO.
    float t = 0.0f;

    // EN: Keeps track of the current sample being processed.
    // ES: Rastrea la muestra actual que se está procesando.
    int currentSample = 0;

    // EN: Phase of the LFO.
    // ES: Fase del LFO.
    float lfoPhase = 0.0f;

    // EN: Size of the circular buffer used for delay.
    // ES: Tamaño del buffer circular utilizado para el retardo.
    static const int circularBufferSize = 1000;

    // EN: Circular buffer to store delayed samples for each channel.
    // ES: Buffer circular para almacenar muestras retrasadas para cada canal.
    float circularBuffer[circularBufferSize][2] = { 0.0f };

    // EN: Pointer to the read position in the circular buffer.
    // ES: Puntero a la posición de lectura en el buffer circular.
    int readerPointer = 0;

    // EN: Array of write pointers for each channel in the circular buffer.
    // ES: Arreglo de punteros de escritura para cada canal en el buffer circular.
    int writterPointer[2] = { 0, 0 };
};
