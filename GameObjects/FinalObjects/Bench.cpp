#include "Bench.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

Bench::Bench(Vec pos, Vec size, Vec hitbox, sf::Texture *texture, sf::Sprite sprite, Vec sprite_size, Vec wind_size, sf::Color color) :
        StaticDrawObject(pos, size, hitbox, texture, sprite, sprite_size, wind_size, color), PhysicalObject(hitbox, pos, size, wind_size),
        DrawableObject(pos, size, texture, sprite, sprite_size, wind_size, color), GameObject(pos, size, wind_size)
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
        fprintf(logfile, "Bench ctr = %p!\n\n", this);
        #endif // !CTR_DEBUG
        }

Bench::~Bench() {
        #ifdef CTR_DEBUG
        fprintf(logfile, "\nBench destructor = %p!\n", this);
        #endif // !CTR_DEBUG

        texture_ = nullptr;
}

int Bench::onCollision(PhysicalObject& physicalObject) {
    fprintf(logfile, "Bench is collided!\n");
    return 0;
}