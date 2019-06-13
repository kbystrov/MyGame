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
    //! @param Inner class for processing GameObjects
    class objProcessor {
    public:
        int procMainPlayer(GameObject * gameObj, size_t objInd, const GameEngine& gameEngine);
        int procTrainInspector(GameObject * gameObj, size_t objInd, const GameEngine& gameEngine);
        int procBench(GameObject * gameObj, size_t objInd, const GameEngine& gameEngine);
    };

    objProcessor proc_;

    const char * configName_ =  defConfigName; ///< @param Config file name to read all levels's params
    FILE * configFile_ = nullptr;              ///< @param Config file to read all levels's params
    bool fileIsOpened_ = false;                ///< @param Flag of config file state (is opened or not)

    sf::RenderWindow * window_ = nullptr;      ///< @param Array of all windows used in game
    size_t windsCount_ = 0;                    ///< @param Number of windows used in game
    sf::Music * music_ = nullptr;              ///< @param Array of all audio compositions used in game
    size_t songsCount_ = 0;                    ///< @param Number of audio compositions used in game
    sf::Texture ** texture_ = nullptr;         ///< @param Array of pointers to all textures used in game
    size_t textureCount_ = 0;                  ///< @param Number of textures used in game
    Vec wind_size_;

    bool cfgObjNumCounted_ = false;
    GameObject ** allObjs_ = nullptr;          ///< @param Array of pointers to all objects in Game
    size_t allObjsCount_ = 0;                  ///< @param Number of elements in Game Objects Array
    MainPlayer * player_ = nullptr;            ///< @param Player's pointer
    size_t playerNum_ = 1;
    size_t enemyNum_ = 0;
    size_t neutralNum_ = 0;
    size_t staticObjNum_ = 0;

    sf::Clock clock_;                          ///< @param Games clock
    bool isAlarm_ = false;                     ///< @param Flag of that Train Inspectors have started their attempts for arresting Player

    /** @def Typedef for function which takes pointer to Game Object as argument and returns int value (for possible error codes)
     * - it is used to have its own managing process for each type of Game Objects in the same  Game Engine
    */
    typedef int (objProcessor:: * objProcFunc)(GameObject *, size_t, const GameEngine&);
    //! @param Array of pointer to functions which processes each type of Game Object in unique way
    objProcFunc procFuncArr_[3] = {&objProcessor::procMainPlayer, &objProcessor::procTrainInspector, &objProcessor::procBench};

    //! A group of methods for Game Engine initialization with parameters from config file (the predefined format of config file is required!)
    int openConfigFile();
    int closeConfigFile();
    int parseConfig();
    int parseConfigWindows();
    int parseConfigMusic();
    int parseConfigObjects();
    int parseObjNums();
    int parseObjs(gameType obj_type);
    int createWindow(uint32_t win_num, uint32_t win_w, uint32_t win_h, const char * title, bool vet_sync_flag, uint32_t frame_rt_lim);
    int createMusicTracks(uint32_t mus_num, const char * musPath, bool setLoop);
    int createTexture(const char * texture_path, sf::Texture ** texture_ptr);
    int genGameObjs(gameType obj_type, Vec size = defSize, Vec hitbox = defHitbox, sf::Texture * texture = nullptr, Vec v = defSpeed);

    //! A group of methods for game processing
    bool checkStopEvents();

public:
    explicit GameEngine(const char * configFileName = defConfigName);

    virtual ~GameEngine();

    int initGameEngineParams();
    int runGame();
};

#endif //MYGAME_GAMEENGINE_H
