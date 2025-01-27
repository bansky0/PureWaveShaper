/*
  ==============================================================================

    AsymetricalDistortion.h
    Created: 4 Sep 2024 1:26:39pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class AsymetricalDistortion: Implements an asymmetrical distortion effect with a custom non-linear function.
//     The effect is based on a DC shift and a power-based distortion curve, which introduces harmonic distortion.
// ES: Clase AsymetricalDistortion: Implementa un efecto de distorsión asimétrica con una función no lineal personalizada.
//     El efecto se basa en un desplazamiento de DC y una curva de distorsión basada en potencias, lo que introduce distorsión armónica.

class AsymetricalDistortion
{
public:
    // EN: Sets the DC value for the distortion. A value of 0 means no distortion, 
    //     negative values reduce the wave, and positive values push it higher.
    // ES: Configura el valor de DC para la distorsión. Un valor de 0 significa sin distorsión, 
    //     valores negativos reducen la onda, y valores positivos la empujan más alto.
    void setDCValue(float inDCValue);

    // EN: Processes the audio buffer and applies the asymmetrical distortion effect.
    //     The effect is based on shifting the signal with DC and applying a custom non-linearity.
    // ES: Procesa el buffer de audio y aplica el efecto de distorsión asimétrica.
    //     El efecto se basa en desplazar la señal con DC y aplicar una no linealidad personalizada.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Default constructor for the AsymetricalDistortion class. | ES: Constructor por defecto de la clase AsymetricalDistortion.
    AsymetricalDistortion();

    // EN: Destructor for the AsymetricalDistortion class. | ES: Destructor de la clase AsymetricalDistortion.
    ~AsymetricalDistortion();

private:
    // EN: Constant Pi used for various calculations. | ES: Constante Pi utilizada para varios cálculos.
    float pi{ juce::MathConstants<float>::pi };

    // EN: DC value for the distortion effect. | ES: Valor de DC para el efecto de distorsión.
    //     Range: -0.7 to 0.7, with 0 meaning no distortion.
    //     Negative values reduce the wave, while positive values push it higher.
    // ES: Rango: -0.7 a 0.7, con 0 significando sin distorsión.
    //     Los valores negativos reducen la onda, mientras que los valores positivos la empujan más alto.
    float dc = {};
};