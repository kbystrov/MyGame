#include "MainPlayer.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

MainPlayer::MainPlayer(Vec pos, Vec size, Vec hitbox, Vec v, sf::Texture * texture, sf::Sprite sprite, sf::Color color)
        : PlayerableObject(pos, size, hitbox, v, texture, sprite, color),
        DrawableObject(pos, size, texture, sprite, color), PhysicalObject(hitbox, pos, size),
        MoveableObject(pos,size, v), GameObject(pos, size)
        {
        #ifdef GAME_DEBUG
        ERRNO_CHECK(logfile);
        errno = 0;
        #endif

        errno = setObjType(type_main_player_e);

        #ifdef GAME_DEBUG
        ERRNO_CHECK(logfile);
        errno = 0;
        #endif

        #ifdef CTR_DEBUG
        printf("MainPlayer ctr = %p!\n\n", this);
        #endif // !CTR_DEBUG
        }

MainPlayer::~MainPlayer() {
    #ifdef CTR_DEBUG
    printf("\nMainPlayer destructor = %p!\n", this);
    #endif // !CTR_DEBUG

    texture_ = nullptr;
}

int MainPlayer::move() {

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Left)) {
        pos_.x -= v_.x;
    }

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Right)) {
        pos_.x += v_.x;
    }

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Up)) {
        pos_.y -= v_.y;
    }

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Down)) {
        pos_.y += v_.y;
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

int MainPlayer::updateParams() {
    v_tmp_ = v_;
    pos_tmp_ = pos_;
    return 0;
}

int MainPlayer::onCollision(PhysicalObject& physicalObject) {
    printf("MainPlayer is collided!\n");
    return 0;
}
