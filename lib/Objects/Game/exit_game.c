# ifndef EXIT_GAME_
# define EXIT_GAME_

# include "save_game.c"

int game_over_msg();



// the following function cleanly exits the program by de-allocating all memory given to the game.

int exit_game(Game* game, int exit) {
    
    if (game != NULL) {
    
        if (exit == SAVE_C) {
            int error;
            error = save_game(game);
            
            if (error) {
                printf("Sorry, there was an error in saving the game.\n");
            }
        }
        
        else if (exit == WIN_GAME_C) {
            print_win_msg(game);
        }
        /*
        if (game->game_over) {
            game_over_msg();
        }
        */
        
        unload_game(game);
    }
    return 0;//clear_screen();
}







int unload_game(Game* game) {
    if (game != NULL) {

        if (game->loaded_rooms) {
            free_all_rooms(game);
        
            //ignore --> // negative error implies player was never set up.
            //if (game->error >= 0) {
            
            if (game->loaded_player) {
            
                free_player(game->player);
            }
        
            // game is never allocated!!! hence no need to free it. Error otherwise.
            //free(game);
        }
    }

    return 0;
}






int free_all_rooms(Game* game) {
    if (NULL == game) {
        null_error(GAME_OBJECT, "free_all_rooms");
        return 1;
    }
    
    if (game->rooms != NULL) {
        
        free_room_ls((game->rooms)[0], 0);
    
        /*
        if (NULL != game->rooms[0]) {
            if (NULL != game->rooms[0]->next) {
                free_error(ROOM_OBJECT);
            }
            if (NULL != game->rooms[0]->room) {
                free_room(game->rooms[0]->room);
            }
        }*/
        
        
        free(game->rooms);
        
    }
    return 0;
}


//////////////////////////////////////////////////////


int gameover(Game* game) {
    if (!game->game_over) {
        printf("ERROR: 'Game' not set to game_over = true.\n");
        pause_function();
    }
    
    // redraw the screen
    draw_screen(game);
    
    game_over_msg();
    
    if (game->options.command_debug) {
        wait_msg();
        
        char c = getchar();
        
        if (c == '/') {
            char str[MOVE_BUFF];
            scanf("%s", str);
            flush_input();
            
            if (str_eq(str, REVIVE_P)) {
                
                game->game_over = 0;
                revive_player(game->player);
                draw_screen(game);
                return WAIT_C;
            }
        }
    }
    else {
        pause_function();
    }
    return EXIT_C;
}







/////////////////////////////////////////////////////

int game_over_msg() {
    return printf("\n"
           "\n"
           "  +-------------------+\n"
           "  |                   |\n"
           "  |     GAME OVER     |\n"
           "  |                   |\n"
           "  +-------------------+\n"
           "\n\n");
}

# endif
