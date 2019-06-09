#include "GameEngine.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

GameEngine::GameEngine(const char * configFileName) {

    if(configFileName = nullptr){
        errno = ERR_GMENG_CRT_CONFNAME;
        return;
    }

}

GameEngine::~GameEngine() {

    if(fileIsOpened_){
        fclose(configFile_);
        configFile_ = nullptr;
        configName_ = nullptr;
        fileIsOpened_ = false;
    }



}

int GameEngine::openConfigFile() {

    if(fileIsOpened_ && (configName_ == nullptr || configFile_ == nullptr) ) {
        return ERR_GMENG_OPNCNFG_INITSTATE;
    } else {
        if ( (configFile_ = fopen(configName_, "r")) == nullptr ) {
            return ERR_GMENG_OPNCNFG_FILE;
        } else {
            fileIsOpened_ = true;
        }
    }

    return 0;
}

int GameEngine::initGameEngineParams() {
    int err_code = 0;

    err_code = openConfigFile();
    ERR_CHECK(logfile);

    err_code = createWindow();
    ERR_CHECK(logfile);

    err_code = createMusicTracks();
    ERR_CHECK(logfile);

    err_code = createTextures();
    ERR_CHECK(logfile);

    err_code = genGameObjs();
    ERR_CHECK(logfile);

    return err_code;
}

int GameEngine::createWindow() {
    return 0;
}

int GameEngine::createMusicTracks() {
    return 0;
}

int GameEngine::createTextures() {
    return 0;
}

int GameEngine::genGameObjs() {
    return 0;
}

int GameEngine::runGame() {
    return 0;
}

bool GameEngine::checkStopEvents() {
    return false;
}

int GameEngine::processMovements() {
    return 0;
}

int GameEngine::processCollisions() {
    return 0;
}

int GameEngine::doRender() {
    return 0;
}
