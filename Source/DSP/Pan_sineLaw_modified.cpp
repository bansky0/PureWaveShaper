/*
  ==============================================================================

    Pan_sineLaw_modified.cpp
    Created: 26 Aug 2024 1:26:44pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Pan_sineLaw_modified.h"

// Configura el valor modificado de panoramización basado en la ley del seno
// ES: Calcula y ajusta el valor de panoramización en el rango [0.5, 1.5] en base a la entrada.
// EN: Computes and adjusts the panning value in the range [0.5, 1.5] based on the input.
void PanSineLawModified::setPanSineLawModifiedValue(float inPanSineLawModifiedValue)
{
    panSineLawModifiedValue = (inPanSineLawModifiedValue / 200.0f) + 0.5f;
}

// Procesa el buffer de audio aplicando la panoramización modificada
// ES: Aplica un efecto de panoramización basado en una versión modificada de la ley del seno.
// EN: Applies a panning effect based on a modified version of the sine law.
void PanSineLawModified::process(juce::AudioBuffer<float>& buffer)
{
    // Itera sobre los canales de audio
    // ES: Recorre cada canal del buffer.
    // EN: Loops through each channel in the buffer.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // Itera sobre las muestras del canal actual
        // ES: Procesa cada muestra del canal.
        // EN: Processes each sample in the current channel.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);

            // Procesa el canal izquierdo
            // ES: Reduce el nivel del canal izquierdo usando la raíz cuadrada de la panoramización modificada.
            // EN: Reduces the left channel's level using the square root of the modified panning.
            if (channel == 0)
            {
                sample *= sqrtf((1 - panSineLawModifiedValue) * sinf((1.0f - panSineLawModifiedValue) * (pi / 2.0f)));
            }
            // Procesa el canal derecho
            // ES: Reduce el nivel del canal derecho usando la raíz cuadrada de la panoramización modificada.
            // EN: Reduces the right channel's level using the square root of the modified panning.
            else
            {
                sample *= sqrtf(panSineLawModifiedValue * sinf(panSineLawModifiedValue * (pi / 2.0f)));
            }

            // Actualiza la muestra procesada en el buffer
            // ES: Escribe la muestra procesada en el buffer.
            // EN: Writes the processed sample back to the buffer.
            buffer.setSample(channel, i, sample);
        }
    }
}

// Constructor
// ES: Inicializa la clase PanSineLawModified.
// EN: Initializes the PanSineLawModified class.
PanSineLawModified::PanSineLawModified()
{
}

// Destructor
// ES: Libera recursos utilizados por la clase (si aplica).
// EN: Releases resources used by the class (if applicable).
PanSineLawModified::~PanSineLawModified()
{
}