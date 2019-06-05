#ifndef VECTOR_ERR_CODES_H
#define VECTOR_ERR_CODES_H
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

#define err_tostr(err_code) #err_code

//!@enum Enumeration of error codes
enum Errors {
    //! Error code: Unknown error code
            ERR_CODE_UNKNOWN = -1,
    //! Error code: GameObject::setSize(Vec size) -> size is a Vector with negative coordinates
            ERR_GAMEOBJ_SETSIZE = 1,
    //! Error code: GameObject::GameObject(Vec pos, Vec size) -> size is a Vector with negative coordinates
            ERR_GAMEOBJ_CTR_SIZE,
    //! Error code: input RenderTraget screen is nullptr in draw function
            ERR_CHAR_OBJ_DRAW_SCREEN,
    //! Error code: input RenderTraget screen is nullptr in draw function with input coordinates
            ERR_CHAR_OBJ_DRAW_POS_SCREEN,
    //! Error code: input RenderTraget screen is nullptr in draw circle function
            ERR_CHAR_OBJ_DRAW_CIRCLE_SCREEN,
};

#endif //VECTOR_ERR_CODES_H
