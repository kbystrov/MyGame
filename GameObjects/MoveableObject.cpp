#include "MoveableObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

MoveableObject::MoveableObject(Vec pos, Vec size, Vec v): GameObject(pos, size) {
    v_ = v;
}
