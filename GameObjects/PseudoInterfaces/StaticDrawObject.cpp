#include "StaticDrawObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

StaticDrawObject::StaticDrawObject(Vec pos, Vec size, Vec hitbox, sf::Texture * texture, sf::Sprite sprite, sf::Color color):
        PhysicalObject(hitbox, pos, size), DrawableObject(pos, size, texture, sprite, color), GameObject(pos, size)
        {
        #ifdef GAME_DEBUG
        ERRNO_CHECK(logfile);
        errno = 0;
        #endif

        errno = setObjType(type_static_draw_obj_e);

        #ifdef GAME_DEBUG
        ERRNO_CHECK(logfile);
        errno = 0;
        #endif

        #ifdef CTR_DEBUG
        printf("StaticObject ctr!\n");
        #endif // !CTR_DEBUG
        }

StaticDrawObject::~StaticDrawObject() {
        texture_ = nullptr;
}