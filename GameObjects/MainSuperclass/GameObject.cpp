#include "GameObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

GameObject::GameObject(Vec pos, Vec size) {

    #ifdef CTR_DEBUG
    printf("\nGameObject ctr = %p!\n", this);
    #endif // !CTR_DEBUG

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

GameObject::~GameObject() {
    #ifdef CTR_DEBUG
    printf("GameObject destructor = %p!\n", this);
    #endif // !CTR_DEBUG
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

int GameObject::setObjType(gameType obj_type) {

    if(obj_type > GAME_TYPES_TOTAL || obj_type < type_unknown_e){
        return ERR_GAMEOBJ_SETOBJTYPE;
    }

    obj_type_ = obj_type;

    return 0;
}

gameType GameObject::getObjType() const {
    return obj_type_;
}


