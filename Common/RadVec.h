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

    RadVec operator + (const RadVec <T> vec) { return RadVec( x + vec.x, y + vec.y ); }
    RadVec operator - (const RadVec <T> vec) { return RadVec( x - vec.x, y - vec.y ); }
    bool operator > (const T val) { return (x > val || y > val) ? true : false; }
    bool operator < (const T val) { return (x < val || y < val) ? true : false; }
    bool operator > (const RadVec <T> vec) { return (x > vec.x && y > vec.y) ? true : false; }
    bool operator < (const RadVec <T> vec) { return (x < vec.x && y < vec.y) ? true : false; }

    RadVec operator + (const RadVec <T> vec) const { return RadVec( x + vec.x, y + vec.y ); }
    RadVec operator - (const RadVec <T> vec) const { return RadVec( x - vec.x, y - vec.y ); }
    bool operator > (const T val) const { return (x > val || y > val) ? true : false; }
    bool operator < (const T val) const { return (x < val || y < val) ? true : false; }
    bool operator > (const RadVec <T> vec) const { return (x > vec.x && y > vec.y) ? true : false; }
    bool operator < (const RadVec <T> vec) const { return (x < vec.x && y < vec.y) ? true : false; }
};


#endif //MYGAME_RADVEC_H
