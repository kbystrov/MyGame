#ifndef MYGAME_PROJ_MACROS_H
#define MYGAME_PROJ_MACROS_H

#include <stdio.h>
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @def Macro for debugging all possible errors in game
#define GAME_DEBUG
//! @def Macro for debugging the sequence of constructors calls
#define CTR_DEBUG

extern FILE * logfile; ///< @param Global pointer to main log file which is defined in main() method;

#endif //MYGAME_PROJ_MACROS_H
