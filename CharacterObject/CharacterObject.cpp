#include "CharacterObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

CharacterObject::CharacterObject(Vec pos, Vec v, Vec size, sf::Sprite sprite, sf::Color color) {
    pos_ = pos;
    v_ = v;
    size_ = size;

    sprite_ = sprite;
    color_ = color;
}

int CharacterObject::draw(sf::RenderTarget * screen) const {

    if(screen == nullptr){
        return ERR_CHAR_OBJ_DRAW_SCREEN;
    }

    int err_code = 0;

    if (sprite_.getTexture()) {
        screen->draw(sprite_);
    } else {
        err_code = DrawCircle(pos_, 2, color_, sf::Color::Transparent, screen);
    }

    return err_code;
}

int CharacterObject::draw(Vec pos, sf::RenderTarget * screen) const {

    if(screen == nullptr){
        return ERR_CHAR_OBJ_DRAW_POS_SCREEN;
    }

    int err_code = 0;

    if (sprite_.getTexture()) {
        sf::Sprite sprite = sprite_;

        sprite.setOrigin   (size_.x/2, size_.y/2);
        sprite.setPosition (pos.x, pos.y);
        screen->draw (sprite);
    } else {
        err_code = DrawCircle (pos_, 2, color_, sf::Color::Transparent, screen);
    }

    return err_code;
}

int DrawCircle (Vec pos, float radius, sf::Color fillColor, sf::Color outlineColor, sf::RenderTarget * screen) {

    #ifdef GAME_DEBUG
    if(screen == nullptr){
        return ERR_CHAR_OBJ_DRAW_CIRCLE_SCREEN;
    }
    #endif !GAME_DEBUG

    sf::CircleShape circle;

    circle.setRadius (radius);
    circle.setFillColor (fillColor);
    circle.setOutlineColor (outlineColor);
    if (outlineColor != sf::Color::Transparent) circle.setOutlineThickness (3);

    circle.setOrigin (radius, radius);
    circle.setPosition (pos.x, pos.y);

    screen->draw (circle);

    return 0;
}

