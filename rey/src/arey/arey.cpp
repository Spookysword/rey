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
    ALenum err, format;
    ALuint buffer;
    SNDFILE* sndfile;
    SF_INFO sfinfo;
    short* membuf;
    sf_count_t num_frames;
    ALsizei num_bytes;

    // Open and check for errors
    sndfile = sf_open(filename, SFM_READ, &sfinfo);
    if (!sndfile) {
        printf("arey: couldn't open audio file %s\n", filename);
        return 0;
    }
    // Ahahaha I have no clue what this MEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAANS
    if (sfinfo.frames < 1 || sfinfo.frames > (sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels) {
        printf("arey: bad sample count in audio file %s\n", filename);
        sf_close(sndfile);
        return 0;
    }
    // Formatting stuff I don't understand I just copied this from one of the examples off of the openal soft github page
    // Also I dunno why they didn't use a switch here so I did >:)
    format = AL_NONE;
    switch(sfinfo.channels) {
    case 1:
        format = AL_FORMAT_MONO16;
        break;
    case 2:
        format = AL_FORMAT_STEREO16;
        break;
    case 3:
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) {
            format = AL_FORMAT_BFORMAT2D_16;
        }
        break;
    case 4:
        if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) {
            format = AL_FORMAT_BFORMAT3D_16;
        }
        break;
    default:
        printf("arey: audio file %s has unsupported channel count %d\n", sfinfo.channels);
        break;
        return 0; // Not sure if this works, we'll find out the hard way.
    }

    // This is why this wasn't done in C.
    membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));
    num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
    if (num_frames < 1) {
        free(membuf);
        sf_close(sndfile);
        printf("arey: couldn't read sample files in sound file %s\n", filename);
        return 0;
    }
    num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

    // Buffer it in and just throw it away
    buffer = 0;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate); // This line is so satisfying lol
    free(membuf);
    sf_close(sndfile);

    // Error checking
    err = alGetError();
    if (err != AL_NO_ERROR) {
        printf("arey: al error: %s\n", alGetString(err));
        if (buffer && alIsBuffer(buffer)) {
            alDeleteBuffers(1, &buffer);
        }
        return 0;
    }

    soundEffectBuffers.push_back(buffer);
    return buffer;
}

void SoundDevice::removeSoundEffect(ALuint buffer) {
    auto it = soundEffectBuffers.begin();
    while (it != soundEffectBuffers.end()) {
        if (*it == buffer) {
            alDeleteBuffers(1, &*it);
            it = soundEffectBuffers.erase(it);
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