/*
  ==============================================================================

    EchoFeedBackAndFordward2.h
    Created: 20 Sep 2024 1:29:43pm
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <vector>

class EchoFBF2
{
public:

    // Funciones para configurar el delay y los parámetros
    void setBPM(float BPM);
    void setBPMOutput(float BPM);
    void setAmpFordward(float inAmpFordward);
    void setAmpFeedback(float inAmpFeedback);
    void setFeedback(float inFeedback);

    void prepare(double theSampleRate, int totalNumChannels);
    // Procesar el buffer de audio
    void process(juce::AudioBuffer<float>& buffer);
	EchoFBF2();
	~EchoFBF2();

private:
    // Variables de retardo (delay)
    int delayM = 0;  // Retardo en la entrada (dM)
    int delayW = 0;  // Retardo en la salida (dW)

    // Tamaño del buffer circular
    const int circularBufferSize = 96000;  // Puedes ajustar el tamaño según tu necesidad
    int numChannels = 2;  // Número de canales (puede ser dinámico)

    // Buffers circulares para entrada y salida
    std::vector<std::vector<float>> circularBufferInput;  // Buffer para x[n - dM]
    std::vector<std::vector<float>> circularBufferOutput; // Buffer para y[n - dW]

    // Punteros de escritura para entrada y salida
    std::vector<int> writterPointerInput{ numChannels, 0 };  // Puntero de escritura para entrada
    std::vector<int> writterPointerOutput{ numChannels, 0 }; // Puntero de escritura para salida

    // Parámetros del delay
    double sampleRate = 48000.0;
    float bM = 0.5f;  // bM en la ecuación
    float aW = 0.5f;  // aW en la ecuación
    float feedback = 0.5f;     // Feedback general

    float b0 = 1.0f;  // Coeficiente para x[n]
};
