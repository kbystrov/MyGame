#include "StaticDrawObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

StaticDrawObject::StaticDrawObject(Vec pos, Vec size, Vec hitbox, sf::Texture * texture, sf::Sprite sprite, sf::Color color):
        PhysicalObject(hitbox, pos, size), DrawableObject(pos, size, texture, sprite, color), GameObject(pos, size)
        {
        #ifdef CTR_DEBUG
        printf("StaticObject ctr!\n");
        #endif // !CTR_DEBUG
        }

int StaticDrawObject::onCollision() {
    printf("Is is just test of onCollision function!");
    return 0;
}

