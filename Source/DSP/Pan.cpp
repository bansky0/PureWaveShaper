/*
  ==============================================================================

    Pan.cpp
    Created: 22 Aug 2024 2:07:46pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Pan.h"

// Constructor de la clase Pan
// ES: El constructor por defecto no realiza ninguna operación especial.
// EN: The default constructor doesn't perform any special operations.
Pan::Pan()
{
}

// Destructor de la clase Pan
// ES: El destructor por defecto no realiza ninguna operación especial.
// EN: The default destructor doesn't perform any special operations.
Pan::~Pan()
{
}

// Establece el valor de panoramización (pan)
// ES: Este método toma un valor de pan en el rango de -100 a 100 y lo normaliza para mapearlo al rango adecuado para la operación de panoramización.
// EN: This method takes a pan value in the range of -100 to 100, normalizes it, and maps it to the appropriate range for pan operation.
void Pan::setPanValue(float inPanValue)
{
    // ES: Normaliza el valor en el rango de 0 a 1
    // EN: Normalizes the value in the range from 0 to 1.
    float normalizedValue = (inPanValue + 100.0f) / 200.0f;

    // ES: Mapea el valor normalizado al rango de 0 a pi/2
    // EN: Maps the normalized value to the range from 0 to pi/2.
    float outputValue = normalizedValue * (pi / 2.0f);

    // ES: Asigna el valor de pan calculado
    // EN: Assigns the calculated pan value.
    panValue = outputValue;
}

// Procesa la señal de audio y aplica la panoramización a cada canal
// ES: Este método ajusta los valores de los canales izquierdo y derecho según el valor de pan.
// EN: This method adjusts the values of the left and right channels based on the pan value.
void Pan::process(juce::AudioBuffer<float>& buffer)
{
    // ES: Recorre cada canal del buffer de audio
    // EN: Loops through each channel of the audio buffer.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // ES: Recorre cada muestra del canal actual
        // EN: Loops through each sample of the current channel.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // ES: Obtiene el valor de la muestra del canal actual
            // EN: Gets the sample value of the current channel.
            float sample = buffer.getSample(channel, i);

            // Procesa el canal izquierdo
            // ES: Aplica el ajuste de panoramización para el canal izquierdo (canal 0).
            // EN: Applies the pan adjustment for the left channel (channel 0).
            if (channel == 0)
            {
                // ES: Calcula el ajuste para el canal izquierdo usando la fórmula matemática
                // EN: Calculates the adjustment for the left channel using the mathematical formula.
                sample *= sqrtf(((pi / 2.0f) - panValue) * (2.0f / pi) * (cosf(panValue)));
            }
            // Procesa el canal derecho
            // ES: Aplica el ajuste de panoramización para el canal derecho (canal 1).
            // EN: Applies the pan adjustment for the right channel (channel 1).
            else
            {
                // ES: Calcula el ajuste para el canal derecho usando la fórmula matemática
                // EN: Calculates the adjustment for the right channel using the mathematical formula.
                sample *= sqrtf(panValue * (2.0f / pi) * sinf(panValue));
            }

            // ES: Establece la muestra procesada en el buffer
            // EN: Sets the processed sample in the buffer.
            buffer.setSample(channel, i, sample);
        }
    }
}