# ifndef MASTER_HEADER__
# define MASTER_HEADER__






// Object names

# define GAME_OBJECT "Game"
# define ENTITY_OBJECT "Entity"
# define ITEM_OBJECT "Item"
# define ENEMY_OBJECT "Enemy"
# define PLAYER_OBJECT "Player"
# define EXIT_OBJECT "Exit"
# define ROOM_OBJECT "Room"
# define ITEM_LS_OBJECT "Item_ls"
# define ENEMY_LS_OBJECT "Enemy_ls"
# define EXIT_LS_OBJECT "Exit_ls"
# define ROOM_LS_OBJECT "Room_ls"
# define ROOM_LS_POINTER "Room_ls Pointer"
# define STRING_OBJECT "String"
# define MOVE_LS_OBJECT "Move_ls"
# define ENTITY_OBJECT "Entity"
# define CHEST_OBJECT "Chest"
# define CHEST_LS_OBJECT "Chest_ls"
# define INVENTORY_OBJECT "Inventory"
# define SPECIAL_ENTITY_OBJECT "Special_Entity"
# define SPECIAL_ENTITY_LS_OBJECT "Special_Entity_ls"
# define NPC_OBJECT "Npc"
# define NPC_LS_OBJECT "Npc_ls"
# define FILE_OBJECT "FILE"




// structs

struct entity_t;
struct item_t;
struct enemy_t;
struct spc_entity_t;
struct npc_t;
struct inv_list;
struct inv_t;
struct i_list;
struct e_list;
struct s_list;
struct n_list;
struct player_t;

struct room_t;
struct room_list_t;
struct exit_t;
struct exit_list_t;
struct chest_t;
struct chest_list_t;

struct game_t;
struct move_list_t;
struct options_t;




/////
/////   struct functions/methods
/////



// game

int exit_game(struct game_t*, int);
int setup_game(struct game_t*);
int start_game(struct game_t*);
int play_game(struct game_t*);

int increment_game_time(struct game_t*);
int game_player_damage(struct game_t*, int);

int gameover(struct game_t*);
int start_menu(struct game_t*, int);
int options_menu(struct game_t*);
int game_select(struct game_t*);

int option_adjust_left(struct game_t*, int);
int option_adjust_right(struct game_t*, int);

int update_switch_blocks(struct game_t*);




// DOOR

// bool:
int set_door_locked(struct exit_t*, int);
int set_door_switch(struct exit_t*, int);
int set_door_bombable(struct exit_t*, int);
int set_door_portal(struct exit_t*, int);

int door_is_locked(struct exit_t*);
int door_is_switch(struct exit_t*);
int door_is_bombable(struct exit_t*);
int door_is_portal(struct exit_t*);



int set_exit_pos(char*, int, int, int*, struct exit_t*);
struct exit_t* find_room_exit(struct game_t*, int, int);
int teleport_player_to_exit(struct game_t*, int, int, int);  // this is given that the room, and exit number is known

struct exit_t* find_exit_point(struct room_t*, int, int);




// ROOM

int read_room_layout(struct room_t*, char*);
int read_room_items(struct room_t*, char*);
int read_room_enemies(struct room_t*, char*);
int read_room_npcs(struct room_t*, char*);
int read_room(struct room_t*, char*, char*, int);

char get_room_tile(struct room_t*, int, int);
int set_room_tile(struct room_t*, int, int, char);

int simple_clear_path(char*, int, int, int, int, int, int);
//int clear_path_up(struct room_t*, int, int, int, int);
//int clear_path_down(struct room_t*, int, int, int, int);
int clear_path_dir(char*, int, int, int, int, int, int, int);

int increment_room_clock(struct room_t*, int);

int room_null_error(char*);

int weapon_damage(struct game_t*, int, int, int, int, int);
int weapon_hit_spc_room_entities(struct game_t*, int, int, int, int, int);

//int set_room_deault_position(struct room_t*, struct player_t*);

int is_clip_position(struct room_t*, struct entity_t*, int, int);




// CHESTS

struct chest_t* player_find_chest(struct chest_list_t*, int, int);
int player_open_chest(struct game_t*);

int open_room_chest(struct player_t*);




/////
/////   ENTITY
/////


// BASE

// bool: int--> 0/1
int set_entity_clip(struct entity_t*, int);
int set_entity_paralysed(struct entity_t*, int);
int set_entity_poisoned(struct entity_t*, int);
int set_entity_override_clip(struct entity_t*, int);

int is_entity_clip(struct entity_t*);
int is_entity_paralysed(struct entity_t*);
int is_entity_poisoned(struct entity_t*);
int get_entity_override_clip(struct entity_t*);

//int entity_room_clip(struct room_t*, struct entity_t*, int, int);


//health    -->  second int => overload
//int set_entity_health(struct entity_t*, int, int);
//int set_entity_max_health(struct entity_t*, int);
//int give_entity_health(struct entity_t*, int, int);


//clock
//int set_entity_clock(struct entity_t*, int);
//int get_entity_clock(struct entity_t*, int);
int increment_entity_clock(struct entity_t*, int);


/*
int move_entity_up(struct entity_t*);
int move_entity_left(struct entity_t*);
int move_entity_down(struct entity_t*);
int move_entity_right(struct entity_t*);*/
int move_entity(struct entity_t*, int, struct room_t*);


int entity_x_pos(struct entity_t*);
int entity_y_pos(struct entity_t*);
int set_entity_pos(struct entity_t*, int, int);

int set_entity_light_dist(struct entity_t*, int);
int get_entity_light_dist(struct entity_t*);
int in_vision_cone(struct entity_t*, int, int, int);


int radial_vision(struct entity_t*, int, int);
int half_radial_vision(struct entity_t*, int, int, int);
int half_radial_forward_vision(struct entity_t*, int, int);
int half_radial_backward_vision(struct entity_t*, int, int);
int cone_vision(struct entity_t*, int, int, int);
int entity_eyesight(struct entity_t*, int, int);




// note this function, automatically decrements velocity timers!!!
int increment_entity_move(struct entity_t*, struct room_t*, int*, int*);
int entity_move(struct entity_t*, struct room_t*, int);



// ENEMY COLLIDE

int entity_room_collide(struct entity_t*, struct room_t*, int, int);
int matrix_room_collide(char*, int, int, int, int, int, int, struct room_t*, int);
int entity_room_tile_collide(struct entity_t*, struct room_t*, int, int, int, int*, int*);
int matrix_entity_collide(char*, int, int, int, int, int, int, struct entity_t*, int);
int entity_entity_collide(struct entity_t*, int, int, struct entity_t*);
int set_entity_hit_box(struct entity_t*, int);

int init_entity_hit_box_block(struct entity_t*, int, int, int, int);







// SPECIAL ENTITY

int increment_spc_entity_time(struct game_t*);
int reset_spc_entity_time(struct game_t*);

int reset_spc_room_entities(struct player_t*);

int activate_switch(struct spc_entity_t*, struct game_t*);




// ITEM

int increment_item_clock(struct item_t*, int);

int item_x_pos(struct item_t*);
int item_y_pos(struct item_t*);
int pickup_item(struct game_t*, struct item_t*);


// ENEMY

int increment_enemy_clock(struct enemy_t*, int);

int enemy_x_pos(struct enemy_t*);
int enemy_y_pos(struct enemy_t*);
int set_enemy_pos(struct enemy_t*, int, int);
int set_enemy_vel(struct enemy_t*, int, int);

int move_enemy_up(struct enemy_t*);
int move_enemy_left(struct enemy_t*);
int move_enemy_down(struct enemy_t*);
int move_enemy_right(struct enemy_t*);
int move_enemy_direction(struct enemy_t*, int, struct player_t*);


int enemy_damage(struct enemy_t*, int);
int enemy_heal(struct enemy_t*, int);
int enemy_absolute_heal(struct enemy_t*, int);


int set_enemy_light_dist(struct enemy_t*, int);
int get_enemy_light_dist(struct enemy_t*);

int enemy_sees_player(struct enemy_t*, struct player_t*);
int enemy_sees_player_room(struct enemy_t*, struct player_t*, struct room_t*);


int move_enemy(struct enemy_t*, struct game_t*);


// AI
int static_enemy(struct enemy_t*, struct player_t*);
int rnd_enemy_wondering(struct enemy_t*, struct player_t*);







// ITEM LIST
struct i_list* first_item_node(struct i_list*);
struct i_list* last_item_node(struct i_list*);

int increment_room_items_clock(struct i_list*, int);



// ENEMY LIST
struct e_list* first_enemy_node(struct e_list*);
struct e_list* last_enemy_node(struct e_list*);

int increment_room_enemies_clock(struct e_list*, int);


// SPECIAL ENTITY LIST
struct s_list* first_special_entity_node(struct s_list*);
struct s_list* last_special_entity_node(struct s_list*);





// INVENTORY
int move_cursor_up(struct game_t*);
int move_cursor_left(struct game_t*);
int move_cursor_down(struct game_t*);
int move_cursor_right(struct game_t*);
int select_cursor(struct game_t*);

int give_player_item(struct game_t*, struct item_t*);
int give_player_new_item(struct game_t*, int);

int exit_inventory(struct game_t*);

int has_item(struct inv_t*, int);

struct item_t* init_inv_item(char*, int, char*, int);




// PLAYER
int set_player_default_position(struct room_list_t**, struct player_t*);
char compute_next_action(struct player_t*);

int set_player_deault_room(struct room_list_t**, struct player_t*);
int set_player_room(struct room_t*, struct player_t*);
int set_room_default_position(struct player_t*);


int move_player(struct game_t*, int);
int set_player_xy(struct player_t*, int, int);
int increment_player_clock(struct player_t*);
int teleport_player_exit(struct player_t*, struct exit_t*);
// this is for when it is known that the player is standing on an exit, but unknown which one it is.
// changed, this is no-longer the case.

int player_damage(struct player_t*, int);
int player_heal(struct player_t*, int);
int player_absolute_heal(struct player_t*, int);
int revive_player(struct player_t*);
int player_is_dead(struct player_t*);

int player_collect_items(struct game_t*, int);
int item_player_interaction(struct game_t*, struct player_t*, struct i_list*, int);
int item_interaction(struct item_t*);


int player_equipped_sword(struct player_t*);
int give_player_sword(struct player_t*);
int take_player_sword(struct player_t*);
int set_player_sword(struct player_t*, int);

int set_player_default_status(struct player_t*);
int set_player_clip(struct player_t*, int);
int set_player_paralysed(struct player_t*, int);
int set_player_poisoned(struct player_t*, int);
int is_player_clip(struct player_t*);
int is_player_paralysed(struct player_t*);
int is_player_poisoned(struct player_t*);


int player_x_pos(struct player_t*);
int player_y_pos(struct player_t*);


int set_player_light_dist(struct player_t*, int);
int get_player_light_dist(struct player_t*);


int player_use_mana(struct player_t*, int);
int player_gain_mana(struct player_t*, int);
int player_gain_absolute_mana(struct player_t*, int);

int player_gain_health_container(struct player_t*, int);
int player_gain_mana_container(struct player_t*, int);

int player_spc_entity_interaction(struct game_t*, int);
int player_npc_interaction(struct game_t*, int);




/////
/////    General Functions
/////

int player_turn(struct game_t*);
int enemy_turn(struct game_t*);


char receive_input_command(struct game_t*);
char simple_input(struct game_t*, int, char);
int is_valid_move(char);
char special_commands(struct game_t*);
int debug_commands(struct game_t*);



// draw screen

int draw_screen(struct game_t*);
int draw_map(struct game_t*);
int draw_hud(struct game_t*);
int draw_inventory(struct game_t*);
int print_room_layout(int*, int, int, int);
int print_tile_sprite(int, int);
int print_item_sprite(int, int);

int append_player_to_room_array(struct room_t*, int*, struct player_t*);
int append_items_to_room_array(struct room_t*, int*);
int append_enemies_to_room_array(struct room_t*, int*);
int append_exits_to_room_array(struct room_t*, int*);
int append_chests_to_room_array(struct room_t*, int*);
int append_spc_entities_to_room_array(struct room_t*, int*);
int append_npcs_to_room_array(struct room_t*, int*);



int item_to_code(struct item_t*);
int enemy_to_code(struct enemy_t*);
char sword_to_code(int);
int is_clip_tile(char);
int door_number(struct exit_t*);
int set_room_dark(char*, int, int, int, int, int);
int spc_entity_to_tile(struct spc_entity_t*);
int npc_to_tile(struct npc_t*);


void print_help_message();
void print_debug_commands();
char setup_player_move_ls(struct game_t*, char*, char);
int pause_game();


int print_dialogue_msg(char*, char*, struct game_t*);
int print_buy_ite_msg(int, int, int);
void print_item_name(int);
int print_win_msg(struct game_t*);




void draw_start_screen(int);
void print_box_topbot(int, int, int, int, int);
void print_box_top(int, int, int, int);
void print_box_bot(int, int, int, int);
int print_box_internal(int, int, int, char*, int, int);
void print_box_side(int, int, int, int);
void print_box_left(int, int);
void print_box_right(int, int, int);
int print_box_empty(int, int, int, int);

int draw_menu_box(char**, int*, int, int, int, int, int);

void draw_options_screen(struct game_t*, int);
int print_box_header(int, int, int, char*, int);
int print_options_header(int, int, int);


int draw_player_status_screen(struct game_t*);
void draw_menu_options_screen(int);

void draw_game_select_screen(struct game_t*, int);


// supplementary functions

int manhattan_metric(int, int, int, int);

char flush_input();
char flush_file_input(FILE*);
char dynamic_flush(FILE*, char);

int read_file(FILE*, char*, char, int);
int find_pwd(char*, int);

int set_char_bool_true(char*, int);
int set_char_bool_false(char*, int);
int read_char_bool(char, int);
int set_bool_array_bool(char*, int, int);
int read_bool_array(char*, int);


int simple_str_concat(char*, char*, char*);
int str_copy(char*, char*);
int str_eq(char*, char*);
int read_str(FILE*, char*, int);


int loading_progress(int);
int clear_screen();
int force_clear_screen();
int loading_progress_no_clr(int);

int wait_msg();
int null_error(char*, char*);
int file_error(char*, char*);
int null_warning(char*, char*);
int already_freed_warning(char*, char*);
int pause_function();
int free_error(char*);


int dir_to_xy(int, int*, int*);
int num_len(int);







// non-implemeted sound functions

int player_heal_sound(int);
int player_hurt_sound(int);
int player_blocked_sound();

# endif
