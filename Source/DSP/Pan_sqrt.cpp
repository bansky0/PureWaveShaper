/*
  ==============================================================================

    Pan_sqrt.cpp
    Created: 26 Aug 2024 11:09:35am
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Pan_sqrt.h"

// Configura el valor de panoramización basado en raíz cuadrada
// ES: Convierte el valor de entrada de un rango arbitrario (-100 a 100) a un rango normalizado (0.0 a 1.0).
// EN: Converts the input value from an arbitrary range (-100 to 100) to a normalized range (0.0 to 1.0).
void PanSqrt::setPanSqrtValue(float inPanSqrtValue)
{
    panSqrtValue = (inPanSqrtValue / 200.0f) + 0.5f;
}

// Procesa el buffer de audio aplicando la panoramización
// ES: Ajusta el nivel de las muestras en cada canal utilizando una función de raíz cuadrada para suavizar los niveles.
// EN: Adjusts the sample levels in each channel using a square root function for smooth level transitions.
void PanSqrt::process(juce::AudioBuffer<float>& buffer)
{
    // ES: Itera sobre cada canal del buffer de audio.
    // EN: Iterates through each channel in the audio buffer.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // ES: Itera sobre cada muestra dentro del canal actual.
        // EN: Iterates through each sample in the current channel.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // ES: Obtiene el valor de la muestra actual.
            // EN: Retrieves the value of the current sample.
            float sample = buffer.getSample(channel, i);

            // Procesa el canal izquierdo
            // ES: Reduce el nivel de la muestra usando la raíz cuadrada del complemento de panSqrtValue.
            // EN: Reduces the sample level using the square root of the complement of panSqrtValue.
            if (channel == 0)
            {
                sample *= sqrtf(1.0f - panSqrtValue);
            }
            // Procesa el canal derecho
            // ES: Reduce el nivel de la muestra usando la raíz cuadrada de panSqrtValue.
            // EN: Reduces the sample level using the square root of panSqrtValue.
            else
            {
                sample *= sqrtf(panSqrtValue);
            }

            // ES: Establece el valor ajustado de la muestra de vuelta en el buffer.
            // EN: Sets the adjusted sample value back into the buffer.
            buffer.setSample(channel, i, sample);
        }
    }
}

// Constructor
// ES: Inicializa la clase PanSqrt.
// EN: Initializes the PanSqrt class.
PanSqrt::PanSqrt()
{
}

// Destructor
// ES: Libera los recursos de la clase PanSqrt (si aplica).
// EN: Releases resources used by the PanSqrt class (if applicable).
PanSqrt::~PanSqrt()
{
}
