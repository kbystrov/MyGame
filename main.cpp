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

    gameEngine->runGame();
    /*
    sf::RenderWindow window(sf::VideoMode(900, 900), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    errno = 0;
    DrawableObject * drawable = new DrawableObject(Vec(100, 100), Vec(50, 50), nullptr, sf::Sprite());
    ERRNO_CHECK(logfile);

    errno = 0;
    Bench * bench = new Bench(Vec(300,300), Vec(100,100), Vec(51, 51), nullptr, sf::Sprite(), sf::Color::Yellow);
    ERRNO_CHECK(logfile);

    errno = 0;
    MainPlayer * player = new MainPlayer(Vec(500,500), Vec(10,10), Vec(5, 5), Vec(4,4), nullptr, sf::Sprite(), sf::Color::Green);
    ERRNO_CHECK(logfile);

    errno = 0;
    TrainInspector * inspector = new TrainInspector(player, Vec(800,800), Vec(100,100), Vec(50, 50), Vec(3,3));
    ERRNO_CHECK(logfile);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        drawable->draw(&window);
        bench->draw(&window);
        player->draw(&window);
        inspector->draw(&window);

        player->move();
        inspector->move();

        if (player->isCollided(*bench)){
            bench->onCollision(*player);
            player->onCollision(*bench);
        }

        if (player->isCollided(*inspector)){
            inspector->onCollision(*player);
            player->onCollision(*inspector);
        }

        if (inspector->isCollided(*bench)){
            bench->onCollision(*inspector);
            inspector->onCollision(*bench);
        }

        window.display();
    }
    */
    delete gameEngine;

    return 0;
}
