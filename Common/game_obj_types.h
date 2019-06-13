#ifndef MYGAME_GAME_OBJ_TYPES_H
#define MYGAME_GAME_OBJ_TYPES_H

#include <stddef.h>
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! @enum Enumeration list for all objects in game
enum gameType {
    type_unknown_e = - 1,
    type_main_player_e = 1,
    type_train_inspector_e,
    type_bench_e,
    type_game_obj_e,
    type_drawable_obj_e,
    type_physical_obj_e,
    type_moveable_obj_e,
    type_with_target_obj_e,
    type_static_draw_obj_e,
    type_playable_obj_e,
    type_enemy_obj_e,
    GAME_TYPES_TOTAL
};

#endif //MYGAME_GAME_OBJ_TYPES_H
