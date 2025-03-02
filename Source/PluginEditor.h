/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================

class TFG_downsampler_tonalAudioProcessorEditor  : public juce::AudioProcessorEditor, 
                                                   public juce::Slider::Listener 
{
public:
    TFG_downsampler_tonalAudioProcessorEditor (TFG_downsampler_tonalAudioProcessor&);
    ~TFG_downsampler_tonalAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged (juce::Slider* slider);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TFG_downsampler_tonalAudioProcessor& audioProcessor;

    juce::Slider fader;
    //juce::Label titleLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TFG_downsampler_tonalAudioProcessorEditor)
};
 