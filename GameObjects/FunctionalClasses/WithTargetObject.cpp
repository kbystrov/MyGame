#include "WithTargetObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

WithTargetObject::WithTargetObject(Vec pos, Vec size, Vec v, GameObject * trgt): MoveableObject(pos, size, v), GameObject(pos, size) {

    #ifdef GAME_DEBUG
    ERRNO_CHECK(logfile);
    errno = 0;
    #endif

    errno = setObjType(type_with_target_obj_e);

    #ifdef GAME_DEBUG
    ERRNO_CHECK(logfile);
    errno = 0;
    #endif

    trgt_ = trgt;

    #ifdef CTR_DEBUG
    printf("WithTargetObject ctr = %p!\n", this);
    #endif // !CTR_DEBUG
}

WithTargetObject::~WithTargetObject() {
    #ifdef CTR_DEBUG
    printf("WithTargetObject destructor = %p!\n", this);
    #endif // !CTR_DEBUG

    trgt_ = nullptr;
}

int WithTargetObject::findPath() {

    if(trgt_ == nullptr){
        return ERR_WTHTRGT_FNDPTH_TRGT;
    }

    return 0;
}

int WithTargetObject::setTarget(GameObject * trgt) {
    trgt_ = trgt;
    return 0;
}

GameObject * WithTargetObject::getTarget() const {
    return trgt_;
}
