#ifndef MYGAME_RADVEC_H
#define MYGAME_RADVEC_H

#include <SFML/Graphics.hpp>
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

template <typename T>
struct RadVec{
    T x, y;

    RadVec() : x (0), y (0) {}

    template <typename U1, typename U2>
    RadVec (U1 anX, U2 anY) : x ((T) anX), y ((T) anY) {}

    template <typename U>
    RadVec (const RadVec <U>& vec) : RadVec(vec.x, vec.y) {}

    template <typename U>
    RadVec (const sf::Vector2 <U>& vec) : RadVec(vec.x, vec.y) {}
};


#endif //MYGAME_RADVEC_H
