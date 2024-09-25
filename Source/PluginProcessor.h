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
#include "DSP/SineWave2.h"
#include "DSP/SquareWave2.h"
#include "DSP/TriangleWave2.h"
#include "DSP/SawtoothWave2.h"
#include "DSP/MorphLFO.h"
#include "DSP/MorphWave.h"
#include "DSP/AutoPan.h"
#include "DSP/MidSide.h"
#include "DSP/StereoImager.h"
#include "DSP/Infiniteclip.h"
#include "DSP/HalfWaveRectification.h"
#include "DSP/FullWaveRectification.h"
#include "DSP/HardClip.h"
#include "DSP/CubicDistortion.h"
#include "DSP/ArctangentDistortion.h"
#include "DSP/SineDistortion.h"
#include "DSP/ExponentialDistortion.h"
#include "DSP/PiceWiseOverdrive.h"
#include "DSP/DiodeClipping.h"
#include "DSP/BitReduction.h"
#include "DSP/AsymetricalDistortion.h"
#include "DSP/WetDry.h"
#include "DSP/DutyCicleWave.h"
#include "DSP/ImpulseTrain.h"
#include "DSP/WhiteNoise.h"
#include "DSP/Addition.h"
#include "DSP/Subtraction.h"
#include "DSP/RingModulation.h"
#include "DSP/SimpleDelay.h"
#include "DSP/SimpleDelay2.h"
#include "DSP/SimpleDelay3.h"
#include "DSP/EchoFeedBackAndFordward.h"
#include "DSP/EchoFeedBackAndFordward2.h"
#include "DSP/EchoStereo.h"
#include "DSP/PingPongEcho.h"

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
    SineWave2 sineWave;
    SquareWave2 squareWave;
    TriangleWave2 triangleWave;
    SawtoothWave2 sawtoothWave;
    MorphLfo morphLFO;
    MorphWave morphWave;
    AutoPan autoPan;
    MidSide midSide;
    bool midSideState{ false };
    StereoImager stereoImager;
    InfiniteClip infinitClip;
    HalfWaveRectification halfWaveRectification;
    FullWaveRectification fullWaveRectification;
    HardClip hardClip;
    CubicDistortion cubicDistortion;
    ArctangentDistortion arctangenteDistortion;
    SineDistortion sineDistortion;
    ExponentialDistortion exponentialDistortion;
    PiceWiseOverdrive piceWiseOverdrive;
    DiodeClipping diodeClipping;
    BitReduction numberBitReduction;
    AsymetricalDistortion asymetricalDistortion;
    WetDry wetDry;
    juce::AudioBuffer<float> dryBuffer;
    DutyCicleWave dutyCicleWave;
    ImpulseTrain impulseTrain;
    WhiteNoise whiteNoise;
    AdditiveSynth additiveSynth;
    Subtraction subtractionSynth;
    RingModulation ringModulation;
    SimpleDelay simpleDelay;
    SimpleDelay2 simpleDelay2;
    SimpleDelay3 simpleDelay3;
    EchoFBF echoFBF;
    EchoFBF2 echoFBF2;
    EchoStereo echoStereo;
    PingPongEcho pingPongEcho;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PureWaveShaperAudioProcessor)
};
