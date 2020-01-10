# ifndef ROOM_HEADER___
# define ROOM_HEADER___

# include "../Entities/entity_header.h"


typedef struct room_t {
    //private
    
    char* room_array;
    int width;
    int height;
    
    int room_id;
    int update_time;
    
    Enemy_ls* enemies;
    Item_ls* items;
    Spc_ent_ls* spc_weapon_entities;
    Spc_ent_ls* spc_room_entities;
    Npc_ls* npcs;
    
    struct exit_list_t* exits;
    struct chest_list_t* chests;
    
    int exit_len;
    
    int is_dark;
    int room_lock; // exits are locked whether enemies are in / out, 0 ==> no 1==> when all defeated -> 0,
    // -1 ==> if any enemy then automatically locked.
} Room;







typedef struct exit_t {
    // private
    
    int x;
    int y;
    
    char status;
    int switch_id;
    
    Room* room;
    struct exit_t* door;
    
    // these give the room and door connected to the exit.
    int room_num;
    int exit_num;
    
    int key;
    
} Exit;

// char_bool lock_types ->
// 1bit ==> locked/open, 2bit ==> switch-type, 3bit ==> bomb-type, 4bit ==> is_portal





typedef struct chest_t {

    int x;
    int y;
    char opened;
    char locked;
    
    Item* item;
    int identity;
} Chest;









typedef struct room_list_t {

    Room* room;
    char name[12];
    struct room_list_t* next;
    
    // if add prev, need to update free and malloc functions
    // in both rooms and game code files.
    
} Room_ls;







typedef struct exit_list_t {

    Exit* exit;
    struct exit_list_t* next;
    struct exit_list_t* prev;
    
} Exit_ls;






typedef struct chest_list_t {
    Chest* chest;
    struct chest_list_t* next;
    struct chest_list_t* prev;
} Chest_ls;




int room_null_error(char* function) {
    return null_error(ROOM_OBJECT, function);
}



# endif
