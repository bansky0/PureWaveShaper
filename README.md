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