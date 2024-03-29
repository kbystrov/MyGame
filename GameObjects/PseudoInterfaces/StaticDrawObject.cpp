#include "StaticDrawObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

StaticDrawObject::StaticDrawObject(Vec pos, Vec size, Vec hitbox, sf::Texture * texture, sf::Sprite sprite, Vec sprite_size, Vec wind_size, sf::Color color):
        PhysicalObject(hitbox, pos, size, wind_size), DrawableObject(pos, size, texture, sprite, sprite_size, wind_size, color), GameObject(pos, size, wind_size)
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
        fprintf(logfile, "StaticObject ctr = %p!\n", this);
        #endif // !CTR_DEBUG
        }

StaticDrawObject::~StaticDrawObject() {
        #ifdef CTR_DEBUG
        fprintf(logfile, "StaticDrawObject destructor = %p!\n", this);
        #endif // !CTR_DEBUG

        texture_ = nullptr;
}