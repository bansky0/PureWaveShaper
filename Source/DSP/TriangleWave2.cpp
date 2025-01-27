/*
  ==============================================================================

    TriangleWave2.cpp
    Created: 9 Sep 2024 3:56:59pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "TriangleWave2.h"

// EN: Sets the frequency of the triangle wave and calculates the phase increment based on the sample rate.
// ES: Establece la frecuencia de la onda triangular y calcula el incremento de fase basado en la tasa de muestreo.
void TriangleWave2::setFrequency(double inFrequency)
{
    frequency = inFrequency;

    // EN: Ensure sampleRate is valid before calculating the phase increment.
    // ES: Asegurarse de que sampleRate sea válido antes de calcular el incremento de fase.
    if (sampleRate > 0.0f)
    {
        phaseIncrement = frequency / sampleRate; // EN: Determines the step size per sample. ES: Determina el tamaño del paso por muestra.
    }
}

// EN: Sets the width (duty cycle) of the triangle wave. This value controls the balance between the rising and falling edges of the wave.
// ES: Establece el ancho (ciclo de trabajo) de la onda triangular. Este valor controla el equilibrio entre los bordes ascendentes y descendentes de la onda.
void TriangleWave2::setWidth(float inWidth)
{
    width = inWidth;
}

// EN: Prepares the wave generator by setting the sample rate.
// ES: Prepara el generador de ondas configurando la tasa de muestreo.
void TriangleWave2::prepare(double theSampleRate)
{
    sampleRate = static_cast<float>(theSampleRate); // EN: Store the sample rate for further calculations. ES: Almacena la tasa de muestreo para cálculos posteriores.
}

// EN: Processes the audio buffer and generates a triangle wave with the specified frequency and width.
// ES: Procesa el buffer de audio y genera una onda triangular con la frecuencia y el ancho especificados.
void TriangleWave2::process(juce::AudioBuffer<float>& buffer)
{
    // EN: Loop through each audio channel.
    // ES: Recorre cada canal de audio.
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        // EN: Loop through each sample in the buffer.
        // ES: Recorre cada muestra en el buffer.
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float outSample = 0.0f;

            // EN: Generate the triangle wave with adjustable width.
            // ES: Generar la onda triangular con un ancho ajustable.
            if (phase[channel] < width)
            {
                // EN: First half of the wave (rising edge).
                // ES: Primera mitad de la onda (borde ascendente).
                outSample = (phase[channel] / width) * 2.0f - 1.0f;
            }
            else
            {
                // EN: Second half of the wave (falling edge).
                // ES: Segunda mitad de la onda (borde descendente).
                outSample = ((phase[channel] - width) / (1.0f - width)) * -2.0f + 1.0f;
            }

            // EN: Store the calculated sample value in the buffer.
            // ES: Almacena el valor de muestra calculado en el buffer.
            buffer.setSample(channel, i, outSample);

            // EN: Update the phase and wrap it within the range [0, 1).
            // ES: Actualiza la fase y la mantiene dentro del rango [0, 1).
            phase[channel] += phaseIncrement;
            if (phase[channel] >= 1.0f)
                phase[channel] -= 1.0f; // EN: Wrap phase back to the start. ES: Reinicia la fase al principio.
        }
    }
}

// EN: Constructor initializes the TriangleWave2 object.
// ES: El constructor inicializa el objeto TriangleWave2.
TriangleWave2::TriangleWave2()
{
}

// EN: Destructor cleans up the TriangleWave2 object.
// ES: El destructor limpia el objeto TriangleWave2.
TriangleWave2::~TriangleWave2()
{
}