#include "MoveableObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

MoveableObject::MoveableObject(Vec pos, Vec size, Vec v): GameObject(pos, size) {
    v_ = v;
    pos_tmp_ = pos_ + v_;
    v_tmp_ = v_;
}
