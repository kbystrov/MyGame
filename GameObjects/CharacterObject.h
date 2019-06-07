#ifndef MYGAME_GAMEOBJECT_H
#define MYGAME_GAMEOBJECT_H

#include "RadVec.h"
#include "err_codes.h"
#include "proj_macros.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @def Default radius vector
using Vec = RadVec<float>;
//! @def Default color for CharacterObject
const sf::Color charColor = sf::Color::White;

//!@class Base class for all character objects
class CharacterObject {
protected:
    //! Current parameters' values of object
    Vec pos_;  ///< @param character's current coordinates radius vector (x,y,...)
    Vec v_;    ///< @param character's current speed radius vector (x,y,...)

    //! Parameters' values of object at next step
    Vec pos_tmp_;  ///< @param character's coordinates radius vector (x,y,...) at next step
    Vec v_tmp_;    ///< @param character's speed radius vector (x,y,...) at next step

    Vec size_; ///< @param character's size radius vector (x,y,...)
    sf::Sprite sprite_; ///< @param character's sprite
    sf::Color color_;   ///< @param color in case there is no sprite for character

public:
    CharacterObject(): CharacterObject(Vec(), Vec(), Vec(), sf::Sprite(), charColor) {}
    CharacterObject(Vec pos, Vec v, Vec size, sf::Sprite sprite, sf::Color color = charColor);

    virtual ~CharacterObject() {}

    virtual int draw (sf::RenderTarget * screen) const;
    virtual int draw (Vec pos, sf::RenderTarget * screen) const;
    virtual int move () = 0;

    Vec getPos();
};

int DrawCircle (Vec pos, float radius, sf::Color fillColor, sf::Color outlineColor, sf::RenderTarget* screen);


#endif //MYGAME_GAMEOBJECT_H
