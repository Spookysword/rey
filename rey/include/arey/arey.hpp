#ifndef AREY_H
#define AREY_H

#include <AL/alc.h>
#include <AL/al.h>
#include <AL/alext.h>
#include <examples/common/alhelpers.h>
#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>

#include <vector>

typedef unsigned int Sound;

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

SoundDevice* mainSoundDevice;

void initArey();

void closeArey();

Sound loadSound(const char* filename);

#endif // AREY_H