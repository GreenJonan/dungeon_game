# ifndef EXIT_INIT__
# define EXIT_INIT__

// HEADER

int front_load_room_exits(struct room_t*);
int connect_room_exits(struct game_t*, struct room_t*, int*);
int connect_exit_with_other_exit(struct game_t*, struct exit_t*, int*, int);
struct room_t* find_exit_room(struct game_t*, int);
struct exit_t* find_connecting_room_exit(struct room_t*, int, int, int);




// load all exit_pointers start with the first exit in the room;

int front_load_room_exits(Room* room) {

    // make sure exit_pointer in room points to first exit.
    if (room->exits == NULL) {
        return 1;
    }
    
    int exit_key = room->exits->exit->key;
    
    if (1 != exit_key) {
        
        printf("Warning: rooms should already be front loaded\n");
        pause_function();
        
        // bottom half of exit_linked list
        
        if ( (room->exit_len / 2) - exit_key < 0 ) {
            while (exit_key != 1) {
                room->exits = room->exits->prev;
                exit_key = room->exits->exit->key;
            }
        }
        // top half of exit linked list
        
        else {
            while (exit_key != 1) {
                room->exits = room->exits->next;
                exit_key = room->exits->exit->key;
            }
        }
        
    }
    return 0;
}









////////////////////////////////////////////////////////////////////

//////
//////      MAIN
//////


// assume all exits are loaded into the game, now make sure



int connect_exits(Game* game) {
    
    if (NULL == game) {
        null_error(GAME_OBJECT, "connect_exits");
        return 1;
    }
    
    
    printf("Connecting exits together...\n");
    int progress = 0;

    // recall, rooms is an array of room_linked list pointers
    // rooms from 1 -> room_len
    // hence connect rooms via a for loop over pointers
    
    
    for (int i = 0; i < game->room_len; i++) {
    
        Room_ls* room_list = game->rooms[i];
        
        if (room_list == NULL) {
            null_error(ROOM_OBJECT, "connect_exits");
        }
        else {
        
            Room* room_ = room_list->room;
            // room_id = i + 1
            
            printf("Connecting exits in room %d\n", room_->room_id);
            connect_room_exits(game, room_, &progress);
            
        }
    }

    clear_screen();
    printf("Connected Exits\n");
    return 0;
}










//////////////////////////////////////////////////////

////
////    SUPPLEMENTARY FUNCTIONS
////



Exit_ls* connect_exit_loop(Game*, Exit_ls*, Room*, int*, int*);



// connect all exits in room, with other exits.

int connect_room_exits(struct game_t* game, struct room_t* room, int* progress) {
    
    int no_exits;
    no_exits = front_load_room_exits(room);
    
    
    if (!no_exits && 1) {
        
        
        //&& room->exit_len > 0
        
        // exits are in a circular list, hence connect next element until reach first element or,
        // exceed exit_num
        
        Exit_ls* exit_list = room->exits;
        
        
        if (exit_list->exit == NULL) {
            null_error(EXIT_OBJECT, "connect_room_exits-err1");
            pause_function();
        }
        
        
        else {
            // index for room_array char* array;
            int index = 0;
            
            
            int exit_num = exit_list->exit->key;    //which should = 1, since front loaded lists.
            int tmp_exit_num = 0;
        
            exit_list = connect_exit_loop(game, exit_list, room, progress, &index);
            
            if (exit_list == NULL) {
                null_error(EXIT_LS_OBJECT, "connect_room_exits-err3");
                return 1;
            }
            
            tmp_exit_num = exit_list->exit->key;
        
        
            // loop through all exits in the room & do the first door last!!!
        
            while (exit_num != tmp_exit_num) {
            
                
                exit_list = connect_exit_loop(game, exit_list, room, progress, &index);
                
                if (exit_list == NULL) {
                    null_error(EXIT_LS_OBJECT, "connect_room_exits-err3");
                    return 1;
                }
                
                
                tmp_exit_num = exit_list->exit->key;
            }
        }
    }
    return 0;
}







Exit_ls* connect_exit_loop(Game* game, Exit_ls* exit_p, Room* room, int* progress, int* index) {

    Exit_ls* new_exit_ls = NULL;
    
    /*
    if (exit_p == NULL) {
        null_error(EXIT_LS_OBJECT, "connect_room_exits-err2");
        return NULL;
    }
    if (exit_p->exit == NULL) {
        null_error(EXIT_OBJECT, "connect_room_exits-err2");
        return NULL;
    }*/
 
    
    if (exit_p->exit->room_num > 0 && exit_p->exit->room_num <= game->room_len && exit_p->exit->exit_num > 0) {
        
        connect_exit_with_other_exit(game, exit_p->exit, progress, room->room_id);
    }
    /*
     else {
     // dont remove the exit, even though it points to nothing,
     //as some door may be pointing to it!
     //already set to NULL
     }*/
    /*
    else {
        printf("\nHERE: room_num: %d, exit_num: %d\n\n", exit_p->exit->room_num, exit_p->exit->exit_num);
    }*/

    set_exit_pos(room->room_array, room->width, room->height, index, exit_p->exit);
    new_exit_ls = exit_p->next;

    if (new_exit_ls == NULL) {
        null_error(EXIT_LS_OBJECT, "connect_room_exits-err2");
        return NULL;
    }
    if (new_exit_ls->exit == NULL) {
        null_error(EXIT_OBJECT, "connect_room_exits-err2");
        return NULL;
    }
    
    return new_exit_ls;
}











int connect_exit_with_other_exit(Game* game, Exit* exit, int* progress, int or_room) {
    
    if (LOADING_PROGRESS) {
        loading_progress(*progress);
        *progress = (*progress) += 1;
    
        if (*progress >= 4) {
            *progress = 0;
        }
    }

    
    Room* exit_room = find_exit_room(game, exit->room_num);
    //printf("room: %p\n", exit_room); working as expected
    Exit* door_ = find_connecting_room_exit(exit_room, exit->exit_num, or_room, exit->key);
    
    // both functions are working AS EXPECTED!!!
    // NOTE:
    // if '$' isnt given, exit wont be read,
    // if DOOR_TILE isnt given, then exit_len = 0, then exit/door will not be connected!!!

    exit->door = door_;

    return 0;
}









// find the room that the exit points to.

struct room_t* find_exit_room(Game* game, int room_num) {
    
    Room* output = NULL;

    if (room_num > 0 && room_num <= game->room_len) {
    
        Room_ls* tmp_room_ls = game->rooms[room_num - 1];
        
        if (tmp_room_ls == NULL) {
            null_error(ROOM_LS_OBJECT, "find_exit_room");
        }
        
        else {
            
            output = tmp_room_ls->room;
        }
    }
    return output;
}
    

                


/*

        int k = 0;

            
            Exit_ls* tmp_exit_ls = tmp_room->exits;
            int found_exit = 0;
            
            while (k < exit_count && !found_exit) {
                
                k++;
                if (exit_list->exit->exit_num == tmp_exit_ls->exit->key) {
                    
                    exit_list->exit->door = tmp_exit_ls->exit;
                    found_exit = 1;
                }
                
                else {
                    tmp_exit_ls = tmp_exit_ls->next;
                }
                
                
            }
            // if haven't found exit, dont do anything
        }
        
        
        else {
            // dont do anything, exit appears to be locked.
        }
        
        
    }



    return 0;
}
*/








// given an original room and exit, and the correpsonding room pointer the exit should exist in,
// find the exit which the original exit should connect to.


struct exit_t* find_connecting_room_exit(Room* room, int exit_num, int or_room, int or_exit) {
    Exit* output = NULL;
    
    if (room == NULL) {
        return output;
    }

    int exit_ls_len = room->exit_len;
    
    // ensure the exit number is a defined within the room.
    if (exit_num <= exit_ls_len) {
    
        
        Exit_ls* tmp_exit_ls = room->exits;
        
        if (tmp_exit_ls != NULL) {
        
            // assume for this function, the lists have NO jumps in numbers
            
            for (int i = 1; i < exit_num; i++) {
                
                if (tmp_exit_ls->next == NULL) {
                    printf("FATAL ERROR:   ");
                    null_error(EXIT_LS_OBJECT, "find_connecting_room_exit");
                    return output;
                }
                
                else {
                    tmp_exit_ls = tmp_exit_ls->next;
                }
            }
            
            output = tmp_exit_ls->exit;
            
            if (output == NULL) {
                null_error(EXIT_OBJECT, "find_connecting_room_exit");
            }
            
            else {
                if (output->key != exit_num ){
                    printf("Exit numbers are not identical: input: %d, exit_key: %d\n", exit_num, output->key);
                }
                
                //debug
                if (ROOM_DEBUG) {
                    printf("\nConnected Door: Room %d, Exit %d, to"
                           "\n          Door: Room %d, Exit %d\n",
                           or_room, or_exit, room->room_id, output->key);
                    pause_function();
                }
            }
            
            

        }
        else {
            null_warning(ROOM_LS_OBJECT, "find_connecting_room_exit");
        }
    }
    else {
        if (ROOM_DEBUG) {
            printf("Invalid exit_number: %d, max: %d\n", exit_num, exit_ls_len);
            pause_function();
        }
    }
    
    return output;
}















///////////////////////

int set_exit_pos_null_error(char* object) {
    return null_error(object, "set_exit_pos");
}





// set the appropriate co-ordinates for each exit for the rooms that they exist in.

int set_exit_pos(char* room_array, int width, int height, int* index, Exit* door) {
    
    if (NULL == room_array) {
        set_exit_pos_null_error(STRING_OBJECT);
        return 1;
    }
    if (NULL == door) {
        set_exit_pos_null_error(EXIT_OBJECT);
        return 1;
    }
    if (NULL == index) {
        set_exit_pos_null_error("int");
    }
    
    //printf("width: %d, height: %d\n", width, height);
    
    int door_found = 0;
    while (!door_found) {
        
        if (*index >= width*height) {
            door_found = 1;
        }
        
        if (!door_found) {
        
            if (room_array[*index] == DOOR_N) {
                door_found = 1;
                
                // computation
                
                int x_ = *index % width;
                int y_ = (*index - x_) / width;
                
                //printf("exit: %d, x: %d, y: %d, index: %d\n", door->key, x_, y_, *index);
                
                door->x = x_;
                door->y = y_;
                
                
            }
            *index = *index + 1;
        }
    }
    
    
    
    return 0;
}




# endif
