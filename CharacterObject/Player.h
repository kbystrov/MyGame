#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H

#include "CharacterObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @def Default color for Player
const sf::Color playerColor = sf::Color::Green;

class Player: public CharacterObject {
public:
    Player():
            Player(Vec(), Vec(), Vec(), sf::Sprite(), playerColor)
    {}
    Player(Vec pos, Vec v, Vec size, sf::Sprite sprite, sf::Color color = playerColor):
    CharacterObject(pos, v, size, sprite, color)
    {}

    ~Player();

    virtual int move() override;
};


#endif //MYGAME_PLAYER_H
