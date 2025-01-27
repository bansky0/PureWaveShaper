/*
  ==============================================================================

    PitchUp.h
    Created: 5 Nov 2024 4:21:53pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Defines a class for implementing a pitch-up effect using a circular delay buffer.
// ES: Define una clase para implementar un efecto de pitch-up usando un búfer circular de retardo.
class PitchUp
{
public:
    // EN: Default constructor and destructor.
    // ES: Constructor y destructor por defecto.
    PitchUp() {}
    ~PitchUp() {}

    // EN: Prepares the effect by initializing parameters and the delay buffer.
    // ES: Prepara el efecto inicializando parámetros y el búfer de retardo.
    void prepare(double theSampleRate);

    // EN: Processes the audio buffer to apply the pitch-up effect.
    // ES: Procesa el búfer de audio para aplicar el efecto pitch-up.
    void process(juce::AudioBuffer<float>& buffer);

private:
    float sampleRate{ 48000 }; // EN: The sampling rate of the audio. Default is 48 kHz.
    // ES: Frecuencia de muestreo del audio. Por defecto, 48 kHz.

    float delay{ 0 };          // EN: Fractional delay in samples for pitch manipulation.
    // ES: Retardo fraccionario en muestras para la manipulación del tono.

    static const int bufferSize = 48000; // EN: Circular buffer size (1 second at 48 kHz).
    // ES: Tamaño del búfer circular (1 segundo a 48 kHz).

    float delayBuffer[bufferSize]; // EN: Circular delay buffer to store past audio samples.
    // ES: Búfer circular de retardo para almacenar muestras de audio pasadas.

    int writePosition{ 0 };         // EN: Write pointer position in the circular buffer.
    // ES: Posición del puntero de escritura en el búfer circular.
};
