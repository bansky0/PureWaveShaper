/*
  ==============================================================================

    PingPongEcho.h
    Created: 24 Sep 2024 10:48:08am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PingPongEcho
{
public:
    // Setters para los par�metros de delay, ganancia, feedback
    void setBPM(float BPM1, float BPM2);
    void setGains(float gain1, float gain2);

    // Funci�n para preparar el procesador
    void prepare(double theSampleRate, int inTotalChannels);

    // Funci�n de procesamiento del buffer de audio
    void process(juce::AudioBuffer<float>& buffer);

	PingPongEcho();
	~PingPongEcho();

private:
    // Variables de retardo (delay)
    int delay1Samples = 48000; // Retardo en la entrada1
    int delay2Samples = 48000; // Retardo en la entrada2

    // Tama�o del buffer circular
    const int circularBufferSize = 96000;  // Puedes ajustar el tama�o seg�n tu necesidad
    int numChannels = 2;  // N�mero de canales (puede ser din�mico)

    // Buffers circulares para entrada y salida
    std::vector<std::vector<float>> circularBufferInput1;  // Buffer para x[n - d1]
    std::vector<std::vector<float>> circularBufferInput2; // Buffer para y[n - d2]

    // Punteros de escritura para entrada y salida
    std::vector<int> writterPointerInput1{ numChannels, 0 };  // Puntero de escritura para entrada
    std::vector<int> writterPointerInput2{ numChannels, 0 }; // Puntero de escritura para salida

    // Par�metros del delay
    double sampleRate = 48000.0;
    float gain1 = 0.75f;
    float gain2 = 0.75f;
    float fb1 = 0.75;
    float fb2 = 0.75;
};