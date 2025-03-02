/*
  ==============================================================================

    Cadena_de_filtros.h
    Created: 9 May 2024 6:38:27pm
    Author:  rafae

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <vector>

class Cadena_de_filtros
{
public:
    std::vector<juce::dsp::IIR::Filter<float>> filtersL;
    std::vector<juce::dsp::IIR::Filter<float>> filtersR;

    Cadena_de_filtros();
};