#ifndef MYGAME_PASSENGER_H
#define MYGAME_PASSENGER_H
#include "CharacterObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @def Default color for Passenger
const sf::Color passColor = sf::Color::Yellow;

class Passenger: public CharacterObject {
private:
    CharacterObject * target = nullptr;

public:
    Passenger():
            Passenger(Vec(), Vec(), Vec(), sf::Sprite(), passColor)
    {}
    Passenger(Vec pos, Vec v, Vec size, sf::Sprite sprite, sf::Color color = passColor):
            CharacterObject(pos, v, size, sprite, color)
    {}

    virtual ~Passenger() override;

    virtual int move() override;
};


#endif //MYGAME_PASSENGER_H
