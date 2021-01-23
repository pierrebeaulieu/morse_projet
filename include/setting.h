#pragma once

/*
This file contains every global variables and settingyou might want
to change

*/


//OUTPUT

const float output_amplitude = 0.65 * (float)32767; //arbitrary initial volume

const float output_frequency = 800; //frequency of the morse wav, must stay under 4000Hz in order to respect Shannon's criteria

const float output_pas_time = 0.2; //time of a beep

//INPUT

const float input_frequency = 800;

const float input_pas_time = 0.2;

const float input_amplitude = 1; 