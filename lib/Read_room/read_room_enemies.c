# ifndef READ_ROOM_ENEMIES_
# define READ_ROOM_ENEMIES_

int read_enemies(Room*, FILE*);
int fix_enemy_identity(struct enemy_t*, char*);
int punctuation_flush(FILE*);

int set_custom_enemy_properties(struct enemy_t*, int, int, int, float, int, int, int, int, int);



int read_room_enemies(Room* empty_room, char* enemy) {
    return read_room(empty_room, enemy, "read_room_enemies", 2);
}




int read_enemies(Room* empty_room, FILE* f) {

    
    int end_of_file = 0;
    Enemy_ls* prev_ls_ptr = NULL;
    
    while (!end_of_file) {
        // read line by line
        char c = fgetc(f);
        
        
        // read until first '$' symbol indicating start of enemy list,
        while (c != '$' && !end_of_file && c != '/') {
            c = fgetc(f);
    
            if (feof(f)) {
                end_of_file = 1;
            }
        }
        
        
        if (c == '/') {
            flush_file_input(f);
            if (feof(f)) {
                end_of_file = 1;
            }
        }
        
        
        
        else if (!end_of_file && c == '$') {
            
            // see what enemy type it is,
            char str[BUFF];
            
            fscanf(f, "%s", str);
            
            if (str_eq(str, NONE)) {
            
                flush_file_input(f);
                if (feof(f)) {
                    end_of_file = 1;
                }
            }
            
            else {
            
                int x_, y_, v_x, v_y, direction, diff, has_item, defauLt; // def_t ==> default type, diff ==>challenge/difficulty
            
                fscanf(f, "%d,%d %d,%d %d %d %d %d", &x_, &y_, &v_x, &v_y, & direction, &diff,
                       &has_item, &defauLt);
            
            
                Enemy* e = allocate_enemy(1);
                
            
            
                // set default & input values
            
                set_enemy_pos(e, x_, y_);
                e->base.vel_x = v_x;
                e->base.vel_y = v_y;
                e->champion = diff;
                e->drop_item = 0;
                e->base.direction = direction;
            
                if (has_item > 0) {
                    e->drop_item = 1;
                }
            
                // set to NULL be default.
                e->item = NULL;
            
            
                // initialise enemy defaults
                int error;
                error = fix_enemy_identity(e, str);
            
            
            
                if (error) {
                    free(e);
                    flush_file_input(f);
                    if (feof(f)) {
                        end_of_file = 1;
                    }
                }
                
                else {
                    prev_ls_ptr = push_enemy_start(prev_ls_ptr, e);
                    // if default is not true, read in values to overwite other default settings
                    if (!defauLt) {
                
                        end_of_file = punctuation_flush(f);
                
                        // if end of file/line, dont modify the default values.
                
                        if (!end_of_file) {
                
                            int health, clock, mass;
                            float rnd;
                        
                            fscanf(f, "%d %d %d %f", &health, &clock, &mass, &rnd);
                    
                    
                            end_of_file = punctuation_flush(f);
                            if (!end_of_file) {
                    
                                int vis_dist, eye, ai;
                                fscanf(f, "%d %d %d", &vis_dist, &eye, &ai);
                        
                        
                                end_of_file = punctuation_flush(f);
                                if (!end_of_file) {
                        
                                    int touch_dmg, shield;
                                    fscanf(f, "%d %d", &touch_dmg, &shield);
                            
                            
                                    // now sort the inputs;
                                    set_custom_enemy_properties(e, health, clock, mass, rnd,
                                                                vis_dist, eye, ai,
                                                                touch_dmg, shield);
                        
                                }
                    
                            }
                        }
                    }
                    if (!end_of_file) {
                        flush_file_input(f);
                        if (feof(f)) {
                            end_of_file = 1;
                        }
                    }
            
            
            
            
            
                    if (has_item) {
                        // c is still equal to $ from initialising enemy, hence need to re-read char
                        c = fgetc(f);
                        
                        while (c != '$' && !end_of_file) {
                            if (c == '/') {
                                flush_file_input(f);
                            }
                            if (feof(f)) {
                                end_of_file = 1;
                            }
                            c = fgetc(f);
                        }
                
                        if (!end_of_file) {
                            // read in the item input
                            char str2[BUFF], msg[BUFF];
                            int n;
                
                            fscanf(f, "%s %d %s", str2, &n, msg);
                            flush_file_input(f);
                            if (feof(f)) {
                                end_of_file = 1;
                            }
                    


                            Item* i = init_inv_item(str2, n, msg, 1);
                            
                    
                            // set the enemy to hold the item.
                            e->item = i;
                        }
                        else {
                            printf("ERROR: No item associated for enemy.\n");
                            pause_function();
                        }
                    }
                }
            }
        }
    
    }
    
    if (prev_ls_ptr != NULL) {
        while (prev_ls_ptr->prev != NULL) {
            prev_ls_ptr = prev_ls_ptr->prev;
        }
    }
    
    empty_room->enemies = prev_ls_ptr;
    
    
    return 0;
}












////////////////////////////////////////

// set the enemy defaults and ID based on string input


int fix_enemy_identity(struct enemy_t* e, char* str) {

    if (str == NULL) {
        null_error(STRING_OBJECT, "fix_enemy_identity");
        return 1;
    }
    if (e == NULL) {
        enemy_null_error("fix_enemy_identity");
        return 1;
    }

    
    if (str_eq(str, ORB)) {
        init_orb(e);
    }
    
    else if (str_eq(str, SLIME)) {
        init_slime(e);
    }
    
    
    else if (str_eq(str, KNIGHT)) {
        init_knight(e);
    }
    
    
    else if (str_eq(str, GHOST)) {
        init_ghost(e);
    }
    
    
    else if (str_eq(str, SKELETON)) {
        init_skeleton(e);
    }
    
    else if (str_eq(str, BABY_SLIME)) {
        init_baby_slime(e);
    }
    
    else if (str_eq(str, ZOMBIE)) {
        init_zombie(e);
    }


    else {
        //if (!SUPPRESS_WARNINGS) { printf("WARNING: unkown enemy type: %s.\n", str);}
        
        printf("WARNING: unkown enemy type: %s.\n", str);
        pause_function();
        e->enemy_id = NONE_ID;
        return 1;
    }
    return 0;

}











////////////////////////////////////////////////////////////////////

int set_custom_enemy_properties(struct enemy_t* e, int health, int clock, int mass, float rnd,
                                int vis_dist, int eyesight, int ai,
                                int touch_dmg, int shield) {

    if (e == NULL) {
        enemy_null_error("set_custom_enemy_properties");
        return 1;
    }
    
    if (health >= 0) {
        e->base.health =health;
        e->base.max_health = health;
    }
    
    
    if (clock >= 0) {
        e->base.clock = clock;
    }
    
    
    if (mass >= MIN_MASS) {
        e->base.mass = mass;
    }
    
    
    if (rnd >= 0) {
        e->wait_rnd = rnd;
        e->turn_rnd = rnd;
    }
    
    
    ///////////////////////////////////////
    
    
    if (vis_dist >= 0) {
        e->base.light_dist = vis_dist;
    }
    
    
    if (eyesight >= MIN_EYE) {
        e->base.eyesight = eyesight;
    }
    
    
    if (eyesight >= MIN_AI) {
        e->ai = ai;
    }
    
    
    
    
    //////////////////////////////////////////
    
    if (touch_dmg) {
        e->touch_dmg = touch_dmg;
    }
    
    
    if (shield >= 0 && shield < 16) {
        e->shield = shield;
    }

    return 0;
}








////////////////////////////////////////////////

int punctuation_flush(FILE* f) {
    int end_of_file = 0;
    char c = fgetc(f);
    
    while (c != '/' && c != '\\' && c != '-' && !end_of_file) {
        c = fgetc(f);
        if (feof(f)) {
            printf("ERROR: no separator after default_boolean in 'enemy' initiation source file.\n");
            end_of_file = 1;
        }
    }
    return end_of_file;
}

# endif
