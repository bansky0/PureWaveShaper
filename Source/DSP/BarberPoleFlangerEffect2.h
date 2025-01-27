/*
  ==============================================================================

    BarberPoleFlangerEffect2.h
    Created: 5 Nov 2024 9:52:36am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>

// EN: Class for implementing a Barberpole Flanger effect.
// ES: Clase para implementar un efecto Barberpole Flanger.
class BarberpoleFlanger2FX
{
public:
    // EN: Constructor. Initializes the effect object.
    // ES: Constructor. Inicializa el objeto del efecto.
    BarberpoleFlanger2FX();

    // EN: Destructor. Cleans up the effect object.
    // ES: Destructor. Limpia el objeto del efecto.
    ~BarberpoleFlanger2FX();

    // EN: Prepares the effect with the given sample rate.
    // ES: Prepara el efecto con la frecuencia de muestreo proporcionada.
    void prepare(double theSampleRate);

    // EN: Sets the depth of the flanger effect.
    // ES: Establece la profundidad del efecto flanger.
    void setDepth(float inDepth);

    // EN: Sets the rate of the LFO as a percentage (0-100%).
    // ES: Establece la velocidad del LFO como porcentaje (0-100%).
    void setRate(float inRatePercentage);

    // EN: Sets the predelay time in milliseconds.
    // ES: Establece el tiempo de predelay en milisegundos.
    void setPredelay(float inPredelayMs);

    // EN: Processes an audio buffer to apply the flanger effect.
    // ES: Procesa un buffer de audio para aplicar el efecto flanger.
    void process(juce::AudioBuffer<float>& buffer);

private:
    // EN: Sample rate for processing audio.
    // ES: Frecuencia de muestreo para procesar audio.
    float sampleRate;

    // EN: LFO time for generating phase values.
    // ES: Tiempo del LFO para generar valores de fase.
    float t;

    // EN: Depth of the flanger effect.
    // ES: Profundidad del efecto flanger.
    float depth;

    // EN: Current rate percentage of the LFO.
    // ES: Porcentaje actual de velocidad del LFO.
    float ratePercentage;

    // EN: Target rate percentage of the LFO.
    // ES: Porcentaje objetivo de velocidad del LFO.
    float targetRatePercentage;

    // EN: Predelay time in samples.
    // ES: Tiempo de predelay en muestras.
    float predelay;

    // EN: Circular buffer size for delay lines.
    // ES: Tamaño del buffer circular para líneas de delay.
    static const int circularBufferSize = 48000;

    // EN: Stereo circular buffer for the first delay line.
    // ES: Buffer circular estéreo para la primera línea de delay.
    float circularBuffer1[circularBufferSize][2];

    // EN: Stereo circular buffer for the second delay line.
    // ES: Buffer circular estéreo para la segunda línea de delay.
    float circularBuffer2[circularBufferSize][2];

    // EN: Writer pointers for each channel in the first circular buffer.
    // ES: Punteros de escritura para cada canal en el primer buffer circular.
    int writterPointer1[2] = { 0, 0 };

    // EN: Writer pointers for each channel in the second circular buffer.
    // ES: Punteros de escritura para cada canal en el segundo buffer circular.
    int writterPointer2[2] = { 0, 0 };

    // EN: Crossfade coefficients for the first delay line.
    // ES: Coeficientes de crossfade para la primera línea de delay.
    static constexpr float crossfade1[2] = { 0.8f, 0.2f };

    // EN: Crossfade coefficients for the second delay line.
    // ES: Coeficientes de crossfade para la segunda línea de delay.
    static constexpr float crossfade2[2] = { 0.2f, 0.8f };

    // EN: Generates a sawtooth waveform based on the given phase.
    // ES: Genera una onda de diente de sierra basada en la fase dada.
    float generateSawtooth(float phase);
};