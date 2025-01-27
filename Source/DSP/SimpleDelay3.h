/*
  ==============================================================================

    SimpleDelay3.h
    Created: 19 Sep 2024 1:00:10pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Declaration of the SimpleDelay3 class, which provides a simple delay effect.
// ES: Declaración de la clase SimpleDelay3, que proporciona un efecto de delay simple.

class SimpleDelay3
{
public:
    // EN: Constructor for the SimpleDelay3 class.
    // ES: Constructor de la clase SimpleDelay3.
    SimpleDelay3();

    // EN: Destructor for the SimpleDelay3 class.
    // ES: Destructor de la clase SimpleDelay3.
    ~SimpleDelay3();

    // EN: Sets the delay time in seconds.
    // ES: Configura el tiempo de delay en segundos.
    void setTimeDelay(float delayTime);

    // EN: Prepares the delay effect with the specified sample rate, block size, DSP specifications, and number of channels.
    // ES: Prepara el efecto de delay con la frecuencia de muestreo, tamaño del bloque, especificaciones de DSP y número de canales especificados.
    void prepare(double theSampleRate, int samplesPerBlock, juce::dsp::ProcessSpec& spec, int numbChannels);

    // EN: Processes the audio buffer, applying the delay effect to the signal.
    // ES: Procesa el búfer de audio, aplicando el efecto de delay a la señal.
    void process(juce::AudioBuffer<float>& buffer);

private:
    // EN: JUCE's DelayLine object to handle the delay processing with linear interpolation.
    // ES: Objeto DelayLine de JUCE para manejar el procesamiento de delay con interpolación lineal.
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> myDelay{ 98000 };

    // EN: Stores the sample rate for delay calculations.
    // ES: Almacena la frecuencia de muestreo para los cálculos de delay.
    double sampleRate{ 0.0 };

    // EN: Stores the delay time in samples.
    // ES: Almacena el tiempo de delay en muestras.
    float delay{};
};