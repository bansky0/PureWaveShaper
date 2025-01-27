/*
  ==============================================================================

    Pan.h
    Created: 22 Aug 2024 2:07:46pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Pan
{
public:
    // ES: Constructor por defecto de la clase Pan.
    // EN: Default constructor for the Pan class.
    Pan();

    // ES: Destructor de la clase Pan.
    // EN: Destructor for the Pan class.
    ~Pan();

    // Establece el valor de panoramización (pan) en la señal.
    // ES: El valor de pan puede ser un valor entre -1 (izquierda) y +1 (derecha).
    // EN: Sets the pan value for the audio signal. The pan value ranges from -1 (left) to +1 (right).
    void setPanValue(float inPanValue);

    // ES: Procesa la señal de audio según el valor de pan, ajustando los niveles de los canales izquierdo y derecho.
    // EN: Processes the audio signal according to the pan value, adjusting the levels of the left and right channels.
    void process(juce::AudioBuffer<float>& buffer);

private:
    // ES: Constante pi para el cálculo de la panoramización.
    // EN: Pi constant for pan calculation.
    float pi{ juce::MathConstants<float>::pi };

    // ES: Valor de panoramización en radianes, por defecto es pi/4 (aproximadamente 45 grados).
    // EN: Pan value in radians, default is pi/4 (approximately 45 degrees).
    float panValue{ juce::MathConstants<float>::pi / 4.0f };
};