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
                                printf("TrainInspector ctr = %p!\n", this);
                                #endif // !CTR_DEBUG

                               }


TrainInspector::~TrainInspector() {
    #ifdef CTR_DEBUG
    printf("\nTrainInspector destructor = %p!\n", this);
    #endif // !CTR_DEBUG

    texture_ = nullptr;
    trgt_ = nullptr;
}

int TrainInspector::onCollision(PhysicalObject& physicalObject) {

    gameType collided_type = physicalObject.getObjType();

    switch(collided_type){
        case type_main_player_e:
            printf("Player is caught!\n");
            break;
        case type_bench_e: {
            Vec speed_vec(pos_ - pos_tmp_);
            float speed_norm = sqrt(speed_vec.x * speed_vec.x + speed_vec.y * speed_vec.y);
            Vec obj_pos(physicalObject.getPos());
            Vec obj_hitbox(physicalObject.getHitbox());
            if(speed_vec.x > 0){
                if(speed_vec.y > 0){

                } else {

                }
            } else {
                if(speed_vec.y > 0){

                } else {

                }
            }
            /*
            if (pos_ > obj_pos) {
                pos_ = obj_pos + hitbox_ + obj_hitbox;
            } else if (pos_ < obj_pos) {
                pos_ = obj_pos - hitbox_ - obj_hitbox;
            } else if (pos_.x < obj_pos.x && pos_.y > obj_pos.y) {
                pos_.x = obj_pos.x - hitbox_.x - obj_hitbox.x;
                pos_.y = obj_pos.y + hitbox_.y + obj_hitbox.y;
            } else {
                pos_.x = obj_pos.x + hitbox_.x + obj_hitbox.x;
                pos_.y = obj_pos.y - hitbox_.y - obj_hitbox.y;
            }*/
            printf("Train Inspector was stuck into bench!\n");
        }
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

    if(pos_.x - hitbox_.x < 0){
        pos_.x = hitbox_.x;
    } else if(pos_.x + hitbox_.x > 1280){
        pos_.x = 1280 - hitbox_.x;
    }

    if(pos_.y - hitbox_.y < 0){
        pos_.y = hitbox_.y;
    } else if (pos_.y + hitbox_.x > 720){
        pos_.y = 720 - hitbox_.y;
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
