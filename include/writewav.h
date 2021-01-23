#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <string>


typedef struct wavfile_header_s wavfile_header_t;

typedef struct mono_s mono_t;

mono_t *allocate_buffer(int32_t nb_of_samples);

void write_WAV_header(FILE* pfile, int nb_of_samples, wavfile_header_t wav_header);

void  write_WAV_data(FILE* pfile, int nb_of_samples, mono_t *pbuffer) ;

void generate_signal(float amplitude, int SampleRate, int nb_of_samples, mono_t *pbuffer, std::string str);

void write_wav(std::string morse, char* path);