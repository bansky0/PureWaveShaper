/*
  ==============================================================================

    EchoFeedBackAndFordward2.h
    Created: 20 Sep 2024 1:29:43pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <vector>

// EN: Class to implement a delay effect with forward and feedback components.
// ES: Clase para implementar un efecto de delay con componentes forward y feedback.
class EchoFBF2
{
public:
    // EN: Sets the BPM for the delay time affecting the input delay (dM).
    // ES: Establece el BPM para el tiempo de delay afectando el retardo de entrada (dM).
    void setBPM(float BPM);

    // EN: Sets the BPM for the delay time affecting the output delay (dW).
    // ES: Establece el BPM para el tiempo de delay afectando el retardo de salida (dW).
    void setBPMOutput(float BPM);

    // EN: Sets the forward gain coefficient (bM in the formula).
    // ES: Establece el coeficiente de ganancia para el forward (bM en la fórmula).
    void setAmpFordward(float inAmpFordward);

    // EN: Sets the feedback gain coefficient (aW in the formula).
    // ES: Establece el coeficiente de ganancia para el feedback (aW en la fórmula).
    void setAmpFeedback(float inAmpFeedback);

    // EN: Sets the general feedback level.
    // ES: Establece el nivel general de feedback.
    void setFeedback(float inFeedback);

    // EN: Prepares the delay with the specified sample rate and number of channels.
    // ES: Prepara el delay con la frecuencia de muestreo y número de canales especificados.
    void prepare(double theSampleRate, int totalNumChannels);

    // EN: Processes the audio buffer, applying the delay effect.
    // ES: Procesa el buffer de audio aplicando el efecto de delay.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor to initialize default values.
    // ES: Constructor para inicializar valores predeterminados.
    EchoFBF2();

    // EN: Destructor for cleanup (if needed).
    // ES: Destructor para limpieza (si es necesario).
    ~EchoFBF2();

private:
    // *** DELAY VARIABLES ***

    // EN: Delay in samples for the input (dM) and output (dW).
    // ES: Retardo en muestras para la entrada (dM) y salida (dW).
    int delayM = 0;
    int delayW = 0;

    // EN: Size of the circular buffer (can be adjusted as needed).
    // ES: Tamaño del buffer circular (puede ajustarse según sea necesario).
    const int circularBufferSize = 96000;

    // EN: Number of audio channels (stereo by default, but dynamic).
    // ES: Número de canales de audio (estéreo por defecto, pero dinámico).
    int numChannels = 2;

    // *** CIRCULAR BUFFERS ***

    // EN: Circular buffer for delayed input samples (x[n - dM]).
    // ES: Buffer circular para muestras de entrada retrasadas (x[n - dM]).
    std::vector<std::vector<float>> circularBufferInput;

    // EN: Circular buffer for delayed output samples (y[n - dW]).
    // ES: Buffer circular para muestras de salida retrasadas (y[n - dW]).
    std::vector<std::vector<float>> circularBufferOutput;

    // *** POINTERS ***

    // EN: Write pointers for input and output circular buffers.
    // ES: Punteros de escritura para los buffers circulares de entrada y salida.
    std::vector<int> writterPointerInput{ numChannels, 0 };
    std::vector<int> writterPointerOutput{ numChannels, 0 };

    // *** DELAY PARAMETERS ***

    // EN: Sample rate of the audio (default: 48,000 Hz).
    // ES: Frecuencia de muestreo del audio (por defecto: 48,000 Hz).
    double sampleRate = 48000.0;

    // EN: Forward gain coefficient for the input delay (bM).
    // ES: Coeficiente de ganancia para el retardo de entrada (bM).
    float bM = 0.5f;

    // EN: Feedback gain coefficient for the output delay (aW).
    // ES: Coeficiente de ganancia para el retardo de salida (aW).
    float aW = 0.5f;

    // EN: General feedback level applied to the output.
    // ES: Nivel de feedback general aplicado a la salida.
    float feedback = 0.5f;

    // EN: Coefficient for the current input sample (b0 in the formula).
    // ES: Coeficiente para la muestra de entrada actual (b0 en la fórmula).
    float b0 = 1.0f;
};
