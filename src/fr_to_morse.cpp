#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include "../include/fr_to_morse.h"

/* Cette fonction prends un texte en français et renvoie son codage morse. On a utilisé la convention: "000" pour les séparations, "1" pour
un point et "000" pour un tiret.*/

std::string convert_to_morse(std::string str) {
    std::map<char, std::string> fr_to_m; //On crée un dictionnaire de correspondance français/morse.
    fr_to_m[' '] = "000";
    fr_to_m['a'] = "10111";
    fr_to_m['b'] = "111010101";
    fr_to_m['c'] = "11101011101";
    fr_to_m['d'] = "1110101"; 
    fr_to_m['e'] = "1";
    fr_to_m['f'] = "101011101";
    fr_to_m['g'] = "111011101";
    fr_to_m['h'] = "1010101";
    fr_to_m['i'] = "101";
    fr_to_m['j'] = "1011101110111";
    fr_to_m['k'] = "111010111";
    fr_to_m['l'] = "101110101";
    fr_to_m['m'] = "1110111";
    fr_to_m['n'] = "11101";
    fr_to_m['o'] = "11101110111";
    fr_to_m['p'] = "10111011101";
    fr_to_m['q'] = "1110111010111";
    fr_to_m['r'] = "1011101";
    fr_to_m['s'] = "10101";
    fr_to_m['t'] = "111";
    fr_to_m['u'] = "1010111";
    fr_to_m['v'] = "101010111";
    fr_to_m['w'] = "101110111";
    fr_to_m['x'] = "11101010111";
    fr_to_m['y'] = "1110101110111";
    fr_to_m['z'] = "11101110101";
    fr_to_m['0'] = "1110111011101110111";
    fr_to_m['1'] = "10111011101110111";
    fr_to_m['2'] = "101011101110111";
    fr_to_m['3'] = "1010101110111";
    fr_to_m['4'] = "10101010111";
    fr_to_m['5'] = "101010101";
    fr_to_m['6'] = "11101010101";
    fr_to_m['7'] = "1110111010101";
    fr_to_m['8'] = "111011101110101";
    fr_to_m['9'] = "11101110111011101";

    std::string morse;
    
    for ( std::string::iterator it=str.begin(); it!=str.end(); ++it) { //On utilise un pointeur qui pointe l'adresse de chaque lettre successivement. 
        morse += fr_to_m[*it];
        morse += "000";
    }
    return morse;
}

// Cette fonction permet de lire un fichier texte et renvoie une chaine de caractère.

std::string get_string(char* path) {

    std::string str;

    //ouvre le fichier spécifié en argument.
    std::ifstream file;
    file.open(path);

    char c ;

    while (file.get(c)) { 

        str += c;
        std::cout<<str<<std::endl;
    }

    file.close();

    return str;
}