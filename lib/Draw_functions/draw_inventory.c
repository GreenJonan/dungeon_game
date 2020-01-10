# ifndef DRAW_MY_ITEMS__
# define DRAW_MY_ITEMS__

# include "draw_items.c"

int draw_active_items(Inventory*, int, int, int);
int draw_passive_items(Inventory*, int, int, int);
int draw_consumable_items(Inventory*, int, int, int);

int draw_inv_items(Item_ls*, int, int, int, int, int);



/////////////////////////////////////////////////////////////////////////////

int draw_inventory(Game* game) {
    
    if (game->player->inventory == NULL) {
        null_error("Inventory", "draw_inventory");
        return 1;
    }
    Inventory* inv = game->player->inventory;
    int cursor = inv->inv_cursor;
    
    // first find the held id values
    
    
    
    printf("\n"
           "  ┌─────────────────────────────────────────────────────────┐\n");
    
    char c = ' ';
    if (cursor <= 0) {
        c = '*';
    }
    printf("  │  %c INVENTORY:                                           │\n", c);
    
    printf("  ├──────────┬──────────────────────────────────────────────┤\n"
           "  │ EQUIPPED │  Select item to equip it.                    │\n"
           "  ├──────────┼──────────────────────────────────────────────┤\n"
           );
    
    
    // ACTIVE ITEMS:
    if ((cursor / 100) == 1) { //cursor == 1
        draw_active_items(game->player->inventory, inv->inv_item_pos[0], inv->inv_item_cursors[0], 1);
    }
    else {
        draw_active_items(game->player->inventory, inv->inv_item_pos[0], inv->inv_item_cursors[0], 0);
    }
    
    printf("  ├──────────┼──────────────────────────────────────────────┤\n");
    
    
    
    // CONSUMABLE ITEMS:
    if (cursor / 100 == 2) {
        draw_consumable_items(game->player->inventory, inv->inv_item_pos[1], inv->inv_item_cursors[1], 1);
    }
    else {
        draw_consumable_items(game->player->inventory, inv->inv_item_pos[1], inv->inv_item_cursors[1], 0);
    }
    
    printf("  ├──────────┼──────────────────────────────────────────────┤\n");
    
    
    // PASSIVE ITEMS:
    if (cursor / 100 == 3) {
        draw_passive_items(game->player->inventory, inv->inv_item_pos[2], inv->inv_item_cursors[2], 1);
    }
    else {
        draw_passive_items(game->player->inventory, inv->inv_item_pos[2], inv->inv_item_cursors[2], 0);
    }
    
    printf("  ├──────────┴──────────────────────────────────────────────┤\n");
    
    
    ///////////////////////////
    
    // now for the bottom portion of the menu:
    
    int style1 = 1;
    int style2 = 1;
    int style3 = 1;
    
    
    if (cursor / 100 == 4) {
        int depth = cursor % 100;
        
        if (depth == 0) {
            style1 = 2;
        }
        else if (depth == 1) {
            style2 = 2;
        }
        else {
            style3 = 2;
        }
    }
    
    
    
    
    print_box_left(1, 2); print_box_top(style1, 8, 2, 0); print_box_top(style2, 16, 3, 0);
    print_box_top(style3, 11, 3, 0); print_box_right(1, 14, 1);
        
    print_box_left(1, 2); print_box_internal(style1, 8, 2, "BACK", 4, 0);
    print_box_internal(style2, 16, 3, "PLAYER STATUS", 13, 0);
    print_box_internal(style3, 11, 3, "OPTIONS", 7, 0); print_box_right(1, 14, 1);
    
    print_box_left(1, 2); print_box_bot(style1, 8, 2, 0); print_box_bot(style2, 16, 3, 0);
    print_box_bot(style3, 11, 3, 0); print_box_right(1, 14, 1);
    
    
    printf("  └─────────────────────────────────────────────────────────┘\n");
    
    if (game->options.command_debug) {
        printf("Inventory cursor:  %d\n", inv->inv_cursor);
        printf("Active cursor:     %d, Position: %d, ID: %d\n", inv->inv_item_cursors[0],
               inv->inv_item_pos[0], inv->active->item->identity);
        printf("Consumable cursor: %d, Position: %d, ID: %d\n", inv->inv_item_cursors[1],
               inv->inv_item_pos[1], inv->consumable->item->identity);
        printf("Passive cursor:    %d, Position: %d, ID: %d\n", inv->inv_item_cursors[2],
               inv->inv_item_pos[2], inv->passive->item->identity);
    }
    return 0;
}










///////////////////////////////////////////////////////////////////////////////



// cursor refers to whether the row is currently being selected or not, i.e. a boolean value.

int draw_active_items(Inventory* inv, int cursor_pos, int item_cursor, int is_cursor) {

    printf("  │  Active  │                                              │\n");
    
    int active_held = EMPTY_ID;
    if (inv->eq_active_item != NULL) {
        active_held = inv->eq_active_item->identity;
    }
    
    draw_inv_items(inv->active, inv->active_len, active_held, cursor_pos, item_cursor, is_cursor);

    return 0;
}



int draw_passive_items(Inventory* inv, int cursor_pos, int item_cursor, int is_cursor) {

    printf("  │  Passive │                                              │\n");
    
    int passive_held = EMPTY_ID;
    if (inv->eq_passive_item != NULL) {
        passive_held = inv->eq_passive_item->identity;
    }
    
    draw_inv_items(inv->passive, inv->passive_len, passive_held, cursor_pos, item_cursor, is_cursor);
    return 0;
}



int draw_consumable_items(Inventory* inv, int cursor_pos, int item_cursor, int is_cursor) {

    printf("  │Consumable│                                              │\n");
    
    int consumable_held = EMPTY_ID;
    if (inv->eq_consumable_item != NULL) {
        consumable_held = inv->eq_consumable_item->identity;
    }
    
    draw_inv_items(inv->consumable, inv->consumable_len, consumable_held, cursor_pos, item_cursor, is_cursor);
    return 0;
}








////////////////////////////////////////////////////////////////////////////////

// assume cursor points to the n-th item in the item list, and corresponds to the item currently being
// selected.
// When there are 5 or less items, display them all left to right, from first item

// when there are more than five items, if you can see the left most item display it at the left, with no spare
//  items

// only scroll across the item list when reach one of the end arrow places.

// for simplicity: the cursor can only take the values 0,1,2,3,4

                          
                          
                          
                          
                          
int draw_inv_items(Item_ls* items, int item_len, int eq_id, int cursor_pos, int cursor, int is_cursor) {

    if (cursor >= 5) {
        printf("ERROR: cursor value for 'draw_inv_items' can only be 0,1,2,3,4, not: %d\n", cursor);
        pause_function();
        return 1;
    }

   
    // in all cases, need to print 5 empty boxes / arrows:
        
    int item_ids[] = {EMPTY_ID, EMPTY_ID, EMPTY_ID, EMPTY_ID, EMPTY_ID};
        
    int cursors[] = {0, 0, 0, 0, 0};
    int indents[] = {2, 3, 3, 3, 3};
    if (is_cursor) {
        cursors[cursor] = 1;
    }
        
        
        
        
        
        
    if (items != NULL && item_len >= 1) {
        
        // this implies that there are items in the player's inventory,
        // and there may be less or more than five.
    
        // the item in question will be inventory cursor position
        Item_ls* item_ptr = items;
        
        
        /*
        if (item_ptr->prev != NULL) {
            
            if (item_ptr->prev->item == NULL) {
                printf("ERRO: previous pointer for inventory item list is not null.\n");
                return 1;
            }
            else {
                printf("ERROR: previous item pointer should be null, but has id: %d\n",
                       item_ptr->prev->item->identity);
                return 1;
            }
        }
        int count;
        for (count = 0; count < cursor_pos; count++) {
            item_ptr = item_ptr->next;
            
            if (item_ptr == NULL) {
                printf("Cursor value: %d, exceeds inventory list length: %d\n",cursor_pos, count);
                null_error(ITEM_LS_OBJECT, "draw_inv_items");
                return 1;
            }
        }
        */
        
            
        int left_arrow = 0;
        int right_arrow = 0;
        Item_ls* first = item_ptr;
        Item_ls* last = item_ptr;
            
            
        // find the first, and last item given the cursor and item_len:
            
        // first
        for (int j = cursor; j > 0; j--) {
            first = first->prev;
            
            if (first == NULL) {
                printf("Left side: too few items for list length: %d\n, null at index: %d, cursor: %d.\n",
                       item_len, j, cursor);
                null_error(ITEM_LS_OBJECT, "draw_inv_items");
                return 1;
            } // dont need.
        }
        
        if (first->prev != NULL) {
            left_arrow = 1;
            first = first->next;
        }
        
        // last
        for (int j = cursor; j < 4 && j < item_len; j++) {
            last = last->next;
            if (last == NULL) {
                printf("Right side: too few items for list length: %d, null at index: %d, cursor: %d.\n",
                       item_len, j, cursor);
                null_error(ITEM_LS_OBJECT, "draw_inv_items");
                return 1;
            }
        }
        if (last->next != NULL) {
            right_arrow = 1;
            last = last->prev;
        }
    
        
        // change ite, ids if left/right arrow.
        if (left_arrow) {item_ids[0] = LEFT_ARROW_ID;}
        if (right_arrow) {item_ids[4] = RIGHT_ARROW_ID;}
            
            
        Item_ls* tmp_item = first;
        int len = 5;
        if (item_len < len) {
            len = item_len;
        }
        for (int i = left_arrow; i < len - right_arrow; i++) {
            item_ids[i] = tmp_item->item->identity;
            tmp_item = tmp_item->next;
        }
    
        
        
    }
        
        
        //////////////////
        
        // print the lines
        
        for (int line = 0; line < 5; line++) {
        
            print_box_left(1, 2); print_item_box(eq_id, line, 2, 0); print_box_left(1, 2);
            
            for (int i = 0; i < 5; i++) {
                print_item_box(item_ids[i], line, indents[i], cursors[i]);
            }
            
            print_box_right(1, 2, 1);
        }
    
    return 0;
}




/*
 int styles[] = {4, 4, 4, 4, 4};
 int ind[] = {2, 3, 3, 3, 3};
 if (cursor) {
 styles[ (cursor - 1) % 5] = 2;
 }
 
 print_box_left(1, 2); print_box_top(4, 6, 2, 0); print_box_left(1, 2);
 for (int i = 0; i < 5; i++) {
 print_box_top(styles[i], 6, ind[i], 0);
 }
 print_box_right(1, 2, 1);
 
 
 for (int i = 0; i < 3; i++) {
 
 print_box_left(1, 2); print_box_empty(4, 6, 2, 0); print_box_left(1, 2);
 for (int i = 0; i < 5; i++) {
 print_box_empty(styles[i], 6, ind[i], 0);
 }
 print_box_right(1, 2, 1);
 }
 
 
 print_box_left(1, 2); print_box_bot(4, 6, 2, 0); print_box_left(1, 2);
 for (int i = 0; i < 5; i++) {
 print_box_bot(styles[i], 6, ind[i], 0);
 }
 print_box_right(1, 2, 1);
 */








////////////////////////////////////////////////////////////////////////////////

int draw_player_status_screen(struct game_t* game) {

    clear_screen();
    printf("NOT YET IMPLEMENTED\n");
    pause_function();
    return 0;
}






















////////////////////////////////////////////////////////////////////////////////

// this is a copy paste from the start menu screen.



void draw_menu_options_screen(int button) {

    clear_screen();
    
    if (button > 3 || button < 1) {
        printf("ERROR: botton value out of range: %d\n", button);
        pause_function();
        return;
    }
    
    
    char* strings[] = {"GAME OPTIONS:", "BACK", "SAVE GAME", EXIT_GAME_MSG};
    int lengths[] = {13, 4, 9, EXIT_GAME_MSG_LEN};
    int len = 4;
    
    draw_menu_box(strings, lengths, len, button, 2, BOT_W, SM_W);
}


# endif
