#include "Bench.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

Bench::Bench(Vec pos, Vec size, Vec hitbox, sf::Texture *texture, sf::Sprite sprite, sf::Color color) :
        StaticDrawObject(pos, size, hitbox, texture, sprite, color), PhysicalObject(hitbox, pos, size),
        DrawableObject(pos, size, texture, sprite, color), GameObject(pos, size)
        {
        #ifdef GAME_DEBUG
        ERRNO_CHECK(logfile);
        errno = 0;
        #endif

        errno = setObjType(type_bench_e);

        #ifdef GAME_DEBUG
        ERRNO_CHECK(logfile);
        errno = 0;
        #endif

        #ifdef CTR_DEBUG
        printf("Bench ctr = %p!\n\n", this);
        #endif // !CTR_DEBUG
        }

Bench::~Bench() {
        #ifdef CTR_DEBUG
        printf("\nBench destructor = %p!\n", this);
        #endif // !CTR_DEBUG

        texture_ = nullptr;
}

int Bench::onCollision(GameObject &physicalObject) {
    printf("Bench is collided!\n");
    return 0;
}