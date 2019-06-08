#include "WithTargetObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

WithTargetObject::WithTargetObject(Vec pos, Vec size, Vec v, GameObject * trgt): MoveableObject(pos, size, v), GameObject(pos, size) {
    trgt_ = trgt;

    #ifdef CTR_DEBUG
    printf("WithTargetObject ctr!\n");
    #endif // !CTR_DEBUG
}

WithTargetObject::~WithTargetObject() {
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

GameObject * WithTargetObject::getTarget() {
    return trgt_;
}
