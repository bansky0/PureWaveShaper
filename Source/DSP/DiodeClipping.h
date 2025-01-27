/*
  ==============================================================================

    DiodeClipping.h
    Created: 3 Sep 2024 4:46:15pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: This class implements a diode clipping effect.
// ES: Esta clase implementa un efecto de recorte de diodo.
class DiodeClipping
{
public:
    // EN: Processes an audio buffer and applies the diode clipping effect.
    // ES: Procesa un buffer de audio y aplica el efecto de recorte de diodo.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the DiodeClipping class.
    // ES: Constructor de la clase DiodeClipping.
    DiodeClipping();

    // EN: Destructor for the DiodeClipping class.
    // ES: Destructor de la clase DiodeClipping.
    ~DiodeClipping();

private:
    // EN: Thermal voltage (Vt), used in the diode clipping calculation.
    // ES: Voltaje térmico (Vt), utilizado en el cálculo del recorte de diodo.
    float Vt = 0.0253f;

    // EN: Emission coefficient (eta), a parameter of the diode's behavior.
    // ES: Coeficiente de emisión (eta), un parámetro del comportamiento del diodo.
    float eta = 1.68f;

    // EN: Saturation current (Is), another diode parameter.
    // ES: Corriente de saturación (Is), otro parámetro del diodo.
    float Is = 0.105f;
};