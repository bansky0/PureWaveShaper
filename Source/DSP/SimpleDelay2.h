/*
  ==============================================================================

    SimpleDelay2.h
    Created: 17 Sep 2024 3:41:36pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: A class implementing a simple delay effect with adjustable BPM, delay amplitude, and feedback.
// ES: Una clase que implementa un efecto de delay simple con BPM, amplitud del delay y realimentación ajustables.
class SimpleDelay2
{
public:

    // EN: Sets the tempo in beats per minute (BPM), which can affect delay calculations.
    // ES: Configura el tempo en pulsaciones por minuto (BPM), lo que puede afectar los cálculos del delay.
    void setBPM(float BPM);

    // EN: Sets the amplitude of the delayed signal.
    // ES: Configura la amplitud de la señal con delay.
    void setAmpDelay(float inAmpDelay);

    // EN: Sets the feedback level for the delay effect.
    // ES: Configura el nivel de realimentación (feedback) para el efecto de delay.
    void setFeedback(float inFeedback);

    // EN: Prepares the delay for processing by setting the sample rate.
    // ES: Prepara el delay para el procesamiento configurando la frecuencia de muestreo.
    void prepare(double theSampleRate);

    // EN: Processes the input audio buffer and applies the delay effect.
    // ES: Procesa el búfer de audio de entrada y aplica el efecto de delay.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the SimpleDelay2 class, initializes default values.
    // ES: Constructor de la clase SimpleDelay2, inicializa valores predeterminados.
    SimpleDelay2();

    // EN: Destructor for the SimpleDelay2 class, cleans up resources if needed.
    // ES: Destructor de la clase SimpleDelay2, libera recursos si es necesario.
    ~SimpleDelay2();

private:

    // EN: The sample rate used for processing audio (e.g., 48000 Hz).
    // ES: La frecuencia de muestreo utilizada para procesar el audio (por ejemplo, 48000 Hz).
    float sampleRate = 48000;

    // EN: The delay time in samples.
    // ES: El tiempo de delay en muestras.
    int delay = 48000;

    // EN: The amplitude of the delayed signal (controls the mix of dry and wet signals).
    // ES: La amplitud de la señal con delay (controla la mezcla de señal directa y con efecto).
    float ampDelay = 0.75f;

    // EN: The feedback amount for the delay (controls how much of the output is fed back into the input).
    // ES: La cantidad de realimentación para el delay (controla cuánto de la salida se realimenta a la entrada).
    float feedback = 0.5f;

    // EN: The size of the circular buffer for storing delayed audio samples.
    // ES: El tamaño del búfer circular para almacenar muestras de audio con delay.
    static const int circularBufferSize = 96000;

    // EN: A 2D array serving as the circular buffer for the delay, one buffer per channel.
    // ES: Un arreglo 2D que actúa como el búfer circular para el delay, uno por canal.
    float circularBuffer[circularBufferSize][2] = { 0.0f };

    // EN: The pointer for reading delayed samples from the circular buffer.
    // ES: El puntero para leer muestras con delay del búfer circular.
    int readerPointer = 0;

    // EN: The pointer for writing new samples into the circular buffer, one for each channel.
    // ES: El puntero para escribir nuevas muestras en el búfer circular, uno por cada canal.
    int writterPointer[2]{};
};
