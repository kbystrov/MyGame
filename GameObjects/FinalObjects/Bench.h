#ifndef MYGAME_BENCH_H
#define MYGAME_BENCH_H

#include "StaticDrawObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

class Bench: virtual public StaticDrawObject {
public:
    explicit Bench(Vec pos = defPos, Vec size = defSize, Vec hitbox = defHitbox, sf::Texture * texture = nullptr, sf::Sprite sprite = sf::Sprite(), Vec wind_size = defWindSize, sf::Color color = defDrawColor);

    virtual ~Bench() override;

    virtual int onCollision(PhysicalObject &physicalObject) override;
};


#endif //MYGAME_BENCH_H
