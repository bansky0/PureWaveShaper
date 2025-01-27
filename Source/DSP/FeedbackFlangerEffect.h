/*
  ==============================================================================

    FeedbackFlangerEffect.h
    Created: 30 Oct 2024 4:35:30pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: The FeedbackFlangerFX class applies a feedback-based flanger effect to an audio signal.
// ES: La clase FeedbackFlangerFX aplica un efecto de flanger con retroalimentación a una señal de audio.
class FeedbackFlangerFX
{
public:
    // EN: Constructor to initialize the feedback flanger effect
    // ES: Constructor para inicializar el efecto de flanger con retroalimentación
    FeedbackFlangerFX();

    // EN: Destructor to clean up any resources used by the effect
    // ES: Destructor para limpiar los recursos usados por el efecto
    ~FeedbackFlangerFX();

    // EN: Prepare the flanger effect with the sample rate
    // ES: Preparar el efecto de flanger con la tasa de muestreo
    void prepare(double theSampleRate);

    // EN: Set the depth of the flanger effect (how intense the effect is)
    // ES: Establecer la profundidad del efecto de flanger (qué tan intenso es el efecto)
    void setDepth(float inDepth);

    // EN: Set the rate of the flanger effect in percentage (controls the modulation speed)
    // ES: Establecer la tasa del efecto de flanger en porcentaje (controla la velocidad de modulación)
    void setRate(float inRatePercentage);

    // EN: Set the predelay time in milliseconds (delays the start of the effect)
    // ES: Establecer el tiempo de predelay en milisegundos (retrasar el inicio del efecto)
    void setPredelay(float inPredelayMs);

    // EN: Set the feedback amount for the flanger (how much of the delayed signal is fed back into the effect)
    // ES: Establecer la cantidad de retroalimentación para el flanger (cuánta señal retrasada se retroalimenta en el efecto)
    void setFeedback(float inFeedback);

    // EN: Process the audio buffer with the flanger effect
    // ES: Procesar el buffer de audio con el efecto de flanger
    void process(juce::AudioBuffer<float>& buffer);

private:
    // EN: Sample rate used for processing the audio signal
    // ES: Tasa de muestreo usada para procesar la señal de audio
    float sampleRate;

    // EN: Time variable used for modulating the flanger
    // ES: Variable de tiempo usada para modular el flanger
    float t;

    // EN: Depth of the flanger effect
    // ES: Profundidad del efecto de flanger
    float depth;

    // EN: Rate of modulation for the flanger, as a percentage
    // ES: Tasa de modulación para el flanger, en porcentaje
    float ratePercentage;

    // EN: Target rate for the flanger, used to smooth transitions
    // ES: Tasa objetivo para el flanger, utilizada para suavizar las transiciones
    float targetRatePercentage;

    // EN: Predelay time in milliseconds
    // ES: Tiempo de predelay en milisegundos
    float predelay;

    // EN: Feedback amount for the flanger effect
    // ES: Cantidad de retroalimentación para el efecto de flanger
    float feedback;

    // EN: Circular buffer for storing the audio signal (stereo buffer with two channels)
    // ES: Buffer circular para almacenar la señal de audio (buffer estéreo con dos canales)
    static const int circularBufferSize = 48000; // Tamaño del buffer circular
    float circularBuffer[circularBufferSize][2]; // Buffer circular estéreo

    // EN: Write pointers for each channel (left and right channels)
    // ES: Punteros de escritura para cada canal (canal izquierdo y derecho)
    int writterPointer[2] = { 0, 0 };            // Punteros de escritura para cada canal
};
