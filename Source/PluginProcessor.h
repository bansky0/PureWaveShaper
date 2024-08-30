/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DSP/Input.h"
#include "DSP/Pan.h"
#include "DSP/Pan_linear.h"
#include "DSP/Pan_sqrt.h"
#include "DSP/Pan_sineLaw.h"
#include "DSP/Pan_sqrt_modified.h"
#include "DSP/Pan_sineLaw_modified.h"
#include "DSP/LFO.h"
#include "DSP/AmpModulation.h"
#include "DSP/SineWave.h"
#include "DSP/SquareWave.h"
#include "DSP/TriangleWave.h"
#include "DSP/SawtoothWave.h"
#include "DSP/MorphLFO.h"
#include "DSP/MorphWave.h"
#include "DSP/AutoPan.h"

//==============================================================================
/**
*/
class PureWaveShaperAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    PureWaveShaperAudioProcessor();
    ~PureWaveShaperAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    void updateParameters();

private:
    //==============================================================================
    Input input;
    Pan pan;
    PanLinear panLinear;
    PanSqrt panSqrt;
    PanSineLaw panSineLaw;
    PanSqrtModidied panSqrtModified;
    PanSineLawModified panSineLawModified;
    LFO lfo;
    bool lfoState{ false };
    AmpModulation ampModulation;
    bool ampModulationState{ false };
    SineWave sineWave;
    SquareWave squareWave;
    TriangleWave triangleWave;
    SawtoothWave sawtoothWave;
    MorphLfo morphLFO;
    MorphWave morphWave;
    AutoPan autoPan;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PureWaveShaperAudioProcessor)
};
