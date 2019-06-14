#ifndef MYGAME_ENEMYOBJECT_H
#define MYGAME_ENEMYOBJECT_H

#include "DrawableObject.h"
#include "PhysicalObject.h"
#include "WithTargetObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @def Default color of the enemy
const sf::Color enemyColor = sf::Color::Red;

const uint8_t defCollisCOunt = 3;
const uint8_t collisionStep = defCollisCOunt - 1;

class EnemyObject: virtual public DrawableObject, virtual public PhysicalObject, virtual public WithTargetObject {
protected:
    bool wasCollided_ = false;
    uint8_t collisionCount_ = 0;
    bool isAttacking_ = false; ///< @param Flag which identifies that this enemy in attacking state

public:
    explicit EnemyObject(GameObject * trgt = nullptr, Vec pos = defPos, Vec size = defSize, Vec hitbox = defHitbox, Vec v = defSpeed, sf::Texture * texture = nullptr,
            sf::Sprite sprite = sf::Sprite(), Vec wind_size = defWindSize, sf::Color color = enemyColor, bool attackState = false);

    virtual ~EnemyObject() override;

    void setCollidedStatus(bool collidedStatus);
    bool getCollidedStatus();
    bool getAttackState() const;
    int setAttackState(bool state);
};


#endif //MYGAME_ENEMYOBJECT_H
