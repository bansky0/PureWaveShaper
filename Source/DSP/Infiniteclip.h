/*
  ==============================================================================

    Infiniteclip.h
    Created: 2 Sep 2024 6:29:56pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once 
#include <JuceHeader.h>

// ES: Clase InfiniteClip que implementa un procesador de audio para realizar un "clipping infinito".
// EN: InfiniteClip class that implements an audio processor for "infinite clipping."
class InfiniteClip
{
public:

    // ES: Procesa un buffer de audio para aplicar el clipping infinito.
    // EN: Processes an audio buffer to apply infinite clipping.
    void process(juce::AudioBuffer<float>& buffer);

    // ES: Constructor de la clase InfiniteClip.
    // EN: Constructor for the InfiniteClip class.
    InfiniteClip();

    // ES: Destructor de la clase InfiniteClip.
    // EN: Destructor for the InfiniteClip class.
    ~InfiniteClip();

private:

    // ES: No se especifican variables miembro en esta versión.
    // EN: No member variables are specified in this version.
};
