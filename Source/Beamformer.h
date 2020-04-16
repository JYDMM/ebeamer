/*
 ==============================================================================
 
 Beamformer.h
 Created: 14 Apr 2020 9:12:12am
 Author:  Luca Bondi
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "BeamformingAlgorithm.h"
#include "FIR.h"
#include "DAS.h"

/** Available configurations */
typedef enum {
    LMA_1ESTICK,
    LMA_2ESTICK,
    LMA_3ESTICK,
    LMA_4ESTICK,
} MicConfig;

class Beamformer{
    
public:
    
    
    /** Initialize the Beamformer with a set of static parameters.
     @param numBeams: number of beams the beamformer has to compute
     @param numDoas: number of directions of arrival to compute the energy
     */
    Beamformer(const AudioProcessor& p, int numBeams, int numDoas);
    /** Destructor. */
    ~Beamformer();
    
    /** Set microphone configuration */
    void setMicConfig(MicConfig micConfig_);
    
    /** Get microphone configuration */
    MicConfig getMicConfig() const;
    
    /** Set the parameters before execution.
     
     To be called inside AudioProcessor::prepareToPlay.
     This method allocates the needed buffers and performs the necessary pre-calculations that are dependent
     on sample rate, buffer size and channel configurations.
     */
    void prepareToPlay(double sampleRate_, int maximumExpectedSamplesPerBlock_, int numActiveInputChannels);
    
    /** Process a new block of samples.
     
     To be called inside AudioProcessor::processBlock.
     */
    void processBlock(const AudioBuffer<float>& inBuffer);
    
    /** Copy the current beams outputs to the provided output buffer
     
     To be called inside AudioProcessor::processBlock, after Beamformer::processBlock
     */
    void getBeams(AudioBuffer<float>& outBuffer);
    
    /** Set the parameters for a specific beam  */
    void setBeamParameters(int beamIdx, const BeamParameters& beamParams);
    
    /** Copy the estimated energy contribution from the directions of arrival */
    void getDoaEnergy(std::vector<float>& energy);
    
    /** Release not needed resources.
     
     To be called inside AudioProcessor::releaseResources.
     */
    void releaseResources();
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Beamformer);
    
    /** Sound speed [m/s] */
    const float soundspeed = 343;
    
    /** Sample rate [Hz] */
    float sampleRate = 48000;
    
    /** Maximum buffer size [samples] */
    int maximumExpectedSamplesPerBlock = 64;
    
    /** Number of active inputs */
    int numActiveInputChannels = 1;
    
    /** Reference to the AudioProcessor instance */
    const AudioProcessor& processor;
    
    /** Number of beams */
    int numBeams;
    
    /** Number of directions of arrival */
    int numDoas;
    
    /** Beamforming algorithm */
    std::unique_ptr<BeamformingAlgorithm> alg;
    
    /** FIR filters length. Diepends on the algorithm */
    int firLen;
    
    /** Shared FFT pointer */
    std::shared_ptr<juce::dsp::FFT> fft;
    
    /** FIR filters for each beam */
    std::vector<AudioBuffer<float>> firIR;
    std::vector<FIR::AudioBufferFFT> firFFT;
    
    /** Inputs' buffer */
    FIR::AudioBufferFFT inputBuffer;
    
    /** Convolution buffer */
    FIR::AudioBufferFFT convolutionBuffer;
    
    /** Beams' outputs buffer */
    AudioBuffer<float> beamBuffer;
    
    /** FIR coefficients update alpha */
    const float alpha = 0.05;
    
    /** Microphones configuration */
    MicConfig micConfig = LMA_1ESTICK;
    
    /** Initialize the beamforming algorithm */
    void initAlg();

};
