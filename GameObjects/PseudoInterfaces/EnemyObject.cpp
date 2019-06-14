#include "EnemyObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

EnemyObject::EnemyObject(GameObject * trgt, Vec pos, Vec size, Vec hitbox, Vec v, sf::Texture *texture,
                         sf::Sprite sprite, Vec sprite_size, Vec wind_size,  sf::Color color, bool attackState):
                         WithTargetObject(pos, size, v, wind_size, trgt), PhysicalObject(hitbox, pos, size, wind_size),
                         DrawableObject(pos, size, texture, sprite, sprite_size, wind_size, color), GameObject(pos, size, wind_size)
                         {
                            #ifdef GAME_DEBUG
                            ERRNO_CHECK(logfile);
                            errno = 0;
                            #endif

                            errno = setObjType(type_enemy_obj_e);

                            #ifdef GAME_DEBUG
                            ERRNO_CHECK(logfile);
                            errno = 0;
                            #endif

                            #ifdef CTR_DEBUG
                            fprintf(logfile, "EnemyObject ctr = %p!\n", this);
                            #endif // !CTR_DEBUG

                            isAttacking_ = attackState;
                         }

EnemyObject::~EnemyObject() {
    #ifdef CTR_DEBUG
    fprintf(logfile, "EnemyObject destructor = %p!\n", this);
    #endif // !CTR_DEBUG

    texture_ = nullptr;
    trgt_ = nullptr;
}

bool EnemyObject::getAttackState() const {
    return isAttacking_;
}

int EnemyObject::setAttackState(bool state) {
    isAttacking_ = state;
    return 0;
}

void EnemyObject::setCollidedStatus(bool collidedStatus) {
    wasCollided_ = collidedStatus;
    if(collidedStatus){
        collisionCount_ = (collisionCount_ + 1) % defCollisCOunt;
    } else {
        collisionCount_ = 0;
    }
}

bool EnemyObject::getCollidedStatus() {
    if(wasCollided_){
        collisionCount_ = (collisionCount_ + 1) % defCollisCOunt;
    }
    return wasCollided_;
}
