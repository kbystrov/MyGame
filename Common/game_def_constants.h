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
//! @def Default size of temporary buffer for read symbols from config lines
const size_t TMP_STR_SIZE = 100;

//! Constant strings for parsing config file
//! @def Default delimiter in config file for group of parameters
const char * const CFG_DELIM_STR = "*******************************";
//! @def Default string to find windows group parameters in config file during parsing of it
const char * const CFG_WIN_GROUP = "WINDOW";
//! @def Default string to find music group parameters in config file during parsing of it
const char * const CFG_MUS_GROUP = "AUDIO";
//! @def Default string to find objects group parameters in config file during parsing of it
const char * const CFG_OBJ_GROUP = "OBJECTS";

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

//! Constant strings for parsing objects and its parameters from config file
//! @def Default string to find bench group parameters in config file during parsing of it
const char * const CFG_OBJNUM_GROUP = "OBJ_NUM";
//! @def Default string to find player group parameters in config file during parsing of it
const char * const CFG_PLAYER_GROUP = "PLAYER";
//! @def Default string to find train inspector group parameters in config file during parsing of it
const char * const CFG_INSP_GROUP = "TRAIN_INSPECTOR";
//! @def Default string to find passenger group parameters in config file during parsing of it
const char * const CFG_PSG_GROUP = "PASSENGER";
//! @def Default string to find bench group parameters in config file during parsing of it
const char * const CFG_BNCH_GROUP = "BENCH";

//! Default number of objects in game
const uint32_t defPlayerNum = 1;
const uint32_t defEnemyNum = 1;
const uint32_t defNeutralNum = 1;
const uint32_t defStaticObjNum = 1;



#endif //MYGAME_GAME_DEF_CONSTANTS_H
