#include "TrainInspector.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

TrainInspector::TrainInspector(GameObject *trgt, Vec pos, Vec size, Vec hitbox, Vec v, sf::Texture *texture,
                               sf::Sprite sprite, sf::Color color, bool attackState) :
                               EnemyObject(trgt, pos, size, hitbox, v, texture, sprite, color, attackState),
                               WithTargetObject(pos, size, v, trgt),
                               MoveableObject(pos, size, v), PhysicalObject(hitbox, pos, size),
                               DrawableObject(pos, size, texture, sprite, color), GameObject(pos, size)
                               {
                                #ifdef GAME_DEBUG
                                ERRNO_CHECK(logfile);
                                errno = 0;
                                #endif

                                errno = setObjType(type_train_inspector_e);

                                #ifdef GAME_DEBUG
                                ERRNO_CHECK(logfile);
                                errno = 0;
                                #endif

                                #ifdef CTR_DEBUG
                                printf("TrainInspector ctr!\n");
                                #endif // !CTR_DEBUG

                               }

int TrainInspector::onCollision(GameObject& physicalObject) {

    gameType collided_type = physicalObject.getObjType();

    switch(collided_type){
        case type_main_player_e:
            printf("Player is caught!\n");
            break;
        case type_bench_e:
            printf("Train Inspector was stuck into bench!\n");
            break;
        case type_train_inspector_e:
            printf("Train Inspector was stuck into another train inspector!\n");
            break;
        default:
            printf("Unknown collision!\n");
            break;
    }

    return 0;
}

int TrainInspector::move() {

    Vec direction = trgt_->getPos() - pos_;

    if( direction.x > hitbox_.x ){
        pos_.x += v_.x;
    } else if ( direction.x < (- hitbox_.x) ){
        pos_.x -= v_.x;
    }

    if( direction.y > hitbox_.y ){
        pos_.y += v_.y;
    } else if (direction.y < (- hitbox_.y)) {
        pos_.y -= v_.y;
    }

    return 0;
}

int TrainInspector::updateParams() {
    v_tmp_ = v_;
    pos_tmp_ = pos_;
    return 0;
}

int TrainInspector::findNewTarget() {
    return 0;
}

int TrainInspector::flashTarget() {
    trgt_ = nullptr;
    return 0;
}
