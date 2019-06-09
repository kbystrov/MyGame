#include <SFML/Graphics.hpp>
#include "GameEngine.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

FILE * logfile; ///< @param Global variable for main log of the game

int main()
{

    if ( (logfile = fopen("log/gamelog", "w")) == nullptr ){
        logfile = stderr;
        fprintf(logfile, "Can't open file for logging game - all game warning and error info will be displayed in stderr\n");
    }

    errno = 0;
    GameEngine * gameEngine = new GameEngine();
    if(errno == ERR_GMENG_CRT_CONFNAME){
        fprintf(stderr, "No config file is obtained by game!\n");
        return errno;
    }
    ERRNO_CHECK(logfile);

    int err_code = 0;

    err_code = gameEngine->initGameEngineParams();
    if(err_code == ERR_GMENG_OPNCNFG_FILE){
        fprintf(stderr, "Can not find game file config file: %s\n"
                        "Please try to add this file to required directory or give alternative path to config file\n",
                        defConfigName);
    }
    ERR_CHECK(logfile, 1);

    err_code = gameEngine->runGame();
    ERR_CHECK(logfile, 0);

    delete gameEngine;

    return err_code;
}
