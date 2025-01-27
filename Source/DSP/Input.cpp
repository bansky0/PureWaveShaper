/*
  ==============================================================================

    Input.cpp
    Created: 19 Aug 2024 3:53:03pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Input.h"

// ES: Constructor de la clase Input.
// EN: Constructor for the Input class.
Input::Input()
{
}

// ES: Destructor de la clase Input.
// EN: Destructor for the Input class.
Input::~Input()
{
}

// ES: Establece el valor de entrada, convirtiendo el valor en decibelios a una ganancia lineal.
// EN: Sets the input value, converting the value from decibels to linear gain.
void Input::setInputValue(float inInputValue)
{
    // ES: Convierte el valor de decibelios (inInputValue) a ganancia lineal y lo almacena.
    // EN: Converts the decibel value (inInputValue) to linear gain and stores it.
    inputValue = juce::Decibels::decibelsToGain(inInputValue);
}

// ES: Procesa un buffer de audio, aplicando la ganancia configurada a cada muestra.
// EN: Processes an audio buffer, applying the configured gain to each sample.
void Input::process(juce::AudioBuffer<float>& buffer)
{
    // ES: Itera por cada canal en el buffer.
    // EN: Iterates through each channel in the buffer.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // ES: Itera por cada muestra dentro del canal.
        // EN: Iterates through each sample within the channel.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // ES: Obtiene la muestra actual del buffer.
            // EN: Retrieves the current sample from the buffer.
            float inSample = buffer.getSample(channel, i);

            // ES: Calcula la muestra procesada aplicando la ganancia.
            // EN: Calculates the processed sample by applying the gain.
            float processedSample = inSample * inputValue;

            // ES: Establece la muestra procesada de vuelta en el buffer.
            // EN: Sets the processed sample back into the buffer.
            buffer.setSample(channel, i, processedSample);
        }
    }
}