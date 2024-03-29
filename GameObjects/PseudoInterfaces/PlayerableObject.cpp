#include "PlayerableObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

PlayerableObject::PlayerableObject(Vec pos, Vec size, Vec hitbox, Vec v, sf::Texture * texture, sf::Sprite sprite, Vec sprite_size, Vec wind_size,
                                   sf::Color color):
                                   DrawableObject(pos, size, texture, sprite, sprite_size, wind_size, color), PhysicalObject(hitbox, pos, size, wind_size),
                                   MoveableObject(pos,size, v, wind_size), GameObject(pos, size, wind_size)
                                   {
                                    #ifdef GAME_DEBUG
                                    ERRNO_CHECK(logfile);
                                    errno = 0;
                                    #endif

                                    errno = setObjType(type_playable_obj_e);

                                    #ifdef GAME_DEBUG
                                    ERRNO_CHECK(logfile);
                                    errno = 0;
                                    #endif

                                    #ifdef CTR_DEBUG
                                    fprintf(logfile, "PlayerableObject ctr = %p!\n", this);
                                    #endif // !CTR_DEBUG
                                    }

PlayerableObject::~PlayerableObject() {
    #ifdef CTR_DEBUG
    fprintf(logfile, "PlayerableObject destructor = %p!\n", this);
    #endif // !CTR_DEBUG

    texture_ = nullptr;
}

int PlayerableObject::setCaugthFlag(bool caugthFlag) {
    isCaught_ = caugthFlag;
    return 0;
}

bool PlayerableObject::getCaughtFlag() const {
    return isCaught_;
}
