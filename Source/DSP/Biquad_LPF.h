/*
  ==============================================================================

    Biquad_LPF.h
    Created: 1 Oct 2024 12:17:44pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once  // EN: Ensures that this header file is included only once in the compilation process.
              // ES: Asegura que este archivo de encabezado se incluya solo una vez en el proceso de compilación.   

#include "JuceHeader.h"  // EN: Includes the JUCE library, which provides necessary classes for audio and DSP.
                         // ES: Incluye la biblioteca JUCE, que proporciona las clases necesarias para audio y DSP.

class Biquad_LPF  // EN: Class declaration for a Low Pass Filter (LPF) using a biquad filter structure.
                  // ES: Declaración de la clase para un filtro pasa bajos (LPF) utilizando una estructura de filtro biquad.
{
public:
    Biquad_LPF();  // EN: Constructor for the Biquad_LPF class. Initializes filter state variables.
                   // ES: Constructor para la clase Biquad_LPF. Inicializa las variables de estado del filtro.
    ~Biquad_LPF();  // EN: Destructor for the Biquad_LPF class. Can be used for cleanup if needed.
                    // ES: Destructor para la clase Biquad_LPF. Se puede utilizar para limpieza si es necesario.

    void prepare(double inSampleRate);  // EN: Prepares the filter for processing by setting the sample rate.
                                        // ES: Prepara el filtro para el procesamiento estableciendo la frecuencia de muestreo.

    void process(juce::AudioBuffer<float> inBuffer);  // EN: Processes an entire audio buffer, applying the LPF to each sample.
                                                      // ES: Procesa todo el buffer de audio, aplicando el LPF a cada muestra.
    float processSample(float inSample, int channel);  // EN: Processes a single sample for a specific channel.
                                                       // ES: Procesa una sola muestra para un canal específico.

    void setFrequency(float inFrequency);  // EN: Sets the cutoff frequency of the LPF.
                                           // ES: Establece la frecuencia de corte del LPF.
    void setQ(float inQ);  // EN: Sets the Q factor of the LPF, controlling the filter's resonance.
                           // ES: Establece el factor Q del LPF, controlando la resonancia del filtro.

    void updateFilter();  // EN: Updates the filter coefficients based on the current frequency and Q values.
                          // ES: Actualiza los coeficientes del filtro en función de los valores actuales de frecuencia y Q.

private:
    double sampleRate{ 0.0f };  // EN: The sample rate of the audio to be processed. Initialized to 0.0f.
                                // ES: La frecuencia de muestreo del audio a procesar. Inicializado a 0.0f.

        // EN: Arrays to hold the previous input and output samples for each channel (used for the filter state).
        //     These are the delay lines for the biquad filter.
        // ES: Arreglos para almacenar las muestras de entrada y salida anteriores para cada canal (utilizados para el estado del filtro).
        //     Estas son las líneas de retardo para el filtro biquad.
    float x1[2] = { 0.0f };  // EN: Input sample delay line 1 for each channel.
                             // ES: Línea de retardo de muestra de entrada 1 para cada canal.
    float x2[2] = { 0.0f };  // EN: Input sample delay line 2 for each channel.
                             // ES: Línea de retardo de muestra de entrada 2 para cada canal.
    float y1[2] = { 0.0f };  // EN: Output sample delay line 1 for each channel.
                             // ES: Línea de retardo de muestra de salida 1 para cada canal.
    float y2[2] = { 0.0f };  // EN: Output sample delay line 2 for each channel.
                             // ES: Línea de retardo de muestra de salida 2 para cada canal.

        // EN: Internal variables to store the calculated filter coefficients (b0, b1, b2 for the numerator;
        //     a0, a1, a2 for the denominator).
        //     These coefficients define the behavior of the LPF.
        // ES: Variables internas para almacenar los coeficientes calculados del filtro (b0, b1, b2 para el numerador;
        //     a0, a1, a2 para el denominador).
        //     Estos coeficientes definen el comportamiento del LPF.
    float w0{ 0.0f };  // EN: Angular frequency, calculated from the sample rate and cutoff frequency.
                       // ES: Frecuencia angular, calculada a partir de la frecuencia de muestreo y la frecuencia de corte.
    float alpha{ 0.0f };  // EN: The "alpha" value that controls the bandwidth of the filter, related to the Q factor.
                          // ES: El valor "alpha" que controla el ancho de banda del filtro, relacionado con el factor Q.

        // EN: Filter coefficients for the LPF in the form of a biquad filter.
        //     These coefficients are calculated based on the frequency, Q, and other filter parameters.
        // ES: Coeficientes del filtro para el LPF en la forma de un filtro biquad.
        //     Estos coeficientes se calculan en función de la frecuencia, Q y otros parámetros del filtro.
    float b0{ 0.0f };  // EN: Numerator coefficient for the LPF filter.
                       // ES: Coeficiente del numerador para el filtro LPF.
    float b1{ 0.0f };  // EN: Numerator coefficient for the LPF filter.
                       // ES: Coeficiente del numerador para el filtro LPF.
    float b2{ 0.0f };  // EN: Numerator coefficient for the LPF filter.
                       // ES: Coeficiente del numerador para el filtro LPF.

    float a0{ 0.0f };  // EN: Denominator coefficient for the LPF filter.
                       // ES: Coeficiente del denominador para el filtro LPF.
    float a1{ 0.0f };  // EN: Denominator coefficient for the LPF filter.
                       // ES: Coeficiente del denominador para el filtro LPF.
    float a2{ 0.0f };  // EN: Denominator coefficient for the LPF filter.
                       // ES: Coeficiente del denominador para el filtro LPF.

    float frequency{ 1000.0f };  // EN: The cutoff frequency of the LPF (in Hz), initialized to 1000 Hz.
                                 // ES: La frecuencia de corte del LPF (en Hz), inicializada a 1000 Hz.
    float Q{ 0.707f };  // EN: The quality factor (Q) of the filter, controlling the sharpness of the cutoff.
                        // ES: El factor de calidad (Q) del filtro, controlando la agudeza de la corte.
};
