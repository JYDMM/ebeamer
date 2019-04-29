/*
  ==============================================================================

    vFIR.h
    Created: 27 Apr 2019 9:45:28am
    Author:  Luca Bondi

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

namespace vFIR{
    // Convolution operations
    void readFIR(std::vector<AudioBuffer<float>>& firTimeSeries, const char* array,const int len);
    
    class AudioBufferFFT{
        
    private:
        AudioBuffer<float> buffer, convBuffer;
        std::shared_ptr<dsp::FFT> fft;
        bool readyForConvolution = false;
        float* getConvReady(int);
        static void prepareForConvolution (float *samples, int fftSize) noexcept;
        static void convolutionProcessingAndAccumulate (const float *input, const float *impulse, float *output, int fftSize);
        static void updateSymmetricFrequencyDomainData (float* samples, int fftSize) noexcept;
        void updateSymmetricFrequency();
        
    public:
        AudioBufferFFT(){};
        AudioBufferFFT(int numChannels,std::shared_ptr<dsp::FFT>&);
        AudioBufferFFT(const AudioBuffer<float>&,std::shared_ptr<dsp::FFT>&);
        void setTimeSeries(const AudioBuffer<float>&);
        
        void getTimeSeries(AudioBuffer<float>&);
        void addTimeSeries(AudioBuffer<float>&);
        void getTimeSeries(int sourceCh, AudioBuffer<float>& dest,int destCh);
        void addTimeSeries(int sourceCh, AudioBuffer<float>& dest,int destCh);
        void convolve(int outputChannel, const AudioBufferFFT& in_, int inChannel, AudioBufferFFT& filter_, int filterChannel );
        void prepareForConvolution();
        bool isReadyForConvolution() const {return readyForConvolution;};
        void copyFrom(int dstChannel, int dstStartSample, const AudioBufferFFT& inFFT, int inChannel, int inStartSample, size_t numSamples);
        
        
        size_t getNumSamples() const {return buffer.getNumSamples();};
        size_t getNumChannels() const {return buffer.getNumChannels();};
        
    };

    
}

