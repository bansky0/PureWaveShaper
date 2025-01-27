/*
  ==============================================================================

    AmpModulation.h
    Created: 27 Aug 2024 2:40:42pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class AmpModulation: Implements amplitude modulation (tremolo) with configurable depth and speed.
// ES: Clase AmpModulation: Implementa modulación de amplitud (tremolo) con profundidad y velocidad configurables.
class AmpModulation
{
public:
    // EN: Constructor and Destructor.
    // ES: Constructor y Destructor.
    AmpModulation();
    ~AmpModulation();

    // EN: Sets the depth of the amplitude modulation (0-100%).
    // ES: Configura la profundidad de la modulación de amplitud (0-100%).
    void setDepth(float inDepthValue);

    // EN: Sets the speed of the amplitude modulation in Hz (0-20 Hz).
    // ES: Configura la velocidad de la modulación de amplitud en Hz (0-20 Hz).
    void setSpeed(float inSpeedValue);

    // EN: Prepares the modulation by initializing the sample rate.
    // ES: Prepara la modulación inicializando la frecuencia de muestreo.
    void prepare(double theSampleRate);

    // EN: Processes the audio buffer and applies amplitude modulation.
    // ES: Procesa el buffer de audio y aplica modulación de amplitud.
    void process(juce::AudioBuffer<float>& buffer);

private:
    // EN: Mathematical constant pi (π).
    // ES: Constante matemática pi (π).
    float pi{ juce::MathConstants<float>::pi };

    // EN: Time and time increment for modulation signal per channel.
    // ES: Tiempo e incremento de tiempo para la señal de modulación por canal.
    float time[2];
    float deltTime[2];

    // EN: Sample rate for audio processing.
    // ES: Frecuencia de muestreo para el procesamiento de audio.
    float sampleRate{ 44100.0f };

    // EN: Parameters for tremolo effect.
    // ES: Parámetros para el efecto de trémolo.
    float depthValue{ 0 };   // EN: Modulation depth (0-100%).
                             // ES: Profundidad de modulación (0-100%).

    float speedValue{ 5.0 }; // EN: Modulation speed in Hz (0-20 Hz).
                             // ES: Velocidad de modulación en Hz (0-20 Hz).

// EN: Additional parameters (commented out for now) for advanced modulation calculations.
// ES: Parámetros adicionales (actualmente comentados) para cálculos avanzados de modulación.
// float amp{0.5 * (depthValue / 100)};
// float offset{ 1 - amp };
// float f{ speed };
// float phi{ 0 };
// float sw{ sinf(2 * pi * f * t * phi) };
// float mod{ amp * sw + offset };
};