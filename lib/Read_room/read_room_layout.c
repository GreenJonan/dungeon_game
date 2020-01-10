# ifndef READ_ROOM_LAYOUT
# define READ_ROOM_LAYOUT

int read_layout_(Room*, FILE*);
int read_layout_layout(Room*, FILE*);
int read_layout_exits(Room*, FILE*);
int read_layout_chests(Room*, FILE*);
char tile_convert(char);
int read_layout_status(Room*, FILE*);
int read_layout_special(Room*, FILE*);
int read_layout_general(Room*, FILE*, int);



int read_room_layout(Room* empty_room, char* f_name) {
    return read_room(empty_room, f_name, "read_room_layout", 0);
}




int loading_room(int t) {
    clear_screen();
    if (LOADING_PROGRESS) {
        printf("Loading room layout...  ");
    }
    return loading_progress_no_clr(t);
}

int loading_doors(int t) {
    clear_screen();
    if (LOADING_PROGRESS) {
        printf("Loading doors...  ");
    }
    return loading_progress_no_clr(t);
}







// file reading algorithm --> assume no Null pointers

int read_layout_(Room* empty_room, FILE* f) {
    
    
    int end_of_file = 0;
    
    while (!end_of_file) {
        char c = 0;
    
        
        while (c != '#' && !end_of_file) {
                
            if (c == '/') {
                flush_file_input(f);
                if (feof(f)) {
                    end_of_file = 1;
                }
            }
            if (feof(f)) {
                end_of_file = 1;
            }

            c = fgetc(f);
            
        }
        
        
        if (!end_of_file) {
            char str[BUFF];
            fscanf(f, "%s", str);
    
    
            // find the first macro in the file.
            // loading_room && loading_doors is a function that indicates progress with a spinning wheel.
            // 0 indicates first state, i.e. '|'
    
            
            if (str_eq(str, SIZE)) {
                loading_room(0);
                end_of_file = read_layout_layout(empty_room, f);
            }
        
            else if (str_eq(str, EXIT)) {
                loading_doors(0);
                end_of_file = read_layout_exits(empty_room, f);
            }
            
            else if (str_eq(str, CHEST)) {
                end_of_file = read_layout_chests(empty_room, f);
            }
        
            /*
            else if (str_eq(str, DARK)) {
                empty_room->is_dark = 1;
            }*/
            
            else if (str_eq(str, STATUS)) {
                end_of_file = read_layout_status(empty_room, f);
            }
            
            else if (str_eq(str, SPECIAL)) {
                end_of_file = read_layout_special(empty_room, f);
            }
            
            else {
                printf("Invalid macro '%s' for room-%d layout.\n", str, empty_room->room_id);
                pause_function();
    
            }
        }
    }
    
    return 0;
}



    





// read the layout of the room and store it into the empty_room

int read_layout_layout(Room* empty_room, FILE* f) {

    // loading progress
    int progress = 0;
    
    
    int width, height;
    fscanf(f, "%d %d", &width, &height);
    
    char c;
    c = flush_file_input(f);
    
    empty_room->height = height;
    empty_room->width = width;
    
    
    // set up empty array for the tile array
    
    empty_room->room_array = (char*) malloc(sizeof(char) * width * height);
    
    
    
    // read layout for room
    //first line should start with line to read
    
    int end_of_file = 0;
    if (feof(f)) {
        end_of_file = 1;
    }
    
    
    empty_room->exit_len = 0;
    
    
    
    
    
    c = fgetc(f);
        
    for (int i = 0; i < height && !end_of_file; i++) {
        int end_of_line = 0;
        
        if (c == '/') {
            i--;
        }
        
        else {
            
            for (int j = 0; (j < width) && !end_of_file && !end_of_line; j++) {
                
                if (c == ' ' || c == '\t') {j--;}
                else if (feof(f)) {
                    end_of_file = 1;
                }
                else if (c == '\n') {
                    end_of_line = 1;
                }
                else {
                    char d = FLOOR_N;
                    
                    
                    if (c == 'F') { init_spc_flag(empty_room, j, i);}
                    
                    else {
                        d = tile_convert(c);
                    }
                    
                    
                    empty_room->room_array[i*width + j] = d;
                    
                    if (d == DOOR_N) {
                        empty_room->exit_len++;
                    }
                    
                }
                c = fgetc(f);
                
            }
            if (LOADING_PROGRESS) {
                loading_room(progress);
                progress++;
                if (progress >= 4) {
                    progress = 0;
                }
            }
        }
        
        
        // use up file input until reach end_of_file or end_of_file characters
        if (!end_of_file && !end_of_line) {
            dynamic_flush(f, c);
            //flush_file_input(f);
        }
        
        c = fgetc(f);
    }

    
    
    clear_screen();
    printf("Room loaded, room: %d\n", empty_room->room_id);
    
    return end_of_file;
}



/*
 Here are the following conversions for chars to int char values
 
 0,...,9 --> 1,...,10
 a,...,j --> 11,..,20    (CLIP OBJECTS)
 
 ` --> 0
 
 & --> 21    (DOOR)
 
 
 
 */


char tile_convert(char c) {
    char output = 0;
    
    if (c == FLOOR_T) {
        output = FLOOR_N;
    }
    else if (c == WALL_T) {
        output = WALL_N;
    }
    else if (c == DOOR_T) {
        output = DOOR_N;
    }
    else if (c == LIGHT_WATER_T) {
        output = LIGHT_WATER_N;
    }
    else if  (c == DARK_WATER_T) {
        output = DARK_WATER_N;
    }
    else if (c == SPIKE_T) {
        output = SPIKE_N;
    }
    else if (c == REFLECT_WALL_T) {
        output = REFLECT_WALL_N;
    }
    else if (c == INVISIBLE_WALL_T) {
        output = INVISIBLE_WALL_N;
    }
    else if (c == OPAQUE_WALL_T) {
        output = OPAQUE_WALL_N;
    }
    else if (c == SWITCH_T) {
        output = OPEN_SWITCH_N;
    }
    else if (c == CHEST_T) {
        output = CHEST_N;
    }
    else if (c == CRACKED_WALL_T) {
        output = CRACKED_WALL_N;
    }
    
    else if (c == LADDER_T) {
        output = LADDER_N;
    }
    
    else if (c == HOLE_T) {
        output = HOLE_N;
    }
    
    else if (c == TELEPHONE_T) {
        output = TELEPHONE_N;
    }
    
    else if (c == PUSH_BLOCK_T) {
        output = PUSH_BLOCK_N;
    }
    
    else if (c == POP_BLOCK_T) {
        output = POP_BLOCK_UP_N;
    }
    
    else if (c == LAMP_T) {
        output = LAMP_OFF_N;
    }
    
    else {
        if (!SUPPRESS_WARNINGS) {
            printf("Undefined tile: '%c'\n", c);
            pause_function();
        }
    }
    
    return output;
}







/////////////////////////////////////////////////////////////////////////




// read the exits of the room and store it into the empty_room

int read_layout_exits(Room* empty_room, FILE* f) {
    
    // measure loading progress
    int progress = 0;
    
    
    char c;
    int end_of_file = 0;
    
    c = flush_file_input(f);
    if (feof(f)) {
        end_of_file = 1;
    }
    
    
    Exit_ls* prev_ptr = NULL;
    int end_of_block = 0;
    int i = 0;
    
    int j = 0;
    
    
    while (!end_of_file && !end_of_block) {
        
        c = fgetc(f);

        if (c == '$') {
            j++;
            
            
            int room_num_, exit_num_, switch_num_, status_, locked, switch_t,
            bomb, portal, invis;
            
            fscanf(f, "%d %d %d %d,%d,%d,%d,%d", &room_num_, &exit_num_, &switch_num_,
                   &locked, &switch_t, &bomb, &portal, &invis);
            c = flush_file_input(f);
            status_ = locked + 2*switch_t + 4*bomb + 8*portal + invis*16;
            
            
            if (feof(f)) {
                end_of_file = 1;
            }
            
            
            prev_ptr = allocate_exit_ls(prev_ptr);
            
            if (i == 0) {
                i = 1;
                empty_room->exits = prev_ptr;
            }
        
            
            prev_ptr->exit->room_num = room_num_;
            prev_ptr->exit->exit_num = exit_num_;
            prev_ptr->exit->switch_id = switch_num_;
            prev_ptr->exit->status = (char) status_;
            set_door_default_locked(prev_ptr->exit, locked);
            
            prev_ptr->exit->key = j;
            
            prev_ptr->exit->room = empty_room;
            prev_ptr->exit->door = NULL;
            
            if (LOADING_PROGRESS) {
                loading_doors(progress);
                progress++;
                if (progress >= 4) {
                    progress = 0;
                }
            }
            
        }
        else if (c == '/') {
            flush_file_input(f);
        }
        else {
            end_of_block = 1;
            if (feof(f)) {
                end_of_file = 1;
            }
        }
    }
    

    if (0 != i) {
        prev_ptr->next = empty_room->exits;
        empty_room->exits->prev = prev_ptr;
    }
    
    
    clear_screen();
    printf("Doors loaded, room: %d\n", empty_room->room_id);
    
    return end_of_file;
}








int read_layout_chests(Room* r, FILE* f) {

    if (r == NULL) {
        null_error(ROOM_OBJECT, "read_layout_chests");
        return 1;
    }
    
    if (f == NULL) {
        null_error("FILE", "read_layout_chests");
        return 1;
    }
    
    
    int end_of_block = 0;
    int end_of_file = 0;



    // measure loading progress
    //int progress = 0;
    
    char c;
    
    c = flush_file_input(f);
    if (feof(f)) {
        end_of_file = 1;
    }

    Chest_ls* prev_ptr = r->chests; // should be NULL
    
    
    while (!end_of_file && !end_of_block) {
    
        
        c = fgetc(f);

        if (feof(f)) {
            end_of_file = 1;
        }
        
        if (!end_of_file) {

            
            if (c == '/') {
                flush_file_input(f);
            
                if (feof(f)) {
                    end_of_file = 1;
                }
            }
        
            else if (c == '$') {
                
            
                char item_name[BUFF];
                int locked;
                int num;
                char msg[BUFF];
                
                fscanf(f, "%d %s %d", &locked, item_name, &num);
                read_str(f, msg, BUFF);
                
                /*
                printf("locked: %d, name: %s, num: %d, msg: %s\n",
                       locked, item_name, num, msg);
                pause_function();*/
                
                
                // intialise the item
                
                
                Item* i = init_inv_item(item_name, num, msg, 1);
                
                
                
                // intialise the chest && set it to contain the item
                
                if (prev_ptr == NULL) {
                    r->chests = allocate_chest_ls(prev_ptr, i);
                    prev_ptr = r->chests;
                }
                else {
                    prev_ptr = allocate_chest_ls(prev_ptr, i);
                }
                
                prev_ptr->chest->locked = locked;
        
                
                flush_file_input(f);
                if (feof(f)) {
                    end_of_file = 1;
                }
            
            }
        
        
        
            else {

                end_of_block = 1;
            }
        }
    }

    return end_of_file;
}
    
    







//////////////////////////////////////////



int read_layout_status(Room* r, FILE* f) {

    char name[] = "read_layout_status";
    if (r == NULL) {
        room_null_error(name);
        return 1;
    }
    if (f == NULL) {
        null_error("FILE", name);
        return 1;
    }

    int dark, enemy_locked;
    fscanf(f, "%d %d", &dark, &enemy_locked);
    
    r->room_lock = enemy_locked;
    r->is_dark = dark;
    
    flush_file_input(f);
    if (feof(f)) {
        return 1;
    }
    return 0;
}







//////////////////////////////////////////////



int room_spc_ent_analysis(Room* r, FILE* f) {

    // assume not null for room and file.


    char obj_name[BUFF];
    fscanf(f, "%s", obj_name);
    
    

    if (str_eq(obj_name, TELEPHONE)) {
        
        // gather data
        int ring_id, local_dist, trig_id, is_trig, invisible;
        fscanf(f, "%d %d %d %d %d", &ring_id, &local_dist, &trig_id, &is_trig, &invisible);
        
        char msg[BUFF];
        read_str(f, msg, BUFF);
        
        
        init_spc_telephone(r, msg, -1, -1,
                           ring_id, local_dist, trig_id, is_trig, invisible);
    }
    
    
    
    else if (str_eq(obj_name, PUSH_BLOCK)) {
        
        int dir = 0, num, strength;
        int d1, d2, d3, d4;
        
        fscanf(f, "%d,%d,%d,%d %d %d", &d1, &d2, &d3, &d4, &num, &strength);
        
        if (d1) { dir += 1;}
        if (d2) { dir += 2;}
        if (d3) { dir += 4;}
        if (d4) { dir += 8;}
        
        init_spc_push_block(r, -1, -1, dir, num, strength);
    }
    
    
    
    else if (str_eq(obj_name, POP_BLOCK)) {
    
        int up, trig_id;
        fscanf(f, "%d %d", &up, &trig_id);
        
        init_spc_pop_block(r, -1, -1, up, trig_id);
    }
    
    
    else if (str_eq(obj_name, SWITCH)) {
        
        int closed, trig_id, type;
        fscanf(f, "%d %d %d", &closed, &trig_id, &type);
        
        
        init_spc_switch(r, -1, -1, closed, trig_id, type);
    }

    
    
    else if (str_eq(obj_name, LAMP)) {
        int trig_id, on, light_dist;
        
        fscanf(f, "%d %d %d", &on, &trig_id, &light_dist);
        
        init_spc_lamp(r, -1, -1, trig_id, on, light_dist);
    }
    
    
    else {
    
        printf("ERROR: unknown special object with name: %s\n", obj_name);
        pause_function();
    }

    
    

    flush_file_input(f);
    
    if (feof(f)) {
        return 1;
    }
    
    else {
        return 0;
    }
}







//////////////////////////////////////////////

int read_layout_special(struct room_t* r, FILE* f) {

    char name[] = "read_layout_special";
    
    if (f == NULL) {
        null_error("FILE", name);
        return 1;
    }
    
    else if (r == NULL) {
        room_null_error(name);
        return 1;
    }
    
    int end_of_file = 0;
    int end_of_block = 0;
    
    
    
    char c = fgetc(f);
    
    
    while (!end_of_file && !end_of_block) {
    
        while (c != '$' && c != '#' && !end_of_file) {
            if (c == '/') {
                flush_file_input(f);
            }
            c = fgetc(f);
            
            if (feof(f)) {
                end_of_file = 1;
            }
        }
        
        
        if (c == '#') {
            end_of_block = 1;
        }
            
        else if (c == '$') {
            
            end_of_file = room_spc_ent_analysis(r, f);
            c = fgetc(f);
        }
        
    }
    
    return end_of_file;
}






/////////////////////////////////////////////////////////////////////

// generalised room reading function.

// dont use this function.


int read_layout_general(struct room_t* r, FILE* f, int key) {
    
    char name[] = "read_layout_special";
    
    if (f == NULL) {
        null_error("FILE", name);
        return 1;
    }
    
    else if (r == NULL) {
        room_null_error(name);
        return 1;
    }
    
    int end_of_file = 0;
    int end_of_block = 0;
    
    
    
    char c;
    
    c = flush_file_input(f);
    if (feof(f)) {
        end_of_file = 1;
    }
    
    
    
    
    while (!end_of_file && !end_of_block) {
        
        c = fgetc(f);
        
        if (feof(f)) {
            end_of_file = 1;
        }
        
        else {
            
            if (c == '/') {
                flush_file_input(f);
                if (feof(f)) {
                    end_of_file = 1;
                }
            }
            
            else if (c == '$') {
                
                if (key == 1) {
                    end_of_file = room_spc_ent_analysis(r, f);
                }
                else {
                    // do something.
                    ;
                }
            }
            
            
            
            else {
                end_of_block = 1;
                flush_file_input(f);
                if (feof(f)) {
                    end_of_file = 1;
                }
            }
        }
    }
    
    return end_of_file;
}


# endif
