/*
  ==============================================================================

    Pan_linear.h
    Created: 22 Aug 2024 6:20:09pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// Definición de la clase PanLinear
// ES: Esta clase implementa un control de panoramización lineal para señales de audio estéreo.
// EN: This class implements a linear panning control for stereo audio signals.

class PanLinear
{
public:
    // Constructor
    // ES: Constructor por defecto de la clase PanLinear.
    // EN: Default constructor for the PanLinear class.
    PanLinear();

    // Destructor
    // ES: Destructor por defecto de la clase PanLinear.
    // EN: Default destructor for the PanLinear class.
    ~PanLinear();

    // Establece el valor de panoramización lineal
    // ES: Este método recibe un valor de panoramización que controla la distribución del audio entre los canales izquierdo y derecho.
    // EN: This method takes a pan value that controls the audio distribution between the left and right channels.
    void setPanLinearValue(float inPanLinearValue);

    // Procesa el buffer de audio
    // ES: Aplica el valor de panoramización lineal al buffer de audio proporcionado.
    // EN: Applies the linear pan value to the provided audio buffer.
    void process(juce::AudioBuffer<float>& buffer);

private:
    // Valor de panoramización lineal
    // ES: Almacena el valor de panoramización lineal que se usará durante el procesamiento.
    // EN: Stores the linear pan value to be used during processing.
    float panLinearValue{};
};

