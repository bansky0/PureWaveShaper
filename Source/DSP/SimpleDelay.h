/*
  ==============================================================================

    SimpleDelay.h
    Created: 17 Sep 2024 1:08:03pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Defines a simple delay effect class.
// ES: Define una clase de efecto de delay simple.
class SimpleDelay
{
public:
    // EN: Prepares the delay effect by setting the sample rate.
    // ES: Prepara el efecto de delay configurando la frecuencia de muestreo.
    void prepare(double theSampleRate);

    // EN: Sets the delay time in samples.
    // ES: Configura el tiempo de delay en muestras.
    void setDelay(float delayTime);

    // EN: Processes the input audio buffer and applies the delay effect.
    // ES: Procesa el búfer de audio de entrada y aplica el efecto de delay.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the SimpleDelay class.
    // ES: Constructor de la clase SimpleDelay.
    SimpleDelay();

    // EN: Destructor for the SimpleDelay class.
    // ES: Destructor de la clase SimpleDelay.
    ~SimpleDelay();

private:
    // EN: The delay time in samples.
    // ES: El tiempo de delay en muestras.
    int delay = 48000;

    // EN: The sample rate of the audio (default: 48kHz).
    // ES: La frecuencia de muestreo del audio (por defecto: 48kHz).
    float sampleRate = 48000;

    // EN: The size of the circular buffer used to store delayed audio.
    // ES: El tamaño del búfer circular utilizado para almacenar el audio con delay.
    static const int circularBufferSize = 96000;

    // EN: A circular buffer to hold audio samples for two channels (stereo).
    // ES: Un búfer circular para almacenar muestras de audio para dos canales (estéreo).
    float circularBuffer[circularBufferSize][2] = { 0.0f };

    // EN: Pointer to read delayed audio from the circular buffer.
    // ES: Puntero para leer el audio con delay desde el búfer circular.
    int readerPointer = 0;

    // EN: Pointer to write incoming audio into the circular buffer for each channel.
    // ES: Puntero para escribir el audio entrante en el búfer circular para cada canal.
    int writterPointer[2]{};
};
