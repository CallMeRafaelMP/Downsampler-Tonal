/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <string>
#include "Cadena_de_filtros.h"

//==============================================================================
/**
*/

class TFG_downsampler_tonalAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    TFG_downsampler_tonalAudioProcessor();
    ~TFG_downsampler_tonalAudioProcessor() override;

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

    void TFG_downsampler_tonalAudioProcessor::updateFilter();

    int reduction = 0;
    

private:
    
    //Filter_coef coef;
    //juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> filtro_tonal;
    
    //std::array<float, 42> coecoe = { 1, -15.8492159538637f, 122.351367159598f, -611.357894333868f, 2216.59374019232f, -6196.56853827436f, 13854.7758525907f, -25365.1748475631f, 38612.7842362582f, -49350.8791608823f, 53244.1895878305f, -48575.6186985437f, 37409.9421129122f, -24190.4763502635f, 13007.2136498455f, -5727.32172371532f, 2017.20300808036f, -547.874118297528f, 107.990651678778f, -13.7803494669367f, 0.85669156897217f, 0.925873066278378f, -14.7829009370079f, 114.97711440851f, -578.884552786441f, 2115.01323060649f, -5958.53542682315f, 13426.8534463372f, -24775.3090326161f, 38013.1523884785f, -48969.9385354845f, 53253.0567923232f, -48969.9385354845f, 38013.1523884785f, -24775.3090326161f, 13426.8534463372f, -5958.53542682315f, 2115.01323060649f, -578.884552786441f, 114.97711440851f, -14.7829009370079f, 0.925873066278378f };

    Cadena_de_filtros cadena;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TFG_downsampler_tonalAudioProcessor)
};

