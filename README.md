# TFG Downsampler Tonal

## Overview
TFG Downsampler Tonal is a real-time audio plugin developed using JUCE in C++. The plugin performs downsampling on an audio signal, introducing aliasing, and then applies a filtering process to ensure that the remaining frequencies conform to the G major scale. The project is designed to allow future expansion where users can select different musical scales for filtering.

## Features
- **Real-time downsampling**: Reduces the sample rate of the audio signal, creating aliasing effects.
- **Harmonic filtering**: Filters out all frequencies outside the G major scale for better tonal integration.
- **JUCE framework**: Built using JUCE, ensuring cross-platform compatibility.
- **Scalability**: Includes a folder (MAJ) storing coefficients for multiple major scales, allowing future expansion to different tonalities.

## How It Works

### 1. **Downsampling**
The plugin processes incoming audio by reducing its sample rate. The amount of reduction is controlled by a parameter (`reduction`), which determines the new sampling frequency and applies a factor to downsample the signal.

### 2. **Filtering**
After downsampling, the signal is processed through a chain of IIR filters. These filters are initialized from coefficients stored in external text files (e.g., `Filtro_dividido222.txt`) that define the frequency response for the G major scale.

### 3. **Processing Flow**
Below is the block diagram showing the signal processing flow:

```
   Input Audio
       |
       v
 +-----------------+
 |  Downsampling  |
 +-----------------+
       |
       v
 +-----------------+
 |  Harmonic IIR  |
 |  Filtering     |
 +-----------------+
       |
       v
   Output Audio
```

## Code Structure

- **`PluginProcessor.cpp`**: Contains the core signal processing logic.
  - Initializes the plugin and manages sample rate changes.
  - Implements the downsampling algorithm.
  - Applies the filter chain.
- **`PluginEditor.cpp`**: Manages the graphical user interface (GUI).
  - Provides a rotary slider to control the downsampling effect.
  - Displays a background image.
- **`Cadena_de_filtros.cpp`**: Loads IIR filter coefficients from external files and applies filtering.
- **`MAJ/` folder**: Stores filter coefficient files for different major scales.

## Installation and Usage
1. **Setup JUCE**
   - Download and install [JUCE](https://juce.com/).
   - Open the Projucer application.
2. **Create a New Project**
   - In Projucer, create a new JUCE Audio Plugin project.
3. **Replace `Source/` Folder**
   - Replace the `Source/` folder in your new project with the `Source/` folder from this repository.
4. **Build and Run**
   - Open the project in your preferred IDE (Visual Studio, Xcode, etc.).
   - Build and test the plugin.

## Future Improvements
- Implement UI controls to allow users to choose different musical scales.
- Optimize the filtering process for better performance.
- Improve aliasing artifacts handling.

## License
This project is open-source and free to use. Feel free to contribute and suggest improvements!

