#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "morse_to_fr.h"

/* Cette fonction ne prend plus un chaine de caractère mais un vecteur de chaines de caractère. En effet on va préférer d'abord
décoder les lettres unes à unes avant de les concaténer pour former un texte*/

std::string convert_to_alphabet(std::vector<std::string> vect) 
{

    std::string result;

    std::map<std::string, char> m_to_fr; //creating the map for alphabet equivalents to morse
    m_to_fr["000"] = ' '; 
    m_to_fr["10111"] = 'a';
    m_to_fr["111010101"] = 'b';
    m_to_fr["11101011101"] = 'c';
    m_to_fr["1110101"] = 'd';
    m_to_fr["1"] = 'e';
    m_to_fr["101011101"] = 'f';
    m_to_fr["111011101"] = 'g';
    m_to_fr["1010101"] = 'h';
    m_to_fr["101"] = 'i';
    m_to_fr["1011101110111"] = 'j';
    m_to_fr["111010111"] = 'k';
    m_to_fr["101110101"] = 'l';
    m_to_fr["1110111"] = 'm';
    m_to_fr["11101"] = 'n';
    m_to_fr["11101110111"] = 'o';
    m_to_fr["10111011101"] = 'p';
    m_to_fr["1110111010111"] = 'q';
    m_to_fr["1011101"] = 'r';
    m_to_fr["10101"] = 's';
    m_to_fr["111"] = 't';
    m_to_fr["1010111"] = 'u';
    m_to_fr["101010111"] = 'v';
    m_to_fr["101110111"] = 'w';
    m_to_fr["11101010111"] = 'x';
    m_to_fr["1110101110111"] = 'y';
    m_to_fr["11101110101"] = 'z';
    m_to_fr["1110111011101110111"] = '0';
    m_to_fr["10111011101110111"] = '1';
    m_to_fr["101011101110111"] = '2';
    m_to_fr["1010101110111"] = '3';
    m_to_fr["10101010111"] = '4';
    m_to_fr["101010101"] = '5';
    m_to_fr["11101010101"] = '6';
    m_to_fr["1110111010101"] = '7';
    m_to_fr["111011101110101"] = '8';
    m_to_fr["11101110111011101"] = '9';

    for (int i = 0; i < vect.size(); i++)
    {
        std::cout<<vect[i]<<std::endl;
        result.push_back(m_to_fr[vect[i]]);
    }

    return result;
}
