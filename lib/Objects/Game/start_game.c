# ifndef SETUP_GAME_
# define SETUP_GAME_

# include "../Room/room_init.c"
# include "../Player_methods/player_init.c"

int start_game(Game* game) {
    if (NULL == game) {
        null_error(GAME_OBJECT, "start_game");
        return 1;
    }
    game->error = 0;
    game->time = 0;
    game->game_over = 0;
    game->draw_hud_items = 1;
    game->player_turn = 1;
    game->is_setup = 0;
    
    
    // set all trig_ids to zero by default
    for (int i = 0; i < TRIG_NUM; i++) {
        game->triggers[i] = 0;
    }
    
    // find the current directory where the program is running.
    
    FILE* output;
    output = popen("pwd", "r");
    if (NULL == output) {
        printf("Error in opening stdout.\n");
        str_copy("./", game->pwd);
    }
    else {
        char tmp_str[BUFF];
        fscanf(output, "%s", tmp_str);
        
        simple_str_concat(game->pwd, tmp_str, "/");
        fclose(output);
    }
    
    
    
    //////////////////////////////////////////////////////////////
    
    // display start screen, and receive input what to do
    int exit;
    exit = start_menu(game, 1);
    
    
    if (exit) {
        return -1;
    }

    
    //////////////////////////////////////////////////////////////
    
    // need to set-up the following pointers
    // player, rooms
    
    
    int error = 0;
    
    
    error = setup_rooms(game);
    
    if (!error) {
        game->loaded_rooms = 1;
        error = setup_player(game);
        game->loaded_player = 1;
        
        
        game->error = error;
    }
    else {
        game->error = -1;
    }
    
    
    game->is_setup = 1;
    
    return 0;
}

# endif
