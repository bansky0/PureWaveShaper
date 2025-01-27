/*
  ==============================================================================

    MorphLFO.h
    Created: 28 Aug 2024 9:52:53am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MorphLfo
{
public:
    // ES: Configura la forma de onda del LFO.
    // EN: Sets the waveform shape of the LFO.
    void setShape(float inShapeValue);

    // ES: Configura la profundidad del LFO.
    // EN: Sets the depth (amplitude) of the LFO.
    void setDepth(float inDepthValue);

    // ES: Configura la frecuencia del LFO.
    // EN: Sets the frequency of the LFO.
    void setFrequency(double inFrequency);

    // ES: Inicializa los parámetros necesarios según la frecuencia de muestreo.
    // EN: Prepares the necessary parameters based on the sample rate.
    void prepare(double theSampleRate);

    // ES: Procesa un buffer de audio aplicando la modulación del LFO.
    // EN: Processes an audio buffer by applying LFO modulation.
    void process(juce::AudioBuffer<float>& buffer);

    // ES: Constructor: Inicializa los valores por defecto del LFO.
    // EN: Constructor: Initializes the LFO with default values.
    MorphLfo();

    // ES: Destructor: Libera recursos si es necesario.
    // EN: Destructor: Frees resources if necessary.
    ~MorphLfo();

private:
    float shapeValue{ 0.0f }; // ES: Forma de onda del LFO (rango: 0-10).
                              // EN: LFO waveform shape (range: 0-10).
    float frequency{ 100.0f }; // ES: Frecuencia del LFO (rango: 0-20 Hz).
                               // EN: LFO frequency (range: 0-20 Hz).
    float depthValue{ 1.0f };  // ES: Profundidad del LFO (rango: 0-100%).
                               // EN: LFO depth (range: 0-100%).
    float sampleRate{ 44100 }; // ES: Frecuencia de muestreo actual (Hz).
                               // EN: Current sample rate (Hz).
    float time[2]{};           // ES: Variables de tiempo independientes para cada canal.
                               // EN: Independent time variables for each channel.
    float deltaTime[2]{};      // ES: Incrementos de tiempo por muestra para cada canal.
                               // EN: Time increments per sample for each channel.
};
