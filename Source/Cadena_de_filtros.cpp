/*
  ==============================================================================

    Cadena_de_filtros.cpp
    Created: 9 May 2024 6:38:27pm
    Author:  rafae

  ==============================================================================
*/

#include "Cadena_de_filtros.h"
#include <vector>
#include <String>
#include <fstream>
#include <array>
#include <sstream>
#include <JuceHeader.h>


Cadena_de_filtros::Cadena_de_filtros()
{
    juce::File file("D:/UPC/TFG/jucecode/TFG_downsampler_tonal/Source/MAJ/Filtro_dividido222.txt");
    if (!file.existsAsFile())
    {
        throw std::runtime_error("Could not open file");
    }

    juce::FileInputStream inputStream(file);
    if (!inputStream.openedOk())
    {
        throw std::runtime_error("Failed to open file stream");
    }

    while (!inputStream.isExhausted())
    {
        juce::String line = inputStream.readNextLine();
        juce::StringArray tokens;
        tokens.addTokens(line, ",", "\"");
        std::array<float, 6> coefs;
        int i = 0;
        for (const auto& token : tokens)
        {
            coefs[i] = token.getDoubleValue();
            i++;
        }

        juce::dsp::IIR::Coefficients<float>::Ptr coefsPtr = new juce::dsp::IIR::Coefficients<float>(coefs);
        filtersL.push_back(juce::dsp::IIR::Filter<float>(coefsPtr));
        filtersR.push_back(juce::dsp::IIR::Filter<float>(coefsPtr));
    }
}
