#ifndef MYGAME_WITHTARGETOBJECT_H
#define MYGAME_WITHTARGETOBJECT_H

#include "MoveableObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @class A superclass for all objects that have target for moving
class WithTargetObject: virtual public MoveableObject {
protected:
    GameObject * trgt_ = nullptr; ///< @param Object's target

public:
    explicit WithTargetObject(Vec pos = defPos, Vec size = defSize, Vec v = defSpeed, GameObject * trgt = nullptr);

    virtual ~WithTargetObject() override;

    virtual int findNewTarget() = 0;
    int findPath();
    virtual int flashTarget() = 0;

    int setTarget(GameObject * trgt);
    GameObject * getTarget();
};

#endif //MYGAME_WITHTARGETOBJECT_H
