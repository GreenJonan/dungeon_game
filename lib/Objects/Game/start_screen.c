# ifndef START_SCREEN___
# define START_SCREEN___

# define MAX_OPTIONS 6




int start_menu(Game* game, int cursor) {
    if (game == NULL) {
        game_null_error("start_menu");
        return -1;
    }
    
    MENU:
    
    if (cursor <= 0 || cursor > 3) {
        cursor = 1;
    }
    
    
    int command = -1;
    //int cursor = 1;
    
    while (command != WAIT_C) {

        
        draw_start_screen(cursor);
        command = receive_input_command(game);

        
        if (command == MOVE_UP_C) {
            if (cursor - 1 > 0) {
                cursor --;
            }
        }
        else if (command == MOVE_DOWN_C) {
            if (cursor + 1 <= 3) {
                cursor ++;
            }
        }
        
    }
    
    
    // selection was made, so change into new page
    
    // START GAME:
    if (cursor == 1) {
        int exit;
        exit = game_select(game);
       
        if (exit) {
            //command = start_menu(game, cursor);
            goto MENU;
        }
        else {
        
        }
    }
    
    
    
    // OPTIONS
    if (cursor == 2) {
        options_menu(game);
        //command = start_menu(game, cursor);
        goto MENU;
    }
    
    
    
    // EXIT GAME:
    if (cursor == 3) {
        command = EXIT_C;
    }
    
    
    return command;
}
















///////////////////////////////////////////////////////////////

///
///     INTERNAL MENUS
///

int options_menu(Game* game) {
    if (game == NULL) {
        game_null_error("options_menu");
        return 1;
    }
    
    int command = -1;
    int cursor = 1;
    
    while (command != WAIT_C || cursor != MAX_OPTIONS) {
        draw_options_screen(game, cursor);
        command = receive_input_command(game);
        
        if (command == MOVE_UP_C) {
            if (cursor <= 1) {
                cursor = MAX_OPTIONS;
            }
            else {
                cursor--;
            }
        }
        else if (command == MOVE_DOWN_C) {
            if ( cursor >= MAX_OPTIONS) {
                cursor = 1;
            }
            else {
                cursor++;
            }
        }
        else if (command != WAIT_C){
        
            // adjust left/right, hence move left/right commands
            
            if (command == MOVE_LEFT_C) {
                option_adjust_left(game,cursor);
            }
            
            else if (command == MOVE_RIGHT_C) {
                option_adjust_right(game,cursor);
            }
        }
    }
    return 0;
}













int game_select(struct game_t* game) {
    int exit = 0;
    
    // for the moment, force set src directory;
    
    
    int cursor = 1;
    int cursor_num = 3;
    
START:;
    int command = -1;
    
    
    
    while ( !(command == WAIT_C || command == REST_C)) {
    
        draw_game_select_screen(game, cursor);
        command = receive_input_command(game);
        
        
        if (command == MOVE_UP_C) {
            if (cursor > 1) {
                cursor --;
            }
        }
        
        else if (command == MOVE_DOWN_C) {
            if (cursor < cursor_num) {
                cursor ++;
            }
        }
    }
    
    
    
    if (cursor == cursor_num) {
        exit = 1; // do nothing and return back to game starting menu.
    }
    
    
    else if (cursor == 1) {
    
        // copy SRC_DIR to src_dir
        str_copy(DEFAULT_SRC_DIR, game->src_dir);
        
        exit = 0;
        // load default save file
    }
    
    
    
    
    
    else if (cursor == 2) {

        printf("Please enter a custom game directory, relative to src/ directory. \n"
               "For example,    enter './src/game_file_1/', as 'game_file_1'\n\n");
        
        
        int found = 0;
        
        while (!found) {
            
            printf("Directory name: ");
            char dir[BUFF];
            scanf("%s", dir); flush_input();
        
            if (str_eq(dir, "exit")) {
                goto START;
            }
            
            
            else {
                char tmp_str1[BUFF];
                char tmp_str2[BUFF];
                
                simple_str_concat(tmp_str1, game->pwd, SRC_DIR);
                simple_str_concat(tmp_str2, tmp_str1, dir);
                
                
                char last_char = 0;
                int len = 0;
                
                while (dir[len] != 0) {
                    len ++;
                }
                
                if (len > 0) {
                    last_char = dir[len - 1];
                }
                
                
                
                if (last_char == '/') {
                    simple_str_concat(tmp_str1, tmp_str2, ROOM_MAP);
                }
                
                else {
                    simple_str_concat(tmp_str2, tmp_str2, "/");
                    simple_str_concat(tmp_str1, tmp_str2, ROOM_MAP);
                }
                
                
                FILE* f = fopen(tmp_str1, "r");
                
                if (f == NULL) {
                    printf("Invalid directory name, or '%s' file does not exist.\n\n", ROOM_MAP);
                }
                
                else {
                    found = 1;
                    fclose(f);
                    
                    str_copy(tmp_str2, game->src_dir);
                }
                
            }
        }
        
        if (found) {
            exit = 0;
        }
        else {
            goto START;
        }
        // load custom directory via file name
    }
    
    
    
    
    
    
    else {
        printf("ERROR: unknown cursor position: %d\n", cursor);
        pause_function();
    }
    
    return exit;
}




// TO DO:
/*
Instead of manually entering in an alternate file directory, have a file in src that lists all the possible
 directories to select from, and select one of them.
 
 Hence will have to open src/game_files.txt
 
 and will have contents, for example:
    default/
    game1/
    game2/
    craxy_game/
    easy_game/
    debug_game/
 
 and so on.
 
 Graphically how should I show this in the start menu?
 Options, 
    * complete vertical list of all files
    * Custom scroll bar, max 5, then arrows top and bottom like how items work in the player's inventory
    * Horizontal scrolling arrows for 2nd option
 

 Alternate ideas:
 
 Vertical scrolling however, default is included as a save file, however there is a separate special spot
 just for the game selected, by default it is NONE, 
 
 select game, then can press start game botton. Until then cannot start the game, or perhaps start default.
 
 */

















/////////////////////////////////////////////////////////////



int option_adjust_left(struct game_t* game, int cursor) {

    if (game == NULL) {
        game_null_error("option_adjust_left");
        return 1;
    }
    
    
    if (cursor == 1) {
        if (game->options.difficulty > -1) {
            game->options.difficulty--;
        }
    }
    
    else if (cursor == 2) {
        if (game->options.command_debug) {
            game->options.command_debug = 0;
        }
    }
    
    else if (cursor == 3) {
        if (num_len(game->options.rnd1 - 1) <= 10) {
            game->options.rnd1--;
        }
    }
    else if (cursor == 4) {
        if (num_len(game->options.rnd2 - 1) <= 10) {
            game->options.rnd2--;
        }
    }
    else if (cursor == 5) {
        if (num_len(game->options.rnd3 - 1) <= 10) {
            game->options.rnd3--;
        }
    }
    return 0;

}






int option_adjust_right(struct game_t* game, int cursor) {

    if (game == NULL) {
        game_null_error("option_adjust_right");
        return 1;
    }
    
    
    if (cursor == 1) {
        if (game->options.difficulty < 1) {
            game->options.difficulty++;
        }
    }
    
    else if (cursor == 2) {
        if (!game->options.command_debug) {
            game->options.command_debug = 1;
        }
    }
    
    else if (cursor == 3) {
        if (num_len(game->options.rnd1 + 1) <= 10) {
            game->options.rnd1++;
        }
    }
    else if (cursor == 4) {
        if (num_len(game->options.rnd2 + 1) <= 10) {
            game->options.rnd2++;
        }
    }
    else if (cursor == 5) {
        if (num_len(game->options.rnd3 + 1) <= 10) {
            game->options.rnd3++;
        }
    }
    
    return 0;
}

# endif
