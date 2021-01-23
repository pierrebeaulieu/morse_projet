#include <iostream>
#include "./include/decode.h"
#include "./include/encode.h"
#include <string>
#include "./include/fr_to_morse.h"

/* taper e pour encode, d pour décode en 1er argument puis le chemin d'entrée puis de sortie*/



int main(int agrc, char** arg){
    char* algo = arg[1];
    
    char* path_entree = arg[2];
    char* path_sortie = arg[3];

    if (algo[0] == 'e'){
        std::string text = get_string(path_entree);
        encode(path_sortie, path_entree);
    }
    else if (algo[0] == 'd'){
        decode(path_entree, path_sortie);
    }
    else {std::cout << "mauvais arguments"<< std::endl;}
    return 1;
}
