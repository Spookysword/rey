#ifndef AREY_H
#define AREY_H

#include <AL/alc.h>
#include <AL/al.h>
#include <AL/alext.h>
#include <examples/common/alhelpers.h>
#include "dr_wav.h"
#include "dr_flac.h"
#include "dr_mp3.h"
#include "stb_vorbis.c"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>

#include <vector>

//typedef ALuint Sound;
class Sound {
public:
    ALuint index = 0;
    ALuint source = 0;
    float pitch = 1.0f;
    float gain = 1.0f;
    float position[3] = { 0, 0, 0 };
    float velocity[3] = { 0, 0, 0 };
    bool loopSound = false;
public:
    bool isActive = false;
};

class SoundDevice {
public:
    SoundDevice* get();
    SoundDevice();
    ~SoundDevice();
    ALCdevice* device;
    ALCcontext* context;

    ALuint addSoundEffect(const char* filename);
    void removeSoundEffect(ALuint buffer);
    std::vector<ALuint> soundEffectBuffers;
};

extern SoundDevice* mainSoundDevice;

void initArey();

void closeArey();

Sound loadSound(const char* filename);

void deleteSound(Sound* sound);

void playSound(Sound* sound);

void stopSound(Sound* sound);

#endif // AREY_H