/*
  ==============================================================================

    Pan_linear.cpp
    Created: 22 Aug 2024 6:20:09pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Pan_linear.h"

// Establece el valor de panoramización lineal
// ES: Normaliza el valor de panoramización recibido en un rango de 0.0 a 1.0. 
//    - Divide el valor de entrada entre 200 para ajustarlo a un rango de -0.5 a 0.5.
//    - Luego, se le suma 0.5 para que esté en el rango deseado.
// EN: Normalizes the received pan value to a range of 0.0 to 1.0. 
//    - Divides the input value by 200 to scale it to a range of -0.5 to 0.5.
//    - Then, adds 0.5 to fit it into the desired range.
void PanLinear::setPanLinearValue(float inPanLinearValue)
{
    panLinearValue = (inPanLinearValue / 200.0f) + 0.5f;
}

// Procesa el buffer de audio
// ES: Aplica el efecto de panoramización lineal al buffer de audio procesando cada muestra.
//    - El canal izquierdo (0) reduce su amplitud según el valor inverso de `panLinearValue`.
//    - El canal derecho (1) escala su amplitud con el valor de `panLinearValue`.
// EN: Applies the linear panning effect to the audio buffer by processing each sample.
//    - The left channel (0) reduces its amplitude based on the inverse of `panLinearValue`.
//    - The right channel (1) scales its amplitude with the value of `panLinearValue`.
void PanLinear::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);

            // Procesa el canal izquierdo
            // ES: Escala la muestra del canal izquierdo en función del valor inverso de `panLinearValue`.
            // EN: Scales the left channel sample based on the inverse of `panLinearValue`.
            if (channel == 0)
            {
                sample *= 1.0f - panLinearValue;
            }
            // Procesa el canal derecho
            // ES: Escala la muestra del canal derecho según el valor de `panLinearValue`.
            // EN: Scales the right channel sample based on the value of `panLinearValue`.
            else
            {
                sample *= panLinearValue;
            }

            // ES: Actualiza el valor de la muestra procesada en el buffer.
            // EN: Updates the processed sample value in the buffer.
            buffer.setSample(channel, i, sample);
        }
    }
}

// Constructor de la clase PanLinear
// ES: Inicializa la clase PanLinear.
// EN: Initializes the PanLinear class.
PanLinear::PanLinear()
{
}

// Destructor de la clase PanLinear
// ES: Limpia los recursos utilizados por la clase (si aplica).
// EN: Cleans up resources used by the class (if any).
PanLinear::~PanLinear()
{
}