#pragma once

#include <map>
#include <string>
#include <vector>

class audio_to_vect
{

    public :

    std::string audio;
    std::string chaine_morse;
    std::vector<std::string> vect;

    public :

        audio_to_vect(){};

        ~audio_to_vect(){};

        void audio_to_chaine(char*, float);

        void letter_separator(void);

        void translate(void);

        void sauvegarde(char* directory);

    };