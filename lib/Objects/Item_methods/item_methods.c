# ifndef SOME_ITEM_METHODS
# define SOME_ITEM_METHODS





// getters and setters

int get_item_price(struct item_t* i) {
    
    if (i == NULL) {
        item_null_error("get_item_price");
        return 1;
    }
    
    return i->max_num; // here using max_num as price since max_num is only applicable for non-merchants
}


int set_item_price(struct item_t* i, int price) {

    if (i == NULL) {
        item_null_error("set_item_price");
        return 1;
    }
    
    i->max_num = price;
    return 0;
}









void print_item_name(int i_id) {

    if (i_id == NONE_ID) {  printf("NONE"); }
    
    
    if (i_id < 100) {
        if (i_id == HEART_ID) {  printf("Heart"); }
    
        else if (i_id == COIN_ID) {  printf("Coin"); }
    
        else if (i_id == KEY_ID) {  printf("Key"); }
    
        else if (i_id == BOMB_ID) {  printf("Bomb"); }
    
        else if (i_id == ARROW_ID) {  printf("Arrow"); }
    
        else if (i_id == MANA_ID) {  printf("Mana"); }
    
        else if (i_id == HEALTH_CONTAINER_ID) {  printf("Health Container"); }
    
        else if (i_id == MANA_CONTAINER_ID) {  printf("Mana Container"); }
        
        
        else {  printf("???"); }
    }
    
    
    
    
    
    else if (i_id < 200) {
        if (i_id == POINTER_ID) {  printf("Pointer"); }
        
        else if (i_id == BASIC_SWORD_ID) {  printf("Sword"); }
        
        else if (i_id == STAFF_ID) {  printf("Staff"); }
        
        else if (i_id == MAGIC_STAFF_ID) {  printf("Magic Staff"); }
        
        else if (i_id == BOW_ID) { printf("Bow"); }
        
        else { printf("???");}
    }
    
    
    
    
    
    else if (i_id < 300) {
        if (i_id == BOTTLE_EMPTY_ID) {  printf("Empty Bottle"); }
        
        else if (i_id == BOTTLE_FULL_DARK_ID) {  printf("Full Potion"); }
        
        else if (i_id == BOTTLE_HALF_FULL_DARK_ID) {  printf("Potion"); }
        
        else if (i_id == BOTTLE_FULL_MED_ID) {  printf("Full Health Potion"); }
        
        else if (i_id == BOTTLE_HALF_FULL_MED_ID) {  printf("Health Potion"); }
        
        else if (i_id == BOTTLE_FULL_LIGHT_ID) {  printf("Full Mana Potion"); }
        
        else if (i_id == BOTTLE_HALF_FULL_LIGHT_ID) {  printf("Mana Potion"); }
        
        
        
        else if (i_id == BOMB_BAG_ID) {  printf("Bomb Bag"); }
        
        else if (i_id == STOPWATCH_ID) {  printf("Stopwatch"); }
        
        else if (i_id == PRESENT_ID) {  printf("Present"); }
        
        else { printf("???");}
    }
    
    
    
    
    
    else if (i_id < 400) {
        if (i_id == BASIC_SHIELD_ID) {  printf("Shield"); }
        
        else if (i_id == HOURGLASS_ID) { printf("Hourglass");}
        
        else if (i_id == ANTI_HOURGLASS_ID) { printf("Anti-Hourglass"); }
        
        else { printf("???"); }
    }



        
    else {  printf("???"); }
}

# endif
