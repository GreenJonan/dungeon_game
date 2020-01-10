# ifndef GIVE_ME_INPUT__
# define GIVE_ME_INPUT__

# include "debug_commands.c"


// header

char multi_commands(Game*);
int invalid_input(Game*);
char get_first_char();

//////////////////////////////////



char receive_input_command(Game* game) {
    char output = WAIT_C;
    

    // ifthe game is not setup, default to simple commands,
    if (!game->is_setup) {
        // prompt = yes, char = no,
        output = simple_input(game, 1, 0);
    }
    
    
    
    
    else if (game->player->moves == NULL) {
    
        char c = get_first_char();
        
        
        // main body
        
        if ( c != '\n' && c != EOF) {
            
            if (c == '-') {
                output = special_commands(game);
            }
            else if (c == '/') {
                debug_commands(game);
                flush_file_input(stdin);
                output = receive_input_command(game);
            }
            
            
            else if (c == '=') {
                output = multi_commands(game);
            }
            
            
            else {
                //this means treat the input as a single input char
                flush_input();
                
                output = simple_input(game, 0, c);
            }
        }
    }
    
    else {
        output = compute_next_action(game->player);
        //printf("output: %c %d\n", output, output);
    }
    return output;
}





    
    
    
    
// function for simple input,
// that is assuming that the player & rooms objects do not exist, only ask for input

char simple_input(Game* game, int prompt, char c) {
    
    char output = WAIT_C;
    
    if (game == NULL) {
        null_error(GAME_OBJECT, "simple_input");
        return 1;
    }
    
    if (prompt) {
        c = get_first_char();
    }
    
    // return if wait command or end of file,
    if ( c == '\n' || c == EOF) {
        return output;
    }
    else if (prompt) {
        flush_input();
    }
    
    if (is_valid_move(c)) {
        output = c;
    }
    
    else if (c == 'p') {
        pause_game();
        output = receive_input_command(game);
    }
    
    else {
        output = invalid_input(game);
    }
    
    return output;
}





















/////////////////////////////////////////////////

// ASSISTANT FUNCTIONS

char setup_player_move_ls(Game* game, char* str, char c) {

    // assume the input is a string of character inputs, hence construct moves list.
    
    int i = 1;
    char d = str[i];
    
    game->player->moves = add_move(d);
    Move_ls* ptr = game->player->moves;
    
    i++;
    d = str[i];
    
    while (is_valid_move(d)) {
        add_new_move(ptr, d);
        // this works as expected
        
        ptr = ptr->next;
        i++;
        d = str[i];
    }
    
    
    // After setting up the move list, pop off the first move
    //(I know its redundant to have assigned it to player rather than leaving it)
    //compute_action(game->player);
    // fixed up redundancies
    
    return c;
}




// pause the game, and wait until the player re-enters p

int pause_game() {
    char c = getchar();
    
    while (c != 'p' && c != 'P') {
        c = getchar();
    }
    flush_input();
    return 0;
}




int invalid_input(Game* game) {
    printf("Invalid command, please try again or enter '-help' for help.\n");
    return receive_input_command(game);
}


// prompt player for command and return first non-space character.

char get_first_char() {
    printf("Enter command: ");
    char c = getchar();
    
    
    // in case of white spaces chew up characters until a new char is reached.
    while (c == ' ') {
        c = getchar();
    }
    return c;
}


//////////////////////////////






// multi-command function, if char = '=', set-up up player move list, interpret command, and return errors.

char multi_commands(Game* game) {
    
    char output = WAIT_C;
    // the characters following the sign will be a stream of input characters.
    
    char input_str[MOVE_BUFF];
    scanf("%s", input_str);
    flush_input();
    
    
    char c = input_str[0];
    if (c == 0) {
        // Im sure its possible to reach here
        printf("ERROR: SHOULD NOT BE HERE\n");
    }
    
    
    else {
        
        if (is_valid_move(c)) {
            output = setup_player_move_ls(game, input_str, c);
        }
        else {
            output = invalid_input(game);
        }
        
    }
    return output;
}










////////////////////////////////////////////////////////////

//// command interpretation

char special_type(char*, Game*);

char special_commands(Game* game) {
    
    char str[BUFF];
    fscanf(stdin, "%s", str);
    flush_file_input(stdin);
    
    return special_type(str, game);
}





char special_type(char* str, Game* game) {
    char output = 0;
    int is_help = 0;
    int is_save = 0;
    int is_load = 0;
    int is_exit = 0;
    

    if (str_eq(str, HELP_P)) {
        is_help = 1;
    }
    else if (str_eq(str, EXIT_P)) {
        is_exit = 1;
    }
    else if (str_eq(str, SAVE_P)) {
        is_save = 1;
    }
    else if (str_eq(str, LOAD_P)) {
        is_load = 1;
    }
    else {
        printf("Invalid command, please try again or enter '-help' for help.\n");
        output = receive_input_command(game);
    }
    
    
    
    if (is_help) {
        print_help_message(game->options.command_debug);
        output = receive_input_command(game);
    }
    
    
    else if (is_exit){
        output = EXIT_C;
    }
    else if (is_save) {
        output = SAVE_C;
    }
    else if (is_load) {
        output = LOAD_C;
    }

    return output;
}







// REMEMBER, NO NEED TO FLUSH INPUT, already taken care of in higher level function.

int debug_commands(Game* game) {
    int output = 0;
    
    char str[BUFF];
    int a = 0,b = 0,c = 0;
    fscanf(stdin, "%s", str);// &a, &b, &c);
    c++; a++; b++;
    c--; a--; b--; // this is to stop 'unused errors etc with -Wall / -Werror

    
    // no need to have else statements, as every if statement returns
    
    if (str_eq(str, DEBUG_P)) {
        return debug_com_game_debug(game);
    }
    
    if (game->options.command_debug) {
    
        if (str_eq(str, CLEAR_P)) {
            return debug_com_screen_clear();
        }
        
        if (str_eq(str, POS_P)) {
            return debug_com_player_pos(game);
        }
    
        if (str_eq(str, MOVE_P)) {
            fscanf(stdin, "%d,%d", &a, &b);
            return debug_com_move_player(game, a, b);
        }
    
        if (str_eq(str, ROOM_P)) {
            fscanf(stdin, "%d", &a);
            return debug_com_room_teleport(game, a);
        }
    
        if (str_eq(str, DOOR_P)) {
            fscanf(stdin, "%d %d", &a, &b);
            return debug_com_exit_teleport(game, a, b);
        }
    
        if (str_eq(str, CLIP_P)) {
            return debug_com_toggle_player_clip(game);
        }
    
        if (str_eq(str, ERROR_P)) {
            return debug_com_error_status(game);
        }
        
        if (str_eq(str, SWORD_P)) {
            return debug_com_toggle_sword(game);
        }
        
        if (str_eq(str, DOOR_POS_P)) {
            fscanf(stdin, "%d %d", &a, &b);
            return debug_com_exit_pos(game, a, b);
        }
        
        if (str_eq(str, TIME_P)) {
            return debug_com_time(game);
        }
        
        if (str_eq(str, ROOM_DARK_P)) {
            fscanf(stdin, "%d", &a);
            return debug_com_toggle_room_dark(game, a);
        }
        
        if (str_eq(str, ROOM_NUM_P)) {
            return debug_com_room_num(game);
        }
        
        if (str_eq(str, PLAYER_VIS)) {
            fscanf(stdin, "%d", &a);
            return debug_com_player_vis(game, a);
        }
        
        if (str_eq(str, GIVE_ITEM)) {
            fscanf(stdin, "%d %d", &a, &b);
            return debug_com_give_player_item(game, a, b);
        }
    }
    else {
        printf("Invalid command, please try again or enter '-help' for help.\n");
        return output;
    }
    
    
    
    printf("NOT IMPLEMENTED DEBUG COMMAND\n");
    return output;
}





# endif
