# ifndef ROOM_INIT_
# define ROOM_INIT_

# include "room_header.h"

# include "../../utility_functions.c"
# include "room_mem.c"
# include "../../Read_room/read_room.c"

# include "exit_init.c"



// INITIALISE ROOM OBJECT

int init_room(char* room_name, char* src, Room* empty_room) {
    
    if (room_name == NULL || src == NULL || empty_room == NULL) {
        return 1;
    }
    
    empty_room->exits = NULL;
    empty_room->enemies = NULL;
    empty_room->items = NULL;
    
    char room_str[BUFF*2];
    simple_str_concat(room_str, src, room_name);
    
    
    
    // if last char isnt '/' insert '/'
    
    int i = 0;
    char c = room_str[i];
    while (c != '\0') {
        i++;
        c = room_str[i];
    }
    if (room_str[i-1] != '/') {
        room_str[i] = '/';
        room_str[i+1] = '\0';
    }
    // function is find room names perfectly
    
    
    // now make room_layout, room_enemies, room_items etc file paths.
    
    char layout[BUFF*2];
    char enemy[BUFF*2];
    char item[BUFF*2];
    char npc[BUFF*2];
    
    simple_str_concat(layout, room_str, LAYOUT_FILE);
    simple_str_concat(enemy, room_str, ENEMY_FILE);
    simple_str_concat(item, room_str, ITEM_FILE);
    simple_str_concat(npc, room_str, NPC_FILE);
    
    
    // file names are being created appropriately
    // now read appropriate files:
    
    // load defaults
    empty_room->width = 0;
    empty_room->height = 0;
    empty_room->enemies = NULL;
    empty_room->items = NULL;
    empty_room->spc_weapon_entities = NULL;
    empty_room->spc_room_entities = NULL;
    empty_room->exits = NULL;
    empty_room->chests = NULL;
    
    empty_room->exit_len = 0;
    empty_room->is_dark = 0;
    empty_room->room_lock = 0;
    

    int error;
    error = read_room_layout(empty_room, layout);
    
    if (!error) {
        read_room_items(empty_room, item);
        read_room_enemies(empty_room, enemy);
        read_room_npcs(empty_room, npc);
    }
    
    return 0;
}












// INITIALISE ROOM_LIST OBJECT


int setup_rooms(Game* g) {
    
    // get room map file
    
    char map[BUFF*2];
    simple_str_concat(map, g->src_dir, ROOM_MAP);

    
    FILE* f = fopen(map, "r");
    
    if (f == NULL) {
        printf("Make sure directory names from root have no spaces.\n");
        file_error(map, "setup_rooms");
        g->error = 1;
        return 1;
    }
    
    
    // assume layout of map file, line 1 = number of rooms, remaining lines = name of directories.
    
    int room_num;
    fscanf(f, "%d", &room_num);
    g->room_len = room_num;
    
    // unless error occurs, assume removes '\n' character. --> no it does not!!!
    
    flush_file_input(f);
    
    if (room_num <= 0 || feof(f)) {
        printf("Invalid number of rooms: %d\n", room_num);
        pause_function();
        g->error = 1;
        return 1;
    }
    
    
    g->rooms = allocate_room_ls_pointer_array(room_num);
    
    
    // read in room names from remaining lines of room_map files
    
    for (int i = 0; i < room_num; i++) {
        fscanf(f, "%s", g->rooms[i]->name);
        
        
        // register and setup each room
        init_room(g->rooms[i]->name, g->src_dir, g->rooms[i]->room);
        
        
        
        flush_file_input(f);
        if (feof(f)) {
            g->room_len = i + 1;
            i = room_num;
        }
    }
    
    fclose(f);
    
    // Now we need to connect all the exits up together, so that they point to the required rooms
    
    connect_exits(g);
    connect_chests(g);
    connect_special_entities(g);
    return 0;
}

# endif
