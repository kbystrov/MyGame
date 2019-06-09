#ifndef VECTOR_ERR_CODES_H
#define VECTOR_ERR_CODES_H
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

#define RETERROR(flg, err_code) if(flg){ return err_code;};

#define ERR_CHECK(logfile, retflg) if(err_code){ fprintf( (logfile == nullptr) ? stderr : logfile, "ERROR: %d in LINE: %d in FILE: %s\n", err_code, __LINE__, __FILE__); RETERROR(retflg, err_code) }
#define ERRNO_CHECK(logfile) if(errno) { fprintf( (logfile == nullptr) ? stderr : logfile, "ERROR: %d in LINE: %d in FILE: %s\n", errno, __LINE__, __FILE__);}

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
    //! Error code: WithTargetObject::findPath() -> Object's target is nullptr
            ERR_WTHTRGT_FNDPTH_TRGT,
    //! Error code: GameObject::setObjType(gameType obj_type) -> obj_type has non-appropriate value
            ERR_GAMEOBJ_SETOBJTYPE,
    //! Error code: GameEngine::GameEngine(const char * configFileName) -> configFileName is nullptr
            ERR_GMENG_CRT_CONFNAME,
    //! Error code: GameEngine::openConfigFile() -> strange Game Engine params before trying to open config file
            ERR_GMENG_OPNCNFG_INITSTATE,
    //! Error code: GameEngine::openConfigFile() -> error during opening config file
            ERR_GMENG_OPNCNFG_FILE,
    //! Error code: GameEngine::createWindow() -> error during allocating memory for window
            ERR_GMENG_CRTWIN_WIN,
    //! Error code: GameEngine::createMusicTracks() -> error during allocating memory for music
            ERR_GMENG_CRTMUS_MUS,
    //! Error code: GameEngine::createMusicTracks() -> no music was found in resources directory
            ERR_GMENG_CRTMUS_MUSPATH,
    //! Error code: GameEngine::createWindow() -> config file is not opened
            ERR_GMENG_CRTWIN_FILECLS,
    //! Error code: GameEngine::createMusicTracks() -> config file is not opened
            ERR_GMENG_CRTMUS_FILECLS,
};

#endif //VECTOR_ERR_CODES_H
