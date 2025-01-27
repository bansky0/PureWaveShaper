/*
  ==============================================================================

    DirectFormII_APF.h
    Created: 2 Oct 2024 11:20:47am
    Author:  Jhonatan López

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// EN: This class implements a Direct Form II All-Pass Filter (APF) for processing audio.
// ES: Esta clase implementa un filtro pasa todo en forma directa II (APF) para procesar audio.
class DirectFormII_APF
{
public:
    // EN: Constructor - Initializes the APF with default settings.
    // ES: Constructor - Inicializa el APF con configuraciones predeterminadas.
    DirectFormII_APF();

    // EN: Destructor - Cleans up any resources used by the APF.
    // ES: Destructor - Libera cualquier recurso utilizado por el APF.
    ~DirectFormII_APF();

    // EN: Processes an entire audio buffer through the APF.
    // ES: Procesa un buffer completo de audio a través del APF.
    void process(juce::AudioBuffer<float>& inBuffer);

    // EN: Processes a single sample through the APF for a specific channel.
    // ES: Procesa una muestra individual a través del APF para un canal específico.
    float processSample(float inSample, int channel);

    // EN: Sets the gain coefficient (g) for the APF.
    // ES: Establece el coeficiente de ganancia (g) para el APF.
    void setG(float inG);

private:
    // EN: Input delay buffer for each channel (previous input sample).
    // ES: Buffer de retardo de entrada para cada canal (muestra de entrada previa).
    float x1[2] = { 0.0f };

    // EN: Output delay buffer for each channel (previous output sample).
    // ES: Buffer de retardo de salida para cada canal (muestra de salida previa).
    float y1[2] = { 0.0f };

    // EN: Feedback/Feedforward coefficient for the APF.
    // ES: Coeficiente de realimentación y adelanto para el APF.
    float g{ 0.5f };
};

