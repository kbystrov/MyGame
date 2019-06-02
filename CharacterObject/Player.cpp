#include "Player.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

int Player::move() {

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Left)) {
        v_.x -= 1;
    }

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Right)) {
        v_.x += 1;
    }

    return 0;
}
