/*
  ==============================================================================

    DirectFormII_NestedAPF.cpp
    Created: 2 Oct 2024 4:44:56pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "DirectFormII_NestedAPF.h"

// EN: Constructor - Initializes the nested Direct Form II All-Pass Filter (APF).
// ES: Constructor - Inicializa el filtro pasa todo en forma directa II anidado.
DirectFormII_NestedAPF::DirectFormII_NestedAPF()
{
}

// EN: Destructor - Cleans up any resources used by the nested APF.
// ES: Destructor - Libera cualquier recurso utilizado por el APF anidado.
DirectFormII_NestedAPF::~DirectFormII_NestedAPF()
{
}

// EN: Processes an audio buffer through the nested APF.
// ES: Procesa un buffer de audio a través del APF anidado.
void DirectFormII_NestedAPF::process(juce::AudioBuffer<float>& inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            // EN: Get the input sample from the current channel and index.
            // ES: Obtiene la muestra de entrada del canal y el índice actual.
            float inSample = inBuffer.getSample(channel, i);

            // EN: Process the input sample through the nested APF and get the output sample.
            // ES: Procesa la muestra de entrada a través del APF anidado y obtiene la muestra de salida.
            float outSample = processSample(inSample, channel);

            // EN: Set the processed sample back into the audio buffer.
            // ES: Asigna la muestra procesada de nuevo en el buffer de audio.
            inBuffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Processes a single sample through the nested APF for a specific channel.
// ES: Procesa una muestra individual a través del APF anidado para un canal específico.
float DirectFormII_NestedAPF::processSample(float inSample, int channel)
{
    // EN: First stage of the nested APF (w1 and w2 calculations).
    // ES: Primera etapa del APF anidado (cálculos de w1 y w2).
    auto w1 = inSample + (-g1 * prevW2[channel]); // EN: First feedback path. | ES: Primer camino de realimentación.
    auto w2 = prevW1[channel];                   // EN: Second feedback path. | ES: Segundo camino de realimentación.

    // EN: Second stage of the nested APF (v and y calculations).
    // ES: Segunda etapa del APF anidado (cálculos de v y y).
    auto v = w2 + (-g2 * prevV[channel]);        // EN: Feedback path for second APF. | ES: Camino de realimentación para el segundo APF.
    auto y = g2 * prevV[channel] + inSample;    // EN: Output calculation. | ES: Cálculo de la salida.

    // EN: Update delay buffers for the current channel.
    // ES: Actualiza los buffers de retardo para el canal actual.
    prevW1[channel] = w1;
    prevW2[channel] = w2;
    prevV[channel] = v;

    // EN: Return the output sample from the nested APF.
    // ES: Devuelve la muestra de salida del APF anidado.
    return y;
}

// EN: Sets the gain coefficients for both stages of the nested APF.
// ES: Establece los coeficientes de ganancia para ambas etapas del APF anidado.
void DirectFormII_NestedAPF::setG(float inG1, float inG2)
{
    g1 = inG1; // EN: Gain for the first APF stage. | ES: Ganancia para la primera etapa del APF.
    g2 = inG2; // EN: Gain for the second APF stage. | ES: Ganancia para la segunda etapa del APF.
}
