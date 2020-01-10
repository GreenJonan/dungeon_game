# ifndef CHEST_METHODS____
# define CHEST_METHODS____



// the following function will go through all the chests in each room and find the corresponding x,y values

int connect_chests(struct game_t* g) {
    
    if (g == NULL) {
        null_error(GAME_OBJECT, "connect_chests");
    }
    
    for (int i = 0; i < g->room_len; i++) {
    
        Room* r = g->rooms[i]->room;
        
        
        if (r->chests != NULL) {
        
            Chest_ls* tmp_ptr = r->chests;
            
            
            char* array = r->room_array;
            
            int i = 0, j = 0;
            int end_of_array = 0;
            
            
            while (!end_of_array) {
            
                if (array[i + j*r->width] == CHEST_N) {
                
                    if (tmp_ptr->chest == NULL) {
                        null_error(CHEST_OBJECT, "connect_chests");
                    }
                    
                    else {
                        tmp_ptr->chest->x = i;
                        tmp_ptr->chest->y = j;
                        
                    }
                    
                    if (tmp_ptr->next == NULL) {
                        end_of_array = 1;
                    }
                    else {
                        tmp_ptr = tmp_ptr->next;
                    }
                }
        
                i++;
                if (i == r->width) {
                    i = 0;
                    j++;
                        
                    if (j == r->height) {
                        end_of_array = 1;
                    }
                }
            }
        }
    }
    
    clear_screen();
    printf("Connected chests to rooms.\n");
    
    return 0;
}















int find_chest_error(char* obj) {
    return null_error(obj, "player_find_chest");
}





// find the chest directly in front of the player.

Chest* player_find_chest(struct chest_list_t* chests, int x, int y) {
    
    if (chests == NULL) {
        find_chest_error(CHEST_LS_OBJECT);
        return NULL;
    }
 
    
    Chest* chest_p = NULL;
    
    //printf("player: x: %d, y: %d\n", x, y);
    
    while (chest_p == NULL && chests != NULL) {
    
        Chest* tmp_chest = chests->chest;
        if (tmp_chest != NULL) {
        
            
            if (tmp_chest->x == x && tmp_chest->y == y) {
            
                chest_p = tmp_chest;
            }
        }
        chests = chests->next;
    }
    

    if (chest_p == NULL) {
        printf("Error: unable to find chest to open at %d,%d in room ?.\n", x, y);
        pause_function();
    }

    return chest_p;
}











// given that the player is facing a chest, find the chest to open, and if found try to open it:


int player_open_chest(struct game_t* g) {
    char name[] = "player_open_chest";
    
    if (g == NULL) {
        game_null_error(name);
        return 1;
    }
    struct player_t* p = g->player;
    if (p == NULL) {
        player_null_error(name);
        return 1;
    }
    if (p->room == NULL) {
        room_null_error(name);
        return 1;
    }
    if (p->room->room_array == NULL) {
        null_error(STRING_OBJECT, name);
        return 1;
    }
    
    /*
    if (p->room->chests == NULL) {
        return 0;
    }*/
    
    
    
    // first see whether or not the chest exists at the point in front of the player
    // if so compute the opening analysis.
    
    int x = p->base.x;
    int y = p->base.y;
    
    dir_to_xy(p->base.direction, &x, &y);
    
    if (p->room->room_array[x + y* p->room->width] != CHEST_N) {
        return 0;
    }
    
    
    
    Chest* c = player_find_chest(p->room->chests, x, y);
    
    
    if (c == NULL) {
        return 1;
    }

    if (p->inventory == NULL) {
        null_error(INVENTORY_OBJECT, "player_open_chest");
        return 1;
    }
    
    if (c->item == NULL) {
        printf("The chest is empty...\n");
        pause_function();
        return 0;
    }
    
    if (c->locked) {
        if (p->inventory->key_num > 0) {
            printf("The chest is locked, enter 'y' to open it.\n");
            
            char c_char = getchar();
            
            dynamic_flush(stdin, c_char);
            
            
            if (c_char == 'y' || c_char == 'Y') {
                c->locked = 0;
                p->inventory->key_num --;
            }
            else {
                // dont receive the item
                return 0;
            }
            
        }
        
        else {
            // dont receive the item.
            printf("The chest is locked...\n");
            pause_function();
            return 0;
        }
    }

    
    
    // if here, receive the item.
    int not_emptied = 0;
    not_emptied = give_player_item(g, c->item);
    
    if (!not_emptied) {
        print_dialogue_msg(c->item->base.msg, NULL, g);
        putchar('\n'); putchar('\n');
        //printf("Equip it by opening the menu with 'm'\n");
        
    
        if (c->item->identity < 100) {
            free_item(c->item);
        }
        c->item = NULL;
    }
    else {
        printf("Unable to pick up item.\n");
    }
    
    pause_function();
    return 0;
}




/*

int open_room_chest(struct player_t* p) {

    if (p == NULL) {
        null_error(PLAYER_OBJECT);
        return 1;
    }
    
    if (p->room == NULL) {
        null_error(ROOM_OBJECT);
        return 1;
    }
    
    int x = p->base.x;
    int y = p->base.y;
    
    // only open the first found with x,y pos
    
    dir_to_xy(p->base.direction, &x, &y);

}*/
# endif
