#define DR_WAV_IMPLEMENTATION
#define DR_FLAC_IMPLEMENTATION
#define DR_MP3_IMPLEMENTATION
#define STB_VORBIS_HEADER_ONLY
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
    int channels;
    int sampleRate;
    unsigned long long totalPCMFrameCount;
    ALenum format;
    ALsizei size;
    short* sampleData;

    std::string s(filename);
    std::string last3 = s.substr(s.size() - 3);
    std::string last3lower;
    for (int i = 0; i < 3; i++) {
        last3lower.push_back(std::tolower(last3[i]));
    }
    std::string last4 = s.substr(s.size() - 4);
    std::string last4lower;
    for (int i = 0; i < 4; i++) {
        last4lower.push_back(std::tolower(last4[i]));
    }
    if (last3lower == "wav") {
        unsigned int u_channels;
        unsigned int u_sampleRate;
        sampleData = drwav_open_file_and_read_pcm_frames_s16(filename, &u_channels, &u_sampleRate, &totalPCMFrameCount, NULL);
        channels = u_channels;
        sampleRate = u_sampleRate;
    }
    else if (last3lower == "mp3") {
        drmp3_config u_config;
        sampleData = drmp3_open_file_and_read_pcm_frames_s16(filename, &u_config, &totalPCMFrameCount, NULL);
        channels = u_config.channels;
        sampleRate = u_config.sampleRate;
    }
    else if (last3lower == "ogg") {
        // Thank you Wyrframe & jfirjebshw <3 https://www.gamedev.net/forums/topic/667704-playing-ogg-file-with-openal-and-stb_vorbis/5224322/
        int sampleDecode = stb_vorbis_decode_filename(filename, &channels, &sampleRate, &sampleData);
        size = sampleDecode * channels * sampleRate * sizeof(short);
    }
    else if (last4lower == "flac") {
        unsigned int u_channels;
        unsigned int u_sampleRate;
        sampleData = drflac_open_file_and_read_pcm_frames_s16(filename, &u_channels, &u_sampleRate, &totalPCMFrameCount, NULL);
        channels = u_channels;
        sampleRate = u_sampleRate;
    }
    else {
        printf("arey: unrecognized file format thrown in %s\n", filename);
        return 0;
    }

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
    size = (ALsizei)(totalPCMFrameCount * channels) * (ALsizei)sizeof(short);

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
    Sound sound;
    sound.index = mainSoundDevice->addSoundEffect(filename);
    return sound;
}

void deleteSound(Sound* sound) {
    mainSoundDevice->removeSoundEffect(sound->index);
    if (sound->isActive) {
        alDeleteSources(1, &sound->source);
    }
    sound->isActive = false;
}

void playSound(Sound* sound) {
    alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);

    alListener3f(AL_POSITION, 0.0, 0.0, 0.0);
	alListener3f(AL_VELOCITY, 0.0, 0.0, 0.0);

    ALfloat pt[6];
	pt[0] = 0.0;
	pt[1] = 0.0;
	pt[2] = 1.0;
	pt[3] = 1.0;
	pt[4] = 0.0;
	pt[5] = 0.0;
	alListenerfv(AL_ORIENTATION, pt);

    sound->isActive = true;
    alGenSources(1, &sound->source); // Problems could come from this line
    alSourcef(sound->source, AL_PITCH, sound->pitch);
    alSourcef(sound->source, AL_GAIN, sound->gain);
    alSource3f(sound->source, AL_POSITION, sound->position[0], sound->position[1], sound->position[2]);
    alSource3f(sound->source, AL_VELOCITY, sound->velocity[0], sound->velocity[1], sound->velocity[2]);
    alSourcei(sound->source, AL_LOOPING, sound->loopSound);
    alSourcei(sound->source, AL_BUFFER, sound->index);
    alSourcePlay(sound->source);
}

void stopSound(Sound* sound) {
    if (sound->isActive == true) {
        sound->isActive = false;
    }
    alSourceStop(sound->source);
    alDeleteSources(1, &sound->source);
}