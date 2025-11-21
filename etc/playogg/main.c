#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vorbis/vorbisfile.h>
#include <AL/al.h>
#include <AL/alc.h>

#define BUFFER_SIZE 4096

int loadAudio(const char* filename, char** buffer, int* bufferSize, int* channels, int* frequency) {
    int bitStream;
    long bytes;
    char* data;
    OggVorbis_File oggFile;
    vorbis_info* info;
    FILE* file;

    file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Failed to open file '%s'\n", filename);
        return 1;
    }

    if (ov_open(file, &oggFile, NULL, 0) != 0) {
        printf("Failed to open ogg file '%s'\n", filename);
        fclose(file);
        return 1;
    }

    info = ov_info(&oggFile, -1);
    *channels = info->channels;
    *frequency = info->rate;

    bytes = ov_pcm_total(&oggFile, -1) * 2 * info->channels;
    data = (char*)malloc(bytes);

    size_t pos = 0;
    while (1) {
        int ret = ov_read(&oggFile, data + pos, 4096, 0, 2, 1, &bitStream);
        if (ret == OV_EBADLINK) {
            printf("Failed to read ogg file '%s'\n", filename);
            free(data);
            ov_clear(&oggFile);
            fclose(file);
            return 1;
        }
        else if (ret == 0) {
            break;
        }
        pos += ret;
    }

    *buffer = data;
    *bufferSize = bytes;

    ov_clear(&oggFile);
    fclose(file);

    return 0;
}

int main(int argc, char** argv) {
    char* musicData;
    int bufferSize, channels, frequency;
    ALCdevice* device;
    ALCcontext* context;
    ALuint source;
    ALuint buffer;

    if (loadAudio("sample.ogg", &musicData, &bufferSize, &channels, &frequency) != 0) {
        printf("Failed to decode ogg file.\n");
        return -1;
    }

    device = alcOpenDevice(NULL);
    if (!device) {
        printf("Failed to open device.\n");
        return -1;
    }
    context = alcCreateContext(device, NULL);
    if (!context) {
        printf("Failed to create context.\n");
    }
    if (!alcMakeContextCurrent(context)) {
        printf("Failed to make context current.\n");
    }

    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_STEREO16, musicData, bufferSize, frequency);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);

    ALuint sourceState;
    while (1) {
        alGetSourcei(source, AL_SOURCE_STATE, &sourceState);
        if (sourceState != AL_PLAYING) {
            break;
        }
    }

    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);

    free(musicData);
    return 0;
}