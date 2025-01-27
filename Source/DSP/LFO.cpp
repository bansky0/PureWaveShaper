/*
  ==============================================================================

    LFO.cpp
    Created: 27 Aug 2024 10:39:40am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "LFO.h"

// ES: Método para establecer la frecuencia del LFO.
// EN: Method to set the frequency of the LFO.
void LFO::setLFOValue(float inRateValue)
{
    frecuency = inRateValue; // ES: Asigna la frecuencia proporcionada por el usuario.
                             // EN: Assigns the frequency provided by the user.
}

// ES: Método para preparar el LFO, inicializando la frecuencia de muestreo y otros valores.
// EN: Method to prepare the LFO, initializing the sample rate and other values.
void LFO::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate); // ES: Configura la frecuencia de muestreo.
                                                    // EN: Sets the sample rate.

    for (int i = 0; i < 2; i++) // ES: Inicializa los valores para ambos canales.
    {
        time[i] = 0.0f; // ES: Inicializa el tiempo actual del LFO.
                        // EN: Initializes the current time of the LFO.

        deltaTime[i] = 1.0f / sampleRate;   // ES: Calcula el incremento de tiempo por muestra.
                                            // EN: Calculates the time increment per sample.
    }
}

// ES: Método para procesar un buffer de audio, aplicando la modulación del LFO.
// EN: Method to process an audio buffer, applying LFO modulation.
void LFO::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++) // ES: Itera por los canales.
    {
        for (int i = 0; i < buffer.getNumSamples(); i++) // ES: Itera por las muestras.
        {
            float inSample = buffer.getSample(channel, i); // ES: Obtiene la muestra actual.
                                                           // EN: Retrieves the current sample.

            // ES: Calcula el valor del LFO usando la fórmula y = 0.5 * sin(2PIft) + 0.5.
            // EN: Calculates the LFO value using the formula y = 0.5 * sin(2PIft) + 0.5.
            float sinValue = (0.5f * sinf(twoPi * frecuency * time[channel])) + 0.5f;

            float outSample = inSample * sinValue; // ES: Aplica la modulación multiplicativa del LFO.
                                                   // EN: Applies multiplicative modulation using the LFO.

            buffer.setSample(channel, i, outSample); // ES: Guarda la muestra procesada en el buffer.
                                                     // EN: Stores the processed sample in the buffer.

            time[channel] += deltaTime[channel]; // ES: Incrementa el tiempo del LFO.
                                                 // EN: Increments the LFO time.

            if (time[channel] >= 1.0f) // ES: Resetea el tiempo si excede un ciclo completo.
            {
                time[channel] = 0.0f;
                                       // EN: Resets the time if it exceeds a full cycle.
            }
        }
    }
}

// Constructor de la clase LFO, no realiza ninguna acción específica.
// EN: Constructor of the LFO class, does not perform any specific action.
LFO::LFO()
{
}

// Destructor de la clase LFO, no realiza ninguna acción específica.
// EN: Destructor of the LFO class, does not perform any specific action.
LFO::~LFO()
{
}
