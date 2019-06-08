#include "MoveableObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

MoveableObject::MoveableObject(Vec pos, Vec size, Vec v): GameObject(pos, size) {

    #ifdef GAME_DEBUG
    ERRNO_CHECK;
    errno = 0;
    #endif

    v_ = v;
    pos_tmp_ = pos_ + v_;
    v_tmp_ = v_;

    #ifdef CTR_DEBUG
    printf("MoveableObject ctr!\n");
    #endif // !CTR_DEBUG
}

int MoveableObject::setSpeed(Vec v) {
    v_ = v;
    return 0;
}

Vec MoveableObject::getSpeed() const {
    return v_;
}
