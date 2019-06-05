#ifndef MYGAME_MOVEABLEOBJECT_H
#define MYGAME_MOVEABLEOBJECT_H

#include "GameObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @def Default object speed
const Vec defSpeed = Vec(10, 10);

//! @class A superclass for all moveable objects in game for moving objects and change their speed
class MoveableObject: virtual public GameObject {
protected:
    Vec v_; ///<@param radius vector of object's current speed

    Vec pos_nxt_; ///<@param radius vector of object's speed counted at next iteration of game engine process
    Vec v_nxt_; ///<@param radius vector of object's speed counted at next iteration of game engine process
public:
    explicit MoveableObject(Vec pos = defPos, Vec size = defSize, Vec v = defSpeed);

    virtual ~MoveableObject() override {} ///< todo Спросить Якова про override и virtual

    virtual int countNextParams() = 0;
    virtual int move() = 0;
};


#endif //MYGAME_MOVEABLEOBJECT_H
