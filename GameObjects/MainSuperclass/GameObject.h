#ifndef MYGAME_GAMEOBJECT_H
#define MYGAME_GAMEOBJECT_H

#include "RadVec.h"
#include "err_codes.h"
#include "proj_macros.h"
#include "game_obj_types.h"
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

//!@class Base class for all game objects
class GameObject {
protected:
    gameType obj_type_ = type_game_obj_e;
    Vec pos_;  ///< @param character's coordinates radius vector (x,y,...)
    Vec size_; ///< @param character's size radius vector (x,y,...)

public:
    explicit GameObject(Vec pos = defPos, Vec size = defSize);

    virtual ~GameObject() {}

    int setPos(Vec pos);
    Vec getPos() const;
    int setSize(Vec size);
    Vec getSize() const;
    gameType getObjType() const;
    int setObjType(gameType obj_type);
};


#endif //MYGAME_GAMEOBJECT_H
