#include "TrainInspector.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

TrainInspector::TrainInspector(GameObject *trgt, Vec pos, Vec size, Vec hitbox, Vec v, sf::Texture *texture,
                               sf::Sprite sprite, sf::Color color, bool attackState) :
                               EnemyObject(trgt, pos, size, hitbox, v, texture, sprite, color, attackState),
                               WithTargetObject(pos, size, v, trgt), PhysicalObject(hitbox, pos, size),
                               DrawableObject(pos, size, texture, sprite, color), GameObject(pos, size)
                               {
                                #ifdef GAME_DEBUG
                                ERRNO_CHECK;
                                errno = 0;
                                #endif

                                errno = setObjType(type_train_inspector_e);

                                #ifdef GAME_DEBUG
                                ERRNO_CHECK;
                                errno = 0;
                                #endif

                                #ifdef CTR_DEBUG
                                printf("TrainInspector ctr!\n");
                                #endif // !CTR_DEBUG

                               }

int TrainInspector::onCollision(GameObject& physicalObject) {

    return 0;
}

int TrainInspector::move() {
    return 0;
}

int TrainInspector::updateParams() {
    return 0;
}

int TrainInspector::findNewTarget() {
    return 0;
}

int TrainInspector::flashTarget() {
    return setTarget(nullptr);
}
