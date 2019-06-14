#include "DrawableObject.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

DrawableObject::DrawableObject(Vec pos, Vec size, sf::Texture * texture, sf::Sprite sprite, Vec sprite_size, Vec wind_size, sf::Color color) : GameObject(pos, size, wind_size) {

    #ifdef CTR_DEBUG
    fprintf(logfile, "DrawableObject ctr = %p!\n", this);
    #endif // !CTR_DEBUG

    #ifdef GAME_DEBUG
    ERRNO_CHECK(logfile);
    errno = 0;
    #endif

    errno = setObjType(type_drawable_obj_e);

    #ifdef GAME_DEBUG
    ERRNO_CHECK(logfile);
    errno = 0;
    #endif

    if(sprite_size < 0) {
        sprite_size = defSpriteSize;
    } else {
        sprite_size_ = sprite_size;
    }

    texture_ = texture;
    sprite_ = sprite;
    color_ = color;
    sprite_size_ = sprite_size;
}

DrawableObject::~DrawableObject() {

    #ifdef CTR_DEBUG
    fprintf(logfile, "DrawableObject destructor = %p!\n", this);
    #endif // !CTR_DEBUG

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
        err_code = drawRect(pos_, size_, color_, sf::Color::Transparent, screen);
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

        //sprite.setOrigin   (size_.x/2, size_.y/2);
        sprite.setPosition (pos.x, pos.y);
        sprite.setTextureRect(sf::IntRect(0, 0, sprite_size_.x, sprite_size_.y));
        sprite.setScale(sf::Vector2f(size_.x / sprite_size_.x, size_.y / sprite_size_.y));
        screen->draw (sprite);
    } else {
        err_code = drawRect (pos_, size_, color_, sf::Color::Transparent, screen);
    }

    return err_code;
}

int drawRect (Vec pos, Vec size, sf::Color fillColor, sf::Color outlineColor, sf::RenderTarget * screen) {

    if(screen == nullptr){
        return ERR_DRAW_RECT_SCREEN;
    }

    if(size < 0){
        return ERR_DRAW_RECT_SIZE;
    }

    sf::RectangleShape circle;

    circle.setSize(sf::Vector2f(size.x, size.y));
    circle.setFillColor (fillColor);
    circle.setOutlineColor (outlineColor);

    if (outlineColor != sf::Color::Transparent){
        circle.setOutlineThickness (DEF_THICKNESS);
    }

    circle.setOrigin (size.x/2, size.y/2);
    circle.setPosition (pos.x, pos.y);

    screen->draw (circle);

    return 0;
}
