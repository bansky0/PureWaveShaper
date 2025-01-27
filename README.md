# PureWaveShaper: DSP Algorithms

## Description

This project contains a collection of Digital Signal Processing (DSP) algorithms implemented using the JUCE framework. It aims to provide efficient and reusable components for audio processing applications.

## Table of Contents

- Installation
- Usage
- Features
- Contributing
- Acknowledgments
- Contact
- References

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

I will assume that all ready have installed JUCE in your computer, if not please download it from this [Link]([https://](https://juce.com/get-juce/)). One Juce is downloaded and installed you need to run projuicer, then go to file >> New Project.. Your new window need to be filled with a project name eg. PureWaveExample. And must select in the left window Plugin --> Basic. Your window configuration should look like the following ![Basic Configuration New Project](Documentation/img01.png "New Project Window"). Click in Create Project.. and a save project window will appear here you need to select the path where your project folder will be saved. Done! You have created your new project!

### Adding DSP library

Copy the 

If you are an experienced juce you will need to 

Once the DSP folder is located in your JUCE project, It is necessary run your projuicer project.

## References

- (1) Tarr, E. (2018). Hack Audio: An Introduction to Computer Programming and Digital Signal Processing in MATLAB (1st ed.). Routledge.
