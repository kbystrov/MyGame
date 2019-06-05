#include "GameObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

GameObject::GameObject(Vec pos, Vec size) {

    pos_ = pos;

    if(size < 0){
        size_ = defSize;
        #ifdef GAME_DEBUG
        errno = ERR_GAMEOBJ_CTR_SIZE;
        #endif // !GAME_DEBUG
    } else {
        size_ = size;
    }

}

int GameObject::setPos(Vec pos) {
    pos_ = pos;
    return 0;
}

Vec GameObject::getPos() const {
    return pos_;
}

int GameObject::setSize(Vec size) {

    if(size < 0){
        #ifdef GAME_DEBUG
        return ERR_GAMEOBJ_SETSIZE;
        #else
        size_ = defSize;
        #endif // !GAME_DEBUG
    }

    size_ = size;

    return 0;
}

Vec GameObject::getSize() const {
    return size_;
}
