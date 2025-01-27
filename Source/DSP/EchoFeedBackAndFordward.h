/*
  ==============================================================================

    EchoFeedBackAndFordward.h
    Created: 19 Sep 2024 11:16:08am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// Clase EchoFBF: Implementa un efecto de eco con feedback y forward utilizando un buffer circular.
class EchoFBF
{
public:
    // Métodos para configurar los parámetros del efecto

    // EN: Sets the BPM (beats per minute) for time-based delay calculation.
    // ES: Establece los BPM (beats por minuto) para calcular el retardo basado en el tiempo.
    void setBPM(float BPM);

    // EN: Sets the forward gain coefficient.
    // ES: Establece el coeficiente de ganancia para la señal de forward.
    void setAmpFordward(float inAmpFordward);

    // EN: Sets the feedback gain coefficient.
    // ES: Establece el coeficiente de ganancia para la señal de feedback.
    void setAmpFeedback(float inAmpFeedback);

    // EN: Prepares the effect with the sample rate of the audio stream.
    // ES: Prepara el efecto con la frecuencia de muestreo de la transmisión de audio.
    void prepare(double theSampleRate);

    // EN: Processes the audio buffer by applying the echo effect.
    // ES: Procesa el buffer de audio aplicando el efecto de eco.
    void process(juce::AudioBuffer<float>& buffer);

    // Constructor y destructor
    // EN: Constructor initializes variables and sets up default values.
    // ES: El constructor inicializa variables y configura valores predeterminados.
    EchoFBF();

    // EN: Destructor cleans up resources (none in this case).
    // ES: El destructor libera recursos (no hay en este caso).
    ~EchoFBF();

private:
    // Parámetros internos de la clase

    // EN: Fixed delay time in samples (default 48000, equivalent to 1 second at 48 kHz).
    // ES: Tiempo de retardo fijo en muestras (por defecto 48000, equivalente a 1 segundo a 48 kHz).
    int delay = 48000;

    // EN: Feedback gain coefficient for the delayed signal.
    // ES: Coeficiente de ganancia del feedback para la señal retardada.
    float ampFeedback = 0.75f;

    // EN: Forward gain coefficient for the delayed signal.
    // ES: Coeficiente de ganancia del forward para la señal retardada.
    float ampFordward = 0.75f;

    // EN: Internal variable to store the amount of feedback.
    // ES: Variable interna para almacenar la cantidad de feedback.
    float feedback = 0.5f;

    // EN: Size of the circular buffer used for delay.
    // ES: Tamaño del buffer circular utilizado para el delay.
    static const int circularBufferSize = 96000;

    // EN: Circular buffer for storing audio samples (stereo: 2 channels).
    // ES: Buffer circular para almacenar muestras de audio (estéreo: 2 canales).
    float circularBuffer[circularBufferSize][2] = { 0.0f };

    // EN: Pointers for reading and writing into the circular buffer.
    // ES: Punteros para lectura y escritura en el buffer circular.
    int readerPointer = 0;              // EN: Read pointer (shared for both channels).
                                        // ES: Puntero de lectura (compartido para ambos canales).
    int writterPointer[2]{};            // EN: Write pointers for each channel.
                                        // ES: Punteros de escritura para cada canal.

// EN: Parameters for the delay coefficients.
// ES: Parámetros para los coeficientes del delay.
    float sampleRate = 48000;           // EN: Sample rate for audio processing.
                                        // ES: Frecuencia de muestreo para el procesamiento de audio.
    float b0 = 1.0f;                    // EN: Coefficient for the input signal.
                                        // ES: Coeficiente para la señal de entrada.
    float bM = 0.5f;                    // EN: Coefficient for the delayed signal (forward path).
                                        // ES: Coeficiente para la señal retardada (camino de forward).
    float aW = 0.7f;                    // EN: Coefficient for the feedback path.
                                        // ES: Coeficiente para la señal de feedback.
};
