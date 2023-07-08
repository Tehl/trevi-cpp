# Trevi | A Ray Tracing Renderer

_Trevi_ is an offline image renderer based on J. Turner Whitted's recursive ray tracing algorithm. It was implemented as an in-course assessment for the _Advanced Image Synthesis_ study module at Teesside University (https://www.tees.ac.uk/) in 2008.

Named for the Trevi Fountain in Rome and meaning ‘three streets’, Trevi uses three key techniques to produce high-quality digital images: basic Whitted raytracing,  raytraced ambient occlusion and raytraced diffuse interreflection.

## Usage

Pre-compiled binaries are provided at `/bin/trevi`. The application should be run from the command line, and will prompt for a scene file to render as part of starting up.

## Dependencies

The project makes use of an XML loader named TXFLIB which was provided by the university and is not included in this repository. To compile the application yourself, either provide an implementation of the included `TXF.h` header if XML loading is desired, or use one of the alternate `SceneLoader` implementations which do not use TXFLIB.

## Build Instructions

Trevi is implemented in Microsoft Visual C++ 8.0 and should be compiled using Visual Studio 2005. Binaries in this repository were compiled on Windows Vista at the time of implementation.

Compilation has been confirmed on Windows 10 version 19045 using Visual Studio 2005 Express, which can be downloaded from Microsoft at https://download.microsoft.com/download/A/9/1/A91D6B2B-A798-47DF-9C7E-A97854B7DD18/VC.iso

## License

Trevi is licensed under the [MIT](LICENSE.md) license except where otherwise specified.

`TXF.h` is (c) 2006 Tyrone Davison. No license is provided.