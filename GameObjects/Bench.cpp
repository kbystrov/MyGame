#include "Bench.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

Bench::Bench(Vec pos, Vec size, Vec hitbox, sf::Texture *texture, sf::Sprite sprite, sf::Color color) :
        StaticDrawObject(pos, size, hitbox, texture, sprite, color), GameObject(pos, size)
        {
        #ifdef CTR_DEBUG
        printf("Bench ctr!\n");
        #endif // !CTR_DEBUG
        }

Bench::~Bench() {
    texture_ = nullptr;
}

int Bench::onCollision(PhysicalObject &physicalObject) {
        return StaticDrawObject::onCollision(physicalObject);
}
