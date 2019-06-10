#include "GameEngine.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

GameEngine::GameEngine(const char * configFileName) {

    if(configFileName == nullptr){
        errno = ERR_GMENG_CRT_CONFNAME;
    } else {
        configName_ = configFileName;
    }

}

GameEngine::~GameEngine() {

    if(fileIsOpened_ && configFile_){
        fclose(configFile_);
    }

    configFile_ = nullptr;
    configName_ = nullptr;
    fileIsOpened_ = false;

    delete texture_;
    texture_ = nullptr;
    textureCount_ = 0;

    delete music_;
    music_ = nullptr;
    songsCount_ = 0;

    if(window_ && window_->isOpen()){
        window_->close();
    }

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

int GameEngine::closeConfigFile() {

    if(fileIsOpened_){
        if(configFile_) {
            fclose(configFile_);
            fileIsOpened_ = false;
        } else {
            return ERR_GMENG_CLSCFG_FILE;
        }
    }

    return 0;
}

int GameEngine::initGameEngineParams() {
    int err_code = 0;

    err_code = openConfigFile();
    ERR_CHECK(logfile, 1);

    err_code = parseConfig();
    ERR_CHECK(logfile, 1);

    err_code = closeConfigFile();
    ERR_CHECK(logfile, 0);

    return err_code;
}

int GameEngine::parseConfig() {

    if(fileIsOpened_) {

        int err_code = 0;
        char tmp[TMP_STR_SIZE] = {};

        while(!feof(configFile_)){
            fscanf(configFile_, "%s", tmp);
            if(!strcmp(CFG_DELIM_STR, tmp)){
                bzero(tmp, TMP_STR_SIZE);
            } else if (!strcmp(CFG_WIN_GROUP, tmp)) {
                bzero(tmp, TMP_STR_SIZE);
                err_code = parseConfigWindows();
                ERR_CHECK(logfile, 0);
                if (err_code) return err_code;
            } else if (!strcmp(CFG_MUS_GROUP, tmp)){
                bzero(tmp, TMP_STR_SIZE);
                err_code = parseConfigMusic();
                ERR_CHECK(logfile, 0);
                if (err_code) return err_code;
            } else if (!strcmp(CFG_OBJ_GROUP, tmp)){
                bzero(tmp, TMP_STR_SIZE);
                err_code = parseConfigObjects();
                ERR_CHECK(logfile, 0);
                if (err_code) return err_code;
            }
        }

    } else {
        return ERR_GMENG_PRSCFG_FILECLS;
    }

    return 0;
}

int GameEngine::parseConfigWindows() {

    if(fileIsOpened_) {

        int err_code = 0;
        char tmp[TMP_STR_SIZE] = {};

        while(!feof(configFile_)){
            fscanf(configFile_, "%s", tmp);
            if(!strcmp(CFG_DELIM_STR, tmp)){
                bzero(tmp, TMP_STR_SIZE);
            } else if (!strcmp(CFG_WIN_GROUP, tmp)) {
                bzero(tmp, TMP_STR_SIZE);
                err_code = parseConfigWindows();
                ERR_CHECK(logfile, 0);
                if (err_code) return err_code;
            } else if (!strcmp(CFG_MUS_GROUP, tmp)){
                bzero(tmp, TMP_STR_SIZE);
                err_code = parseConfigMusic();
                ERR_CHECK(logfile, 0);
                if (err_code) return err_code;
            } else if (!strcmp(CFG_OBJ_GROUP, tmp)){
                bzero(tmp, TMP_STR_SIZE);
                err_code = parseConfigObjects();
                ERR_CHECK(logfile, 0);
                if (err_code) return err_code;
            }
        }

        uint32_t win_num = defWinNum;
        uint32_t win_w = defWinW;
        uint32_t win_h = defWinH;
        char title[TMP_STR_SIZE] = {};
        uint32_t vert_sync_flag = true;
        uint32_t frame_rt_lim = defFrameRateLim;

        PARSE_CONFIG_PARAMS(configFile_, "%d", win_num, defWinNum);
        PARSE_CONFIG_PARAMS(configFile_, "%d", win_w, defWinW);
        PARSE_CONFIG_PARAMS(configFile_, "%d", win_h, defWinH);

        fscanf(configFile_, "%s", tmp);
        if ( !fscanf(configFile_, "%s",  title) ){
            bzero(title, TMP_STR_SIZE);
            strcpy(title, defTitle);
        }

        PARSE_CONFIG_PARAMS(configFile_, "%d", vert_sync_flag, defVertSyncFlag);
        PARSE_CONFIG_PARAMS(configFile_, "%d", frame_rt_lim, defFrameRateLim);

        err_code = createWindow(win_num, win_w, win_h, title, vert_sync_flag, frame_rt_lim);
        ERR_CHECK(logfile, 1);

    } else {
        return ERR_GMENG_PRSCFGWIN_FILECLS;
    }

    return 0;
}

int GameEngine::parseConfigMusic() {

    if(fileIsOpened_) {

        int err_code = 0;
        char tmp[TMP_STR_SIZE] = {};
        uint32_t mus_num = defSongsNum;
        char mus_path[TMP_STR_SIZE] = {};
        uint32_t set_loop = 1;

        PARSE_CONFIG_PARAMS(configFile_, "%d", mus_num, defSongsNum);

        songsCount_ = mus_num;
        if (!songsCount_) return 0;

        fscanf(configFile_, "%s", tmp);
        if ( !fscanf(configFile_, "%s",  mus_path) ){
            bzero(mus_path, TMP_STR_SIZE);
            strcpy(mus_path, defMusic);
        }

        PARSE_CONFIG_PARAMS(configFile_, "%d", set_loop, defSetLoopFlag);

        err_code = createMusicTracks(mus_num, mus_path, set_loop);
        ERR_CHECK(logfile, 1);

    } else {
        return ERR_GMENG_PRSCFGMUS_FILECLS;
    }

    return 0;
}

int GameEngine::parseConfigObjects() {

    if(fileIsOpened_) {

        int err_code = 0;
        char tmp[TMP_STR_SIZE] = {};

        while(!feof(configFile_)){
            fscanf(configFile_, "%s", tmp);
            if(!strcmp(CFG_DELIM_STR, tmp)){
                bzero(tmp, TMP_STR_SIZE);
            } else if (!strcmp(CFG_OBJNUM_GROUP, tmp)) {
                bzero(tmp, TMP_STR_SIZE);
                err_code = parseObjNums();
                ERR_CHECK(logfile, 0);
                if (err_code) return err_code;
            } else {

                gameType obj_type = type_unknown_e;

                if( !strcmp(CFG_PLAYER_GROUP, tmp) ){
                    obj_type = type_playable_obj_e;
                } else if ( !strcmp(CFG_INSP_GROUP, tmp) ) {
                    obj_type = type_enemy_obj_e;
                } else if ( !strcmp(CFG_PSG_GROUP, tmp) ) {
                    obj_type = type_moveable_obj_e;
                } else if ( !strcmp(CFG_BNCH_GROUP, tmp) ) {
                    obj_type = type_static_draw_obj_e;
                } else {
                    continue;
                }


                bzero(tmp, TMP_STR_SIZE);
                err_code = parseObjs(obj_type);
                ERR_CHECK(logfile, 0);
                if (err_code) return err_code;
            }
        }

    } else {
        return ERR_GMENG_PRSCFGOBJ_FILECLS;
    }

    return 0;
}

int GameEngine::parseObjNums() {

    if(fileIsOpened_) {

        char tmp[TMP_STR_SIZE] = {};
        uint32_t player_num = defPlayerNum;
        uint32_t enemy_num = defEnemyNum;
        uint32_t neutral_num = defNeutralNum;
        uint32_t staticObj_num = defStaticObjNum;

        PARSE_CONFIG_PARAMS(configFile_, "%d", player_num, defPlayerNum);
        PARSE_CONFIG_PARAMS(configFile_, "%d", enemy_num, defEnemyNum);
        PARSE_CONFIG_PARAMS(configFile_, "%d", neutral_num, defNeutralNum);
        PARSE_CONFIG_PARAMS(configFile_, "%d", staticObj_num, defStaticObjNum);

        playerNum_ = player_num;
        enemyNum_ = enemy_num;
        neutralNum_ = neutral_num;
        staticObjNum_ = staticObj_num;

        allObjsCount_ = playerNum_ + enemyNum_ + neutralNum_ + staticObjNum_;
        cfgObjNumCounted_ = true;

    } else {
        return ERR_GMENG_PRSCFGOBJNUMS_FILECLS;
    }

    return 0;
}

int GameEngine::parseObjs(gameType obj_type) {

    if(fileIsOpened_) {

        if (cfgObjNumCounted_) {

            int err_code = 0;
            char tmp[TMP_STR_SIZE] = {};
            dataType size_x = defSize.x;
            dataType size_y = defSize.y;
            dataType hitbox_x = defHitbox.x;
            dataType hitbox_y = defHitbox.y;
            dataType v_x = defSpeed.x;
            dataType v_y = defSpeed.y;
            char texture_path[TMP_STR_SIZE] = {};
            sf::Texture * texture = nullptr;

            PARSE_CONFIG_PARAMS(configFile_, "%f", size_x, defSize.x);
            PARSE_CONFIG_PARAMS(configFile_, "%f", size_y, defSize.y);
            PARSE_CONFIG_PARAMS(configFile_, "%f", hitbox_x, defHitbox.x);
            PARSE_CONFIG_PARAMS(configFile_, "%f", hitbox_y, defHitbox.y);
            if(obj_type == type_playable_obj_e || obj_type == type_enemy_obj_e || obj_type == type_moveable_obj_e) {
                PARSE_CONFIG_PARAMS(configFile_, "%f", v_x, defSpeed.x);
                PARSE_CONFIG_PARAMS(configFile_, "%f", v_y, defSpeed.y);
            }

            fscanf(configFile_, "%s", tmp);
            if ( !fscanf(configFile_, "%s",  texture_path) ){
                bzero(texture_path, TMP_STR_SIZE);
                strcpy(texture_path, NO_TEXTURE_SYMBOLS);
            }

            if( !strcmp(texture_path, NO_TEXTURE_SYMBOLS) ){
                texture = nullptr;
            } else {
                texture = new sf::Texture();
                if (!texture->loadFromFile (texture_path)){
                    delete texture;
                    texture = nullptr;
                } else {
                    texture->setSmooth(defTextureSmooth);
                }
            }

            err_code = genGameObjs(obj_type, Vec(size_x, size_y), Vec(hitbox_x, hitbox_y), texture, Vec(v_x, v_y) );
            ERR_CHECK(logfile, 1);

        } else {
            return ERR_GMENG_PRSCFOBJS_CFGSEQ;
        }

    } else {
        return ERR_GMENG_PRSCFOBJS_FILECLS;
    }

}

int GameEngine::createWindow(uint32_t win_num, uint32_t win_w, uint32_t win_h, const char * title, bool vet_sync_flag, uint32_t frame_rt_lim) {

    if (windsCount_ = win_num) {
        window_ = new sf::RenderWindow(sf::VideoMode(win_w, win_h), (title) ? title : defTitle);
        if (window_ == nullptr) {
            return ERR_GMENG_CRTWIN_WIN;
        }
        windsCount_ = win_num;

        window_->setVerticalSyncEnabled(vet_sync_flag);
        window_->setFramerateLimit(frame_rt_lim);
    } else {
        return ERR_GMENG_CRTWIN_WINNUM;
    }

    return 0;
}

int GameEngine::createMusicTracks(uint32_t mus_num, const char * musPath, bool setLoop) {

    if (mus_num) {
        music_ = new sf::Music();
        if (music_ == nullptr) {
            return ERR_GMENG_CRTMUS_MUS;
        }

        if (!music_->openFromFile( (musPath) ? musPath : defMusic )) {
            fprintf(logfile, "No music for game was found\n");
            return ERR_GMENG_CRTMUS_MUSPATH;
        }

        music_->setLoop(setLoop);
    }

    return 0;
}

int GameEngine::createTextures() {
    return 0;
}

int GameEngine::genGameObjs(gameType obj_type, Vec size, Vec hitbox, sf::Texture * texture, Vec v) {

    switch(obj_type){
        case type_playable_obj_e:
            break;
        case type_enemy_obj_e:
            break;
        case type_moveable_obj_e:
            break;
        case type_static_draw_obj_e:
            break;
        default:
            break;
    }

    return 0;
}

int GameEngine::runGame() {

    if(songsCount_) {
        music_->play();
    }

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
        if( checkStopEvents() ){
            break;
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

    if(window_->isOpen()){
        window_->close();
    }

    return 0;
}

bool GameEngine::checkStopEvents() {

    sf::Event event;
    while (window_->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            window_->close();
            return true;
        }
    }

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Escape)){
        window_->close();
        return true;
    }

    if (!window_->isOpen()){
        window_->close();
        return true;
    }

    if(player_ && player_->getCaughtFlag()){
        return true;
    }

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