/*
  ==============================================================================

    PingPongEcho.h
    Created: 24 Sep 2024 10:48:08am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// Clase para el efecto de PingPong Echo
// ES: Esta clase implementa un efecto de eco PingPong, utilizando dos buffers circulares 
// para generar los ecos en diferentes canales con retardo y ganancia.
class PingPongEcho
{
public:
    // Setters para los parámetros de BPM y ganancia
    // ES: Establece el tempo en BPM para los dos canales de entrada.
    // EN: Sets the BPM for both input channels.
    void setBPM(float BPM1, float BPM2);

    // Setters para las ganancias de los canales de eco
    // ES: Establece las ganancias para los dos canales del efecto PingPong.
    // EN: Sets the gains for both channels of the PingPong effect.
    void setGains(float gain1, float gain2);

    // Función para preparar el procesador con la tasa de muestreo y el número de canales
    // ES: Configura los buffers de audio y la tasa de muestreo para el procesamiento.
    // EN: Prepares the processor with the sample rate and number of channels.
    void prepare(double theSampleRate, int inTotalChannels);

    // Función de procesamiento de audio, aplica el eco PingPong a los buffers de entrada.
    // ES: Aplica el efecto de eco PingPong al buffer de audio. Usa dos canales con diferentes retardos.
    // EN: Processes the audio buffer, applies the PingPong echo effect using two channels with different delays.
    void process(juce::AudioBuffer<float>& buffer);

    // Constructor de la clase PingPongEcho
    // ES: Inicializa una nueva instancia del efecto PingPong Echo.
    // EN: Initializes a new instance of the PingPong Echo effect.
    PingPongEcho();

    // Destructor de la clase PingPongEcho
    // ES: Libera los recursos asociados con la instancia de PingPongEcho.
    // EN: Releases the resources associated with the PingPongEcho instance.
    ~PingPongEcho();

private:
    // Variables de retardo (delay)
    // ES: Retardo en muestras para el primer canal de eco.
    // EG: Delay in samples for the first echo channel.
    int delay1Samples = 48000; // Retardo para la entrada1 (en muestras)

    // ES: Retardo en muestras para el segundo canal de eco.
    // EG: Delay in samples for the second echo channel.
    int delay2Samples = 48000; // Retardo para la entrada2 (en muestras)

    // Tamaño del buffer circular para los retrasos de entrada y salida
    // ES: Define el tamaño del buffer circular. Puede ajustarse según las necesidades del proyecto.
    // EG: Defines the size of the circular buffer. It can be adjusted based on project needs.
    const int circularBufferSize = 96000;  // Tamaño del buffer circular, ajustable según necesidades

    // ES: Número de canales a procesar. Por defecto es 2 (estéreo).
    // EG: Number of channels to process. By default, it's 2 (stereo).
    int numChannels = 2;  // Número de canales para el procesamiento (por defecto 2)

    // Buffers circulares para manejar las entradas y salidas
    // ES: Buffer que contiene las muestras de entrada para el primer canal.
    // EG: Buffer holding the input samples for the first channel.
    std::vector<std::vector<float>> circularBufferInput1;  // Buffer para el primer canal (entrada)

    // ES: Buffer que contiene las muestras de entrada para el segundo canal.
    // EG: Buffer holding the input samples for the second channel.
    std::vector<std::vector<float>> circularBufferInput2; // Buffer para el segundo canal (salida)

    // Punteros de escritura para las muestras dentro de los buffers
    // ES: Puntero de escritura para la entrada1, controla dónde se escriben las muestras en circularBufferInput1.
    // EG: Write pointer for input1, controls where the samples are written in circularBufferInput1.
    std::vector<int> writterPointerInput1{ numChannels, 0 };  // Puntero de escritura para la entrada1

    // ES: Puntero de escritura para la entrada2, controla dónde se escriben las muestras en circularBufferInput2.
    // EG: Write pointer for input2, controls where the samples are written in circularBufferInput2.
    std::vector<int> writterPointerInput2{ numChannels, 0 }; // Puntero de escritura para la entrada2

    // Parámetros del efecto de delay
    // ES: Tasa de muestreo del audio. 48 kHz por defecto.
    // EG: Audio sample rate. Default is 48 kHz.
    double sampleRate = 48000.0;  // Tasa de muestreo del audio (por defecto 48 kHz)

    // ES: Ganancia aplicada al primer canal de eco.
    // EG: Gain applied to the first echo channel.
    float gain1 = 0.75f;          // Ganancia del primer canal de eco

    // ES: Ganancia aplicada al segundo canal de eco.
    // EG: Gain applied to the second echo channel.
    float gain2 = 0.75f;          // Ganancia del segundo canal de eco

    // ES: Feedback (retroalimentación) aplicado al primer canal de eco.
    // EG: Feedback applied to the first echo channel.
    float fb1 = 0.75f;            // Feedback del primer canal de eco

    // ES: Feedback (retroalimentación) aplicado al segundo canal de eco.
    // EG: Feedback applied to the second echo channel.
    float fb2 = 0.75f;            // Feedback del segundo canal de eco
};