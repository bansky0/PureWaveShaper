/*
  ==============================================================================

    TriangleWave2.h
    Created: 9 Sep 2024 3:56:59pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: This class generates a triangle wave with adjustable frequency and width parameters.
// ES: Esta clase genera una onda triangular con parámetros ajustables de frecuencia y ancho.
class TriangleWave2
{
public:
    // EN: Sets the frequency of the triangle wave.
    // ES: Establece la frecuencia de la onda triangular.
    void setFrequency(double inFrequency);

    // EN: Sets the width (duty cycle) of the triangle wave.
    // ES: Establece el ancho (ciclo de trabajo) de la onda triangular.
    void setWidth(float inWidth);

    // EN: Prepares the wave generator by setting the sample rate and initializing the phase variables.
    // ES: Prepara el generador de ondas configurando la tasa de muestreo e inicializando las variables de fase.
    void prepare(double theSampleRate);

    // EN: Processes the audio buffer and fills it with the generated triangle wave.
    // ES: Procesa el buffer de audio y lo llena con la onda triangular generada.
    void process(juce::AudioBuffer<float>& buffer);

    // EN: Constructor initializes the TriangleWave2 object.
    // ES: El constructor inicializa el objeto TriangleWave2.
    TriangleWave2();

    // EN: Destructor cleans up the TriangleWave2 object.
    // ES: El destructor limpia el objeto TriangleWave2.
    ~TriangleWave2();

private:
    // EN: The sample rate for the audio processing.
    // ES: La tasa de muestreo para el procesamiento de audio.
    float sampleRate{};

    // EN: The frequency of the triangle wave.
    // ES: La frecuencia de la onda triangular.
    float frequency{ 44100.0f };

    // EN: The increment value for the phase, determined by the frequency and sample rate.
    // ES: El valor de incremento para la fase, determinado por la frecuencia y la tasa de muestreo.
    float phaseIncrement{};

    // EN: The width (duty cycle) of the triangle wave. Ranges between 0 and 1.
    // ES: El ancho (ciclo de trabajo) de la onda triangular. Oscila entre 0 y 1.
    float width{};

    // EN: The phase accumulator for each channel (stereo support).
    // ES: El acumulador de fase para cada canal (soporte estéreo).
    float phase[2]{};
};