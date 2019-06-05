#ifndef MYGAME_GAMEOBJECT_H
#define MYGAME_GAMEOBJECT_H

#include "RadVec.h"
#include "err_codes.h"
#include "proj_macros.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @def Default radius vector
using Vec = RadVec<float>;
//! @def Default object position
const Vec defPos = Vec(1, 1);
//! @def Default object size
const Vec defSize = Vec(1, 1);

//!@class Base class for all game objects
class GameObject {
protected:
    Vec pos_;  ///< @param character's coordinates radius vector (x,y,...)
    Vec size_; ///< @param character's size radius vector (x,y,...)

public:
    GameObject(): GameObject( defPos , defSize ){}
    GameObject(Vec pos, Vec size);

    virtual ~GameObject() {}

    int setPos(Vec pos);
    Vec getPos() const;
    int setSize(Vec size);
    Vec getSize() const;
};


#endif //MYGAME_GAMEOBJECT_H
