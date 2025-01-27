/*
  ==============================================================================

    DirectFormII_NestedAPF.h
    Created: 2 Oct 2024 4:44:56pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Defines a class for a Nested All-Pass Filter (APF) in Direct Form II.
// ES: Define una clase para un filtro pasa todo anidado (APF) en forma directa II.
class DirectFormII_NestedAPF
{
public:
    // EN: Constructor - Initializes the nested APF.
    // ES: Constructor - Inicializa el APF anidado.
    DirectFormII_NestedAPF();

    // EN: Destructor - Releases resources used by the nested APF.
    // ES: Destructor - Libera los recursos utilizados por el APF anidado.
    ~DirectFormII_NestedAPF();

    // EN: Processes an entire audio buffer through the nested APF.
    // ES: Procesa un buffer de audio completo a través del APF anidado.
    void process(juce::AudioBuffer<float>& inBuffer);

    // EN: Processes a single audio sample through the nested APF for a specific channel.
    // ES: Procesa una sola muestra de audio a través del APF anidado para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the gain coefficients for both stages of the nested APF.
    // ES: Establece los coeficientes de ganancia para ambas etapas del APF anidado.
    void setG(float inG1, float inG2);

private:
    // EN: Delay buffers for intermediate calculations in the APF.
    // ES: Buffers de retardo para los cálculos intermedios en el APF.
    float prevV[2] = { 0.0f };  // EN: Stores the delayed output of the second stage. | ES: Almacena la salida retardada de la segunda etapa.
    float prevW1[2] = { 0.0f }; // EN: Stores the delayed output of the first stage. | ES: Almacena la salida retardada de la primera etapa.
    float prevW2[2] = { 0.0f }; // EN: Stores the second delayed value of the first stage. | ES: Almacena el segundo valor retardado de la primera etapa.

    // EN: Gain coefficients for the two stages of the nested APF.
    // ES: Coeficientes de ganancia para las dos etapas del APF anidado.
    float g1{ 0.5f }; // EN: Gain for the first stage. | ES: Ganancia para la primera etapa.
    float g2{ 0.5f }; // EN: Gain for the second stage. | ES: Ganancia para la segunda etapa.
};
