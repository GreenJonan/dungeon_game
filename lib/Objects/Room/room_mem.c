# ifndef EXIT_AND_ROOM_MEM__
# define EXIT_AND_ROOM_MEM__

# include "room_header.h"




////////////////////////////////////////////////////////////////////

/////
/////     MEMORY DE-ALLOCATION
/////




////////////////////////////////////////////////////////////////////

////
////    DOORS
////

/*
int free_exit(Exit* exit, int ide) {

    if (exit != NULL) {
        if (ide == 0) {
            free_exit(exit->door, exit->iden);
        }
        else if (ide >= 0 && ide != exit->iden) {
            free_exit(exit->door, ide);
        }
        printf("freed exit: %d\n", exit->iden);
        free(exit);
    }
    
    return 0;
} */ // WAY TOO COMPLICATED TO FREE ALL DOORS LINKED TO ONE ANOTHER,
//think about d1->d2, but d2->d3 and d3->d2, hence will never loop back to d1 and will be stuck in endless loop.

// cannot free room, else there will be and endless loop, even in one door room.
// assume we have already removed the door from the room_array.




int free_exit(Exit* exit) {
    if (exit == NULL) {
        already_freed_warning(EXIT_OBJECT, "free_exit");
        return 1;
    }
    
    free(exit);
    // still possible to access exit->key since, pointer does not becomes NULL.
    
    return 0;
}






// free list of exits from memory
// assume list loops around

int free_exit_ls(Exit_ls* exit_ls, int key_) {
    
    if (exit_ls == NULL) {
        already_freed_warning(EXIT_LS_OBJECT, "free_exit_ls");
        return 1;
    }
    
    if (exit_ls->next == NULL) {
        free_exit(exit_ls->exit);
        free(exit_ls);
        return 0;
    }
    
    
    int door_key;
    
    if (exit_ls->exit == NULL) {
        printf("Error: unable to fetch exit 'key', exit already de-allocated.\n");
        pause_function();
        door_key = 0;
    }
    else {
        door_key = exit_ls->exit->key;
    }
    
    
    
    // main body

    if (0 == key_) {
        
        free_exit_ls(exit_ls->next, door_key);
    }
    else {
        if (key_ != door_key) {
            free_exit_ls(exit_ls->next, key_);
        }
        free_exit(exit_ls->exit);
        free(exit_ls);
    }
    
    return 0;
}
// if first time, key_ should be zero, hence dont deallocate and set key to be first exit_ls node.
// if havent looped back to the begining or hit null, reiterate function,
// then free all structure pointers.


/*
 printf("here   -->   \n");
 printf("Potential error with 'free_exit_ls' function, Exit: %d.", exit_ls->exit->key);
 getchar();
 */




////////////////////////////////////////////////////////////////////

////
////    CHESTS
////



int free_chest(Chest* chest) {
    if (chest == NULL) {
        null_warning(CHEST_OBJECT, "free_chest");
        return 1;
    }
    
    // free item;
    if (chest->item != NULL) {
        free_item(chest->item);
    }
    
    free(chest);
    return 0;
}



int free_chest_list(Chest_ls* c_ls) {

    if (c_ls == NULL) {
        return 0;
    }
    
    free_chest_list(c_ls->next);
    free_chest(c_ls->chest);
    free(c_ls);
    return 0;
}



int free_room_chests(Room* r) {
    if (r == NULL) {
        null_error(ROOM_OBJECT, "free_room_chests");
        return 1;
    }
    
    if (r->chests != NULL) {
        while (r->chests->prev != NULL) {
            r->chests = r->chests->prev;
        }
        
        return free_chest_list(r->chests);
    }
    return 0;
}


////////////////////////////////////////////////////////////////////

////
////    ROOMS
////


// free the internal structures

int free_room_exits(Room* room) {
    if (room->exit_len > 0) {
        free_exit_ls(room->exits, 0);
    }
    
    
    // make sure first entry of array is null, else free it manually
    /*
    if (NULL != room->exits) {
        if (NULL != room->exits->next) {
            
            printf("Error: unable to deallocate all exits appropraitely in room %d.\n", room->room_id);
            wait_msg();
        }
        
        if (NULL != room->exits->exit) {
            printf("here!!!\n");
            free_exit(room->exits->exit);
        }
        printf("here vvvvv\n");
        free(room->exits);
    }
     */
    // NOTE: pointers do not becomes NULL after they have been freed!!!!!
    // instead they are just 'freed' and can be overwritten by other functions.
    return 0;
}







int free_room_items(Room* room) {
    if (NULL == room) {
        null_error(ROOM_OBJECT, "free_room_items");
        getchar();
        return 1;
    }
    
    if (room->items != NULL) {
        free_item_ls(room->items);
    }
    return 0;
}







int free_room_enemies(Room* room) {
    if (NULL == room) {
        null_error(ROOM_OBJECT, "free_room_enemies");
        getchar();
        return 1;
    }
    if (room->enemies != NULL) {
        free_enemy_ls(room->enemies);
    }
    
    return 0;
}



int free_room_spc_weapon_entities(Room* room) {
    if (NULL == room) {
        null_error(ROOM_OBJECT, "free_room_spc_weapon_entities");
        return 1;
    }
    
    if (room->spc_weapon_entities != NULL) {
        free_special_entity_ls(room->spc_weapon_entities);
    }
    
    return 0;
}

int free_room_spc_room_entities(Room* room) {
    if (NULL == room) {
        null_error(ROOM_OBJECT, "free_room_spc_room_entities");
        return 1;
    }
    
    if (room->spc_room_entities != NULL) {
        free_special_entity_ls(room->spc_room_entities);
    }
    
    return 0;
}






// free room object from memory

int free_room(Room* room) {
    
    free_room_enemies(room);
    free_room_items(room);
    free_room_spc_weapon_entities(room);
    free_room_spc_room_entities(room);
    
    free_room_exits(room);
    free_room_chests(room);
    
    free_room_array(room->room_array);
    free(room);
    
    return 0;
}





int free_room_array(char* array) {
    if (array != NULL) {
        free(array);
    }
    return 0;
}





// free room list, recursively free rooms
// imagine/assume the list is circular

int free_room_ls(Room_ls* room_list, int key) {
    
    if (room_list != NULL) {
        
        if (room_list->room != NULL) {
            
            if (0 == key) {
                free_room_ls(room_list->next, room_list->room->room_id);
            }
            
            
            
            else {
                //printf("here: room num %d\n", room_list->room->room_id);
                
                if (room_list->room->room_id != key) {
                    free_room_ls(room_list->next, key);
                }
                
                free_room(room_list->room);
                //free(room_list->name); NOT MALLOCED
                
                free(room_list);
                return 0;
            }
        }
    }
    
    return 0;
}


















////////////////////////////////////////////////////////////////////

////
////    MEMORY ALLOCATION
////


Room_ls** allocate_room_ls_pointer_array(int num) {
    Room_ls** ptr = (Room_ls**) malloc(sizeof(Room_ls*)*num);
    for (int i = 0; i < num; i++) {
        ptr[i] = (Room_ls*) malloc(sizeof(Room_ls));
    }
    
    // forward and back arrangements
    // connect front and back end to one another
    
    //ptr[0]->prev = ptr[num-1];
    ptr[num-1]->next = ptr[0];
    
    for (int i = 0; i < num - 1; i++) {
    
        //ptr[i+1]->prev = ptr[i];
        ptr[i]->next = ptr[i+1];
        
        ptr[i]->room = allocate_room(i+1);
    }
    ptr[num-1]->room = allocate_room(num);
    return ptr;
}







Room* allocate_room(int room_id_) {

    Room* ptr = (Room*)malloc(sizeof(Room));
    ptr->room_id = room_id_;
    ptr->update_time = -1;
    ptr->is_dark = 0;
    
    ptr->room_array = NULL;
    ptr->width = 0;
    ptr->height = 0;
    
    ptr->enemies = NULL;
    ptr->items = NULL;
    ptr->spc_weapon_entities = NULL;
    ptr->spc_room_entities = NULL;
    
    ptr->exits = NULL;
    ptr->chests = NULL;
    
    return ptr;
}









///// EXIT MEMORY ALLOCATION



Exit* allocate_exit() {
    return (Exit*) malloc(sizeof(Exit));
}


Exit_ls* allocate_exit_ls(Exit_ls* prev_exit) {
    
    Exit_ls* ptr = (Exit_ls*) malloc(sizeof(Exit_ls));
    ptr->exit = allocate_exit();
    
    
    if (NULL != prev_exit) {
        prev_exit->next = ptr;
    }
    ptr->prev = prev_exit;
    return ptr;
}







// CHEST MEMORY ALLOCATION

Chest* allocate_chest(Item* i) {
    Chest* ptr = (Chest*) malloc(sizeof(Chest));
    
    ptr->item = i;
    return ptr;
}

Chest_ls* allocate_chest_ls(Chest_ls* prev_chest, Item* i) {
    
    Chest_ls* new_ptr = (Chest_ls*) malloc(sizeof(Chest_ls));
    new_ptr->chest = allocate_chest(i);
    
    new_ptr->prev = prev_chest;
    new_ptr->next = NULL;
    
    int c_id = 0;
    if (prev_chest == NULL) {
        c_id = 1;
    }
    
    else {
        prev_chest->next = new_ptr;
        
        if (prev_chest->chest == NULL) {
            null_error(CHEST_OBJECT, "allocate_chest_ls");
        }
        else {
            c_id = prev_chest->chest->identity += 1;
        }
    }
    new_ptr->chest->identity = c_id;
    
    return new_ptr;
}




# endif










/*
 if (do_free_room && exit->room != NULL) {
 free_room(exit->room);
 }*/


/*
 int free_next_room_ls_node(Room_ls*) {
 
 
 }*/ // not useful function currently.
