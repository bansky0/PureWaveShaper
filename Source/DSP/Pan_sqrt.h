/*
  ==============================================================================

    Pan_sqrt.h
    Created: 26 Aug 2024 11:09:35am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// Clase PanSqrt
// ES: Implementa un efecto de panoramización que utiliza una función basada en la raíz cuadrada.
// EN: Implements a panning effect that uses a square root-based function.

class PanSqrt
{
public:
    // Constructor
    // ES: Inicializa la clase PanSqrt.
    // EN: Initializes the PanSqrt class.
    PanSqrt();

    // Destructor
    // ES: Libera recursos utilizados por la clase (si aplica).
    // EN: Releases resources used by the class (if applicable).
    ~PanSqrt();

    // Configura el valor de panoramización basado en raíz cuadrada
    // ES: Ajusta el valor de panoramización en el rango esperado.
    // EN: Adjusts the panning value within the expected range.
    void setPanSqrtValue(float inPanSqrtValue);

    // Procesa el buffer de audio aplicando la panoramización
    // ES: Modifica las muestras de audio para distribuir el nivel de salida entre los canales izquierdo y derecho.
    // EN: Modifies the audio samples to distribute output levels between the left and right channels.
    void process(juce::AudioBuffer<float>& buffer);

private:
    // Valor de panoramización
    // ES: Determina el nivel relativo de cada canal en función de la raíz cuadrada.
    // EN: Determines the relative level of each channel based on the square root.
    float panSqrtValue{};
};