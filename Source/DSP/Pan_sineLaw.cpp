/*
  ==============================================================================

    Pan_sineLaw.cpp
    Created: 26 Aug 2024 12:08:48pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Pan_sineLaw.h"

// Configura el valor de panoramización basado en la ley del seno
// ES: Normaliza el valor de entrada a un rango entre 0 y 1 y lo ajusta para su uso en la ley del seno.
// EN: Normalizes the input value to a range between 0 and 1 and adjusts it for use in the sine law.
void PanSineLaw::setPanSineLawValue(float inPanSineLawValue)
{
    panSineLawValue = (inPanSineLawValue / 200.0f) + 0.5f;
}

// Procesa el buffer de audio con la ley del seno
// ES: Aplica un procesamiento de panoramización basado en la ley del seno al buffer de audio.
// EN: Applies sine-law-based panning processing to the audio buffer.
void PanSineLaw::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++) // ES: Itera sobre los canales de audio. EN: Iterates over audio channels.
    {
        for (int i = 0; i < buffer.getNumSamples(); i++) // ES: Itera sobre las muestras de cada canal. EN: Iterates over samples in each channel.
        {
            float sample = buffer.getSample(channel, i); // ES: Obtiene la muestra actual. EN: Retrieves the current sample.

            // Procesa el canal izquierdo
            // ES: Reduce la amplitud de la muestra basándose en el valor inverso de la panoramización (1.0 - panSineLawValue).
            // EN: Attenuates the sample amplitude based on the inverse of the panning value (1.0 - panSineLawValue).
            if (channel == 0)
            {
                sample *= sinf((1.0f - panSineLawValue) * (pi / 2.0f));
            }
            // Procesa el canal derecho
            // ES: Reduce la amplitud de la muestra basándose en el valor directo de la panoramización (panSineLawValue).
            // EN: Attenuates the sample amplitude based on the direct panning value (panSineLawValue).
            else
            {
                sample *= sinf(panSineLawValue * (pi / 2.0f));
            }

            buffer.setSample(channel, i, sample); // ES: Almacena la muestra procesada de nuevo en el buffer. EN: Stores the processed sample back in the buffer.
        }
    }
}

// Constructor de PanSineLaw
// ES: Inicializa la clase sin configuraciones adicionales.
// EN: Initializes the class without additional setups.
PanSineLaw::PanSineLaw()
{
}

// Destructor de PanSineLaw
// ES: Limpia cualquier recurso utilizado por la clase (si aplica).
// EN: Cleans up any resources used by the class (if applicable).
PanSineLaw::~PanSineLaw()
{
}