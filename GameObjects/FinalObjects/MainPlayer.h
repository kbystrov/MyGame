#ifndef MYGAME_MAINPLAYER_H
#define MYGAME_MAINPLAYER_H

#include "PlayerableObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

class MainPlayer: public PlayerableObject  {
public:
    explicit MainPlayer(Vec pos = defPos, Vec size = defSize, Vec hitbox = defHitbox, Vec v = defSpeed, sf::Texture * texture = nullptr, sf::Sprite sprite = sf::Sprite(), sf::Color color = playerColor);

    virtual ~MainPlayer() override;

    int move() override;
    int updateParams() override;
    int onCollision(PhysicalObject& physicalObject) override;
    dataType sweptAABB(PhysicalObject& physicalObject);
};


#endif //MYGAME_MAINPLAYER_H
