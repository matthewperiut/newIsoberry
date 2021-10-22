//
// Created by matthewperiut on 10/22/21.
//

#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <string>

class SoundHandler
{
public:
    ALCdevice *device;
    ALCcontext *context;
    ALboolean enumeration;
    ALuint source;
    ALuint buffer;

    // sound
    ALsizei size, freq;
    ALenum format;
    ALvoid *data;
    ALboolean loop = AL_FALSE;

    void OpenDevice();

    void DefineListener();

    void GenerateSource();

    void GenerateBuffer();

    void LoadSound(std::__cxx11::basic_string<char> filepath);
};