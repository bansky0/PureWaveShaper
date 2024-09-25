/*
  ==============================================================================

    EchoStereo.h
    Created: 23 Sep 2024 9:46:31am
    Author:  Jhonatan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class EchoStereo
{
public:

    // Setters para los parámetros de delay, ganancia y paneo
    void setBPM(float BPM1, float BPM2);
    void setGains(float gain1, float gain2);
    //void setPan(float inPanValue);
    
    // Función para preparar el procesador
    void prepare(double theSampleRate, int inTotalChannels);

    // Función de procesamiento del buffer de audio
    void process(juce::AudioBuffer<float>& buffer);

	EchoStereo();
	~EchoStereo();

private:
    // Variables de retardo (delay)
    int delay1Samples = 48000; // Retardo en la entrada1
    int delay2Samples = 48000; // Retardo en la entrada2

    // Tamaño del buffer circular
    const int circularBufferSize = 96000;  // Puedes ajustar el tamaño según tu necesidad
    int numChannels = 2;  // Número de canales (puede ser dinámico)

    // Buffers circulares para entrada y salida
    std::vector<std::vector<float>> circularBufferInput1;  // Buffer para x[n - d1]
    std::vector<std::vector<float>> circularBufferInput2; // Buffer para y[n - d2]

    // Punteros de escritura para entrada y salida
    std::vector<int> writterPointerInput1{ numChannels, 0 };  // Puntero de escritura para entrada
    std::vector<int> writterPointerInput2{ numChannels, 0 }; // Puntero de escritura para salida

    // Parámetros del delay
    double sampleRate = 48000.0;
    float gain1 = 0.75f;
    float gain2 = 0.75f;

    // Paneos
    //float panValue{}, panLeft{}, panRight{};
};
