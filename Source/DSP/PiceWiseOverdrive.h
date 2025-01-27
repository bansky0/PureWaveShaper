/*
  ==============================================================================

    PiceWiseOverdrive.h
    Created: 3 Sep 2024 1:43:52pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// Definición de la clase PiceWiseOverdrive
// ES: Esta clase implementa un efecto de distorsión que utiliza una técnica de sobrecarga por tramos (piecewise).
// EN: This class implements an overdrive effect that uses a piecewise distortion technique.
class PiceWiseOverdrive
{
public:

    // Método comentado (posiblemente a implementar)
    // ES: Este método permitiría ajustar el valor de la distorsión por tramos (piecewise overdrive).
    // EN: This method would allow adjusting the value of the piecewise overdrive distortion.
    // void setPiceWiseOverdriveValue(float inPiceWiseOverdriveValue);

    // Método para procesar el buffer de audio
    // ES: Este método procesa el buffer de audio para aplicar el efecto de distorsión por tramos.
    // EN: This method processes the audio buffer to apply the piecewise overdrive effect.
    void process(juce::AudioBuffer<float>& buffer);

    // Constructor de la clase
    // ES: Inicializa una nueva instancia de la clase PiceWiseOverdrive.
    // EN: Initializes a new instance of the PiceWiseOverdrive class.
    PiceWiseOverdrive();

    // Destructor de la clase
    // ES: Libera recursos cuando la instancia de PiceWiseOverdrive se destruye.
    // EN: Releases resources when the PiceWiseOverdrive instance is destroyed.
    ~PiceWiseOverdrive();

private:

    // No se han definido miembros privados para esta clase en este archivo de cabecera
    // ES: Actualmente no hay variables privadas para esta clase.
    // EN: Currently, there are no private variables for this class.
};