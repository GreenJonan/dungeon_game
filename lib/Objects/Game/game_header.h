# ifndef GAME_HEADER
# define GAME_HEADER

int game_null_error(char* function) {
    return null_error(GAME_OBJECT, function);
}

# define TRIG_NUM 8



typedef struct options_t {
    int difficulty;    // easy, med, hard
    int command_debug; // on off
    int rnd1;
    int rnd2;
    int rnd3;
} GameOptions;



typedef struct game_t {
    //private
    
    Room_ls** rooms;
    Player* player;
    int room_len;
    int is_setup;
    
    GameOptions options;
    
    char triggers[TRIG_NUM];
    
    // public
    
    int is_hard;
    int game_over;
    char pwd[BUFF];
    char src_dir[BUFF];
    long time;
    int error;
    int inventory;
    
    int draw_hud_items;
    
    char player_turn;
    
    // loaded objects
    int loaded_rooms;
    int loaded_player;
} Game;


# endif


