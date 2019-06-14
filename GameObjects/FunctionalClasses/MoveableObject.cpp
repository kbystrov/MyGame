#include "MoveableObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

MoveableObject::MoveableObject(Vec pos, Vec size, Vec v, Vec wind_size): GameObject(pos, size, wind_size) {

    #ifdef GAME_DEBUG
    ERRNO_CHECK(logfile);
    errno = 0;
    #endif

    errno = setObjType(type_moveable_obj_e);

    #ifdef GAME_DEBUG
    ERRNO_CHECK(logfile);
    errno = 0;
    #endif

    v_ = v;
    pos_tmp_ = pos_ + v_;
    v_tmp_ = v_;

    #ifdef CTR_DEBUG
    printf("MoveableObject ctr = %p!\n", this);
    #endif // !CTR_DEBUG
}

MoveableObject::~MoveableObject() {
    #ifdef CTR_DEBUG
    printf("MoveableObject destructor = %p!\n", this);
    #endif // !CTR_DEBUG
}

int MoveableObject::setSpeed(Vec v) {
    v_ = v;
    return 0;
}

Vec MoveableObject::getSpeed() const {
    return v_;
}
