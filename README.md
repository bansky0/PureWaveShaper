# PureWaveShaper: DSP Algorithms | Algoritmos de DSP

## Description | Descripción

**PureWaveShaper** is a library of Digital Signal Processing (DSP) algorithms implemented using the JUCE framework. It provides efficient and reusable components for audio processing applications, designed for both professional audio developers and students exploring audio effects and tools design.

**PureWaveShaper** es una librería de algoritmos de procesamiento digital de señales (DSP) implementada con el framework JUCE. Su objetivo es proporcionar componentes eficientes y reutilizables para aplicaciones de procesamiento de audio, dirigidos tanto a desarrolladores de audio profesionales como a estudiantes interesados en explorar el diseño de efectos y herramientas de audio.

---

## Table of Contents | Tabla de Contenidos

- [PureWaveShaper: DSP Algorithms | Algoritmos de DSP](#purewaveshaper-dsp-algorithms--algoritmos-de-dsp)
  - [Description | Descripción](#description--descripción)
  - [Table of Contents | Tabla de Contenidos](#table-of-contents--tabla-de-contenidos)
  - [1. Introduction | Introducción](#1-introduction--introducción)
  - [2. Installation | Instalación](#2-installation--instalación)
    - [Steps | Pasos](#steps--pasos)
  - [3. Features | Características](#3-features--características)
  - [4. Usage | Uso](#4-usage--uso)
  - [5. List of Algorithms | Lista de Algoritmos](#5-list-of-algorithms--lista-de-algoritmos)
  - [6. Contributing | Contribuciones](#6-contributing--contribuciones)
  - [7. Acknowledgments | Agradecimientos\*\*](#7-acknowledgments--agradecimientos)
  - [8. Contact | Contacto](#8-contact--contacto)
  - [Installation](#installation)
  - [List of Algorithms](#list-of-algorithms)
  - [Usage](#usage)
    - [Creating a new project](#creating-a-new-project)
    - [Adding DSP library](#adding-dsp-library)
  - [References](#references)

---

## 1. Introduction | Introducción

**PureWaveShaper** is ideal for:

- Audio developers looking to expand their toolkit.  
- Students eager to learn DSP with ready-to-use algorithms.  
- Sound designers aiming to customize or build audio effects.  

The library includes classic DSP algorithms such as filters (FIR, IIR, Biquad), modulations (chorus, vibrato), distortions, delay effects, and more.

**PureWaveShaper** es ideal para:  

- Desarrolladores de audio interesados en ampliar su conjunto de herramientas.  
- Estudiantes que desean aprender DSP aplicando algoritmos listos para usar.  
- Diseñadores de sonido que buscan personalizar o construir efectos de audio.  

Esta librería incluye implementaciones de algoritmos clásicos como filtros (FIR, IIR, Biquad), modulaciones (chorus, vibrato), distorsiones, efectos de retardo, y más.

---

## 2. Installation | Instalación

### Steps | Pasos  

1. **Clone the repository | Clonar el repositorio**  

```bash
   git clone https://github.com/bansky0/PureWaveShaper
```

2. **Copy the DSP folder | Copiar la carpeta DSP**

Place the `DSP` folder inside the `Source` folder of your JUCE project:
Coloca la carpeta `DSP` dentro de la carpeta `Source` de tu proyecto JUCE:

``` bash
ProjectName/
├── Source/
│   ├── DSP/
│   └── MainComponent.cpp
```

3. **Optional: Add the Assets folder | Opcional: Añadir la carpeta Assets**

If you want to use the included examples, copy the `Assets` folder next to the `Source` folder.

4. **Update Projucer | Configurar Projucer**

Open your `.jucer` file in Projucer and add the `DSP` folder as part of the project. Then, rebuild the project files.

---

## 3. Features | Características

* **Modularity | Modularidad:** Algorithms are designed for easy integration into JUCE projects.
* **Variety | Variedad:** Includes over 90 algorithms, such as filters, modulations, distortions, and spatial effects.
* **Optimization | Optimización:** Implemented for optimal performance, leveraging real-time processing capabilities.

---

## 4. Usage | Uso

**Creating a new project | Crear un nuevo proyecto**

1. Download and install JUCE from [here](https://juce.com/get-juce/).
2. Open Projucer and create a new project:
   * Go to `File > New Project`.
   * Select `Plugin > Basic`.
   * Name your project (e.g., `PureWaveExample`).
   * Save it in your desired folder.
3. Open the `.jucer` file to configure the project as described in the installation section.

**Adding the DSP library | Agregar la librería DSP**

Follow the steps in the Installation section to add the `DSP` folder to your project.

---

## 5. List of Algorithms | Lista de Algoritmos

The library includes a wide range of algorithms categorized as follows:
La librería incluye una amplia gama de algoritmos categorizados como sigue:

**Filters | Filtros**
FIR: FIR_LPF, FIR_LPF2
IIR: IIR_HPF, IIR_LPF, IIR_Notch
Biquad: Biquad_LPF, Biquad_HPF, Biquad_Notch
**Modulations | Modulaciones**
VibratoEffect
ChorusEffect
BarberPoleFlangerEffect
**Distortions | Distorsiones**
HardClipping
ExponentialDistortion
ArctangentDistortion
**Delay Effects | Efectos de Retardo**
SimpleDelay
PingPongEcho
ModularDelay
**Wave Generators | Generadores de Ondas**
SineWave
SquareWave
ImpulseTrain
(See the full list in Documentation/AlgorithmList.md.)
(Consulta la lista completa en Documentation/AlgorithmList.md.)

---

## 6. Contributing | Contribuciones

If you wish to contribute:

1. Fork the repository.
2. Create a new branch for your changes.
3. Submit a Pull Request with a clear description.

Si deseas contribuir:

1. Realiza un fork del repositorio.
2. Crea una nueva rama para tus cambios.
3. Envía un Pull Request con una descripción clara.

---

## 7. Acknowledgments | Agradecimientos**

* Thanks to the JUCE team for their framework.

* Key references:

    Hack Audio: An Introduction to Computer Programming and Digital Signal Processing in MATLAB (E. Tarr, 2018).

## 8. Contact | Contacto

For inquiries or suggestions, contact:
Para consultas o sugerencias, contáctame:

Email | Correo: support@jhonatanlopez.com
GitHub: [bansky0](https://github.com/bansky0/)

## Installation

To make use of PureWaveShaper you need to download the git project and add the DSP folder into your JUCE project inside your source folder.
The source should be `ProjectName\Source\DSP` being DSP folder the one located in this project. An you also might need to copy the Assets folder next the source folder to implement some of the examples. The files inside this folder can be replaced for your own files. Eg: your own impulse responses.

NB: It is not needed to run or copy the PureWaveShaper.jucer project. It is just used to debug the algorithms.

## List of Algorithms

1. Addition
2. AmpModulation
3. ArctangentDistortion
4. AsymetricalDistortion
5. AutoPan
6. BarberPoleFlangerEffect
7. BarberPoleFlangerEffect2
8. Biquad_APF
9. Biquad_BPF
10. Biquad_BPF2
11. Biquad_HPF
12. Biquad_HSF
13. Biquad_II_APF
14. Biquad_II_BPF
15. Biquad_II_HPF
16. Biquad_II_HSF
17. Biquad_II_LPF
18. Biquad_II_LSF
19. Biquad_II_Notch
20. Biquad_II_Peaking
21. Biquad_TDFII_APF
22. Biquad_TDFII_BPF
23. Biquad_TDFII_HPF
24. Biquad_TDFII_HSF
25. Biquad_TDFII_LPF
26. Biquad_TDFII_LSF
27. Biquad_TDFII_Notch
28. Biquad_TDFII_Peaking
29. BitReduction
30. ChorusEffect
31. Convolution
32. CubicDistortion
33. DiodeClipping
34. DirectFormII_APF
35. DirectFormII_NestedAPF
36. DutyCicleWave
37. EchoFeedBackAndFordward
38. EchoFeedBackAndFordward2
39. EchoStereo
40. ExponentialDistortion
41. FeedbackFlangerEffect
42. FIR_LPF
43. FIR_LPF2
44. FlangerEffect
45. FullWaveRectification
46. HalfWaveRectification
47. HardClipping
48. IIR_APF
49. IIR_BFP
50. IIR_FirstOrderAPF
51. IIR_FirstOrderHPF
52. IIR_FirstOrderLPF
53. IIR_HPF
54. IIR_LPF
55. IIR_LSF
56. IIR_Notch
57. IIR_PeakFilter
58. ImpulseTrain
59. Infinteclip
60. Input
61. LFO
62. MidSide
63. ModularDelay
64. MorphLFO
65. MorphWave
66. Pan
67. Pan_linear
68. Pan_sineLaw
69. Pan_sineLaw_modified
70. Pan_sqrt
71. Pan_sqrt_modified
72. PiceWiseOverdrive
73. PingPongEcho
74. PitchDown
75. PitchShifter
76. PitchUp
77. RingModulation
78. SawtoothWave
79. SawtoothWave2
80. SimpleDelay
81. SimpleDelay2
82. SimpleDelay3
83. SimpleDelay4
84. SineDistortion
85. SineWave
86. SineWave2
87. SlewRateDistortion
88. SquareWave
89. SquareWave2
90. StereoImager
91. Subtraction
92. TriangleWave
93. TriangleWave2
94. VibratoEffect
95. VibratoEffectExample
96. WetDry
97. WhiteNoise

## Usage

### Creating a new project

I will assume that all ready have installed JUCE in your computer, if not please download it from this [Link]([https://](https://juce.com/get-juce/)). One Juce is downloaded and installed you need to run projuicer, then go to file >> New Project... Your new window need to be filled with a project name eg. PureWaveExample. And must select in the left window Plugin --> Basic. Your window configuration should look like the following ![Basic Configuration New Project](Documentation/img01.png "New Project Window"). Click in Create Project... and a save project window will appear here you need to select the path where your project folder will be saved. Done! You have created your new project!

### Adding DSP library

Copy the

If you are an experienced juce you will need to

Once the DSP folder is located in your JUCE project, It is necessary run your projuicer project.

## References

- (1) Tarr, E. (2018). Hack Audio: An Introduction to Computer Programming and Digital Signal Processing in MATLAB (1st ed.). Routledge.
