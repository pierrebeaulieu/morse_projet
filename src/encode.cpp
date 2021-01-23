#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include "../include/encode.h"
#include "../include/fr_to_morse.h"
#include "../include/writewav.h"

// Cette fonction permet de convertir un texte français en un fichier .wav morse.

void encode(char* path, std::string str){
std::string suite_morse =convert_to_morse(str);
write_wav(suite_morse, path);
}