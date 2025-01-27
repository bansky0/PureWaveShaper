/*
  ==============================================================================

    BarberPoleFeedback.h
    Created: 5 Nov 2024 8:29:25am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class implementing a Barberpole Flanger effect.
// ES: Clase que implementa un efecto Barberpole Flanger.
class BarberpoleFlangerFX
{
public:
    BarberpoleFlangerFX(); // EN: Constructor.
                           // ES: Constructor.
    ~BarberpoleFlangerFX(); // EN: Destructor.
                            // ES: Destructor.

// Public methods
    void prepare(double theSampleRate); // EN: Initializes the effect with the given sample rate.
                                        // ES: Configuración inicial del efecto con la frecuencia de muestreo.
    void setDepth(float inDepth); // EN: Sets the depth of the effect.
                                  // ES: Ajusta la profundidad del efecto.
    void setRate(float inRatePercentage); // EN: Sets the LFO rate as a percentage of the range.
                                          // ES: Ajusta la velocidad del LFO como porcentaje del rango.
    void setPredelay(float inPredelayMs); // EN: Configures the predelay in milliseconds.
                                          // ES: Configura el predelay en milisegundos.
    void process(juce::AudioBuffer<float>& buffer); // EN: Processes the audio buffer to apply the effect.
                                                    // ES: Procesa el buffer de audio para aplicar el efecto.

private:
    // Internal attributes
    float sampleRate; // EN: Sampling rate of the audio processing.
                      // ES: Frecuencia de muestreo del procesamiento de audio.
    float t; // EN: Internal time variable for LFO phase.
             // ES: Variable de tiempo interna para la fase del LFO.
    float depth; // EN: Depth of the modulation effect.
                 // ES: Profundidad del efecto de modulación.
    float ratePercentage; // EN: Current LFO rate as a percentage of the range.
                          // ES: Velocidad actual del LFO como porcentaje del rango.
    float targetRatePercentage; // EN: Target LFO rate percentage to transition toward.
                                // ES: Porcentaje objetivo del LFO hacia el que se transiciona.
    float predelay; // EN: Predelay time in samples.
                    // ES: Tiempo de pre-delay en muestras.
    static const int circularBufferSize = 48000; // EN: Size of the circular buffer (samples).
                                                 // ES: Tamaño del buffer circular (muestras).
    float circularBuffer[circularBufferSize][2]; // EN: Stereo circular buffer for delay storage.
                                                 // ES: Buffer circular estéreo para almacenamiento del delay.
    int writterPointer[2] = { 0, 0 }; // EN: Write pointers for each stereo channel.
                                      // ES: Punteros de escritura para cada canal estéreo.

// Private methods
    float generateSawtooth(float phase); // EN: Generates a sawtooth wave based on the input phase.
                                         // ES: Genera una onda diente de sierra basada en la fase de entrada.
};