//
// Created by matthewperiut on 10/22/21.
//

#include "SoundHandler.h"
#include "LoadWav.h"
#include <iostream>
#include <cstring>

static void list_audio_devices(const ALCchar *devices)
{
    const ALCchar *device = devices, *next = devices + 1;
    size_t len = 0;

    fprintf(stdout, "Devices list:\n");
    fprintf(stdout, "----------\n");
    while (device && *device != '\0' && next && *next != '\0') {
        fprintf(stdout, "%s\n", device);
        len = strlen(device);
        device += (len + 1);
        next += (len + 2);
    }
    fprintf(stdout, "----------\n");
}

void SoundHandler::OpenDevice()
{
    //list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
    device = alcOpenDevice(nullptr);
    if(!device)
        std::cout << "No suitable audio device detected." << std::endl;

    context = alcCreateContext(device, nullptr);
    if (!alcMakeContextCurrent(context))
        // failed to make context current
        std::cout << "Context was unable to be made" << std::endl;
}

void SoundHandler::DefineListener()
{
    ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

    alListener3f(AL_POSITION, 0, 0, 1.0f);
    // check for errors
    alListener3f(AL_VELOCITY, 0, 0, 0);
    // check for errors
    alListenerfv(AL_ORIENTATION, listenerOri);
    // check for errors
}

void SoundHandler::GenerateSource()
{
    alGenSources((ALuint)1, &source);
    // check for errors

    alSourcef(source, AL_PITCH, 1);
    // check for errors
    alSourcef(source, AL_GAIN, 1);
    // check for errors
    alSource3f(source, AL_POSITION, 0, 0, 0);
    // check for errors
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    // check for errors
    alSourcei(source, AL_LOOPING, AL_FALSE);
    // check for errros
}

void SoundHandler::GenerateBuffer()
{
    alGenBuffers((ALuint)1, &buffer);
    // check for errors
}

SoundHandler::SoundHandler()
{
    OpenDevice();
    DefineListener();
    GenerateSource();
    GenerateBuffer();
}

void SoundHandler::LoadSound(std::string filepath)
{
    alcMakeContextCurrent(context);
    data = LoadWAV(filepath.c_str(), channel, sampleRate, bps, size);
    int format;
    if (channel == 1)
    {
        if (bps == 8)
        {
            format = AL_FORMAT_MONO8;
        }
        else {
            format = AL_FORMAT_MONO16;
        }
    }
    else {
        if (bps == 8)
        {
            format = AL_FORMAT_STEREO8;
        }
        else {
            format = AL_FORMAT_STEREO16;
        }
    }

    alBufferData(buffer, format, data, size, sampleRate);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
}

void SoundHandler::Play()
{
    alSourcePlay(source);
}

void SoundHandler::UnloadSound() const
{
    delete[] data;
}

SoundHandler::~SoundHandler()
{
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    device = alcGetContextsDevice(context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);

    UnloadSound();
}
