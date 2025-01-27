/*
  ==============================================================================

    VibratoEffect.h
    Created: 23 Oct 2024 4:32:52pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: This class implements a vibrato audio effect with adjustable depth and rate.
// ES: Esta clase implementa un efecto de vibrato con profundidad y velocidad ajustables.
class VibratoFX
{
public:

    // EN: Sets the vibrato depth (amplitude of the delay modulation).
    // ES: Establece la profundidad del vibrato (amplitud de la modulación del delay).
    void setDepth(float inDepth);

    // EN: Sets the vibrato rate (frequency of the delay modulation as a percentage).
    // ES: Establece la velocidad del vibrato (frecuencia de la modulación del delay como porcentaje).
    void setRate(float inRate);

    // EN: Prepares the vibrato effect by setting the sample rate.
    // ES: Prepara el efecto de vibrato configurando la tasa de muestreo.
    void prepare(double theSampleRate);

    // EN: Processes the audio buffer to apply the vibrato effect.
    // ES: Procesa el buffer de audio para aplicar el efecto de vibrato.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor for the VibratoFX class.
    // ES: Constructor de la clase VibratoFX.
    VibratoFX();

    // EN: Destructor for the VibratoFX class.
    // ES: Destructor de la clase VibratoFX.
    ~VibratoFX();

private:
    // EN: The sample rate of the audio stream (samples per second).
    // ES: La tasa de muestreo del flujo de audio (muestras por segundo).
    float sampleRate = 48000;

    // EN: The base delay in samples used for the vibrato effect.
    // ES: El delay base en muestras usado para el efecto de vibrato.
    int delay = 1000;

    // EN: The depth of the vibrato modulation.
    // ES: La profundidad de la modulación del vibrato.
    float depth = 0.0f;

    // EN: The rate of the vibrato modulation expressed as a percentage.
    // ES: La velocidad de la modulación del vibrato expresada como porcentaje.
    float ratePercentage = 0.0f;

    // EN: A target value for the rate to allow smooth transitions when changing the rate parameter.
    // ES: Un valor objetivo para la velocidad que permite transiciones suaves al cambiar el parámetro de velocidad.
    float targetRatePercentage{};

    // EN: The current time variable for phase calculations (normalized between 0 and 1).
    // ES: Variable de tiempo actual para cálculos de fase (normalizada entre 0 y 1).
    float t = 0.0f;

    // EN: The size of the circular buffer used for delay.
    // ES: El tamaño del buffer circular utilizado para el delay.
    static const int circularBufferSize = 1000;

    // EN: A 2D circular buffer for processing audio for both channels.
    // ES: Un buffer circular 2D para procesar el audio de ambos canales.
    float circularBuffer[circularBufferSize][2] = { 0.0f };

    // EN: The read pointer for reading delayed samples from the circular buffer.
    // ES: El puntero de lectura para leer muestras retrasadas del buffer circular.
    int readerPointer = 0;

    // EN: The write pointers for writing new audio samples into the circular buffer, one for each channel.
    // ES: Los punteros de escritura para escribir nuevas muestras de audio en el buffer circular, uno por cada canal.
    int writterPointer[2]{};
};

