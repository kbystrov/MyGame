#ifndef MYGAME_ENEMYOBJECT_H
#define MYGAME_ENEMYOBJECT_H

#include "DrawableObject.h"
#include "PhysicalObject.h"
#include "WithTargetObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @def Default color of the enemy
const sf::Color enemyColor = sf::Color::Red;

class EnemyObject: virtual public DrawableObject, virtual public PhysicalObject, virtual public WithTargetObject {
protected:
    bool isAttacking_ = false; ///< @param Flag which identifies that this enemy in attacking state

public:
    explicit EnemyObject(GameObject * trgt = nullptr, Vec pos = defPos, Vec size = defSize, Vec hitbox = defHitbox, Vec v = defSpeed, sf::Texture * texture = nullptr,
            sf::Sprite sprite = sf::Sprite(), sf::Color color = enemyColor, bool attackState = false);

    virtual ~EnemyObject() override;

    bool getAttackState() const;
    int setAttackState(bool state);
};


#endif //MYGAME_ENEMYOBJECT_H
