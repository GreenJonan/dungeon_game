# ifndef INITIALISE_INVENTORY_ITEMS
# define INITIALISE_INVENTORY_ITEMS

// std messages

//pointer
char std_pointer_msg[] = "Pointer";

// basic sword
char std_basic_sword_msg[] = "Basic sword";

// staff
char std_staff_msg[] = "Staff";

// magic staff
char std_magic_staff_msg[] = "Magic staff";

// bow
char std_bow_msg[] = "Bow";



// empty bottle
char std_bottle_empty_msg[] = "Empty bottle";

// full dark bottle
char std_bottle_full_dark_msg[] = "full potion";
// half-full dark bottle
char std_bottle_half_full_dark_msg[] = "half-full potion";

// full med bottle
char std_bottle_full_med_msg[] = "full health potion";
// half-full med bottle
char std_bottle_half_full_med_msg[] = "half-full health potion";

// full light bottle
char std_bottle_full_light_msg[] = "full mana potion";
// half-full light bottle
char std_bottle_half_full_light_msg[] = "half full mana potion";


char std_bomb_bag_msg[] = "Bomb bag";

char std_present_msg[] = "Present";

char std_stopwatch_msg[] = "Stopwatch";



char std_basic_shield_msg[] = "Basic shield";

char std_hourglass_msg[] = "Hourglass";

char std_anti_hourglass_msg[] = "Anti-Hourglass";








///////

// temporary function.

int init_item_inv_temp_(struct item_t* item, char* msg, char* default_msg, char* name, int i_id) {

    if (name == NULL) {
        null_error(STRING_OBJECT, "init_item_inv_temp_");
        return 1;
    }
    if (item == NULL) {
        printf("NULL ERROR: initialising %s item object\n", name);
        pause_function();
        return 1;
    }
    
    if (msg == NULL || default_msg == NULL) {
        printf("NULL ERROR: message string for initalising %s item object.\n", name);
        pause_function();
        return 1;
    }
    
    item->identity = i_id;
    
    
    if (str_eq(msg, DEFAULT_MSG)) {

        simple_str_concat(item->base.msg, default_msg, "\nEquip it by opening the menu with 'm'");
                          
        //str_copy(default_msg, item->base.msg);
    }
    else if (!str_eq(msg, NONE_MSG)) {
        str_copy(msg, item->base.msg);
    }
    
    return 0;
}











// inits for inventory items;


int init_pointer(struct item_t* item, char* msg, char* name) {
    
    return init_item_inv_temp_(item, msg, std_pointer_msg, name, POINTER_ID);
    
    /*
    if (item == NULL) {
        item_null_error("init_pointer");
        return 1;
    }
    
    item->identity = POINTER_ID;
    
    if (str_eq(msg, DEFAULT_MSG)) {
        str_copy(std_pointer_msg, item->base.msg);
    }
    else if (!str_eq(msg, NONE_MSG)) {
        str_copy(msg, item->base.msg);
    }
    return 0;*/
}




int init_basic_shield(struct item_t* item, char* msg, char* name) {
    return init_item_inv_temp_(item, msg, std_basic_shield_msg, name, BASIC_SHIELD_ID);
}




int init_basic_sword(struct item_t* item, char* msg, char* name) {
    return init_item_inv_temp_(item, msg, std_basic_sword_msg, name, BASIC_SWORD_ID);
}



int init_staff(struct item_t* item, char* msg, char* name) {
    return init_item_inv_temp_(item, msg, std_staff_msg, name, STAFF_ID);
}



int init_magic_staff(struct item_t* item, char* msg, char* name) {
    return init_item_inv_temp_(item, msg, std_magic_staff_msg, name, MAGIC_STAFF_ID);
}


int init_bow(struct item_t* item, char* msg, char* name) {
    item->base.light_dist = BOW_DIST;
    item->max_num = MAX_QUIVER;
    return init_item_inv_temp_(item, msg, std_bow_msg, name, BOW_ID);
}










int init_bottle_empty(struct item_t* item, char* msg, char* name) {
    return init_item_inv_temp_(item, msg, std_bottle_empty_msg, name, BOTTLE_EMPTY_ID);
}



int init_bottle_full_dark(struct item_t* item, char* msg, char* name) {
    return init_item_inv_temp_(item, msg, std_bottle_full_dark_msg, name, BOTTLE_FULL_DARK_ID);
}



int init_bottle_half_full_dark(struct item_t* item, char* msg, char* name) {
    return init_item_inv_temp_(item, msg, std_bottle_half_full_dark_msg, name, BOTTLE_HALF_FULL_DARK_ID);
}


int init_bottle_full_med(struct item_t* item, char* msg, char* name) {
    return init_item_inv_temp_(item, msg, std_bottle_full_med_msg, name, BOTTLE_FULL_MED_ID);
}



int init_bottle_half_full_med(struct item_t* item, char* msg, char* name) {
    return init_item_inv_temp_(item, msg, std_bottle_half_full_med_msg, name, BOTTLE_HALF_FULL_MED_ID);
}



int init_bottle_full_light(struct item_t* item, char* msg, char* name) {
    return init_item_inv_temp_(item, msg, std_bottle_full_light_msg, name, BOTTLE_FULL_LIGHT_ID);
}




int init_bottle_half_full_light(struct item_t* item, char* msg, char* name) {
    return init_item_inv_temp_(item, msg, std_bottle_half_full_light_msg, name, BOTTLE_HALF_FULL_LIGHT_ID);
}







int init_bomb_bag(struct item_t* item, char* msg, char* name) {
    item->base.light_dist = 1;
    item->base.health = 1;
    item->max_num = MAX_BOMB_BAG;
    return init_item_inv_temp_(item, msg, std_bomb_bag_msg, name, BOMB_BAG_ID);
}


int init_present(struct item_t* item, char* msg, char* name) {
    return init_item_inv_temp_(item, msg, std_present_msg, name, PRESENT_ID);
}


int init_stopwatch(struct item_t* item, char* msg, char* name) {
    return init_item_inv_temp_(item, msg, std_stopwatch_msg, name, STOPWATCH_ID);
}






int init_hourglass(struct item_t* item, char* msg, char* name) {
    return init_item_inv_temp_(item, msg, std_hourglass_msg, name, HOURGLASS_ID);
}


int init_anti_hourglass(struct item_t* item, char* msg, char* name) {
    return init_item_inv_temp_(item, msg, std_anti_hourglass_msg, name, ANTI_HOURGLASS_ID);
}


















///////////////////////////////////////////////////////////////////////////

Item* init_inv_item(char* name, int num, char* msg, int pickup) {

    if (name == NULL || msg == NULL) {
        null_error(STRING_OBJECT, "init_inv_items");
        return NULL;
    }
    
    
    Item* i = NULL;
    
    
    
    if (!str_eq(name, EMPTY)) {
    
    
        i = allocate_item(1);
        i->base.msg[0] = 0;
        i->num = num;
    
        
        // test for string equality

        
        if (str_eq(name, POINTER)) {  init_pointer(i, msg, name);}
        
        else if (str_eq(name, BASIC_SWORD)) {  init_basic_sword(i, msg, name);}
        
        else if (str_eq(name, STAFF)) {  init_staff(i, msg, name);}
        
        else if (str_eq(name, MAGIC_STAFF)) {  init_magic_staff(i, msg, name);}
        
        else if (str_eq(name, BOW)) {  init_bow(i, msg, name);}
        
        
        
        
        else if (str_eq(name, BOTTLE_EMPTY)) {  init_bottle_empty(i, msg, name);}
        else if (str_eq(name, BOTTLE_FULL_DARK)) {  init_bottle_full_dark(i, msg, name);}
        else if (str_eq(name, BOTTLE_HALF_FULL_DARK)) {  init_bottle_half_full_dark(i, msg, name);}
        else if (str_eq(name, BOTTLE_FULL_MED)) {  init_bottle_full_med(i, msg, name);}
        else if (str_eq(name, BOTTLE_HALF_FULL_MED)) {  init_bottle_half_full_med(i, msg, name);}
        else if (str_eq(name, BOTTLE_FULL_LIGHT)) {  init_bottle_full_light(i, msg, name);}
        else if (str_eq(name, BOTTLE_HALF_FULL_LIGHT)) {  init_bottle_half_full_light(i, msg, name);}
        
        else if (str_eq(name, BOMB_BAG)) {  init_bomb_bag(i, msg, name);}
        
        else if (str_eq(name, PRESENT)) {  init_present(i, msg, name);}
        
        else if (str_eq(name, STOPWATCH)) {  init_stopwatch(i, msg, name);}
        
        
        
        else if (str_eq(name, BASIC_SHIELD)) {  init_basic_shield(i, msg, name);}
        
        else if (str_eq(name, HOURGLASS)) {  init_hourglass(i, msg, name);}
        
        else if (str_eq(name, ANTI_HOURGLASS)) {  init_anti_hourglass(i, msg, name);}
        
        
        
        else if (pickup) {
            fix_item_identity(i, name, msg);
        }
        
        
        
        else {
            free_item(i);
            return NULL;
        }
    }
    
    return i;
}






# endif
