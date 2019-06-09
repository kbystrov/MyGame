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

    delete texture_;
    texture_ = nullptr;
    textureCount_ = 0;

    delete music_;
    music_ = nullptr;
    songsCount_ = 0;

    delete window_;
    window_ = nullptr;
    windsCount_ = 0;

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
    ERR_CHECK(logfile, 1);

    err_code = createWindow();
    ERR_CHECK(logfile, 1);

    err_code = createMusicTracks();
    ERR_CHECK(logfile, 0);

    err_code = createTextures();
    ERR_CHECK(logfile, 1);

    err_code = genGameObjs();
    ERR_CHECK(logfile, 1);

    return err_code;
}

int GameEngine::createWindow() {

    window_ = new sf::RenderWindow(sf::VideoMode(900, 900), "SFML works!");
    if(window_ == nullptr){
        return ERR_GMENG_CRTWIN_WIN;
    }
    windsCount_ = 1;

    window_->setVerticalSyncEnabled (true);
    window_->setFramerateLimit (25);

    return 0;
}

int GameEngine::createMusicTracks() {

    music_ = new sf::Music();
    if(music_ == nullptr){
        return ERR_GMENG_CRTMUS_MUS;
    }

    if (!music_->openFromFile(defMusic)){
        fprintf(logfile, "No music for game was found\n");
        return ERR_GMENG_CRTMUS_MUSPATH;
    }

    music_->setLoop (true);

    return 0;
}

int GameEngine::createTextures() {
    return 0;
}

int GameEngine::genGameObjs() {
    return 0;
}

int GameEngine::runGame() {
    music_->play();

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

    while (window_->isOpen())
    {
        sf::Event event;
        while (window_->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_->close();
        }

        window_->clear();

        drawable->draw(window_);
        bench->draw(window_);
        player->draw(window_);
        inspector->draw(window_);

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

        window_->display();
    }

    window_->close();

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
