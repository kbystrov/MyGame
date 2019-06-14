#include "PhysicalObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

PhysicalObject::PhysicalObject(Vec hitbox, Vec pos, Vec size, Vec wind_size): GameObject(pos, size, wind_size) {

    #ifdef CTR_DEBUG
    printf("PhysicalObject ctr = %p!\n", this);
    #endif // !CTR_DEBUG

    #ifdef GAME_DEBUG
    ERRNO_CHECK(logfile);
    errno = 0;
    #endif

    errno = setObjType(type_physical_obj_e);

    #ifdef GAME_DEBUG
    ERRNO_CHECK(logfile);
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

PhysicalObject::~PhysicalObject() {
    #ifdef CTR_DEBUG
    printf("PhysicalObject destructor = %p!\n", this);
    #endif // !CTR_DEBUG
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

    if( absVec(pos_ - physicalObject.pos_) < (hitbox_ + physicalObject.hitbox_) ){
        return true;
    } else {
        return false;
    }

}

void PhysicalObject::checkBounds() {

    if(pos_.x - hitbox_.x < 0){
        pos_.x = hitbox_.x;
    } else if(pos_.x + hitbox_.x > wind_size_.x){
        pos_.x = wind_size_.x - hitbox_.x;
    }

    if(pos_.y - hitbox_.y < 0){
        pos_.y = hitbox_.y;
    } else if (pos_.y + hitbox_.x > wind_size_.y){
        pos_.y = wind_size_.y - hitbox_.y;
    }

}

