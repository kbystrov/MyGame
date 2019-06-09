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

    if(fileIsOpened_) {

        char tmp[TMP_STR_SIZE] = {};
        uint32_t win_num = defWinNum;
        uint32_t win_w = defWinSize;
        uint32_t win_h = defWinSize;
        char title[TMP_STR_SIZE] = {};
        bool vet_sync_flag = false;
        uint32_t frame_rt_lim = defFrameRateLim;


        fscanf(configFile_, "%s", tmp);
        fscanf(configFile_, "%s", tmp);
        fscanf(configFile_, "%s", tmp);
        fscanf(configFile_, "%d", &win_num);
        fscanf(configFile_, "%s", tmp);
        fscanf(configFile_, "%d",  &win_w);
        fscanf(configFile_, "%s", tmp);
        fscanf(configFile_, "%d",  &win_h);
        fscanf(configFile_, "%s", tmp);
        fscanf(configFile_, "%s",  title);
        fscanf(configFile_, "%s", tmp);
        fscanf(configFile_, "%d",  &vet_sync_flag);
        fscanf(configFile_, "%s", tmp);
        fscanf(configFile_, "%d",  &frame_rt_lim);
        fscanf(configFile_, "%s", tmp);

        window_ = new sf::RenderWindow(sf::VideoMode(win_w, win_h), title);
        if (window_ == nullptr) {
            return ERR_GMENG_CRTWIN_WIN;
        }
        windsCount_ = win_num;

        window_->setVerticalSyncEnabled(vet_sync_flag);
        window_->setFramerateLimit(frame_rt_lim);

    } else {
        return ERR_GMENG_CRTWIN_FILECLS;
    }

    return 0;
}

int GameEngine::createMusicTracks() {

    if(fileIsOpened_){

        char tmp[TMP_STR_SIZE] = {};
        uint32_t mus_num = defWinNum;
        char mus_path[TMP_STR_SIZE] = {};
        bool set_loop = true;

        fscanf(configFile_, "%s", tmp);
        fscanf(configFile_, "%s", tmp);
        fscanf(configFile_, "%s", tmp);
        fscanf(configFile_, "%d", &mus_num);

        songsCount_ = mus_num;
        if (!songsCount_) return 0;

        fscanf(configFile_, "%s", tmp);
        fscanf(configFile_, "%s", mus_path);
        fscanf(configFile_, "%s", tmp);
        fscanf(configFile_, "%d", &set_loop);
        fscanf(configFile_, "%s", tmp);

        music_ = new sf::Music();
        if(music_ == nullptr){
            return ERR_GMENG_CRTMUS_MUS;
        }

        if (!music_->openFromFile(mus_path)){
            fprintf(logfile, "No music for game was found\n");
            return ERR_GMENG_CRTMUS_MUSPATH;
        }

        music_->setLoop (set_loop);

    } else {
        return ERR_GMENG_CRTMUS_FILECLS;
    }

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
