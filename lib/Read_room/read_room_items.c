# ifndef READ_ROOM_ITEMS_
# define READ_ROOM_ITEMS_

int read_items(Room*, FILE*);
//int fix_item_identity(struct item_t*, char*, char*);

int read_room_items(Room* empty_room, char* item) {
    
    return read_room(empty_room, item, "read_room_items", 1);
}



int read_items(Room* empty_room, FILE* f) {

    //assume the pointers are not NULL
    
    
    int end_of_file = 0;
    Item_ls* prev_ls_ptr = NULL;
    char c = fgetc(f);
    
    
    while (!end_of_file) {
        
        
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
        
            char msg[BUFF];
            char str[BUFF];
            int x_, y_, v_x, v_y, n;
            
            fscanf(f, "%s %d,%d %d,%d %d", str, &x_, &y_, &v_x, &v_y, &n);
            read_str(f, msg, BUFF);
            
            
            // using more general function for inventory items as well so can pickup inventory items from
            // the floor, not just chests.
            // used to be the code commented out below.
            
            Item* item_ = init_inv_item(str, n, msg, 1);
            
            prev_ls_ptr = push_item_start(prev_ls_ptr, item_);
            
            
            item_->base.x = x_;
            item_->base.y = y_;
            item_->base.vel_x = v_x;
            item_->base.vel_y = v_y;
            item_->num = n;
            
            
            c = flush_file_input(f);
            if (feof(f)) {
                end_of_file = 1;
            }
        }
    }
    empty_room->items = prev_ls_ptr;
    
    return end_of_file;
}


/*
 Item* item_ = allocate_item(1);
 prev_ls_ptr = push_item_start(prev_ls_ptr, item_);
 
 
 item_->base.x = x_;
 item_->base.y = y_;
 item_->base.vel_x = v_x;
 item_->base.vel_y = v_y;
 item_->num = n;
 //item_->base.msg = NULL; // 'not assignable'
 item_->base.msg[0] = 0;
 
 //fix_item_identity(item_, str, msg);
 */









// given a string for an item, find the corresponding Identity
/*
 Currently implemented items:
 
    0  ==>  None
    1  ==>  Heart
    2  ==>  Coin
    3  ==>  Key
    4  ==>  Bomb
    5  ==>  Arrow
    6  ==>  Mana
 */



int fix_item_identity(Item* item, char* str, char* msg) {
    
    char* func = "fix_item_identity";
    if (str == NULL) {
        null_error(STRING_OBJECT, func);
        return 1;
    }
    if (item == NULL) {
        item_null_error(func);
        return 1;
    }

    //int n = item->num;
    
    
    if (str_eq(str, HEART)) {
        init_heart(item, msg);
    }
    
    else if (str_eq(str, COIN)) {
        init_coin(item, msg);
    }
    
    else if (str_eq(str, KEY)) {
        init_key(item, msg);
    }
    
    else if (str_eq(str, BOMB)) {
        init_bomb(item, msg);
    }
    
    else if (str_eq(str, ARROW)) {
        init_arrow(item, msg);
    }
    
    else if (str_eq(str, MANA)) {
        init_mana(item, msg);
    }
    
    else if (str_eq(str, HEALTH_CONTAINER)) {
        init_health_container(item, msg);
    }
    
    else if (str_eq(str, MANA_CONTAINER)) {
        init_mana_container(item, msg);
    }
    
    else if (str_eq(str, FREEZE)) {
        init_freeze(item, msg);
    }
    
    
    
    else {
        if (!SUPPRESS_WARNINGS) {
            printf("Warning, unknown item type '%s'.\n", str);
            pause_function();
        }
        
        item->identity = NONE_ID;
        
        item->base.mass = -1;
        
        item->base.health = -1;
        item->base.max_health = -1;
        item->base.status = (char) 0;
        item->base.clock = -1;
        item->base.timer = 0;
        
        return 1;
    }
    return 0;
}




# endif
