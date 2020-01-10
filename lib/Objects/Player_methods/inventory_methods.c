# ifndef INVENTORY_METHODOLOGIES__
# define INVENTORY_METHODOLOGIES__

int inv_null_error(char* function) {
    return null_error("Inventory", function);
}

int receive_basic_item(struct game_t*, struct item_t*);


////////////////////////////////////////////////////////

int move_cursor_up(struct game_t* game) {

    Inventory* inv = game->player->inventory;
    int level = inv->inv_cursor / 100;
    
    if (level > 0) {
        inv->inv_cursor = 100* (level -1);
        
        if (level > 1 && level <= 4) {
            inv->inv_cursor += inv->inv_item_pos[level - 2];
        }
    }
    return 0;
}









int move_cursor_down(struct game_t* game) {
    
    Inventory* inv = game->player->inventory;
    int level = inv->inv_cursor / 100;
    
    if (level < 4) {
        // 4 is the button options, 3 item types + extra buttons.
        inv->inv_cursor = 100 * (level + 1);
        
        if (level >= 0 && level < 3) {
            inv->inv_cursor += inv->inv_item_pos[level];
        }
    }
    return 0;
}








int move_cursor_left(struct game_t* game) {
    Inventory* inv = game->player->inventory;
    

    if (inv == NULL) {
        inv_null_error("move_cursor_left");
        return 1;
    }
    int level = inv->inv_cursor / 100;
    int depth = inv->inv_cursor % 100;
    
    if (depth > 0) {
        inv->inv_cursor = inv->inv_cursor - 1;
        
        if (level != 0 && level <= 3) {
            if (inv->inv_item_cursors[(level) - 1] > 0) {
                Item_ls* item_list;
                
                if (level == 1) { item_list = inv->active;}
                else if (level == 2) {item_list = inv->consumable;}
                else {item_list = inv->passive;}
                
                if (item_list != NULL) {
                
                    int cursor_pos = inv->inv_item_cursors[(level) - 1];
                    int minus = 0;
                
                    if (cursor_pos <= 1) {
                        if (item_list->prev == NULL) {
                            null_error(ITEM_LS_OBJECT, "move_cursor_left");
                            return 1;
                        }
                        if (item_list->prev->prev == NULL) {
                            minus = 1;
                        }
                    }
                
                    else { minus = 1;  }
                
                    if (minus) {
                        inv->inv_item_cursors[(level) - 1] --;
                    }
                }
            }
            
            
            
            inv->inv_item_pos[level - 1] --;
            // NOTE: need to implement movement of item_ls* pointer.
            
            
            if (level == 1) {
                if (inv->active != NULL) {
                    if (inv->active->prev != NULL) {
                        inv->active = inv->active->prev;
                    }
                    else {
                        printf("here 1\n");
                        pause_function();
                    }
                }
                else {
                    printf("here 2\n");
                    pause_function();
                }
            }
            
            else if (level == 2) {
                if (inv->consumable != NULL) {
                    if (inv->consumable->prev != NULL) {
                        inv->consumable = inv->consumable->prev;
                    }
                }
                
            }
            
            else if (level == 3) {
                if (inv->passive != NULL) {
                    if (inv->passive->prev != NULL) {
                        inv->passive = inv->passive->prev;
                    }
                }
            }
        }
    }
    
    return 0;
}










int move_cursor_right(struct game_t* game) {
    Inventory* inv = game->player->inventory;
    
    
    if (inv == NULL) {
        inv_null_error("move_cursor_right");
        return 1;
    }
    
    
    int level = inv->inv_cursor / 100;
    int depth = inv->inv_cursor % 100;
    
    if (level != 0) {
        if (level > 3) {
            if (depth < 2) {
                inv->inv_cursor ++;
            }
        }
        
        else {
            // this implies we are in one of the three item selection rows:
            // Active, Consumable, Passive
            
            int len = 0;
            if (level == 1) {len = inv->active_len;}
            else if (level == 2) {len = inv->consumable_len;}
            else {len = inv->passive_len;}
            
            if (depth < len) {
                inv->inv_cursor++;
                if (inv->inv_item_cursors[level - 1] < 4) {
                    
                    Item_ls* item_list;
                    
                    if (level == 1) { item_list = inv->active;}
                    else if (level == 2) {item_list = inv->consumable;}
                    else {item_list = inv->passive;}
                    
                    if (item_list != NULL) {
                        
                        int cursor_pos = inv->inv_item_cursors[(level) - 1];
                        int plus = 0;
                        
                        if (cursor_pos >= 3) {
                            if (item_list->next == NULL) {
                                null_error(ITEM_LS_OBJECT, "move_cursor_left");
                                return 1;
                            }
                            if (item_list->next->next == NULL) {
                                plus = 1;
                            }
                        }
                        
                        else { plus = 1;  }
                        
                        if (plus) {
                            inv->inv_item_cursors[(level) - 1] ++;
                        }
                    }
                }
                
                
                inv->inv_item_pos[level - 1] ++;
                // when depth == len ==> cursor is on NONE item.
                
                // NOTE: need to implement movement of item_ls* pointer.
                if (level == 1) {
                    if (inv->active != NULL) {
                        if (inv->active->next != NULL) {
                            inv->active = inv->active->next;
                        }
                    }
                }
                
                else if (level == 2) {
                    if (inv->consumable != NULL) {
                        if (inv->consumable->next != NULL) {
                            inv->consumable = inv->consumable->next;
                        }
                    }
                
                }
                
                else if (level == 3) {
                    if (inv->passive != NULL) {
                        if (inv->passive->next != NULL) {
                            inv->passive = inv->passive->next;
                        }
                    }
                }
            }
        }
    
    }
    return 0;
}









int select_cursor(struct game_t* game) {
    Inventory* inv = game->player->inventory;
    
    if (inv == NULL) {
        inv_null_error("move_cursor_down");
        return -1;
    }
    
    
    int level = inv->inv_cursor / 100;
    int depth = inv->inv_cursor % 100;
    
    if (level != 0) {
        if (level > 3) {
            
            if (depth == 0) {
                exit_inventory(game);
                draw_screen(game);
                return player_turn(game);
            }
            
            else if (depth == 1) {
                char c = 0;
                draw_player_status_screen(game);
                while (c != '\n') {
                    c = getchar();
                }
                draw_screen(game);
            }
            
            else {
                // enter options menu:
                
                int cursor = 1;
                int exit = 0;
                
                while (!exit) {
                    draw_menu_options_screen(cursor);
                    char c = receive_input_command(game);
                    
                    if (c == MOVE_DOWN_C) {
                        if (cursor < 3) {
                            cursor++;
                        }
                    }
                    else if (c == MOVE_UP_C) {
                        if (cursor > 1) {
                            cursor --;
                        }
                    }
                    else if (c == MENU_C) {
                        exit = 1;
                        cursor = 1;
                    }
                    else if (c == WAIT_C || c == REST_C) {
                        if (cursor == 1 || cursor == 3) {
                            exit = 1;
                        }
                    }
                }
                
                if (cursor == 3) {
                    return EXIT_C;
                }
                else {
                    draw_screen(game);
                }
                
            }
        }
        
        
        
        // heavy duty: item selection:
        else {
            
            if (level == 1) {
                if (inv->active != NULL) {
                    
                    if (inv->active->item == NULL && inv->eq_active_item != NULL) {
                        inv->active->item = inv->eq_active_item;
                        printf("ERROR: active list pointer now points to NULL");
                        pause_function();
                        return -1;
                    }
                
                
                    else {
                        if (depth >= inv->active_len) {
                            inv->prev_active = inv->eq_active_item;
                            inv->eq_active_item = NULL;
                        }
                        else {
                            if (inv->eq_active_item == NULL) {
                                inv->prev_active = NULL;
                            }
                            else if (inv->active->item != NULL) {
                                if (inv->active->item->identity != inv->eq_active_item->identity) {
                                    inv->prev_active = inv->eq_active_item;
                                }
                            }
                            
                            inv->eq_active_item = inv->active->item;
                        }
                    }
                }
            }
            
            
            else if (level == 2) {
                if (inv->consumable != NULL) {
                    
                    if (inv->consumable->item == NULL && inv->eq_consumable_item != NULL) {
                        inv->consumable->item = inv->eq_consumable_item;
                        printf("ERROR: consumable list pointer now points to NULL");
                        pause_function();
                        return -1;
                    }
                
                
                    else {
                        if (depth >= inv->consumable_len) {
                            inv->prev_consumable = inv->eq_consumable_item;
                            inv->eq_consumable_item = NULL;
                        }
                        else {
                            if (inv->eq_consumable_item == NULL) {
                                inv->prev_consumable = NULL;
                            }
                            else if (inv->consumable->item != NULL) {
                                if (inv->consumable->item->identity != inv->eq_consumable_item->identity) {
                                    inv->prev_consumable = inv->eq_consumable_item;
                                }
                            }
                            
                            inv->eq_consumable_item = inv->consumable->item;
                        }
                    }
                }
            }
            
            
            else if (level == 3) {
                if (inv->passive != NULL) {
                    if (inv->passive->item == NULL && inv->eq_passive_item != NULL) {
                        inv->passive->item = inv->eq_passive_item;
                        printf("ERROR: passive list pointer now points to NULL");
                        pause_function();
                        return -1;
                    }
                
                
                    else {
                        if (depth >= inv->passive_len) {
                            inv->prev_passive = inv->eq_passive_item;
                            inv->eq_passive_item = NULL;
                        }
                        else {
                            if (inv->eq_passive_item == NULL) {
                                inv->prev_passive = NULL;
                            }
                            else if (inv->passive->item != NULL) {
                                if (inv->passive->item->identity != inv->eq_passive_item->identity) {
                                    inv->prev_passive = inv->eq_passive_item;
                                }
                            }
                            
                            inv->eq_passive_item = inv->passive->item;
                        }
                    }
                }
            }
        }
    }
    
    return 0;
}














//////////////////////////////////////////////////////////////////////////////////////



int give_player_item(Game* g, Item* i) {

    char* give_item = "give_player_item";
    
    if (g == NULL) {
        game_null_error(give_item);
        return 1;
    }
    struct player_t* p = g->player;
    
    if (i == NULL) {
        item_null_error(give_item);
        return 1;
    }
    if (p == NULL) {
        player_null_error(give_item);
        return 1;
    }
    if (p->inventory == NULL) {
        inv_null_error(give_item);
    }
    
    int i_id = i->identity;
    /*
    if (i_id < 100 || i_id >= 400) {
        printf("ERROR: item id %d is too great to belong in player inventory.\n");
        return 1;
    }*/ // yes but it would be more interesting to be able to glitch out and receive hearts for example.
    
    // if i_id < 100 ==> that it is not an inventory item, but a receivable item.
    
    if (i_id < 100) {
        return receive_basic_item(g, i);
    }
    
    
    /*
    if (has_item(p->inventory, i->identity)) {
        printf("Warning: already has item id %d\n", i->identity);
        return 1;
    }*/ // commenting out so can pick up the same item multiple times.
    
    
    Item_ls* insert;
    
    if (i_id < 200) {
        insert = p->inventory->active;
    }
    else if (i_id >= 300) {
        insert = p->inventory->passive;
    }
    else {
        insert = p->inventory->consumable;
    }

    
    
    if (insert == NULL) {
        printf("ERROR: Item list for item id: %d, is empty, inserting NONE item.\n", i_id);
        pause_function();
        if (i_id < 200) {
            p->inventory->active = init_none_list();
            insert = p->inventory->active;
        }
        else if (i_id >= 300) {
            p->inventory->passive = init_none_list();
            insert = p->inventory->passive;
        }
        else {
            p->inventory->consumable = init_none_list();
            insert = p->inventory->consumable;
        }
    }
    
    
    
    if (insert->item == NULL) {
        printf("Item in inventory list is NULL.\n");
        item_null_error(give_item);
        return 1;
    }
    
    i_id = insert->item->identity;
    int not_null = 1;
    
    while (i_id != NONE_ID && not_null) {
    
        if (insert->next == NULL) {
            not_null = 0;
        }
        
        else {
            insert = insert->next;
            
            if (insert->item == NULL) {
                printf("Item in inventory list is NULL.\n");
                item_null_error(give_item);
                return 1;
            }
            
            else {
                i_id = insert->item->identity;
            }
        }
    }
    if (!not_null) {
        printf("ERROR: last item in item list is not NONE.\n");
        pause_function();
        return 1;
    }
    
    // now, the insert pointer, points to the NONE item, insert the new item in the place right before the
    // none item.
    int prev_is_null = (insert->prev == NULL);
    
    Item_ls* tmp_node = (Item_ls*) malloc(sizeof(Item_ls));
    tmp_node->prev = insert->prev;
    tmp_node->next = insert;
    
    tmp_node->item = i;
    
    
    if (prev_is_null) {
        insert->prev = tmp_node;
    }
    
    else {
        insert->prev->next = tmp_node;
        insert->prev = tmp_node;
    }
    
    
    // add +1 to item counters, and move cursor to first position.
    // recall, have overwritten i_id, hence overwrite it again.
    i_id = i->identity;
    
    if (i_id < 200) {
        p->inventory->active_len++;
        while(p->inventory->active->prev != NULL) {
            p->inventory->active = p->inventory->active->prev;
        }
    }
    else if (i_id >= 300) {
        p->inventory->passive_len++;
        while(p->inventory->passive->prev != NULL) {
            p->inventory->passive = p->inventory->passive->prev;
        }
    }
    else {
        p->inventory->consumable_len++;
        while(p->inventory->consumable->prev != NULL) {
            p->inventory->consumable = p->inventory->consumable->prev;
        }
    }

    return 0;
}








int give_player_new_item(struct game_t* g, int i_id) {

    Item* i = (Item*) malloc(sizeof(Item));
    i->identity = i_id;
    i->num = 0;
    i->max_num = 0;
    i->equipped = 0;
    
    int not_given = give_player_item(g, i);
    if (!not_given) {
        if (i_id < 100) {
            free_item(i);
        }
    }
    return not_given;
}









/////////////////////////////////////////////////////////////////

int exit_inventory(struct game_t* game) {

    game->inventory = 0;
    game->player->inventory->inv_cursor = 400;
    for (int i = 0; i < 3; i++) {
        game->player->inventory->inv_item_cursors[i] = 0;
        game->player->inventory->inv_item_pos[i] = 0;
    }

    // move active to 1st
    Inventory* inv = game->player->inventory;
    if (inv->active != NULL) {
        while (inv->active->prev != NULL) {
            inv->active = inv->active->prev;
        }
    }
    if (inv->consumable != NULL) {
        while (inv->consumable->prev != NULL) {
            inv->consumable = inv->consumable->prev;
        }
    }
    if (inv->passive != NULL) {
        while (inv->passive->prev != NULL) {
            inv->passive = inv->passive->prev;
        }
    }

    return 0;
}





int has_item(Inventory* inv, int i_id) {
    
    if (inv == NULL) {
        inv_null_error("has_item");
        return 0;
    }
    
    Item_ls* items = NULL;
    if (i_id >= 100) {
        if (i_id < 200) {
            items = inv->active;
        }
        else if (i_id < 300) {
            items = inv->consumable;
        }
        else if (i_id < 400) {
            items = inv->passive;
        }
    }
    
    if (items == NULL) {
        printf("Possible invalid item id: %d\n", i_id);
        null_error(ITEM_LS_OBJECT, "has_item");
        return 0;
    }
    
    // wind back to find item
    
    while (items->prev != NULL) {
        items = items->prev;
    }
    

    while (items != NULL) {
        
        if (items->item == NULL) {
            item_null_error("has_item");
        }
        
        else {
            if (items->item->identity == i_id) {
                return 1;
            }
        }
        
        items = items->next;
    }
    
    
    return 0;
}










/////////////////////////////////////////////////////////////////////

// item id's less than 100 count as a basic item. This function assumes that the item will be freed after it is
// given to the player.

int receive_basic_item(struct game_t* g, struct item_t* i) {

    int not_success = pickup_item(g, i);
    if (not_success < 0) {
        not_success = 1;
    }
    
    return not_success;
    
    
    /*
    int i_id = i->identity;
    
    if (i_id == HEART_ID) {
        
        pickup_item(p, i);
    }
    
    else if (i_id == COIN_ID) {
    
        pickup_coin(p, i);
    }
    
    else if (i_id == BOMB_ID) {
    
        // something
        
        if (!has_item(p->inventory, BOMB_BAG_ID)) {
            return 1;
        }
        pickup_bomb(p, i);
    }
    
    else if (i_id == MANA_ID) {
    
        pickup_mana(p, i);
    }
    
    else if (i_id == ARROW_ID) {
    
        if (!has_item(p->inventory, BOW_ID) {
            return 1;
        }
        pickup_arrow(p, i);
    }
    
    else if (i_id == KEY_ID) {
        
        pickup_key(p, i);
    }


    return 0; */
}
# endif
