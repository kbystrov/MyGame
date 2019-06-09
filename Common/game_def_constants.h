#ifndef MYGAME_GAME_DEF_CONSTANTS_H
#define MYGAME_GAME_DEF_CONSTANTS_H

#include <stdio.h>
#include <stdint.h>
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

///! @def Global pointer to main log file which is defined in main() method;
extern FILE * logfile;
//! @def Default config file for current level
const char * const defConfigName = "configs/config.ini";
//! @def Default path to music
const char * const defMusic = "GameResources/Music/game_music.wav";
//! @def Default size of temporary buffer for read symbols from config lines
const size_t TMP_STR_SIZE = 100;
const uint32_t defWinNum = 0;
const uint32_t defWinSize = 0;
const uint32_t defFrameRateLim = 0;


#endif //MYGAME_GAME_DEF_CONSTANTS_H
