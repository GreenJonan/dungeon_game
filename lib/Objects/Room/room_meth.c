# ifndef ROOM_LACED_WITH_METH__
# define ROOM_LACED WITH_METH__

# include "../special_entity_methods.c"

// return the char in the room_array, given x,y

char get_room_tile(Room* room, int x, int y) {
    
    if (room == NULL) {
        null_error(ROOM_OBJECT, "get_room_tile");
        return 0;
    }
    
    if (room->room_array == NULL) {
        null_error(STRING_OBJECT, "get_room_tile");
        return 0;
    }
    
    int w = room->width;
    int h = room->height;
        
    if (x < 0 || x >= w || y >=h || y < 0) {
        printf("VALUE ERROR: %d %d in 'get_room_tile'\n", x, y);
        pause_function();
        return 0;
    }
    
    // body of function
    return room->room_array[x + y * room->width];
}




int set_room_tile(struct room_t* room, int x, int y, char c) {
    
    if (room == NULL) {
        null_error(ROOM_OBJECT, "set_room_tile");
        return 1;
    }
    
    if (room->room_array == NULL) {
        null_error(STRING_OBJECT, "set_room_tile");
        return 1;
    }
    
    int w = room->width;
    int h = room->height;
    
    if (x < 0 || x >= w || y >=h || y < 0) {
        printf("VALUE ERROR: %d %d in 'set_room_tile'\n", x, y);
        pause_function();
        return 1;
    }
    
    // body of function
    room->room_array[x + y * room->width] = c;
    return 0;
}







int is_clip_tile(char c) {
    char output = 0;
    if (c != 0 && c <= MAX_CLIP_T) {
        output = 1;
    }
    return output;
}






// sees whether a certain position is able to be stood on.

int is_clip_position(Room* r, Entity* e, int new_x, int new_y) {
    
    int output = 0;
    
    char name[] = "is_clip_pos";
    if (r == NULL) {
        room_null_error(name);
        return -1;
    }
    
    if (new_x < 0 || new_x >= r->width) {
        printf("VALUE ERROR: invalid x-value: %d. Boundaries are, min: 0, max: %d\n", new_x, r->width);
        pause_function();
        return -1;
    }
    if (new_y < 0 || new_y >= r->height) {
        printf("VALUE ERROR: invalid y-value: %d. Boundaries are, min: 0, max: %d\n", new_y, r->height);
        pause_function();
        return -1;
    }
    
    
    // search through special entities, in particular spc_room_entities
    
    if (r->spc_room_entities != NULL) {
    
        while (r->spc_room_entities->prev != NULL && output == 0) {
            r->spc_room_entities = r->spc_room_entities->prev;
        }
        
        
        Spc_ent_ls* tmp_ls = r->spc_room_entities;
        
        while (tmp_ls != NULL) {
        
            if (tmp_ls->spc_entity == NULL) {
                special_entity_null_error(name);
            }
            
            else {
                int ent_id = tmp_ls->spc_entity->entity_id;
                
                
                // telephone
                if (ent_id == SPC_TELEPHONE_ID) {
                    if (tmp_ls->spc_entity->base.x == new_x && tmp_ls->spc_entity->base.y == new_y) {
                    output = 1;
                    }
                }
                
                
                
                // push_block
                else if (ent_id == SPC_PUSH_BLOCK_ID) {
                    if (tmp_ls->spc_entity->base.x == new_x && tmp_ls->spc_entity->base.y == new_y) {
                        output = 1;
                    }
                }
                
                
                
                // pop_block
                else if (ent_id == SPC_POP_BLOCK_ID) {
                    if (tmp_ls->spc_entity->base.x == new_x && tmp_ls->spc_entity->base.y == new_y) {
                        
                        if (get_pop_block_up(tmp_ls->spc_entity)) {
                        
                            // this implies block walking into will be a pop up block
                            // if also standing on a pop up block, then allow to walk on
                            
                            // search through all spc_entities again.
                            
                            
                            Spc_ent_ls* tmp_tmp_ls = r->spc_room_entities;
                            
                            int found = 0;
                            while (tmp_tmp_ls != NULL && !found) {
                            
                                // already previous reported null error.
                                if (tmp_tmp_ls->spc_entity != NULL) {
                                
                                    if (get_pop_block_up(tmp_tmp_ls->spc_entity)) {
                                    
                                        if (tmp_tmp_ls->spc_entity->base.x == e->x &&
                                            tmp_tmp_ls->spc_entity->base.y == e->y) {
                                            
                                            // this implies standing on pop-up block
                                            found = 1;
                                        }
                                    }
                                }
                                    
                                
                                tmp_tmp_ls = tmp_tmp_ls->next;
                            }
                            
                            if (!found) { output = 1;}
                        }
                    }
                }
                
                else if (ent_id == SPC_SWITCH_ID) {

                    if (tmp_ls->spc_entity->base.x == new_x && tmp_ls->spc_entity->base.y == new_y) {
                        output = 1;
                    }
                }
            }
            
            
            
            tmp_ls = tmp_ls->next;
        }
    }
    
    
    
    
    
    /////////////////////////////////////////
    
    // search in room_array
    
    
    if (output == 0) {
        // analyse the room contents
        
        if (r->room_array == NULL) {
            null_error("Room_array", name);
            return -1;
        }
        
        int tile = get_room_tile(r, new_x, new_y);
        
        
        if (tile == HOLE_N) {
            if (!e->fly) {
            output = 1;
            }
        }
        
        else {
            output = is_clip_tile(tile);
        }
    }
    
    
    return output;
}












/////////////////////////////////////////////////////////////////////////////////


// given a room number and an exit-key, return the appropriate exit if it exits.

Exit* find_room_exit(Game* game, int room_num_, int door_num) {
    
    //Exit* output = NULL;
    
    
    
    if (door_num <= 0) {
        printf("Invalid exit number\n");
        pause_function();
        return NULL;
    }
    if (room_num_ <= 0 || room_num_ > game->room_len) {
        printf("Invalid room number: %d\n", room_num_);
        pause_function();
        return NULL;
    }
    
    
    
    Room* tmp_room = game->rooms[room_num_ - 1]->room;
    if (tmp_room->exits == NULL) {
        printf("No exits in room %d\n", room_num_);
        pause_function();
        return NULL;
    }
    int error;
    error = front_load_room_exits(tmp_room);
    
    if (error) {
        return NULL;
    }
    
    
    
    Exit_ls* exit_ls_p = tmp_room->exits;
    
    int tmp_key = 1;
    int max_key = tmp_room->exit_len;
    
    if (exit_ls_p->prev->exit != NULL) {
        if (max_key < exit_ls_p->prev->exit->key) {
            max_key = exit_ls_p->prev->exit->key;
        }
    }
    
    
    if (exit_ls_p->exit != NULL) {
        tmp_key = exit_ls_p->exit->key;
    }
    
    
    int i = 0;
    
    while (tmp_key != door_num) {
        
        exit_ls_p = exit_ls_p->next;
        
        if (exit_ls_p == NULL) {
            null_error(EXIT_LS_OBJECT, "find_room_exit");
            return NULL;
        }
        
        Exit* tmp_exit = exit_ls_p->exit;
        if (tmp_exit != NULL) {
            tmp_key = tmp_exit->key;
        }
        
        
        i++;
        if (i > max_key) {
            printf("Sorry unable to find exit.\n");
            pause_function();
            return NULL;
        }
    }
    
    
    return exit_ls_p->exit;
}




Exit* find_exit_point(Room* r, int x, int y) {

    if (r == NULL) {
        null_error(ROOM_OBJECT, "find_exit_point");
        return NULL;
    }
    Exit_ls* ptr = r->exits;
    int exit_num = r->exit_len;
    
    if (exit_num <= 0) {
        return NULL;
    }
    else if (ptr == NULL) {
        null_error(EXIT_LS_OBJECT, "find_exit_point");
        return NULL;
    }
    else if (ptr->exit == NULL) {
        null_error(EXIT_OBJECT, "find_exit_point");
        return NULL;
    }
    
    
    
    int found = 0;
    
    
    if (ptr->exit->x == x && ptr->exit->y == y) {
        found = 1;
    }
    
    
    int i = 0;
    while (!found) {
        ptr = ptr->next;
        
        if (ptr == NULL) {
            null_error(EXIT_LS_OBJECT, "find_exit_point");
            return NULL;
        }
        if (ptr->exit == NULL) {
            null_error(EXIT_OBJECT, "find_exit_point");
            return NULL;
        }
        
        if (ptr->exit->x == x && ptr->exit->y == y) {
            found = 1;
        }
        
        i++;
        if (i > exit_num) {
            return NULL;
        }
    }

    // if reached here the exit_ls object should point to the desired exit, hence return it
    
    return ptr->exit;
}









int teleport_player_to_exit(Game* game, int room_num_, int exit_num, int debug) {

    Exit* tmp_exit = find_room_exit(game, room_num_, exit_num);
    if (tmp_exit == NULL) {
        return 1;
    }
    if (tmp_exit->room == NULL) {
        room_null_error("teleport_to_exit");
    }
    
    reset_spc_room_entities(game->player);
    
    game->player->base.x = tmp_exit->x;
    game->player->base.y = tmp_exit->y;
    game->player->room = tmp_exit->room;
    draw_screen(game);
    
    if (debug) {
        printf("Teleported player: Room %d, Exit %d\n", room_num_, exit_num);
    }


    return 0;
}







//////////////////////////////////////////////////////////////////////////////////

// probably one of the hardest functions to make sure it works appropriately, is path finding
// in particular, this function sees if the route between two points (x1,y1) and (x2,y2) is clear
/* e.g.
 
 `#```B
 #`#```
 ```#``
 A```#` --> this arrangement is blocked
 
 
 ``##B```
 ``#`|```
 ``##|```
 ``#`|```
 ``#`|```
 ``A-+``` --> this path is clear.
 ````````
 ````````
 
 #+-+##
 #|#+-B
 `|####
 A+````  --> path should be blocked
 
 ```#B#
 ####|#
 #+--+#
 #|####
 #+--+#
 ####|#  --> this path should be blocked
 A---+#
 
 ``B  --> Case 1
 ```
 A``
 
 A``  --> case 2
 ```
 ``B
 
 
 
 ``A  --> case 3
 ```
 B``
 
 B``  --> case 4
 ```
 ``A
 */

/*
int clear_path(struct room_t* r, int x1, int y1, int x2, int y2) {
    if (r == NULL) {
        room_null_error("clear_path");
        return -1;
    }
    if (r->room_array == NULL) {
        null_error(STRING_OBJECT, "clear_path");
        return -1;
    }
    
    // function is symmetric for (x1,y1) and (x2,y2)
    // hence adjust input values to only deal with case 1,2
    
    // test if within bounds
    if (x1 < 0 || x1 >= r->width)  { return 0;}
    if (x2 < 0 || x2 >= r->width)  { return 0;}
    if (y1 < 0 || y1 >= r->height) { return 0;}
    if (y2 < 0 || y2 >= r->height) { return 0;}
    
    if (x1 == x2 && y1 == y2) { return 1; }
    
    
    int xa = x1;
    int xb = x2;
    int ya = y1;
    int yb = y2;
    if (xa > xb) {xa = x2; xb = x1; ya = y2; yb = y1;}
    
    if (get_room_tile(r, xb, yb) != 0 && get_room_tile(r, xb, yb) <= MAX_VIS_BLOCK_T) { return 0;}
    
    
    
    if (yb - ya >= 0) {
        return clear_path_down(r, xa, ya, xb, yb);
    }
    else {
        return clear_path_up(r, xa, ya, xb, yb);
    }
}








// recursive function to see whether the path is clear, only two movement up/down and right

int clear_path_dir(struct room_t* r, int xa, int ya, int xb, int yb, int dir) {
    
    // see whether the current tile is able to be seen through
    char tile = get_room_tile(r, xa, ya);
    if (tile != 0 && tile <= MAX_VIS_BLOCK_T) {
        return 0;
    }
    
    
    if (xb == xa && yb == ya) {
        return 1;
    }
    // can only move right or up
    char result = 0;
    
    
    if (xa < xb) {
        result = clear_path_up(r, xa+1, ya, xb, yb);
    }
    
    if (!result) {
        if (ya > yb) {
            result = clear_path_up(r, xa, ya+dir, xb, yb);
        }
    }
    
    return result;
}






int clear_path_up(struct room_t* r, int xa, int ya, int xb, int yb) {
    return clear_path_dir(r, xa, ya, xb, yb, -1);
}



int clear_path_down(struct room_t* r, int xa, int ya, int xb, int yb) {
    return clear_path_dir(r, xa, ya, xb, yb, 1);
}*/


/*
 A````     right, down
 `````
 ````B --> +x, +y, dir = 1
 
 ````B     right, up
 `````
 A```` --> +x, -y, dir = 2
 
 ````A     left, down
 `````
 B```` --> -x, +y, dir = 3
 
 B````     left, up
 `````
 ````A --> -x, -y, dir = 4
 */





// The code has been reworked to work from point a --> b without compressing into two cases
// the return values are: 1,2,3,4,5 <==> W,A,S,D,SAME


int simple_clear_path(char* array, int w, int h, int x1, int y1, int x2, int y2) {

    if (array == NULL) {
        null_error("Array", "simple_clear_path");
        return 0;
    }
    
    // function should be symmetric for (x1,y1) and (x2,y2)
    
    // test if within bounds
    if (x1 < 0 || x1 >= w)  { return 0;}
    if (x2 < 0 || x2 >= w)  { return 0;}
    if (y1 < 0 || y1 >= h) { return 0;}
    if (y2 < 0 || y2 >= h) { return 0;}
    
    // return true if same point
    if (x1 == x2 && y1 == y2) { return 5; }

    
    // if (x2,y2) is a blocked tile, return false
    char tile = array[x2 + y2 * w];
    if (tile != 0) { return 0;}
    
    
    int rel_x = x2 - x1;
    int rel_y= y2 - y1;
    

    int result = 0;
    int dir = 0;
    
    if (rel_y >= 0) {
        
        if (rel_x >= 0) {
            dir = 1;
        }
        
        else {
            dir = 3;
        }
    }
    
    else {
        if (rel_x >= 0) {
            dir = 2;
        }
        else {
            dir = 4;
        }
    }
    
    
    
    result = clear_path_dir(array, w, h, x1, y1, x2, y2, dir);
    
    
    if (VISION_DEBUG) {
        printf("direction+1: %d\n", result);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (array[i*w +j]) {
                    putchar('#');
                }
                else {
                    putchar(' ');
                }
            }
            putchar('\n');
        }
        pause_function();
    }
    
    return result;
}


/////////////////////////////////////////////////////////////////////



# define MOVE_UP 1
# define MOVE_LEFT 2
# define MOVE_DOWN 3
# define MOVE_RIGHT 4
# define STAY_STILL 5








int clear_path_dir(char* array, int w, int h, int x1, int y1, int x2, int y2, int dir) {
    // assume everything is valid, and no nulls, and dir is valid.

    
    // see whether the current tile is able to be seen through
    char tile = array[x1 + y1 * w];
    if (tile != 0) {
        return 0;
    }
    
    // set array such that don't count the same path twice
    array[x1 + w * y1] = 5;
    
    
    // see if we have reached the point.
    if (x1 == x2 && y1 == y2) {
        return STAY_STILL;
    }
    
    // intialise result:
    int result = 0;
    
    
    // compute which directions to go depending on dir.
    int del_x = 1;
    int del_y = 1;
    
    if (dir == 2) { del_y = -1;}
    else if (dir == 3) { del_x = -1;}
    else if (dir == 4) { del_x = -1; del_y = -1;}
    
    
    
    // now combinatorically find the path horizontally and vertically
    // assume x1,x2 and y1,y2 will never exceed each other.
    
    int hor = rand() % 2;
    int vert = 0;
    
    if (hor) {
        hor = 0;
        goto HORIZONTAL;
    }
    else {
        hor = 0;
        goto VERTICAL;
    }
    
    
    
HORIZONTAL:
    hor = 1;
    if (del_x * (x2 - x1) > 0) { //ensure x1 and x2 never exceed each other, del_x < 0 ==> while x2 < x1
        
        
        int clr;
        clr = clear_path_dir(array, w, h, x1 + del_x, y1, x2, y2, dir);
        
        if (clr) {
            if (del_x > 0) { result = MOVE_RIGHT;}
            else {           result = MOVE_LEFT;}
        }
    }
    if (!vert && !result){
        goto VERTICAL;
    }
    else {
        goto END;
    }
    
    
    
VERTICAL:
    vert = 1;
    if (del_y * (y2 - y1) > 0) { //same as for x
    

        int clr;
        clr = clear_path_dir(array, w, h, x1, y1 + del_y, x2, y2, dir);
            
        if (clr) {
            if (del_y > 0) { result = MOVE_DOWN;}
            else {           result = MOVE_UP;}
        }
        
    }
    if (!hor && !result){
        goto HORIZONTAL;
    }
    else {
        goto END;
    }
    
    
END:
    return result;
}




/////////////////////////////////////////////////////////////




















# endif
