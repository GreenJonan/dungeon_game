# ifndef ENTITY_
# define ENTITY_

// Assume all variables are private,
// that is no functions outside of this directory may access the values.


// each entity will have an x,y position in space
// clock refers to how many ing ame ticks before the entity next updates its actions
// timer refers to how many in game ticks left until the entity updates.
// clip <==> can other entities clip through it or not.



// ENTITY BASE

typedef struct entity_t {
    char status;
    int clock; // clock is static
    int timer; // timer counts down
    
    int mass;
    int x;
    int y;
    int vel_x;
    int vel_y;
    
    int vel_x_timer;
    int vel_y_timer;
    
    int health;
    int max_health;
    int mana;
    int max_mana;
    
    int light_dist;
    int direction;
    int eyesight;
    
    char fly; // not implemented yet.
    
    char* default_hit_box;
    char* hit_box;
    char width;
    char height;
    
    // this restricts and somewhat saves the memory
    char e_x;
    char e_y;
    char tmp_height;
    char tmp_width;
    char rot_style;
    
    char msg[BUFF];
    
} Entity;

// status: (clip, paralysed, poison, 0, 0, 0, 0, 0)i
//





// ITEM

typedef struct item_t {
    Entity base;
    int identity;
    int num;
    int max_num;
    char equipped;
} Item;
// num -- how many items are stacked ontop of each other.
// identity, is it a heart, coin, bomb etc.




// ENEMY

typedef struct enemy_t {
    Entity base;
    int ai;
    int touch_dmg;  //touch damage
    char shield;
    char drop_item;
    int enemy_id;
    int champion;
    
    float wait_rnd;
    float turn_rnd;
    float item_rnd;
    Item* item;
    
    int player_x;
    int player_y;
} Enemy;



// SPECIAL ENTITIES, bombs etc

typedef struct spc_entity_t {

    Entity base;
    int entity_id;
    char player_id;
    char wait_update;
} Spc_ent;








// NPC's // i.e. non-playerable characters, for exmaple shopkeepers

typedef struct npc_t {

    Entity base;
    int character_id;
    
    struct i_list* items;
    
    char dialogue[DIALOGUE_BUFF];
} Npc;












// ITEM ROOM LIST

typedef struct i_list {
    Item* item;
    struct i_list* next;
    struct i_list* prev;
} Item_ls;


// ENEMY ROOM LIST

typedef struct e_list {
    Enemy* enemy;
    struct e_list* next;
    struct e_list* prev;
} Enemy_ls;



// SPECIAL ENTITY LIST

typedef struct s_list {
    Spc_ent* spc_entity;
    struct s_list* next;
    struct s_list* prev;
} Spc_ent_ls;



// NPC LIST

typedef struct n_list {
    Npc* character;
    struct n_list* next;
    struct n_list* prev;
} Npc_ls;












// PLAYER

typedef struct player_t {
    Entity base;
    int has_sword;
    int has_mana;
    int hit;
    char loop;
    
    struct room_t* room;
    
    //int direction; // which direction is the player facing. N,E,S,W <==> 0,1,2,3 ==> moved to entity
    struct exit_t* last_door;
    
    struct inv_t* inventory;
    struct move_list_t* moves;
} Player;









typedef struct move_list_t {
    char action;
    struct move_list_t* next;
} Move_ls;






// inventory:


// GENERAL INVENTORY

typedef struct inv_t {
    
    // equipped items:
    
    Item* eq_active_item;
    Item* eq_passive_item;
    Item* eq_consumable_item;
    
    Item* prev_active;
    Item* prev_passive;
    Item* prev_consumable;
    
    
    Item_ls* active;
    Item_ls* passive;
    Item_ls* consumable;
    
    int active_len;
    int passive_len;
    int consumable_len;
    
    int inv_cursor;
    int inv_item_cursors[3];
    int inv_item_pos[3];
    
    int key_num;
    int coin_num;
    int bomb_num;
    int arrow_num;
} Inventory;



/*
 struct inv_list* active;
 struct inv_list* passive;
 struct inv_list* consumable;
 
 
 
typedef struct inv_list {

    Item* item;
    struct inv_list* next;
    struct inv_list* prev;
}*/






//////////////////////////////////////

// null errors


int entity_null_error(char* function) {
    return null_error(ENTITY_OBJECT, function);
}
int item_null_error(char* function) {
    return null_error(ITEM_OBJECT, function);
}
int enemy_null_error(char* function) {
    return null_error(ENEMY_OBJECT, function);
}

int special_entity_null_error(char* function) {
    return null_error(SPECIAL_ENTITY_OBJECT, function);
}


int npc_null_error(char* function) {
    return null_error(NPC_OBJECT, function);
}



# endif
