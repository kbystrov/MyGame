#include "PlayerableObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

PlayerableObject::PlayerableObject(Vec pos, Vec size, Vec hitbox, Vec v, sf::Texture * texture, sf::Sprite sprite,
                                   sf::Color color):
                                   DrawableObject(pos, size, texture, sprite, color), PhysicalObject(hitbox, pos, size),
                                   MoveableObject(pos,size, v), GameObject(pos, size)
                                   {
                                    #ifdef GAME_DEBUG
                                    ERRNO_CHECK;
                                    errno = 0;
                                    #endif

                                    #ifdef CTR_DEBUG
                                    printf("PlayerableObject ctr!\n");
                                    #endif // !CTR_DEBUG
                                    }

PlayerableObject::~PlayerableObject() {
    texture_ = nullptr;
}
