/*
  ==============================================================================

    WetDry.h
    Created: 5 Sep 2024 10:20:06am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class to handle wet/dry mixing for audio effects.
// ES: Clase para manejar la mezcla entre señales "wet" (procesada) y "dry" (original).

class WetDry
{
public:
    // EN: Sets the wet/dry mix value.
    // ES: Configura el valor de mezcla entre señales "wet" y "dry".
    void setDryWet(float inDryWetValue);

    // EN: Processes the wet and dry audio buffers to mix them based on the dry/wet value.
    // ES: Procesa los buffers de audio "wet" y "dry" para mezclarlos según el valor de mezcla.
    void process(juce::AudioBuffer<float>& dryBuffer,
        juce::AudioBuffer<float>& wetBuffer);

    // EN: Constructor. Initializes the wet/dry mixer.
    // ES: Constructor. Inicializa el mezclador "wet/dry".
    WetDry();

    // EN: Destructor. Cleans up resources if necessary.
    // ES: Destructor. Libera recursos si es necesario.
    ~WetDry();

private:
    // EN: The wet/dry mix value (0.0 = 100% dry, 1.0 = 100% wet).
    // ES: El valor de mezcla "wet/dry" (0.0 = 100% dry, 1.0 = 100% wet).
    float dryWet{ 0.0f };
};