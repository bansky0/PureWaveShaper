/*
  ==============================================================================

    FIR_LPF2.cpp
    Created: 28 Sep 2024 9:39:51pm
    Author:  Jhonatan López

  ==============================================================================
*/

#include "FIR_LPF2.h"

// EN: Constructor for FIR_LPF2 class. Initializes the filter with default values.
// ES: Constructor para la clase FIR_LPF2. Inicializa el filtro con valores predeterminados.
FIR_LPF2::FIR_LPF2()
{
}

// EN: Destructor for FIR_LPF2 class. Cleans up any resources when the filter is no longer needed.
// ES: Destructor para la clase FIR_LPF2. Limpia los recursos cuando el filtro ya no es necesario.
FIR_LPF2::~FIR_LPF2()
{
}

// EN: Prepares the filter by setting up the sample rate, block size, and number of channels.
//     This is done before processing the audio data to set up the necessary configurations.
void FIR_LPF2::prepare(double inSampleRate, int inSamplesPerBlock, int inChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = inSampleRate;  // Set the sample rate
    spec.maximumBlockSize = inSamplesPerBlock; // Set the maximum number of samples per block
    spec.numChannels = inChannels; // Set the number of channels (e.g., stereo or mono)

    sampleRate = inSampleRate; // Store the sample rate for later use

    // Prepares the filter with the given process specifications
    lowPassFilter.prepare(spec);
    //lowPassFilter2.prepare(spec); // Prepare for the second filter (unnecessary if not used)

    updateFilter();  // Initialize the filter with the default cutoff frequency
}

// EN: Processes the audio buffer by applying the low-pass filter to the audio data for each channel.
//     The filter is applied only to the left and right channels, based on the buffer's channels.
void FIR_LPF2::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);  // Creates a DSP audio block from the buffer

    // EN: Process the right channel if it exists (channel 1 in stereo)
    // ES: Procesa el canal derecho si existe (canal 1 en estéreo)
    if (block.getNumChannels() > 1)
    {
        // Get the audio block for the right channel (index 1)
        auto channelBlock = block.getSingleChannelBlock(1);

        // Apply the low-pass filter to the right channel
        juce::dsp::ProcessContextReplacing<float> context(channelBlock);
        lowPassFilter.process(context);
    }

    // EN: Process the left channel if it exists (channel 0 in stereo)
    // ES: Procesa el canal izquierdo si existe (canal 0 en estéreo)
    if (block.getNumChannels() > 0)
    {
        // Get the audio block for the left channel (index 0)
        auto channelBlock = block.getSingleChannelBlock(0);

        // Apply the low-pass filter to the left channel
        juce::dsp::ProcessContextReplacing<float> context(channelBlock);
        lowPassFilter2.process(context);  // This filter is used for the left channel
    }
}

// EN: Updates the cutoff frequency for the filter and recalculates the filter coefficients.
//     This method is used to change the behavior of the filter dynamically.
void FIR_LPF2::setCutoffFrequency(float frequency)
{
    cutoffFrequency = frequency;  // Update the cutoff frequency with the new value
    updateFilter();  // Recalculate the filter coefficients based on the new cutoff
}

// EN: This method updates the filter coefficients using the Kaiser window method for low-pass FIR filter design.
//     It designs a filter with the current cutoff frequency and sample rate.
// ES: Este método actualiza los coeficientes del filtro utilizando el método de ventana Kaiser para el diseño de un filtro FIR de paso bajo.
//     Diseña un filtro con la frecuencia de corte y la frecuencia de muestreo actuales.
void FIR_LPF2::updateFilter()
{
    // EN: Designs the FIR low-pass filter coefficients using the Kaiser method with adjustable parameters.
    // ES: Diseña los coeficientes del filtro FIR de paso bajo utilizando el método de Kaiser con parámetros ajustables.
    auto coefficients = juce::dsp::FilterDesign<float>::designFIRLowpassTransitionMethod(
        cutoffFrequency,   // Set the cutoff frequency
        sampleRate,        // Set the sample rate
        125,               // Number of coefficients (order of the filter); adjust as needed
        0.4, 4.0);         // Kaiser window parameters (beta for the window)

    // EN: Assign the calculated coefficients to both filter instances.
    // ES: Asigna los coeficientes calculados a ambas instancias del filtro.
    lowPassFilter.coefficients = coefficients;
    lowPassFilter2.coefficients = coefficients;
}
