#ifndef MYGAME_TRAININSPECTOR_H
#define MYGAME_TRAININSPECTOR_H

#include "CharacterObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @def Default color for Train Ispector
const sf::Color trainInspColor = sf::Color::Red;

class TrainInspector: public CharacterObject {
private:
    CharacterObject * target = nullptr;

public:
    TrainInspector():
        TrainInspector(Vec(), Vec(), Vec(), sf::Sprite(), trainInspColor)
        {}
    TrainInspector(Vec pos, Vec v, Vec size, sf::Sprite sprite, sf::Color color = trainInspColor):
        CharacterObject(pos, v, size, sprite, color)
        {}

    virtual ~TrainInspector() override;

    int findTarget() const;
    virtual int move() override;
};


#endif //MYGAME_TRAININSPECTOR_H
