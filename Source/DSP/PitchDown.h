/*
  ==============================================================================

    PitchDown.h
    Created: 5 Nov 2024 1:03:19pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// EN: The PitchDown class implements a pitch-shifting effect that lowers the pitch of an audio signal
//     by manipulating the playback speed and introducing fractional delays.
// ES: La clase PitchDown implementa un efecto de cambio de tono que reduce el tono de una señal de audio
//     manipulando la velocidad de reproducción e introduciendo retardos fraccionarios.

class PitchDown
{
public:
    // EN: Constructor for the PitchDown class.
    //     Initializes the object without additional setup.
    // ES: Constructor para la clase PitchDown.
    //     Inicializa el objeto sin configuraciones adicionales.
    PitchDown() {}

    // EN: Destructor for the PitchDown class.
    //     Cleans up resources if necessary (no resources are dynamically allocated here).
    // ES: Destructor para la clase PitchDown.
    //     Libera recursos si es necesario (aquí no se asignan recursos dinámicos).
    ~PitchDown() {}

    // EN: Prepares the pitch-shifting effect by setting up the sample rate.
    //     The sample rate is used to calculate delays and manage the circular buffer.
    // ES: Prepara el efecto de cambio de tono configurando la frecuencia de muestreo.
    //     La frecuencia de muestreo se usa para calcular retardos y gestionar el búfer circular.
    void prepare(double sampleRate);

    // EN: Processes the input audio buffer to apply the pitch-down effect.
    //     This modifies the buffer in place by altering the playback with fractional delays.
    // ES: Procesa el búfer de audio de entrada para aplicar el efecto de tono descendente.
    //     Esto modifica el búfer directamente, alterando la reproducción con retardos fraccionarios.
    void process(juce::AudioBuffer<float>& buffer);

private:
    // EN: The sample rate of the audio being processed.
    // ES: La frecuencia de muestreo del audio que se está procesando.
    float sampleRate;

    // EN: Fractional delay used for pitch-shifting calculations.
    // ES: Retardo fraccionario utilizado para los cálculos de cambio de tono.
    float delay;

    // EN: Size of the circular buffer, defined for 2 seconds of audio at a 48kHz sample rate.
    // ES: Tamaño del búfer circular, definido para 2 segundos de audio a una frecuencia de 48kHz.
    static const int bufferSize = 48000 * 2;

    // EN: Circular buffer used to store past audio samples for delay-based processing.
    // ES: Búfer circular utilizado para almacenar muestras de audio pasadas para el procesamiento basado en retardos.
    float delayBuffer[bufferSize];

    // EN: Write pointer for the circular buffer, indicating the current position for writing samples.
    // ES: Puntero de escritura para el búfer circular, que indica la posición actual para escribir muestras.
    int writePosition = 0;

    // EN: Variable for tracking time in the processing function, used for delay calculations.
    // ES: Variable para rastrear el tiempo en la función de procesamiento, utilizada para cálculos de retardo.
    float t;
};