#define DR_WAV_IMPLEMENTATION
#include <arey/arey.hpp>

SoundDevice* mainSoundDevice;

SoundDevice* SoundDevice::get() {
    SoundDevice* device = new SoundDevice();
    return device;
}

SoundDevice::SoundDevice() {
    // Grab default device
    device = alcOpenDevice(nullptr);
    if (!device) {
        printf("arey: no sound device found.\n");
    }
    // Make sound context
    context = alcCreateContext(device, nullptr);
    if (!context) {
        printf("arey: context couldn't be created.\n");
    }
    if (!alcMakeContextCurrent(context)) {
        printf("arey: couldn't make context current\n");
    }
    soundEffectBuffers.clear();
}

SoundDevice::~SoundDevice() {
    if (!alcMakeContextCurrent(nullptr)) {
        printf("arey: couldn't void current audio context\n");
    }
    alcDestroyContext(context);
    if (context) {
        printf("arey: couldn't close audio context\n");
    }
    if (!alcCloseDevice(device)) {
        printf("arey: couldn't close audio device");
    }

    alDeleteBuffers(soundEffectBuffers.size(), soundEffectBuffers.data());
    soundEffectBuffers.clear();
}

ALuint SoundDevice::addSoundEffect(const char* filename) {
    unsigned int channels;
    unsigned int sampleRate;
    drwav_uint64 totalPCMFrameCount;
    ALenum format;
    ALsizei size;
    float* sampleData = drwav_open_file_and_read_pcm_frames_f32(filename, &channels, &sampleRate, &totalPCMFrameCount, NULL);
    if (sampleData == NULL) {
        printf("arey: failed to read file %s\n", filename);
        return 0;
    }
    switch(channels) {
    case 1:
        format = AL_FORMAT_MONO16;
        break;
    case 2:
        format = AL_FORMAT_STEREO16;
        break;
    case 3:
        format = AL_FORMAT_BFORMAT2D_16;
        break;
    case 4:
        format = AL_FORMAT_BFORMAT3D_16;
        break;
    default:
        printf("arey: audio file %s has unsupported channel count %d\n", channels);
        drwav_free(sampleData, NULL);
        break;
        return 0; // Not sure if this works, we'll find out the hard way.
    }
    size = (ALsizei)(totalPCMFrameCount * channels) * (ALsizei)sizeof(float);

    ALuint buffer = 0;
    alGenBuffers(1, &buffer);
    // Maybe sampleData doesn't work here
    alBufferData(buffer, format, sampleData, size, sampleRate); // This line is so satisfying lol
    drwav_free(sampleData, NULL);

    soundEffectBuffers.push_back(buffer);
    return buffer;
}

void SoundDevice::removeSoundEffect(ALuint buffer) {
    auto it = soundEffectBuffers.begin();
    while (it != soundEffectBuffers.end()) {
        if (*it == buffer) {
            alDeleteBuffers(1, &*it);
            it = soundEffectBuffers.erase(it);
            return;
        }
        else {
            ++it;
        }
    }
    printf("arey: failed to delete sound effect %i, probably invalid index\n", buffer);
}

void initArey() {
    mainSoundDevice = new SoundDevice();
}

void closeArey() {

}

Sound loadSound(const char* filename) {
    Sound sound = mainSoundDevice->addSoundEffect(filename);
    return sound;
}

void deleteSound(Sound sound) {
    mainSoundDevice->removeSoundEffect(sound);
}