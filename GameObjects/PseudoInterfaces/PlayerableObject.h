#ifndef MYGAME_PLAYERABLEOBJECT_H
#define MYGAME_PLAYERABLEOBJECT_H

#include "DrawableObject.h"
#include "PhysicalObject.h"
#include "MoveableObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @def Default color for Player
const sf::Color playerColor = sf::Color::Green;

class PlayerableObject: virtual public DrawableObject, virtual public PhysicalObject, virtual public MoveableObject {
private:
    bool isCaught_ = false;
public:
    explicit PlayerableObject(Vec pos = defPos, Vec size = defSize, Vec hitbox = defHitbox, Vec v = defSpeed, sf::Texture * texture = nullptr, sf::Sprite sprite = sf::Sprite(), Vec wind_size = defWindSize, sf::Color color = playerColor);

    virtual ~PlayerableObject() override;

    int setCaugthFlag(bool caugthFlag);
    bool getCaughtFlag() const;
};

#endif //MYGAME_PLAYERABLEOBJECT_H
