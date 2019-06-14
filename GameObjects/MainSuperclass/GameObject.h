#ifndef MYGAME_GAMEOBJECT_H
#define MYGAME_GAMEOBJECT_H

#include "RadVec.h"
#include "err_codes.h"
#include "proj_macros.h"
#include "game_obj_types.h"
#include "game_def_constants.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @def Default data type for used radius vector in game
typedef float dataType;

//! @def Default radius vector
using Vec = RadVec<dataType>;
//! @def Default object position
const Vec defPos = Vec(1, 1);
//! @def Default object size
const Vec defSize = Vec(1, 1);
//! @def Default window size
const Vec defWindSize = Vec(defWinW, defWinH);

//! @class Base class for all game objects
class GameObject {
protected:
    gameType obj_type_ = type_game_obj_e;
    Vec pos_;  ///< @param character's coordinates radius vector (x,y,...)
    Vec size_; ///< @param character's size radius vector (x,y,...)
    Vec wind_size_; ///< @param Default size of game window to checking moving over the window bounds

public:
    explicit GameObject(Vec pos = defPos, Vec size = defSize, Vec wind_size = defWindSize);

    virtual ~GameObject();

    int setPos(Vec pos);
    Vec getPos() const;
    int setSize(Vec size);
    Vec getSize() const;
    gameType getObjType() const;
    int setObjType(gameType obj_type);

    virtual void pureVirt() {};
};

#endif //MYGAME_GAMEOBJECT_H
