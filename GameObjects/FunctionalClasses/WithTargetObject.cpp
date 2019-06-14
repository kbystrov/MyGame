#include "WithTargetObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

WithTargetObject::WithTargetObject(Vec pos, Vec size, Vec v, Vec wind_size, GameObject * trgt): MoveableObject(pos, size, v, wind_size), GameObject(pos, size, wind_size) {

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
    fprintf(logfile, "WithTargetObject ctr = %p!\n", this);
    #endif // !CTR_DEBUG
}

WithTargetObject::~WithTargetObject() {
    #ifdef CTR_DEBUG
    fprintf(logfile, "WithTargetObject destructor = %p!\n", this);
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
