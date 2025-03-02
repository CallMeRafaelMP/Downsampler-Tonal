/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
TFG_downsampler_tonalAudioProcessorEditor::TFG_downsampler_tonalAudioProcessorEditor (TFG_downsampler_tonalAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    // Slider
    fader.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    fader.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 64, 40);
    fader.setRange( 0, 100, 1);
    fader.addListener(this);
    addAndMakeVisible(fader);
    
    //title
    //titleLabel.setText("Downsampler Tonal", juce::dontSendNotification);
    //titleLabel.setFont(juce::Font(40.0f,4));
    //addAndMakeVisible(titleLabel);

    setSize (600, 400);
}

TFG_downsampler_tonalAudioProcessorEditor::~TFG_downsampler_tonalAudioProcessorEditor()
{
}

//==============================================================================
void TFG_downsampler_tonalAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    //juce::Image backimg = juce::ImageCache::getFromMemory(BinaryData::Apaso_jpg, BinaryData::Apaso_jpgSize);
    juce::Image backimg = juce::ImageCache::getFromMemory(BinaryData::DOWNSAMPLER_png, BinaryData::DOWNSAMPLER_pngSize);
    backimg = backimg.juce::Image::rescaled(600, 400);
    g.drawImageAt(backimg, 0, 0);
    
}

void TFG_downsampler_tonalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    fader.setBounds(202, 125, 221, 172);
    //titleLabel.setBounds(135, 30, getWidth() - 20, 50);
    
}

void TFG_downsampler_tonalAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &fader)
    {
        audioProcessor.reduction = fader.getValue();
    }
}