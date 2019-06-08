#include "MainPlayer.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

MainPlayer::MainPlayer(Vec pos, Vec size, Vec hitbox, Vec v, sf::Texture *texture, sf::Sprite sprite, sf::Color color)
        : PlayerableObject(pos, size, hitbox, v, texture, sprite, color),
        DrawableObject(pos, size, texture, sprite, color), PhysicalObject(hitbox, pos, size),
        MoveableObject(pos,size, v), GameObject(pos, size)
        {
        #ifdef GAME_DEBUG
        ERRNO_CHECK;
        errno = 0;
        #endif

        errno = setObjType(type_main_player_e);

        #ifdef GAME_DEBUG
        ERRNO_CHECK;
        errno = 0;
        #endif

        #ifdef CTR_DEBUG
        printf("MainPlayer ctr!\n\n");
        #endif // !CTR_DEBUG
        }

MainPlayer::~MainPlayer() {
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

    return 0;
}

int MainPlayer::updateParams() {
    v_tmp_ = v_;
    pos_tmp_ = pos_;
    return 0;
}

int MainPlayer::onCollision(GameObject &physicalObject) {
    printf("MainPlayer is collided!\n");
    return 0;
}
