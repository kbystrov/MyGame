#include "DrawableObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

/*
DrawableObject::DrawableObject(sf::Texture * texture, sf::Sprite sprite, sf::Color color) {
    texture_ = texture;
    sprite_ = sprite;
    color_ = color;
}
*/

DrawableObject::DrawableObject(Vec pos, Vec size, sf::Texture * texture, sf::Sprite sprite, sf::Color color) : GameObject(pos, size) {
    texture_ = texture;
    sprite_ = sprite;
    color_ = color;
}

DrawableObject::~DrawableObject() {
    texture_ = nullptr;
}

int DrawableObject::draw(sf::RenderTarget * screen) const {

    if(screen == nullptr){
        return ERR_DRAWOBJ_DRAW_SIMPLE_SCREEN;
    }

    int err_code = 0;

    if (sprite_.getTexture()) {
        screen->draw(sprite_);
    } else {
        err_code = drawCircle(pos_, (size_.x + size_.y) / 4, color_, sf::Color::Transparent, screen);
    }

    return err_code;
}

int DrawableObject::draw(Vec pos, sf::RenderTarget * screen) const {

    if(screen == nullptr){
        return ERR_DRAWOBJ_DRAW_POS_SCREEN;
    }

    int err_code = 0;

    if (sprite_.getTexture()) {
        sf::Sprite sprite = sprite_;

        sprite.setOrigin   (size_.x/2, size_.y/2);
        sprite.setPosition (pos.x, pos.y);
        screen->draw (sprite);
    } else {
        err_code = drawCircle (pos_, (size_.x + size_.y) / 4, color_, sf::Color::Transparent, screen);
    }

    return err_code;
}

int drawCircle (Vec pos, float radius, sf::Color fillColor, sf::Color outlineColor, sf::RenderTarget * screen) {

    if(screen == nullptr){
        return ERR_DRAW_CIRCLE_SCREEN;
    }

    if(radius < 0){
        return ERR_DRAW_CIRCLE_RAD;
    }

    sf::CircleShape circle;

    circle.setRadius (radius);
    circle.setFillColor (fillColor);
    circle.setOutlineColor (outlineColor);

    if (outlineColor != sf::Color::Transparent){
        circle.setOutlineThickness (DEF_THICKNESS);
    }

    circle.setOrigin (radius, radius);
    circle.setPosition (pos.x, pos.y);

    screen->draw (circle);

    return 0;
}
