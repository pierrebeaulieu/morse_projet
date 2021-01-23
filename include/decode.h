#pragma once
#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include "../include/decode.h"
#include "../include/morse_to_fr.h"
#include "../include/readwav.h"

void decode(char* path_wav, char* path_sortie);