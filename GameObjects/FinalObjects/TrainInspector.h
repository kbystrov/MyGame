#ifndef MYGAME_TRAININSPECTOR_H
#define MYGAME_TRAININSPECTOR_H

#include "EnemyObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

class TrainInspector: virtual public EnemyObject {
public:
    explicit TrainInspector(GameObject * trgt = nullptr, Vec pos = defPos, Vec size = defSize, Vec hitbox = defHitbox, Vec v = defSpeed, sf::Texture * texture = nullptr,
                            sf::Sprite sprite = sf::Sprite(), sf::Color color = enemyColor, bool attackState = false);

    virtual ~TrainInspector() override;
    int onCollision(PhysicalObject &physicalObject) override;
    float sweptAABB(PhysicalObject &physicalObject);

    int move() override;
    int updateParams() override;

    int findNewTarget() override;
    int flashTarget() override;
};


#endif //MYGAME_TRAININSPECTOR_H
