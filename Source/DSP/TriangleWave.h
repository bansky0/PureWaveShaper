/*
  ==============================================================================

    TriangleWave.h
    Created: 28 Aug 2024 5:32:09pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: Class definition for a TriangleWave generator, which can generate a triangle wave signal with adjustable frequency.
// ES: Definición de clase para un generador de onda triangular, que puede generar una señal de onda triangular con frecuencia ajustable.
class TriangleWave
{
public:
    // EN: Sets the frequency of the triangle wave.
    // ES: Establece la frecuencia de la onda triangular.
    void setFrequency(double inFrequecy);

    // EN: Prepares the triangle wave generator by setting the sample rate.
    // ES: Prepara el generador de onda triangular configurando la tasa de muestreo.
    void prepare(double theSampleRate);

    // EN: Processes the audio buffer by generating a triangle wave for each sample in the buffer.
    // ES: Procesa el buffer de audio generando una onda triangular para cada muestra en el buffer.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor initializes the TriangleWave object.
    // ES: El constructor inicializa el objeto TriangleWave.
    TriangleWave();

    // EN: Destructor cleans up the TriangleWave object.
    // ES: El destructor limpia el objeto TriangleWave.
    ~TriangleWave();

private:
    // EN: Frequency of the triangle wave in Hz (default is 100 Hz).
    // ES: Frecuencia de la onda triangular en Hz (por defecto es 100 Hz).
    float frequency{ 100.0f };

    // EN: Sample rate of the audio system (default is 44,100 Hz).
    // ES: Tasa de muestreo del sistema de audio (por defecto es 44,100 Hz).
    float sampleRate{ 44100 };

    // EN: Current time position for each channel, used to track the phase of the triangle wave.
    // ES: Posición de tiempo actual para cada canal, utilizada para rastrear la fase de la onda triangular.
    float time[2]{};

    // EN: Increment of time for each sample, calculated based on frequency and sample rate.
    // ES: Incremento de tiempo para cada muestra, calculado en función de la frecuencia y la tasa de muestreo.
    float deltaTime[2]{};
};