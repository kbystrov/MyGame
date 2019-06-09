#ifndef MYGAME_GAME_DEF_CONSTANTS_H
#define MYGAME_GAME_DEF_CONSTANTS_H

#include <stdio.h>
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

extern FILE * logfile; ///< @param Global pointer to main log file which is defined in main() method;

//! @def Default config file for current level
const char * const defConfigName = "configs/config.ini";

//! @def Default path to music
const char * const defMusic = "GameResources/Music/game_music.wav";

#endif //MYGAME_GAME_DEF_CONSTANTS_H
