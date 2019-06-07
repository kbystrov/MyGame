#ifndef MYGAME_BENCH_H
#define MYGAME_BENCH_H

#include "PhysicalObject.h"
#include "StaticDrawObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

class Bench: public StaticDrawObject {
public:
    explicit Bench(Vec pos = defPos, Vec size = defSize, Vec hitbox = defHitbox, sf::Texture * texture = nullptr, sf::Sprite sprite = sf::Sprite(), sf::Color color = defDrawColor);

    virtual ~Bench() override;

    int onCollision(PhysicalObject * physicalObject) override;
};


#endif //MYGAME_BENCH_H
