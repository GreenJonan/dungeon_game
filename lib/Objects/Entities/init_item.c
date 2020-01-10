# ifndef INIT_ITEMS__
# define INIT_ITEMS__

// define standard messages for items

//heart
char* std_heart_msg = "It's a heart, pick it up to regain health.\n";

// coin
char* std_coin_msg = "It's a coin, use it to buy items at shops.\n(NOT IMPLEMENTED)\n";

// key
char* std_key_msg = "It's a key, use it to unlock locked doors.\n";

// bomb
char* std_bomb_msg = "It's a bomb, use it to damage enemies or reveal secrets.\n";

// arrpw
char* std_arrow_msg = "It's an arrow, use it with a bow to fire at enemies.\n";

// mana
char* std_mana_msg = "It's an energy elixer, pick it to replenish mana.\n";




//
int init_base_item(struct item_t* i, char* msg, int i_id, char* name, char* default_msg){

    if (i == NULL) {
        item_null_error(name);
        return 1;
    }
    
    i->identity = i_id;
    
    i->base.mass = -1;
    i->base.health = -1;
    i->base.max_health = -1;
    
    i->base.status = (char) 0;
    i->base.clock = -1;
    i->base.timer = 0;
    
    
    if (str_eq(msg, DEFAULT_MSG)) {
        str_copy(default_msg, i->base.msg);
    }
    else if (!str_eq(msg, NONE_MSG)) {
        str_copy(msg, i->base.msg);
    }
    return 0;
}








int init_heart(struct item_t* item, char* msg) {
    return init_base_item(item, msg, HEART_ID, "init_heart", std_heart_msg);
}



int init_coin(struct item_t* item, char* msg) {
    return init_base_item(item, msg, COIN_ID, "init_coin", std_coin_msg);
}



int init_key(struct item_t* item, char* msg) {
    return init_base_item(item, msg, KEY_ID, "init_key", std_key_msg);
}



int init_bomb(struct item_t* item, char* msg) {
    return init_base_item(item, msg, BOMB_ID, "init_bomb", std_bomb_msg);
}



int init_arrow(struct item_t* item, char* msg) {
    return init_base_item(item, msg, ARROW_ID, "init_arrow", std_arrow_msg);
}



int init_mana(struct item_t* item, char* msg) {
    return init_base_item(item, msg, MANA_ID, "init_mana", std_mana_msg);
}


int init_health_container(struct item_t* item, char* msg) {
    char std_health_container_msg[] = "It's a health container, pick it up to increase maximum health.\n";
    return init_base_item(item, msg, HEALTH_CONTAINER_ID, "init_health_container", std_health_container_msg);
}

int init_mana_container(struct item_t* item, char* msg) {
    char std_mana_container_msg[] = "It's a mana container, pick it up to increase maximum mana.\n";
    return init_base_item(item, msg, MANA_CONTAINER_ID, "init_mana_container", std_mana_container_msg);
}


int init_freeze(struct item_t* item, char* msg) {
    char std_freeze_msg[] = "Pocket watch?!\n";
    return init_base_item(item, msg, FREEZE_ID, "init_freeze", std_freeze_msg);
}



/////////////////////////////////////////////////////

Item* init_none_item() {

    Item* p = (Item*) malloc(sizeof(Item));
    
    p->identity = NONE_ID;
    return p;
}








//////////////////////////////////////////////////////






# endif
