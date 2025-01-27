/*
  ==============================================================================

    DirectFormII_APF.cpp
    Created: 2 Oct 2024 11:20:47am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "DirectFormII_APF.h"

// EN: Constructor - Initializes the Direct Form II All-Pass Filter (APF).
// ES: Constructor - Inicializa el filtro pasa todo en forma directa II (APF).
DirectFormII_APF::DirectFormII_APF()
{
}

// EN: Destructor - Cleans up any resources used by the APF.
// ES: Destructor - Libera cualquier recurso utilizado por el APF.
DirectFormII_APF::~DirectFormII_APF()
{
}

// EN: Processes an audio buffer through the APF.
// ES: Procesa un buffer de audio a través del APF.
void DirectFormII_APF::process(juce::AudioBuffer<float>& inBuffer)
{
    for (int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            // EN: Get the input sample from the current channel and index.
            // ES: Obtiene la muestra de entrada del canal y el índice actual.
            float inSample = inBuffer.getSample(channel, i);

            // EN: Process the input sample through the APF and get the output sample.
            // ES: Procesa la muestra de entrada a través del APF y obtiene la muestra de salida.
            float outSample = processSample(inSample, channel);

            // EN: Set the processed sample back into the audio buffer.
            // ES: Asigna la muestra procesada de nuevo en el buffer de audio.
            inBuffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Processes a single sample through the APF for a specific channel.
// ES: Procesa una muestra individual a través del APF para un canal específico.
float DirectFormII_APF::processSample(float inSample, int channel)
{
    // EN: Calculate the output sample using the Direct Form II APF equation.
    // ES: Calcula la muestra de salida usando la ecuación del APF en forma directa II.
    auto y = g * inSample + (-g) * y1[channel] + x1[channel];

    // EN: Update the delay buffers for the current channel.
    // ES: Actualiza los buffers de retardo para el canal actual.
    x1[channel] = inSample;
    y1[channel] = y;

    // EN: Return the filtered output sample.
    // ES: Devuelve la muestra de salida filtrada.
    return y;
}

// EN: Sets the gain coefficient (g) for the APF.
// ES: Establece el coeficiente de ganancia (g) para el APF.
void DirectFormII_APF::setG(float inG)
{
    g = inG;
}
