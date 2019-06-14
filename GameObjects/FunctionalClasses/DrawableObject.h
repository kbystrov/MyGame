#ifndef MYGAME_DRAWABLEOBJECT_H
#define MYGAME_DRAWABLEOBJECT_H

#include "GameObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @def Default color for DrawableObject
const sf::Color defDrawColor = sf::Color::White;
//! @def Default thickness for circles
const int DEF_THICKNESS = 3;

//! @class A superclass for drawable objects
class DrawableObject: virtual public GameObject {
protected:
    sf::Texture * texture_ = nullptr;   ///< @param The pointer to this object texture (is stored under GameEngine)
    sf::Sprite sprite_;                 ///< @param object's current sprite
    sf::Color color_;                   ///< @param color in case there is no sprite for object
public:
    explicit DrawableObject(Vec pos = defPos, Vec size = defSize, sf::Texture * texture = nullptr, sf::Sprite sprite = sf::Sprite(), Vec wind_size = defWindSize, sf::Color color = defDrawColor);

    virtual ~DrawableObject() override;

    virtual int draw (sf::RenderTarget * screen) const;
    virtual int draw (Vec pos, sf::RenderTarget * screen) const;
};

int drawRect (Vec pos, Vec size, sf::Color fillColor, sf::Color outlineColor, sf::RenderTarget * screen);


#endif //MYGAME_DRAWABLEOBJECT_H
