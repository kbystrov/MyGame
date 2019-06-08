#include "PhysicalObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

PhysicalObject::PhysicalObject(Vec hitbox, Vec pos, Vec size): GameObject(pos, size) {

    #ifdef CTR_DEBUG
    printf("PhysicalObject ctr!\n");
    #endif // !CTR_DEBUG

    #ifdef GAME_DEBUG
    ERRNO_CHECK;
    errno = 0;
    #endif

    errno = setObjType(type_physical_obj_e);

    #ifdef GAME_DEBUG
    ERRNO_CHECK;
    errno = 0;
    #endif

    if( hitbox < 0 ){
        hitbox_ = defHitbox;
        #ifdef GAME_DEBUG
        errno = ERR_PHYSOBJ_CTR_HITBOX;
        #endif // !GAME_DEBUG
    } else {
        hitbox_ = hitbox;
    }

}

int PhysicalObject::setHitbox(Vec hitbox) {

    if(hitbox < 0){
        hitbox_ = defHitbox;
        #ifdef GAME_DEBUG
        return ERR_PHYSOBJ_SETHITBOX;
        #endif // !GAME_DEBUG
    } else {
        hitbox_ = hitbox;
    }

    return 0;
}

Vec PhysicalObject::getHitbox() const {
    return hitbox_;
}

bool PhysicalObject::isCollided(const PhysicalObject& physicalObject) const {

    if( (pos_ - physicalObject.pos_) < (hitbox_ + physicalObject.hitbox_) ){
        return true;
    } else {
        return false;
    }

}


