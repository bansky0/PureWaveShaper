/*
  ==============================================================================

    AutoPan.h
    Created: 30 Aug 2024 12:13:48pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class AutoPan: Implements an auto-pan effect that modulates the stereo field based on a sine wave.
// ES: Clase AutoPan: Implementa un efecto de auto-pan que modula el campo estéreo basado en una onda sinusoidal.
class AutoPan
{
public:
    // EN: Sets the depth of the auto-pan effect (0-100). | ES: Configura la profundidad del efecto de auto-pan (0-100).
    void setDepth(float inDepthValue);

    // EN: Sets the speed of the auto-pan effect (0-20 Hz). | ES: Configura la velocidad del efecto de auto-pan (0-20 Hz).
    void setSpeed(float inSpeedValue);

    // EN: Prepares the auto-pan effect by setting the sample rate and initializing parameters.
    // ES: Prepara el efecto de auto-pan configurando la tasa de muestreo e inicializando parámetros.
    void prepare(double theSampleRate);

    // EN: Processes the audio buffer to apply the auto-pan effect. | ES: Procesa el buffer de audio para aplicar el efecto de auto-pan.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the AutoPan class. | ES: Constructor de la clase AutoPan.
    AutoPan();

    // EN: Destructor for the AutoPan class. | ES: Destructor de la clase AutoPan.
    ~AutoPan();

private:
    float pi{ juce::MathConstants<float>::pi };  // EN: Value of Pi for sine wave calculations. | ES: Valor de Pi para cálculos de onda sinusoidal.
    float time[2];  // EN: Time variables for each stereo channel. | ES: Variables de tiempo para cada canal estéreo.
    float deltTime[2];  // EN: Delta time for advancing the sine wave. | ES: Delta de tiempo para avanzar la onda sinusoidal.
    float sampleRate{ 44100.0f };  // EN: Sample rate of the audio buffer. | ES: Tasa de muestreo del buffer de audio.

    // EN: Parameters for the tremolo modulation.
    // ES: Parámetros para la modulación del tremolo.
    float depthValue{ 0 };  // EN: Depth of the modulation (0-100). | ES: Profundidad de la modulación (0-100).
    float speedValue{ 5.0 };  // EN: Speed of the modulation in Hz (0-20). | ES: Velocidad de la modulación en Hz (0-20).
};