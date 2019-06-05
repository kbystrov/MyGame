#ifndef MYGAME_PASSENGER_H
#define MYGAME_PASSENGER_H
#include "CharacterObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @def Default color for Passenger
const sf::Color passColor = sf::Color::Yellow;

class Passenger: public CharacterObject {
private:
    bool was_checked = false; ///< @param flag of checked ticket by Train Inspector
    bool isGoing = false; ///< @param flag of Passenger has started his movement to the doors
    Vec  doors_coord; ///< @param Coordinates of the closest doors where Passenger will go at his station

public:
    Passenger():
            Passenger(Vec(), Vec(), Vec(), sf::Sprite(), passColor)
    {}
    Passenger(Vec pos, Vec v, Vec size, sf::Sprite sprite, sf::Color color = passColor):
            CharacterObject(pos, v, size, sprite, color)
    {}

    virtual ~Passenger() override;

    virtual int move() override;
    int showTicket();
};


#endif //MYGAME_PASSENGER_H
