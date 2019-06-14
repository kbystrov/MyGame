#ifndef MYGAME_PHYSICALOBJECT_H
#define MYGAME_PHYSICALOBJECT_H

#include <limits>
#include "GameObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @def Default hitbox for physical objects
const Vec defHitbox = Vec(defSize.x / 2, defSize.y / 2);

//! @class A superclass for all physical objects which may have collisions with other objects and should have some reactions on such collisions
class PhysicalObject: virtual public GameObject {
protected:
    Vec hitbox_; ///< @param vector of distance from the center of object ("pos_" field) - determines the zone of collision for object
public:
    explicit PhysicalObject(Vec hitbox = defHitbox, Vec pos = defPos, Vec size = defSize, Vec wind_size = defWindSize);

    virtual ~PhysicalObject() override;

    int setHitbox(Vec hitbox);
    Vec getHitbox() const;
    bool isCollided(const PhysicalObject& physicalObject) const;
    void checkBounds();
    virtual int onCollision(PhysicalObject& physicalObject) = 0;
};


#endif //MYGAME_PHYSICALOBJECT_H
