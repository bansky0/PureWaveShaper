/*
  ==============================================================================

    Biquad_BPF.h
    Created: 1 Oct 2024 12:24:54pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

// EN: The Biquad_BPF class implements a Biquad Band-Pass Filter (BPF) for audio processing.
// ES: La clase Biquad_BPF implementa un filtro Biquad de paso banda (BPF) para procesamiento de audio.
class Biquad_BPF
{
public:
    // EN: Constructor for the Biquad_BPF class, initializes the filter with default values.
    // ES: Constructor para la clase Biquad_BPF, inicializa el filtro con valores predeterminados.
    Biquad_BPF();

    // EN: Destructor for the Biquad_BPF class.
    // ES: Destructor para la clase Biquad_BPF.
    ~Biquad_BPF();

    // EN: Prepares the filter by setting the sample rate and updating the filter coefficients.
    // ES: Prepara el filtro estableciendo la frecuencia de muestreo y actualizando los coeficientes del filtro.
    void prepare(double inSampleRate);

    // EN: Processes an audio buffer by applying the band-pass filter to each sample.
    // ES: Procesa un buffer de audio aplicando el filtro de paso banda a cada muestra.
    void process(juce::AudioBuffer<float> inBuffer);

    // EN: Processes a single audio sample and applies the filter's equation.
    // ES: Procesa una sola muestra de audio y aplica la ecuación del filtro.
    float processSample(float inSample, int channel);

    // EN: Sets the center frequency of the band-pass filter and updates the coefficients.
    // ES: Establece la frecuencia central del filtro de paso banda y actualiza los coeficientes.
    void setFrequency(float inFrequency);

    // EN: Sets the quality factor (Q) of the filter and updates the coefficients.
    // ES: Establece el factor de calidad (Q) del filtro y actualiza los coeficientes.
    void setQ(float inQ);

    // EN: Updates the filter's coefficients based on the frequency and Q values.
    // ES: Actualiza los coeficientes del filtro según los valores de frecuencia y Q.
    void updateFilter();

private:
    // EN: The sample rate of the audio processing.
    // ES: La frecuencia de muestreo del procesamiento de audio.
    double sampleRate{ 0.0f };

    // EN: Arrays for storing the input and output samples for the filter's delay line.
    // ES: Arreglos para almacenar las muestras de entrada y salida de la línea de retardo del filtro.
    float x1[2] = { 0.0f }; // EN: Previous input sample for the current and previous channels.
    float x2[2] = { 0.0f }; // EN: Input sample before x1 for the current and previous channels.
    float y1[2] = { 0.0f }; // EN: Previous output sample for the current and previous channels.
    float y2[2] = { 0.0f }; // EN: Output sample before y1 for the current and previous channels.

    // EN: Angular frequency (w0) and alpha values used in the filter equation.
    // ES: Frecuencia angular (w0) y valores de alpha usados en la ecuación del filtro.
    float w0{ 0.0f }; // EN: Normalized angular frequency.
    float alpha{ 0.0f }; // EN: Alpha value, controlling the filter's bandwidth.

    // EN: Filter coefficients used in the difference equation for the band-pass filter.
    // ES: Coeficientes del filtro usados en la ecuación diferencial para el filtro de paso banda.
    float b0{ 0.0f }; // EN: Numerator coefficient for the current filter stage.
    float b1{ 0.0f }; // EN: Numerator coefficient for the previous stage.
    float b2{ 0.0f }; // EN: Numerator coefficient for the stage before the previous one.
    float a0{ 0.0f }; // EN: Denominator coefficient for the current filter stage.
    float a1{ 0.0f }; // EN: Denominator coefficient for the previous stage.
    float a2{ 0.0f }; // EN: Denominator coefficient for the stage before the previous one.

    // EN: The center frequency of the band-pass filter, typically set between 20Hz and 20kHz.
    // ES: La frecuencia central del filtro de paso banda, generalmente establecida entre 20Hz y 20kHz.
    float frequency{ 1000.0f }; // EN: Default center frequency in Hz.

    // EN: The quality factor (Q) of the filter, typically between 0.1 and 10.0.
    // ES: El factor de calidad (Q) del filtro, generalmente entre 0.1 y 10.0.
    float Q{ 0.707f }; // EN: Default quality factor value (Q).
};