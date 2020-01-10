# ifndef PLAYER_INITIALISE__
# define PLAYER_INITIALISE__

# include "../Entities/player_memory.c"

int setup_player(Game* game) {

    if (game == NULL) {
        null_error(GAME_OBJECT, "setup_player");
        return 1;
    }
    
    // find src location
    char player_str[BUFF*2];
    simple_str_concat(player_str, game->src_dir, PLAYER_FILE);

    FILE* f = fopen(player_str, "r");

    if (f == NULL) {
        file_error(player_str, "setup_player");
        
        game->player = allocate_player();
        init_player(game, game->player, f);
        return 1;
    }
    game->player = allocate_player();
    
    game->error = init_player(game, game->player, f);
    
    fclose(f);
    return 0;
}



///////////////////////////////////////////////////////////////////////


int load_player_status(struct game_t* g, struct player_t* p, FILE* f) {

    char name[] = "load_player_status";
    if (g == NULL) {
        game_null_error(name);
        return 1;
    }
    if (p == NULL) {
        player_null_error(name);
        return 1;
    }
    if (f == NULL) {
        null_error(FILE_OBJECT, name);
        return 1;
    }
    
    
    
    
    int end_of_file = 0;
    int end_of_block = 0;
    
    while (!end_of_block && !end_of_file) {
    
        char c = fgetc(f);
        
        while (c != '$' && c != '#' && !end_of_file) {
            if (c == '/') {
                flush_file_input(f);
            }
            
            if (feof(f)) {
                end_of_file = 1;
            }
            
            c = fgetc(f);
        }
        
        
        
        if (c == '#') {
            end_of_block = 1;
        }
        
        
        else if (c == '$') {
        
            char str[BUFF];
            fscanf(f, "%s", str);
            
            if (feof(f)) {
                end_of_file = 1;
            }
            
            else {
                
                
                if (str_eq(str, MAX_HEALTH)) {
                    int health;
                    fscanf(f, "%d", &health);
                    p->base.max_health = health;
                }
                else if (str_eq(str, HEALTH)) {
                    int health;
                    fscanf(f, "%d", &health);
                    p->base.health = health;
                }
                else if (str_eq(str, MANA)) {
                    int health;
                    fscanf(f, "%d", &health);
                    p->base.mana = health;
                }
                else if (str_eq(str, MAX_MANA)) {
                    int health;
                    fscanf(f, "%d", &health);
                    p->base.max_mana = health;
                }
                
                
                else if (str_eq(str, ROOM_NUM)) {
                    int room_num;
                    fscanf(f, "%d", &room_num);
                    if (room_num != 0) {
                        room_num = (room_num - 1) % g->room_len;
                        
                        p->room = g->rooms[room_num]->room;
                    }
                }
                
                
                else if (str_eq(str, POSITION)) {
                    int a,b;
                    fscanf(f, "%d,%d", &a, &b);
                    p->base.x = a;
                    p->base.y = b;
                }
                
                
                else if (str_eq(str, VELOCITY)) {
                    int a,b;
                    fscanf(f, "%d,%d", &a, &b);
                    p->base.vel_x = a;
                    p->base.vel_y = b;
                }
                
                
                else if (str_eq(str, CLOCK)) {
                    int a;
                    fscanf(f, "%d", &a);
                    p->base.clock = a;
                }
                
                
                else if (str_eq(str, TIMER)) {
                    int a;
                    fscanf(f, "%d", &a);
                    p->base.timer = a;
                }
                
                
                else if (str_eq(str, MASS)) {
                    int a;
                    fscanf(f, "%d", &a);
                    p->base.mass = a;
                }
                
                
                else if (str_eq(str, FLY)) {
                    int a;
                    fscanf(f, "%d", &a);
                    p->base.fly = a;
                }
                
                
                else if (str_eq(str, PLAYER_STATUS)) {
                    int a,b,c,d;
                    fscanf(f, "%d,%d,%d,%d", &a,&b,&c,&d);
                    p->base.status = a + (2 * b) + (4 * c) + (8 * d);
                }
                
                
                else if (str_eq(str, DIRECTION)) {
                    // NOTE: assuming directions w,a,s,d <==> 0,1,2,3
                    int a;
                    fscanf(f, "%d", &a);
                    a = a % 4;
                    p->base.direction = a;
                }
                
                
                else if (str_eq(str, LIGHT_DISTANCE)) {
                    int a;
                    fscanf(f, "%d", &a);
                    p->base.light_dist = a;
                }
                
                
                
                else {
                    if (!SUPPRESS_WARNINGS) {
                        printf("WARNING: undefined player status macro: '%s', in function: '%s'.\n", str, name);
                        pause_function();
                    }
                }
        
            }
        }
        // flush file input
        flush_file_input(f);
        if (feof(f)) {
            end_of_file = 1;
        }
    }



    // final check to make sure nothing escaped
    if (feof(f)) {
        end_of_file = 1;
    }
    
    return end_of_file;
}




///////////////////////////////////////////////////////



int load_player_items(struct game_t* g, FILE* f) {
    char name[] = "load_player_items";
    
    if (g == NULL) {
        game_null_error(name);
        return 1;
    }
    if (f == NULL) {
        null_error(FILE_OBJECT, name);
        return 1;
    }
    
    int end_of_file = 0;
    int end_of_block = 0;
    
    while (!end_of_file && !end_of_block) {
    
        char c = fgetc(f);
        
        while (c != '$' && c != '#' && !end_of_file) {
            if (c == '/') {
                flush_file_input(f);
            }
            if (feof(f)) {
                end_of_file = 1;
            }
            c = fgetc(f);
        }
        
        
        if (c == '#') {
            end_of_block = 1;
            flush_file_input(f);
        }
        
        else if (c == '$') {
        
            char str[BUFF];
            int num;
            fscanf(f, "%s %d", str, &num);
            
            Item* i = init_inv_item(str, num, NONE, 1); // 1==> heart, bombs etc.
            int pickup = give_player_item(g, i);
            
            if (pickup) {
                if (!SUPPRESS_WARNINGS) {
                    printf("WARNING: unable to pickup item, '%s', in function: '%s', name\n", str, name);
                    pause_function();
                }
                
                // free item:
                free_item(i);
            }
        }
        flush_file_input(f);
        if (feof(f)) {
            end_of_file = 1;
        }
    }
    
    
    // final check to make sure nothing escaped
    if (feof(f)) {
        end_of_file = 1;
    }
    
    return end_of_file;
}


////////////////////////////////////////////


int load_player_moves(struct player_t* p, FILE* f) {

    char name[] = "load_player_moves";
    if (p == NULL) {
        player_null_error(name);
        return 1;
    }
    if (f == NULL) {
        null_error(FILE_OBJECT, name);
        return 1;
    }
    
    
    // end of block only occurs when hit new line character
    
    int end_of_file = 0;
    int end_of_block = 0;
    
    
    while (!end_of_file && !end_of_block) {
    
        char c = fgetc(f);
        if (feof(f)) {
            end_of_file = 1;
        }
        if (c =='\n') {
            end_of_block = 1;
        }
        
        if (is_valid_move(c)) {
            
            add_player_move(p, c);
        }
    }
    
    
    
    return end_of_file;
}


    







///////////////////////////////////////////////////////////////////////





// initialise player status, by either default or file input

int init_player(Game* game, Player* p, FILE* f) {
    
    char name[] = "init_player";
    if (game == NULL) {
        game_null_error(name);
        return 1;
    }
    if (p == NULL) {
        player_null_error(name);
        return 1;
    }
    
    
    init_player_default(game, p);
    if (game->is_hard) {
        p->moves = add_move('r');
    }
    

    if (NULL == f) {
        null_warning("FILE", name);
        return 0;
    }

    
    
    
    int end_of_file = 0;
    
    
    while (!end_of_file) {
        char c = fgetc(f);
    
        while (c != '#' && !end_of_file) {
            if (c == '/') {
                flush_file_input(f);
            }
            if (feof(f)) {
                end_of_file = 1;
            }
            
            c = fgetc(f);
        }
    
    
    
    
    
    
        if (!end_of_file) {
            
            // now see what macro follows '#'
            char str[BUFF];
            fscanf(f, "%s", str);
            
            if (str_eq(str, DEFAULT_MSG)) {
                end_of_file = 1;
            }
            
            
            else if (str_eq(str, STATUS)) {
                end_of_file = load_player_status(game, p, f);
            }
            
            else if (str_eq(str, ITEMS)) {
                end_of_file = load_player_items(game, f);
            }
            
            else if (str_eq(str, MOVES)) {
                end_of_file = load_player_moves(p, f);
            }
            
            
            else {
                printf("WARNING: undefined macro: '%s', in function: '%s'.\n", str, name);
                pause_function();
            }
        }
    }
    
    
    
    
    return 0;
}





















// Initialise the default state of the player, given no file input

int init_player_default(Game* game, Player* p) {

    // intialise default room.
    //p->room = game->rooms[0];
    
    // intilise base
    set_player_default_status(p);
    
    p->base.clock = PLAYER_CLOCK;
    p->base.timer = 0;
    p->base.mass = 100;
    
    p->base.vel_x = 0.0;
    p->base.vel_y = 0.0;
    p->base.health = 6;
    p->base.max_health = 6;
    
    p->has_sword = 0;
    set_player_light_dist(p, LIGHT_DIST);
    p->last_door = NULL;
    p->moves = NULL;
    
    p->base.fly = 0;
    set_entity_override_clip(&(p->base), 1);
    p->base.direction = 0;
    
    
    // below is testing just for fun, toggle on / off
    // int width = 1;
    // int height = 1;
    //init_entity_hit_box_block(&(p->base), width, height, ROT_CENTRE_STYLE, p->base.direction);
    
    
    
    
    // with reference to first room in game rooms, set the player's position in the direct centre.
    return set_player_default_position(game->rooms, p);
}








int set_player_default_position(Room_ls** room_p, Player* p) {
    
    int error = set_player_deault_room(room_p, p);
    
    if (error) { return error;}
    
    return set_room_default_position(p);
}



// set the value 'room' pointer in player.

int set_player_deault_room(struct room_list_t** room_p, struct player_t* p) {
    if (room_p == NULL || p == NULL) {
        return 1;
    }
    
    Room_ls* tmp_room_ls = room_p[0];
    if (tmp_room_ls == NULL) {
        null_error(ROOM_LS_OBJECT, "set_player_default_position");
        return 2;
    }
    return set_player_room(tmp_room_ls->room, p);
}



// setter for player and room variables

int set_player_room(struct room_t* room_, struct player_t* p) {

    if (p == NULL) {
        null_error(PLAYER_OBJECT, "set_player_room");
        return 1;
    }
    
    p->room = room_;
    return 0;
}





int set_room_default_position(Player* p) {
    
    Room* room = p->room;
    
    
    if (room == NULL) {
        null_error(ROOM_OBJECT, "set_room_default_position");
        return 2;
    }
    
    p->base.x = room->width / 2;
    p->base.y = room->height / 2;
    
    char* tmp_array = room->room_array;
    if (NULL == tmp_array) {
        null_warning(STRING_OBJECT, "set_room_default_position");
        return 0;
    }
    
    int loop = 0;
    int try = 0;
    
    char c = tmp_array[room->width * p->base.y + p->base.x];
    while (c != 0 && c <= MAX_CLIP_T && try <= 100) {
        try ++;
        printf("Unable to place the player... trying again... [%d]\n", try);
        p->base.y++;
        p->base.x++;
        
        if (p->base.y++ == room->height) {
            if (!loop) {
                loop = 1;
            }
            else {
                loop = 0;
                p->base.x--;
            }
            p->base.y = 0;
        }
        
        if (p->base.x++ == room->width) {
            
        }
        
        c = tmp_array[room->width*p->base.y + p->base.x];
        try++;
        if (try > 100) {
            printf("Giving up player placement\n");
            pause_function();
            clear_screen();
        }
    }

    return 0;
}
# endif
