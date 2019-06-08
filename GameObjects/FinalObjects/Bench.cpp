#include "Bench.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

Bench::Bench(Vec pos, Vec size, Vec hitbox, sf::Texture *texture, sf::Sprite sprite, sf::Color color) :
        StaticDrawObject(pos, size, hitbox, texture, sprite, color), PhysicalObject(hitbox, pos, size),
        DrawableObject(pos, size, texture, sprite, color), GameObject(pos, size)
        {
        #ifdef GAME_DEBUG
        ERRNO_CHECK;
        errno = 0;
        #endif

        #ifdef CTR_DEBUG
        printf("Bench ctr!\n");
        #endif // !CTR_DEBUG
        }

Bench::~Bench() {
    texture_ = nullptr;
}

int Bench::onCollision(GameObject &physicalObject) {
    printf("Bench is collided!\n");
    return 0;
}