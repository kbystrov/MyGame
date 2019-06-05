#include "Player.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

int Player::move() {

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Left)) {
        pos_.x -= v_.x;
    }

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Right)) {
        pos_.x += v_.x;
    }

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Up)) {
        pos_.y -= v_.y;
    }

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Down)) {
        pos_.y += v_.y;
    }

    return 0;
}
