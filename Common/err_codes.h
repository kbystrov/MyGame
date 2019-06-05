#ifndef VECTOR_ERR_CODES_H
#define VECTOR_ERR_CODES_H
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

#define ERR_CHECK if(err_code){ printf("ERROR: %d in LINE: %d in FILE: %s\n", err_code, __LINE__, __FILE__); return err_code;}
#define ERRNO_CHECK if(errno){ printf("ERROR: %d in LINE: %d in FILE: %s\n", errno, __LINE__, __FILE__); }


//!@enum Enumeration of error codes
enum Errors {
    //! Error code: Unknown error code
            ERR_CODE_UNKNOWN = -1,
    //! Error code: GameObject::setSize(Vec size) -> size is a Vector with negative coordinates
            ERR_GAMEOBJ_SETSIZE = 1,
    //! Error code: GameObject::GameObject(Vec pos, Vec size) -> size is a Vector with negative coordinates
            ERR_GAMEOBJ_CTR_SIZE,
    //! Error code: DrawableObject::draw(sf::RenderTarget * screen) -> screen is nullptr
            ERR_DRAWOBJ_DRAW_SIMPLE_SCREEN,
    //! Error code: DrawableObject::draw(Vec pos, sf::RenderTarget * screen) -> screen is nullptr
            ERR_DRAWOBJ_DRAW_POS_SCREEN,
    /** Error code: drawRect (Vec pos, float radius, sf::Color fillColor, sf::Color outlineColor, sf::RenderTarget * screen)
     *              -> screen is nullptr
     */
            ERR_DRAW_RECT_SCREEN,
    /** Error code: drawRect (Vec pos, float radius, sf::Color fillColor, sf::Color outlineColor, sf::RenderTarget * screen)
     *              -> size is a Vector with negative coordinate
     */
            ERR_DRAW_RECT_SIZE,
    //! Error code: PhysicalObject::PhysicalObject(Vec hitbox, Vec pos, Vec size) -> hitbox is a Vector with negative coordinates
            ERR_PHYSOBJ_CTR_HITBOX,
    //! Error code: PhysicalObject::setHitbox(Vec hitbox) -> hitbox is a Vector with negative coordinates
            ERR_PHYSOBJ_SETHITBOX,
    //! Error code: input RenderTraget screen is nullptr in draw function
            ERR_CHAR_OBJ_DRAW_SCREEN,
    //! Error code: input RenderTraget screen is nullptr in draw function with input coordinates
            ERR_CHAR_OBJ_DRAW_POS_SCREEN,
    //! Error code: input RenderTraget screen is nullptr in draw circle function
            ERR_CHAR_OBJ_DRAW_CIRCLE_SCREEN,
};

#endif //VECTOR_ERR_CODES_H
