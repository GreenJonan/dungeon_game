# ifndef DEBUG_THIS_COMMAND__
# define DEBUG_THIS_COMMAND__

// header of debug commands
// all functions from this file start with debug_com_...


int debug_com_game_debug(Game*);
int debug_com_screen_clear();
int debug_com_error_status(Game*);
int debug_com_time(Game*);
int debug_com_player_pos(Game*);

//int debug_com_set_time(Game*, int);
//int debug_com_time(Game*);
int debug_com_toggle_player_clip(Game*);
int debug_com_toggle_sword(Game*);

int debug_com_move_player(Game*, int, int);
int debug_com_room_teleport(Game*, int);
int debug_com_exit_teleport(Game*, int, int);
int debug_com_exit_pos(Game*, int, int);

int debug_com_room_num(Game*);
int debug_com_toggle_room_dark(Game*, int);
int debug_com_light_dist(Game*, int);
int debug_com_player_vis(Game*, int);

int debug_com_give_player_item(Game*, int, int);


///////////////////////////////////////////////////////////////////////////////////////


int print_debug_error() {
    return printf("Unable to execute command.\n");
}





int debug_com_game_debug(Game* game) {
    int val = game->options.command_debug;
    if (val) {
        val = 0;
    }
    else {
        val = 1;
    }
    game->options.command_debug = val;
    return 0;
}


int debug_com_screen_clear() {
    return force_clear_screen();
}






int debug_com_error_status(Game* game) {
    int stat = game->error;
    printf("Error status: %d\n", stat);
    return 0;
}



int debug_com_time(Game* game) {
    return printf("Game time: %ld\n", game->time);
}













int debug_com_toggle_player_clip(Game* game) {
    int clp = is_player_clip(game->player);
    
    if (clp) {
        clp = 0;
    }
    else {
        clp = 1;
    }
    set_player_clip(game->player, clp);
    return 0;
}



int debug_com_toggle_sword(Game* game) {
    int sword = game->player->has_sword;
    
    if (sword) {
        sword = 0;
    }
    else {
        sword = 1;
    }
    game->player->has_sword = sword;
    draw_screen(game);
    return 0;
}





int debug_com_player_pos(Game* game) {
    if (game->player == NULL) {
        print_debug_error();
        return 1;
    }
    return printf("Player position: %d,%d\n", game->player->base.x, game->player->base.y);
}









////////////////////////////////////////////////////////////////////////////////////////

/////
/////    TELEPORT FUNCTIONS
/////


// teleport a player within a room

int debug_com_move_player(Game* game, int x_, int y_) {
    
    set_player_xy(game->player, x_, y_);
    draw_screen(game);
    printf("Teleported player: x-%d, y-%d\n", x_, y_);
    return 0;
}











// teleport a player to a new room, and try to set their position in the centre.

int debug_com_room_teleport(Game* game, int room_num_) {

    if (room_num_ <= 0 || room_num_ > game->room_len) {
        printf("Invalid room number\n");
        return 1;
    }
    //game->player->room_num =room_num_;
    reset_spc_room_entities(game->player);
    
    game->player->room = game->rooms[room_num_ - 1]->room;
    
    set_room_default_position(game->player);
    draw_screen(game);
    printf("Teleported player: Room %d\n", room_num_);
    return 0;
}








// teleport a player to a new room, and set the position to be that of the exit specified.

int debug_com_exit_teleport(Game* game, int room_num_, int exit_num) {
    
    return teleport_player_to_exit(game, room_num_, exit_num, 1);
}




// find the x,y position of an exit

int debug_com_exit_pos(Game* game, int room_num, int exit_num) {
    Exit* tmp_exit = find_room_exit(game, room_num, exit_num);
    if (tmp_exit == NULL) {
        return 1;
    }
    
    printf("Room %d exit %d position: %d,%d\n", room_num, exit_num, tmp_exit->x, tmp_exit->y);
    return 0;
}



///////////////////////////////////////////////////////////////////////////



//// room specific functions

int debug_com_room_num(Game* game) {
    return printf("Current Room number: %d\n", game->player->room->room_id);
}


int debug_com_toggle_room_dark(Game* game, int n) {
    if (n < 0 || n > game->room_len) {
        printf("Invalid room number.\n");
        return 1;
    }
    
    Room* room = game->player->room;
    if (n != 0) {
        room = game->rooms[n-1]->room;
    }
    
    int is_dark = room->is_dark;
    
    if (is_dark) {
        is_dark = 0;
    }
    else {
        is_dark = 1;
    }
    room->is_dark = is_dark;
    return draw_screen(game);
}



// set the player's vision, how far they can see in the dark, error if less than zero

int debug_com_player_vis(Game* game, int d) {
    if (d < 0) {
        printf("Invalid distance: %d\n", d);
        return 1;
    }
    set_player_light_dist(game->player, d);
    return draw_screen(game);
}








int debug_com_give_player_item(Game* game, int i_id, int num) {
    
    if (i_id < 100) {
        if (i_id == HEART_ID) {player_heal(game->player, num); }
        
        else if (i_id == COIN_ID) { game->player->inventory->coin_num += num;}
        
        else if (i_id == KEY_ID) { game->player->inventory->key_num += num;}
        
        else if (i_id == BOMB_ID) { game->player->inventory->bomb_num += num;}
        
        else if (i_id == ARROW_ID) { game->player->inventory->arrow_num += num;}
        
        else if (i_id == MANA_ID) { player_gain_mana(game->player, num);}
        
        else if (i_id == HEALTH_CONTAINER_ID) { player_gain_health_container(game->player, num);}
        
        else if (i_id == MANA_CONTAINER_ID) {
            player_gain_mana_container(game->player, num);
            if (!game->player->has_mana && game->player->base.max_mana > 0) {
                game->player->has_mana = 1;
            }
        }
        
        else if (i_id == FREEZE_ID) {
            game->player->loop = FREEZE_LOOP_LEN;
        }
        
        else {
            printf("Invalid item id: %d\n", i_id);
            return 0;
        }
    }
    
    else {
        give_player_new_item(game, i_id);
    }
    
   
    draw_screen(game);
    return 0;
}
# endif
