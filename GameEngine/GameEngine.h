#ifndef MYGAME_GAMEENGINE_H
#define MYGAME_GAMEENGINE_H

#include "RadVec.h"
#include "err_codes.h"
#include "proj_macros.h"
#include "characters.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

class GameEngine {
    //CharacterObject * allCharsArr_;  ///< @param Array of Characters in Game
    size_t allCharsCount_;           ///< @param Number of elements in Characters Array
    //MainPlayer * player_;                ///< @param Player's pointer
    bool isAlarm_;                   ///< @param Flag of that Train Inspectors have started their attempts for arresting Player
};


#endif //MYGAME_GAMEENGINE_H
