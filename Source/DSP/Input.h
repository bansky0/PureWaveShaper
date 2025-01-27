/*
  ==============================================================================

    Input.h
    Created: 19 Aug 2024 3:53:03pm
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// ES: Clase Input que representa un módulo para manipular un valor de entrada en un buffer de audio.
// EN: Input class representing a module to manipulate an input value in an audio buffer.
class Input
{
public:
    // ES: Constructor de la clase Input.
    // EN: Constructor for the Input class.
    Input();

    // ES: Destructor de la clase Input.
    // EN: Destructor for the Input class.
    ~Input();

    // ES: Método para establecer un valor de entrada. Este método es útil para sincronizar el valor
    // con un controlador o interfaz de usuario mediante updateParameters().
    // EN: Method to set an input value. This method is useful for synchronizing the value
    // with a controller or user interface using updateParameters().
    void setInputValue(float inInputValue);

    // ES: Método para procesar un buffer de audio. Modifica el contenido del buffer basado en el valor de entrada.
    // EN: Method to process an audio buffer. Modifies the buffer content based on the input value.
    void process(juce::AudioBuffer<float>& buffer);

private:
    // ES: Valor de entrada utilizado para modificar el buffer de audio.
    // Inicializado a 0.0f.
    // EN: Input value used to modify the audio buffer.
    // Initialized to 0.0f.
    float inputValue{ 0.0f };
};

