#ifndef MYGAME_GAMEENGINE_H
#define MYGAME_GAMEENGINE_H

#include <stdio.h>
#include <string.h>
#include <SFML/Audio.hpp>
#include "game_def_constants.h"
#include "RadVec.h"
#include "err_codes.h"
#include "proj_macros.h"
#include "characters.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @class Class for processing all game logic with objects, sounds, textures, etc.
class GameEngine {
private:
    const char * configName_ =  defConfigName; ///< @param Config file name to read all levels's params
    FILE * configFile_ = nullptr;              ///< @param Config file to read all levels's params
    bool fileIsOpened_ = false;                ///< @param Flag of config file state (is opened or not)

    sf::RenderWindow * window_ = nullptr;     ///< @param Array of all windows used in game
    size_t windsCount_ = 0;                   ///< @param Number of windows used in game
    sf::Music * music_ = nullptr;             ///< @param Array of all audio compositions used in game
    size_t songsCount_ = 0;                    ///< @param Number of audio compositions used in game
    sf::Texture * texture_ = nullptr;         ///< @param Array of all textures used in game
    size_t textureCount_ = 0;                  ///< @param Number of textures used in game

    GameObject * allObjs_ = nullptr;          ///< @param Array of all objetcs in Game
    size_t allObjsCount_ = 0;                 ///< @param Number of elements in Game Objects Array
    MainPlayer * player_ = nullptr;           ///< @param Player's pointer

    sf::Clock clock_;                          ///< @param Games clock
    bool isAlarm_ = false;                     ///< @param Flag of that Train Inspectors have started their attempts for arresting Player
public:
    explicit GameEngine(const char * configFileName = defConfigName);

    virtual ~GameEngine();

    //! A group of methods for Game Engine initialization with parameters from config file (the predefined format of config file is required!)
    int openConfigFile();
    int closeConfigFile();
    int initGameEngineParams();
    int parseConfig();
    int parseConfigWindows();
    int parseConfigMusic();
    int parseConfigObjects();
    int createWindow();
    int createWindow(uint32_t win_num, uint32_t win_w, uint32_t win_h, const char * title, bool vet_sync_flag, uint32_t frame_rt_lim);
    int createMusicTracks();
    int createTextures();
    int genGameObjs();
    //! A group of methods for game processing
    int runGame();

    bool checkStopEvents();

    int processMovements();
    int processCollisions();

    int doRender();
};


#endif //MYGAME_GAMEENGINE_H
