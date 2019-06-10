#include "EnemyObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

EnemyObject::EnemyObject(GameObject * trgt, Vec pos, Vec size, Vec hitbox, Vec v, sf::Texture *texture,
                         sf::Sprite sprite, sf::Color color, bool attackState):
                         WithTargetObject(pos, size, v, trgt), PhysicalObject(hitbox, pos, size),
                         DrawableObject(pos, size, texture, sprite, color), GameObject(pos, size)
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
                            printf("EnemyObject ctr!\n");
                            #endif // !CTR_DEBUG

                            isAttacking_ = attackState;
                         }

EnemyObject::~EnemyObject() {
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
