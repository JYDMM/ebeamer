#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "vAudioParts.h"
#include "vFIR.h"

#define FIR_LEN 512
#define NUM_BEAMS 2
#define METERS_DECAY 0.15 //s
#define BEAMSTEERING_ALG_IDEAL


//==============================================================================

class JucebeamAudioProcessor  : public AudioProcessor
{
public:

//==============================================================================
    JucebeamAudioProcessor();
    ~JucebeamAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    // Meters
    float getBeamMeter(int channel);
    std::vector<float> getInputMeters();
    
    //==============================================================================
    // VST parameters
    AudioParameterFloat* steeringBeam[NUM_BEAMS];
    AudioParameterFloat* widthBeam[NUM_BEAMS];
    AudioParameterFloat* panBeam[NUM_BEAMS];
    AudioParameterFloat* levelBeam[NUM_BEAMS];
    AudioParameterBool*  muteBeam[NUM_BEAMS];
    AudioParameterFloat* micGain;
    AudioParameterFloat* hpfFreq;
    
    //==============================================================================
    // FFT
    const int getFftSize(){ return fft->getSize();}
    
    //==============================================================================
    // Buffers
    AudioBuffer<float> fftInput;
    bool newFftInputDataAvailable = false;
    SpinLock fftInputLock;
    
    //==============================================================================
    // DOA
    std::vector<std::vector<std::vector<float>>> firSteeringFFT;
    
    
    //==============================================================================
    // Meters
    std::vector<float> inputMeters;
    std::vector<float> beamMeters;
    SpinLock inputMetersLock;
    SpinLock beamMetersLock;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JucebeamAudioProcessor)
    
    //==============================================================================
    // FFT
    std::unique_ptr<dsp::FFT> fft;
    
    //==============================================================================
    // Meters
    std::unique_ptr<MeterDecay> inputMeterDecay;
    std::unique_ptr<MeterDecay> beamMeterDecay;
    
    //==============================================================================
    std::vector<std::vector<std::vector<float>>> prepareIR(const std::vector<std::vector<std::vector<float>>> fir);
    // FIR filters, ready for convolution
    std::vector<std::vector<std::vector<float>>> firBeamwidthFFT;
    
    //==============================================================================
    // Buffers
    AudioBuffer<float> beamsBuffer;
    AudioBuffer<float> fftBuffer;
    AudioBuffer<float> fftOutput;
    
    //==============================================================================
    // HPF filters
    float prevHpfFreq = 0;
    IIRCoefficients iirCoeffHPF;
    std::vector<std::unique_ptr<IIRFilter>> iirHPFfilters;

    //==============================================================================
    // Gains
    dsp::Gain<float> commonGain, beamGain[NUM_BEAMS];
    
};
