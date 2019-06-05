#ifndef MYGAME_PHYSICALOBJECT_H
#define MYGAME_PHYSICALOBJECT_H

#include "GameObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

const Vec defHitbox = Vec(defSize.x / 2, defSize.y / 2);

//! @class An superclass for all physical objects which may have collisions with other objects and should have some reactions on such collisions
class PhysicalObject: public GameObject {
protected:
    Vec hitbox_; ///< @param vector of distance from the center of object ("pos_" field) - determines the zone of collision for object
public:
    explicit PhysicalObject(Vec hitbox = defHitbox, Vec pos = defPos, Vec size = defSize);

    virtual ~PhysicalObject() override {} ///< todo Спросить Якова про override и virtual

    int setHitbox(Vec hitbox);
    Vec getHitbox() const;
    bool isCollided(const PhysicalObject& physicalObject) const;
    virtual int onCollision() = 0;
};


#endif //MYGAME_PHYSICALOBJECT_H
