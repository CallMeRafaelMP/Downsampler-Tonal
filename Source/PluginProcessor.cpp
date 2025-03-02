/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Cadena_de_filtros.h"


//==============================================================================
TFG_downsampler_tonalAudioProcessor::TFG_downsampler_tonalAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )//, filtro_tonal(new juce::dsp::IIR::Coefficients<float>(coecoe))//(0.925873066278378f, -14.7829009370079f, 114.97711440851f, -578.884552786441f, 2115.01323060649f, -5958.53542682315f, 13426.8534463372f, -24775.3090326161f, 38013.1523884785f, -48969.9385354845f, 53253.0567923232f, -48969.9385354845f, 38013.1523884785f, -24775.3090326161f, 13426.8534463372f, -5958.53542682315f, 2115.01323060649f, -578.884552786441f, 114.97711440851f, -14.7829009370079f, 0.925873066278378f, 1, -15.8492159538637f, 122.351367159598f, -611.357894333868f, 2216.59374019232f, -6196.56853827436f, 13854.7758525907f, -25365.1748475631f, 38612.7842362582f, -49350.8791608823f, 53244.1895878305f, -48575.6186985437f, 37409.9421129122f, -24190.4763502635f, 13007.2136498455f, -5727.32172371532f, 2017.20300808036f, -547.874118297528f, 107.990651678778f, -13.7803494669367f, 0.85669156897217f))//(juce::dsp::IIR::Coefficients < float >::Coefficients(coef.coeficients))//(coecoe))//makeLowPass(44100, 20000))//preguntar
#endif
{
}

TFG_downsampler_tonalAudioProcessor::~TFG_downsampler_tonalAudioProcessor()
{
}

//==============================================================================
const juce::String TFG_downsampler_tonalAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TFG_downsampler_tonalAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TFG_downsampler_tonalAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TFG_downsampler_tonalAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TFG_downsampler_tonalAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TFG_downsampler_tonalAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TFG_downsampler_tonalAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TFG_downsampler_tonalAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TFG_downsampler_tonalAudioProcessor::getProgramName (int index)
{
    return {};
}
 
void TFG_downsampler_tonalAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TFG_downsampler_tonalAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::dsp::ProcessSpec spec{};
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    //filtro_tonal.prepare(spec);
    //filtro_tonal.reset();
   /*
    float frequency1 = 300;
    float frequency2 = 3000;
    filters[0].coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, frequency1);
    filters[1].coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, frequency2);

    for (auto& filter : filters)
    {
        filter.prepare(spec);
        filter.reset();
    }
  */
    //preparamos la cadena de filtros
    for (auto& filter : cadena.filtersL)
    {
        filter.prepare(spec);
        filter.reset();
    }
    for (auto& filter : cadena.filtersR)
    {
        filter.prepare(spec);
        filter.reset();
    }
}

void TFG_downsampler_tonalAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TFG_downsampler_tonalAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

// /*
void TFG_downsampler_tonalAudioProcessor::updateFilter()
{
    //float srate = 44100;
    //float freq = 500;
    //*filtro_tonal.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(srate, freq);
    // Crear los coeficientes para el filtro
    //    auto coefficients = new juce::dsp::IIR::Coefficients<float>(0.8713, 0.8713, 0.7979, 1);
    
    //juce::dsp::IIR::Coefficients<float>::Ptr coeffs(new juce::dsp::IIR::Coefficients<float>(coecoe));
    
    // Establecer los coeficientes para el filtro en el ProcessorDuplicator
    //*filtro_tonal.state = *coeffs;
    
    //*filtro_tonal.state = juce::dsp::IIR::Coefficients<float>::Coefficients(coef.getcoef());
    //*filtro_tonal.state = ptrcoef;
}
// */

void TFG_downsampler_tonalAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

  
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        //downsampling
        int sampleRatex = 44100;
        float reductionFactor = 1 - reduction / static_cast<float>(100);
        float newSampleRate = sampleRatex * reductionFactor;
        int factorDownsampling = (sampleRatex / newSampleRate)*2.5;
        if (reduction > 0 && reduction <100)
        {
            for (int i = 0; i < buffer.getNumSamples(); i++)
            {
                if (i % int(factorDownsampling) == 0)
                {
                    channelData[i] = channelData[i];
                }
                else
                {
                    channelData[i] = 0; 
                }
            }
        }
        else if (reduction == 100)
        {
            for (int i = 0; i < buffer.getNumSamples(); i++)
            {
                channelData[i] = 0;
            }
        }
        else
        {
            for (int i = 0; i < buffer.getNumSamples(); i++)
            {
                channelData[i] = channelData[i];
            }
        }
        
        //filtrado
        if (channel == 0) // process left channel with filtersL
        {
            for (auto& filter : cadena.filtersL)
            {
                for (int i = 0; i < buffer.getNumSamples(); ++i)
                {
                    channelData[i] = filter.processSample(channelData[i]);
                }
            }
        }
        else if (channel == 1) // process right channel with filtersR
        {
            for (auto& filter : cadena.filtersR)
            {
                for (int i = 0; i < buffer.getNumSamples(); ++i)
                {
                    channelData[i] = filter.processSample(channelData[i]);
                }
            }
        }
    }
    /*
    Filter_coef coef;
    juce::dsp::IIR::Filter<double> filter;
   */

    // intento con tutorial 
    //juce::dsp::AudioBlock<float> block(buffer);
    //updateFilter();
    //filtro_tonal.process(juce::dsp::ProcessContextReplacing< float >(block));
    
}

//==============================================================================
bool TFG_downsampler_tonalAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TFG_downsampler_tonalAudioProcessor::createEditor()
{
    return new TFG_downsampler_tonalAudioProcessorEditor (*this);
}

//==============================================================================
void TFG_downsampler_tonalAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TFG_downsampler_tonalAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TFG_downsampler_tonalAudioProcessor();
}
