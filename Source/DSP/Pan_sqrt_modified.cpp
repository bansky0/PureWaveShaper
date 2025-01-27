/*
  ==============================================================================

    Pan_sqrt_modified.cpp
    Created: 26 Aug 2024 1:26:18pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "Pan_sqrt_modified.h"

// Configura el valor de panoramización modificada
// ES: Ajusta el valor de panoramización normalizándolo al rango de 0.5 a 1.5. 
// EN: Adjusts the panning value by normalizing it to the range of 0.5 to 1.5.
void PanSqrtModidied::setPanSqrtModidiedValue(float inPanSqrtModidiedValue)
{
    panSqrtModifiedValue = (inPanSqrtModidiedValue / 200.0f) + 0.5f;
}

// Procesa el buffer de audio
// ES: Aplica la panoramización modificada al buffer de audio usando una función exponencial.
// EN: Applies the modified panning effect to the audio buffer using an exponential function.
void PanSqrtModidied::process(juce::AudioBuffer<float>& buffer)
{
    // Itera por cada canal en el buffer
    // ES: Procesa cada canal (izquierdo y derecho) en el buffer.
    // EN: Processes each channel (left and right) in the buffer.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // Itera por cada muestra en el canal
        // ES: Procesa cada muestra de audio en el canal actual.
        // EN: Processes each audio sample in the current channel.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float sample = buffer.getSample(channel, i);

            // Procesa el canal izquierdo
            // ES: Reduce la amplitud del canal izquierdo usando una función de potencia de base (1 - panSqrtModifiedValue) y exponente 0.75.
            // EN: Reduces the amplitude of the left channel using a power function with base (1 - panSqrtModifiedValue) and exponent 0.75.
            if (channel == 0)
            {
                sample *= powf(1 - panSqrtModifiedValue, 0.75f);
            }
            // Procesa el canal derecho
            // ES: Reduce la amplitud del canal derecho usando una función de potencia de base panSqrtModifiedValue y exponente 0.75.
            // EN: Reduces the amplitude of the right channel using a power function with base panSqrtModifiedValue and exponent 0.75.
            else
            {
                sample *= powf(panSqrtModifiedValue, 0.75f);
            }

            // Almacena la muestra procesada en el buffer
            // ES: Sobrescribe la muestra actual con el valor procesado.
            // EN: Overwrites the current sample with the processed value.
            buffer.setSample(channel, i, sample);
        }
    }
}

// Constructor
// ES: Inicializa una instancia de la clase PanSqrtModified.
// EN: Initializes an instance of the PanSqrtModified class.
PanSqrtModidied::PanSqrtModidied()
{
}

// Destructor
// ES: Libera recursos utilizados por la instancia de PanSqrtModified (si aplica).
// EN: Releases resources used by the PanSqrtModified instance (if applicable).
PanSqrtModidied::~PanSqrtModidied()
{
}
