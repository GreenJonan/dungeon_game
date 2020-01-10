# ifndef READ_ALL_MY_ROOMS__
# define READ_ALL_MY_ROOMS__

# include "read_room_layout.c"
# include "read_room_items.c"
# include "read_room_enemies.c"
# include "read_room_npcs.c"



int read_room(Room* room, char* f_name, char* funct_name, int i) {

    if (room == NULL) {
        null_error(ROOM_OBJECT, funct_name);
        return 1;
    }
    if (NULL == f_name) {
        null_error(STRING_OBJECT, funct_name);
        return 1;
    }
    
    
    
    FILE* f = fopen(f_name, "r");
    
    if (NULL == f) {
        file_error(f_name, funct_name);
        return 1;
    }
    
    // employ algorithm to read file:
    
    if (i == LAYOUT_FILE_ID) {
        read_layout_(room, f);
    }
    else if ( i == ITEM_FILE_ID) {
        read_items(room, f);
    }
    else if (i == ENEMY_FILE_ID) {
        read_enemies(room, f);
    }
    else if (i == NPC_FILE_ID) {
        read_npcs(room, f);
    }
    else {
        printf("Unkown function type %d for 'read_room'.\n", i);
    }
    
    
    return fclose(f);
}




/*
 Current values of i:
 
 0 ==> room layout
 1 ==> items
 2 ==> enemies
 */

# endif
