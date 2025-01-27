/*
  ==============================================================================

    Convolution.h
    Created: 26 Sep 2024 10:28:16am
    Author:  Jhonatan L�pez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Convolution
{
public:
    // EN: Prepares the convolution processor with the given sample rate, block size, and number of channels.
    // ES: Prepara el procesador de convoluci�n con la frecuencia de muestreo, tama�o de bloque y n�mero de canales especificados.
    void prepare(double inSampleRate, int inSamplesPerblock, int inNumChannels);

    // EN: Processes the input audio buffer using the convolution effect.
    // ES: Procesa el buffer de audio de entrada utilizando el efecto de convoluci�n.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Constructor for the Convolution class.
    // ES: Constructor de la clase Convolution.
    Convolution();

    // EN: Destructor for the Convolution class.
    // ES: Destructor de la clase Convolution.
    ~Convolution();

private:
    // EN: JUCE's convolution object used to apply the convolution effect.
    // ES: Objeto de convoluci�n de JUCE utilizado para aplicar el efecto de convoluci�n.
    juce::dsp::Convolution convolution;
};

