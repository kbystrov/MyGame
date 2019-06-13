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
            dataType collisionTime = sweptAABB(physicalObject);
            Vec speed_vec(pos_ - pos_tmp_);
            Vec diff_dist(speed_vec * collisionTime);
            pos_ = pos_ - diff_dist;
            printf("Train Inspector was stuck into bench!\n");
        }
            break;
        case type_train_inspector_e: {
            dataType collisionTime = sweptAABB(physicalObject);
            Vec speed_vec(pos_ - pos_tmp_);
            Vec diff_dist(speed_vec * collisionTime);
            pos_ = pos_ - diff_dist;
            printf("Train Inspector was stuck into another train inspector!\n");
        }
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

float TrainInspector::sweptAABB(PhysicalObject& physicalObject) {

    dataType xInvEntry = 0;
    dataType yInvEntry = 0;
    dataType xInvExit = 0;
    dataType yInvExit = 0;

    Vec speed_vec(pos_ - pos_tmp_);
    Vec b1_size = hitbox_ * 2;
    Vec b2_size(physicalObject.getHitbox() * 2);

    Vec b1(pos_ - hitbox_);
    Vec b2(physicalObject.getPos() - physicalObject.getHitbox());

    // find the distance between the objects on the near and far sides for both x and y
    if (speed_vec.x > 0.0f) {
        xInvEntry = (b1.x + b1_size.x) - b2.x;
        xInvExit = (b2.x + b2_size.x) - b1.x;
    } else {
        xInvEntry = (b2.x + b2_size.x) - b1.x;
        xInvExit = b2.x - (b1.x + b1_size.x);
    }

    if (speed_vec.y > 0.0f) {
        yInvEntry = (b1.y + b1_size.y) - b2.y;
        yInvExit = (b2.y + b2_size.y) - b1.y;
    } else {
        yInvEntry = (b2.y + b2_size.y) - b1.y;
        yInvExit = b2.y - (b1.y + b1_size.y);
    }

    // find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
    dataType xEntry = 0;
    dataType yEntry = 0;
    dataType xExit = 0;
    dataType yExit = 0;

    if (speed_vec.x == 0.0f) {
        xEntry = -std::numeric_limits<float>::infinity();
        xExit = std::numeric_limits<float>::infinity();
    } else {
        xEntry = xInvEntry / speed_vec.x;
        xExit = xInvExit / speed_vec.y;
    }

    if (speed_vec.y == 0.0f) {
        yEntry = -std::numeric_limits<float>::infinity();
        yExit = std::numeric_limits<float>::infinity();
    } else {
        yEntry = yInvEntry / speed_vec.y;
        yExit = yInvExit / speed_vec.y;
    }

    // find the earliest/latest times of collision
    float entryTime = std::max(xEntry, yEntry);
    float exitTime = std::min(xExit, yExit);

    // if there was no collision
    if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f) {
        return 1.0f;
    } else { // if there is collision
        // return the time of collision
        return entryTime;
    }

}
