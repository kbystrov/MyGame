#ifndef MYGAME_GAME_DEF_CONSTANTS_H
#define MYGAME_GAME_DEF_CONSTANTS_H

#include <stdio.h>
#include <stdint.h>
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

#define PARSE_CONFIG_PARAMS(file, specifier, var, def_val) {\
    fscanf(file, "%s", tmp); \
        if ( !fscanf(file, specifier, &var) ){ \
            var = def_val; \
        } \
}

///! @def Global pointer to main log file which is defined in main() method;
extern FILE * logfile;
//! @def Default config file for current level
const char * const defConfigName = "configs/config2.ini";
//! @def Default delimiter in config file for group of parameters
const char * const CFG_DELIM_STR = "*******************************";
//! @def Default size of temporary buffer for read symbols from config lines
const size_t TMP_STR_SIZE = 100;

//! Default window parameters
const uint32_t defWinNum = 1;
const uint32_t defWinSize = 1280;
const uint32_t defWinW = 1280;
const uint32_t defWinH = 720;
const char * const defTitle = "Suburban_Train_Game";
const bool defVertSyncFlag = true;
const uint32_t defFrameRateLim = 25;

//! Default music parameters
const uint32_t defSongsNum = 1;
const char * const defMusic = "GameResources/Music/game_music.wav";
const bool defSetLoopFlag = true;



#endif //MYGAME_GAME_DEF_CONSTANTS_H
