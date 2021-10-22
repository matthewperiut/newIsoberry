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
    char* data;
    int channel, sampleRate, bps, size;

    SoundHandler();

    void OpenDevice();

    void DefineListener();

    void GenerateSource();

    void GenerateBuffer();

    void LoadSound(std::string filepath);

    void UnloadSound() const;

    ~SoundHandler();

    void Play();
};