#ifndef MYGAME_STATICDRAWOBJECT_H
#define MYGAME_STATICDRAWOBJECT_H

#include "DrawableObject.h"
#include "PhysicalObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

class StaticDrawObject: public DrawableObject, PhysicalObject {
public:
    explicit StaticDrawObject(Vec pos = defPos, Vec size = defSize, Vec hitbox = defHitbox, sf::Texture * texture = nullptr, sf::Sprite sprite = sf::Sprite(), sf::Color color = defDrawColor);

    virtual ~StaticDrawObject() override {} ///< todo Спросить Якова про override и virtual

    int onCollision() override;
};


#endif //MYGAME_STATICDRAWOBJECT_H
