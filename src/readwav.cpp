/* This file is the implementation of the function that takes a wav file as input and returns an array with the morse code 
following the nomenclature in "fr_to_m.cpp" 

Method used : We first extract the wav data in an array of float, knowing the morse beat we can set a window of morse_beat/2 seconds that first 
can be used to find a mean value of the absolute integer of the signal on this time window. Then we check every beat : if the absolute integer is
higher than the mean : it is a 1, else it is a 0 as the signal is flat when it is 0 and oscilate (so in absolute falue is not nul almost everywhere)
so the absolute integer us higher than the mean
*/
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>

#include "../include/setting.h"
#include "../include/readwav.h"
#include "../include/morse_to_fr.h"

/* Ce fichier est une implémentation de la classe audio_to_vect. Elle a pour but de convertir un audio en un texte français.
La méthode utilisé est la suivante. On va parcourir une fois le .wav et obtenir les valeurs des amplitudes. Nous allons ensuite 
échantillonner une deuxième fois l'audio par un pas de l'ordre de 0.1 s, qui est inférieur au temps caractéristique d'un point morse à priori.
Puis nous allons faire la moyenne de l'amplitude sur ce pas de temps. Ensuite nous allons détecter les tiret et les blanc en cherchant
l'intervalle maximale en valeur haute et en valeur basse. Enfin, il ne reste plus qu'à reparcourir le .wav en attribuant les tirets et les points.*/


std::string audio;
std::string normalisation;
std::string chaine_morse;
std::vector<std::string> vect;

// On définit une structure header pour les fichiers wav.

typedef struct wavfile_header_s
{
    char    ChunkID[4] = {'R', 'I', 'F', 'F'};
    int     ChunkSize; //depends on the size of the two chunck and the size on the 2nd chunck depends on the data
    char    Format[4] = {'W', 'A', 'V', 'E'};

    char    Subchunk1ID[4] = {'f', 'm', 't', ' '};
    int     Subchunk1Size = 16;
    short   AudioFormat = 1; //for PCM
    short   NumChannels = 1; //for mono output
    int     SampleRate = 8000; //as it's juste a sequence of beeps lets reduce the size of the file, 8kHz is more than enough 
    int     ByteRate = 8000*1*16/8; //= NumChannels*SampleRate*BitsPerSample/8 to go from Bits of info per sec to Bytes per second
    short   BlockAlign = 1*16/8; //= NumChannels*BitsPerSample/8
    short   BitsPerSample = 16;  //once more, 16bits is more than enough for beeps

    char    Subchunk2ID[4] = {'d', 'a', 't', 'a'};
    int     Subchunk2Size; // = duration*SampleRate*NumChannels*BitsPerSample/8 and duration depend on the input given
} wavfile_header_t;

// Cette fonction va lire le .wav et le convertir en une chaine de caractère.

void audio_to_vect::audio_to_chaine(char* path_wav, float pas) 
{
    FILE*        pfile;
    char*        mystring;
    wavfile_header_t wav_header;
    

    // On utilise "rb" car on ouvre un .wav et non un fichier texte.

    pfile = fopen(path_wav, "rb");

    // On lit le wavheader que l'on conserve en mémoire dans la structure.

    fread(&wav_header, sizeof(wav_header), 1, pfile);

    // on vérifie que c'est bien du mono en entrée.

    if (wav_header.NumChannels != 1) 
    {
        std::cout << "error : the wav file must be mono" << std::endl;
        exit(1);
    }

    // Avec les données du wavheader, on peut en déduire le nombre d'échantillon, et donc la durée de l'audio.
    
    int    nb_samples = (int)(wav_header.Subchunk2Size/wav_header.BlockAlign);
    int    sample_value ;
    int    tab[nb_samples]; //Ce tableau va contenir la valeur des échantillons.
    int    i = 0;
    int    samples_by_pas = (int)(pas*wav_header.SampleRate); 
    int    nb_pas = (int)(nb_samples/samples_by_pas);

    //On lit le fichier wav et on stocke ses  données dans tab. fread renvoie le nombre de blocks lu. Si c'est 0 (false) on sort du while.
    
    while (fread(&sample_value, wav_header.BitsPerSample/8, 1, pfile))
    {
        tab[i] = sample_value;
        i++;
    }
    
    /* on va parcourir le fichier wav une fois pour détecter le plus long temps en valeur haute et en valeur basse. Ce seront nos tirets 
    et nos blancs. On va encore échantilloner notre signal et faire une moyenne dessus. On note pas cet échantionnage.*/


    float val_moy[nb_pas];//valeur moyenne de l'amplitude sur un pas.
    signed short int valeur;

    //On va faire la valeur moyenne du signal sur un pas.
    for (int i = 0 ; i < nb_pas ; i++) 
    {
        val_moy[i] = 0;
        for (int j = 0 ; j < samples_by_pas ; j++)
        {
            // On va sommer les valeurs absolues de tous les samples dans le pas.

            valeur = tab[i*samples_by_pas + j]; 
        
            if (valeur < 0) {

                val_moy[i] = val_moy[i] - valeur;
                
            } 
            else {
                val_moy[i] = val_moy[i] + valeur;
            }
    // On ne stocke que la moyenne du signal.

        val_moy[i] = val_moy[i]/samples_by_pas;

        }
        
    }

    
    // On construit notre suite de 0 et de 1.
    
    for (int i = 0 ; i < nb_pas ; i++) 
    {

        if (val_moy[i] < input_amplitude) //On doit mettre un seuil arbitraire au delà duquel on se considère en valeur haute. Il serait bien de coder une fonction qui ajuste ce seuil.
        {
            audio += "0";
        }
        else 
        {
            audio += "1";
        }
    }

    fclose(pfile);

}

/* Il s'agit maintenant d'identifier les paliers hauts et bas. Pour ce faire on va convertir le signal en une suite de 0 et 1 et
on va compter le plus grand nombre de 1 et de 0 qui seront alors un tiret et un blanc */

void audio_to_vect::letter_separator(void) //cette fonction, pour fonctionner, doit être paramétrée par la longueur de pas qui doit etre en adéquation avec la norme choisie.
{
    int len = audio.length();
    int zero_counter = 0;
    int un_counter = 0;
    int cursor = 0;
    int max_blanc = 0;
    int tiret = 0;
    int min_blanc = 0;
    std::string to_append;

    for (int i = 1; i < len; i++){
        if (i == 1){
            if (audio[i]=='0'){
                zero_counter++;
            }
            else {
                un_counter++;
            }
        }
        else if (audio[i]=='0'){
            if (audio[i-1]=='0'){
                zero_counter++;
            }
            else {
                if (zero_counter>max_blanc){
                    max_blanc = zero_counter;
                }
                if (min_blanc==0){
                    min_blanc = zero_counter;
                }
                if (zero_counter<min_blanc){
                    min_blanc=zero_counter;
                }
                zero_counter=0;
            }
        }
        else {
            if (audio[i-1]=='1'){
                un_counter++;
            }
            else {
                if(un_counter>tiret){
                    tiret = un_counter;
                }
                un_counter=0;
            }
        }

    }

    std::cout<<tiret<<std::endl;
std::cout<<max_blanc<<std::endl;
std::cout<<min_blanc<<std::endl;


        for (int i = 1; i < len; i++){
        if (i == 1){
            if (audio[i]=='0'){
                zero_counter++;
            }
            else {
                un_counter++;
            }
        }
        else if (audio[i]=='0'){
            if (audio[i-1]=='0'){
                zero_counter++;
            }
                
        else {
                if(un_counter==tiret || un_counter == tiret - 1){
                    to_append+="111";
                }
                else {
                    to_append+="1";
                }
                un_counter=0;}


        }
            
        else {
            if (audio[i-1]=='1'){
                un_counter++;
            }

            else {
                if (zero_counter==max_blanc || zero_counter==max_blanc-1){
                    vect.emplace_back(to_append);
                    vect.emplace_back("000");
                    to_append.erase();
                    
                }
                else if (zero_counter==min_blanc || zero_counter==min_blanc+1){
                    to_append += "0";
                }
                else {
                    vect.emplace_back(to_append);
                    to_append.erase();
                }
                zero_counter=0;
            }

    }    
}
}



//On effectue la traduction morse vers français, et on obtient une chaine de caractère du texte.
void audio_to_vect::translate(void)
{
    std::cout<<audio<<std::endl;
    chaine_morse = convert_to_alphabet(vect);

}

//On écrit la traduction dans un fichier texte. 
void audio_to_vect::sauvegarde(char* path_sortie)
{
    std::cout << chaine_morse << std::endl; //affiche le résultat
    
    std::ofstream file(path_sortie);

    int size = chaine_morse.length() + 1;

    for (int i = 0; i < size; i++)
    {
        file << chaine_morse[i];

        if (chaine_morse[i] == ' ') i++; //solving a problem with space encoding
        
    }
}