#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include "../include/decode.h"
#include "../include/morse_to_fr.h"
#include "../include/readwav.h"

// Cette fonction permet de convertir un fichier .wav morse en un texte français.

void decode(char* path_wav, char* path_sortie){
audio_to_vect signal;
signal.audio_to_chaine(path_wav,0.2);

signal.letter_separator();

signal.translate();

signal.sauvegarde(path_sortie);
}