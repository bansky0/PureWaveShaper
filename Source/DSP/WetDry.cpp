/*
  ==============================================================================

    WetDry.cpp
    Created: 5 Sep 2024 10:20:06am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "WetDry.h"

// EN: Sets the wet/dry mix value, normalizing it to a range of 0.0 to 1.0 (assuming input is 0 to 100).
// ES: Configura el valor de mezcla "wet/dry", normalizándolo a un rango de 0.0 a 1.0 (suponiendo que la entrada está entre 0 y 100).
void WetDry::setDryWet(float inDryWetValue)
{
    dryWet = inDryWetValue / 100.0f;
}

// EN: Processes the audio by mixing the wet and dry buffers based on the wet/dry value.
// ES: Procesa el audio mezclando los buffers "wet" (procesado) y "dry" (original) según el valor de mezcla "wet/dry".
void WetDry::process(juce::AudioBuffer<float>& dryBuffer,
    juce::AudioBuffer<float>& wetBuffer)
{
    // EN: Iterate through each channel in the buffers.
    // ES: Itera a través de cada canal en los buffers.
    for (int channel = 0; channel < dryBuffer.getNumChannels(); channel++)
    {
        // EN: Process each sample in the current channel.
        // ES: Procesa cada muestra en el canal actual.
        for (int i = 0; i < dryBuffer.getNumSamples(); i++)
        {
            // EN: Get the current sample from the wet and dry buffers.
            // ES: Obtiene la muestra actual de los buffers "wet" y "dry".
            float wetSample = wetBuffer.getSample(channel, i);
            float drySample = dryBuffer.getSample(channel, i);

            // EN: Compute the mixed output sample based on the wet/dry value.
            // ES: Calcula la muestra de salida mezclada según el valor de "wet/dry".
            float outSample = drySample * (1.0f - dryWet) + (wetSample * dryWet);

            // EN: Write the mixed sample to the wet buffer (used as the output buffer).
            // ES: Escribe la muestra mezclada en el buffer "wet" (que se usa como buffer de salida).
            wetBuffer.setSample(channel, i, outSample);
        }
    }
}

// EN: Constructor. Initializes the WetDry object.
// ES: Constructor. Inicializa el objeto WetDry.
WetDry::WetDry()
{
}

// EN: Destructor. Cleans up the WetDry object.
// ES: Destructor. Libera el objeto WetDry.
WetDry::~WetDry()
{
}