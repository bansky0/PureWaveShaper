/*
  ==============================================================================

    EchoStereo.h
    Created: 23 Sep 2024 9:46:31am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class EchoStereo
{
public:
    // EN: Setters for delay parameters, gains, and panning
    // ES: Setters para los parámetros de delay, ganancia y paneo
    void setBPM(float BPM1, float BPM2); // EN: Set delay times based on BPM for two inputs
    // ES: Configura los tiempos de retardo basados en BPM para dos entradas

    void setGains(float gain1, float gain2); // EN: Set gains for the two delay channels
    // ES: Configura las ganancias para los dos canales de delay

// void setPan(float inPanValue);        // EN: Set panning value (commented out in the code)
                                        // ES: Configura el valor de paneo (comentado en el código)

// EN: Function to prepare the processor
// ES: Función para preparar el procesador
    void prepare(double theSampleRate, int inTotalChannels);

    // EN: Function to process the audio buffer
    // ES: Función de procesamiento del buffer de audio
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor and destructor
    // ES: Constructor y destructor
    EchoStereo();
    ~EchoStereo();

private:
    // EN: Delay variables
    // ES: Variables de retardo (delay)
    int delay1Samples = 48000; // EN: Delay for input 1
    // ES: Retardo para la entrada 1

    int delay2Samples = 48000; // EN: Delay for input 2
    // ES: Retardo para la entrada 2

// EN: Circular buffer size
// ES: Tamaño del buffer circular
    const int circularBufferSize = 96000; // EN: Adjustable buffer size based on your needs
                                          // ES: Tamaño ajustable del buffer según tu necesidad

    int numChannels = 2; // EN: Number of channels (can be dynamic)
                         // ES: Número de canales (puede ser dinámico)

// EN: Circular buffers for input and output
// ES: Buffers circulares para entrada y salida
    std::vector<std::vector<float>> circularBufferInput1; // EN: Buffer for x[n - d1]
                                                          // ES: Buffer para x[n - d1]

    std::vector<std::vector<float>> circularBufferInput2; // EN: Buffer for y[n - d2]
                                                          // ES: Buffer para y[n - d2]

// EN: Write pointers for input and output
// ES: Punteros de escritura para entrada y salida
    std::vector<int> writterPointerInput1{ numChannels, 0 }; // EN: Write pointer for input 1
                                                             // ES: Puntero de escritura para entrada 1

    std::vector<int> writterPointerInput2{ numChannels, 0 }; // EN: Write pointer for input 2
                                                             // ES: Puntero de escritura para entrada 2

// EN: Delay parameters
// ES: Parámetros del delay
    double sampleRate = 48000.0; // EN: Sample rate for processing
                                 // ES: Tasa de muestreo para el procesamiento

    float gain1 = 0.75f; // EN: Gain for the first channel
                         // ES: Ganancia para el primer canal

    float gain2 = 0.75f; // EN: Gain for the second channel
                         // ES: Ganancia para el segundo canal

};
