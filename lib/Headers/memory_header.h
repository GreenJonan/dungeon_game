# ifndef MEMORY_HEADER__
# define MEMORY_HEADER__

# include "master_header.h"

//game
int unload_game(struct game_t*);
int free_all_rooms(struct game_t*);

int set_game_trig(struct game_t*, int, int, int);
int get_game_trig(struct game_t*, int);



//exit
int free_exit(struct exit_t*);
int free_exit_ls(struct exit_list_t*, int);

int connect_exits(struct game_t*);

struct exit_t* allocate_exit();
struct exit_list_t* allocate_exit_ls(struct exit_list_t*);

// chest
int free_chest(struct chest_t*);
int free_chest_ls(struct chest_list_t*);
int connect_chests(struct game_t*);

int free_room_chests(struct room_t*);



// room
int free_room_exits(struct room_t*);
int free_room_items(struct room_t*);
int free_room_enemies(struct room_t*);

int free_room(struct room_t*);
int free_room_array(char*);
int free_room_ls(struct room_list_t*, int);


int setup_rooms(struct game_t*);
struct room_list_t* init_room_ls(struct game_t*);
int init_room(char*, char*, struct room_t*);

struct room_list_t** allocate_room_ls_pointer_array(int);
struct room_t* allocate_room(int);





/////
/////   ENTITY
/////


//entity base
int free_entity(struct entity_t*);
struct entity_t* allocate_entity();




//item
int free_item(struct item_t*);
struct item_t* allocate_item(int);
int fix_item_identity(struct item_t*, char*, char*);

// item init types
int init_heart(struct item_t*, char*);
int init_coin(struct item_t*, char*);
int init_key(struct item_t*, char*);
int init_bomb(struct item_t*, char*);
int init_arrow(struct item_t*, char*);
int init_mana(struct item_t*, char*);
int init_heart_container(struct item_t*, char*);
int init_mana_container(struct item_t*, char*);
int init_freeze(struct item_t*, char*);

struct item_t* init_none_item();



//enemy
int free_enemy(struct enemy_t*);
struct enemy_t* allocate_enemy(int);

// enemy init types
int init_slime(struct enemy_t*);
int init_knight(struct enemy_t*);
int init_ghost(struct enemy_t*);
int init_orb(struct enemy_t*);
int init_baby_slime(struct enemy_t*);
int init_skeleton(struct enemy_t*);
int init_zombie(struct enemy_t*);



// special entity
int free_special_entity(struct spc_entity_t*);
struct spc_entity_t* allocate_special_entity(int);

int init_spc_basic_sword(struct player_t*);
int init_spc_basic_staff(struct player_t*);
int init_spc_basic_bomb(struct player_t*);
struct spc_entity_t* init_spc_arrow(struct player_t*, int);
int init_spc_fast_arrow(struct game_t*, int);
int init_spc_slow_arrow(struct player_t*, int);

int init_spc_flag(struct room_t*, int, int);
int init_spc_telephone(struct room_t*, char*, int, int, int, int, int, int, int);
int init_spc_push_block(struct room_t*, int, int, int, int, int);
int init_spc_pop_block(struct room_t*, int, int, int, int);
int init_spc_switch(struct room_t*, int, int, int, int, int);
int init_spc_lamp(struct room_t*, int, int, int, int, int);


int connect_special_entities(struct game_t*);



// npc
int free_npc(struct npc_t*);
struct item_t* pop_item_ls_npc(struct i_list*, struct npc_t*);
struct npc_t* allocate_npc(int);
struct n_list* allocate_npc_ls(struct npc_t*);




// npc lists
int free_npc_ls(struct n_list*);
int free_npc_nodes(struct n_list*);
int kill_npc(struct room_t*, struct n_list*);
int queue_npc(struct room_t*, struct npc_t*);





// special entity list
int free_special_entity_ls(struct s_list*);
int free_special_entity_nodes(struct s_list*);
int kill_special_entity(struct room_t*, struct s_list*, int);
struct s_list* allocate_special_entity_ls(struct spc_entity_t*);
struct s_list* push_special_entity_end(struct s_list*, struct spc_entity_t*);


//item list
int free_item_ls(struct i_list*);
int free_item_nodes(struct i_list*);
int kill_item(struct room_t*, struct i_list*);
struct item_t* pop_item_ls_room(struct i_list*, struct room_t*);
struct i_list* allocate_item_ls(struct item_t*);
struct i_list* push_item_start(struct i_list*, struct item_t*);



//enemy list
int free_enemy_ls(struct e_list*);
int free_enemy_nodes(struct e_list*);
int kill_enemy(struct room_t*, struct e_list*);
struct e_list* kill_enemy_ls(struct e_list* e_ls, struct room_t* r);
struct e_list* allocate_enemy_ls(struct enemy_t*);
struct e_list* push_enemy_start(struct e_list*, struct enemy_t*);



//inventory
int free_inventory(struct inv_t*);
struct inv_t* init_inventory();



//player
int free_player(struct player_t*);
int free_move_ls(struct move_list_t*);
struct move_list_t* next_move(struct move_list_t*);
int add_player_move(struct player_t*, char);


struct player_t* allocate_player();
int init_player(struct game_t*, struct player_t*, FILE*);
int init_player_default(struct game_t*, struct player_t*);
int setup_player(struct game_t*);
int add_new_move(struct move_list_t*, char);
struct move_list_t* add_move(char);







# endif
