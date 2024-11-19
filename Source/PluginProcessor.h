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
#include "DSP/Convolution.h"
#include "DSP/FIR_LPF.h"
#include "DSP/FIR_LPF2.h"
#include "DSP/IIR_HPF.h"
#include "DSP/IIR_APF.h"
#include "DSP/IIR_LPF.h"
#include "DSP/IIR_LSF.h"
#include "DSP/IIR_BPF.h"
#include "DSP/IIR_Notch.h"
#include "DSP/IIR_PeakFilter.h"
#include "DSP/IIR_FirstOrderLPF.h"
#include "DSP/IIR_FirstOrderHPF.h"
#include "DSP/IIR_FirstOrderAPF.h"
#include "DSP/Biquad_APF.h"
#include "DSP/Biquad_BPF.h"
#include "DSP/Biquad_BPF2.h"
#include "DSP/Biquad_HPF.h"
#include "DSP/Biquad_HSF.h"
#include "DSP/Biquad_LPF.h"
#include "DSP/Biquad_LSF.h"
#include "DSP/Biquad_Notch.h"
#include "DSP/Biquad_Peaking.h"
#include "DSP/DirectFormII_APF.h"
#include "DSP/DirectFormII_NestedAPF.h"
#include "DSP/Biquad_II_LPF.h"
#include "DSP/Biquad_II_APF.h"
#include "DSP/Biquad_II_BPF.h"
#include "DSP/Biquad_II_HPF.h"
#include "DSP/Biquad_II_HSF.h"
#include "DSP/Biquad_II_LSF.h"
#include "DSP/Biquad_II_Notch.h"
#include "DSP/Biquad_II_Peaking.h"
#include "DSP/Biquad_TDFII_LPF.h"
#include "DSP/Biquad_TDFII_APF.h"
#include "DSP/Biquad_TDFII_BPF.h"
#include "DSP/Biquad_TDFII_HPF.h"
#include "DSP/Biquad_TDFII_HSF.h"
#include "DSP/Biquad_TDFII_LSF.h"
#include "DSP/Biquad_TDFII_Notch.h"
#include "DSP/Biquad_TDFII_Peaking.h"
#include "DSP/SlewRateDistortion.h"
#include "DSP/VibratoEffectExample.h"
#include "DSP/VibratoEffect.h"
#include "DSP/ChorusEffect.h"
#include "DSP/FlangerEffect.h"
#include "DSP/FeedbackFlangerEffect.h"
#include "DSP/BarberPoleFlangerEffect.h"
#include "DSP/BarberPoleFlangerEffect2.h"
#include "DSP/PitchDown.h"
#include "DSP/PitchUp.h"
#include "DSP/PitchShifter.h"
#include "DSP/ModulatedDelay.h"
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
    Convolution convolution;
    FIR_LPF firLpf;
    FIR_LPF2 firLpf2;
    IIR_HPF iirHpf;
    IIR_APF iirApf;
    IIR_LPF iirLpf;
    IIR_LSF iirLsf;
    IIR_BPF iirBpf;
    IIR_Notch iirNotch;
    IIR_PeakF iirPeak;
    IIRFirstOrderLPF iirFoLpf;
    IIRFirstOrderHPF iirFoHpf;
    IIRFirstOrderAPF iirFoApf;
    Biquad_APF biquadApf;
    Biquad_BPF biquadBpf;
    Biquad_BPF2 biquadBpf2;
    Biquad_HPF biquadHpf;
    Biquad_HSF biquadHsf;
    Biquad_LPF biquadLpf;
    Biquad_LSF biquadLsf;
    Biquad_Notch biquadNotch;
    Biquad_Peaking biquadPeaking;
    DirectFormII_APF dfApf;
    DirectFormII_NestedAPF dfNApf;
    Biquad_II_LPF biquadIILpf;
    Biquad_II_APF biquadIIApf;
    Biquad_II_BPF biquadIIBpf;
    Biquad_II_HPF biquadIIHpf;
    Biquad_II_HSF biquadIIHsf;
    Biquad_II_LSF biquadIILsf;
    Biquad_II_Notch biquadIINotch;
    Biquad_II_Peaking biquadIIPeaking;
    Biquad_TDFII_LPF biquadTDFIILpf;
    Biquad_TDFII_APF biquadTDFIIApf;
    Biquad_TDFII_BPF biquadTDFIIBpf;
    Biquad_TDFII_HPF biquadTDFIIHpf;
    Biquad_TDFII_HSF biquadTDFIIHsf;
    Biquad_TDFII_LSF biquadTDFIILsf;
    Biquad_TDFII_Notch biquadTDFIINotch;
    Biquad_TDFII_Peaking biquadTDFIIPeaking;
    SlewRateDistortion slewRateDisto;
    VibratoEffect vibratoExample;
    VibratoFX vibratoEffect;
    ChorusFX chorusEffect;
    FlangerFX flangerEffect;
    FeedbackFlangerFX feedbackFlangerEffect;
    BarberpoleFlangerFX barberpoleFlangerEffect;
    BarberpoleFlanger2FX barberpoleFlangerEffect2;
    PitchDown pitchDown;
    PitchUp pitchUp;
    PitchShift pitchShifter;
    ModulatedDelay modulatedDelay;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PureWaveShaperAudioProcessor)
};
