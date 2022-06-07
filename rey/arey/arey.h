#ifndef AREY_H
#define AREY_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define STB_VORBIS_HEADER_ONLY
#include "extras/stb_vorbis.c"

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

ma_engine engine;

void initArey() {
	ma_result res;

	res = ma_engine_init(NULL, &engine);
	if (res != MA_SUCCESS) {
		printf("Failed to initialize arey!");
		exit(-1);
	}
}

void playSound(const char* sound) {


	ma_result res = ma_engine_play_sound(&engine, sound, NULL);
	if (res != MA_SUCCESS) {
		printf("Couln't play sound located at path '%s'", sound);
	}
}

void closeArey() {
	ma_engine_uninit(&engine);
}

#ifdef __cplusplus
}
#endif
#endif