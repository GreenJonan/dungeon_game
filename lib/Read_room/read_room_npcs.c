# ifndef READ_ROOM_NPCS_
# define READ_ROOM_NPCS_

# include "../Objects/Item_methods/item_meth_head.c"

int read_npcs(Room*, FILE*);
Npc* load_simple_npc(FILE*, int*);
Npc* load_shopkeeper_npc(FILE*, int*);


Npc* init_basic_npc(int, int, int, int);




//////////////////////////////////////////////////////////////////////

int read_room_npcs(Room* empty_room, char* npc) {
    return read_room(empty_room, npc, "read_room_npcs", NPC_FILE_ID);
}




int read_npcs(Room* empty_room, FILE* f) {

    char name[] = "read_npcs";
    
    int end_of_file = 0;
    //Npc_ls* prev_ls_ptr = NULL;
    
    while (!end_of_file) {
        // read line by line
        char c = fgetc(f);
        
        
        // read until first '$' symbol indicating start of enemy list,
        while (c != '$' && !end_of_file && c != '/') {
            c = fgetc(f);
    
            if (feof(f)) {
                end_of_file = 1;
            }
        }
        
        
        if (c == '/') {
            flush_file_input(f);
            if (feof(f)) {
                end_of_file = 1;
            }
        }
        
        
        
        else if (!end_of_file && c == '$') {
            
            // see what npc type it is,
            char str[BUFF];
            
            fscanf(f, "%s", str);
            
            if (str_eq(str, NONE)) {
            
                flush_file_input(f);
                if (feof(f)) {
                    end_of_file = 1;
                }
            }
            
            else {
                /////
                /////      MAIN ANALYSIS FOR NPC INPUT
                /////
                
                
                
                // Record and fix identities
                int error = 0;
                int item = 0;
                Npc* npc = NULL;
                
                
                if (str_eq(str, SIMPLE_NPC)) {
                
                    npc = load_simple_npc(f, &item);
                }
                
                
                
                else if (str_eq(str, SHOPKEEPER_NPC)) {
                
                    npc = load_shopkeeper_npc(f, &item);
                }
                
                
                
                else {
                    if (!SUPPRESS_WARNINGS) {
                        printf("ERROR: unknown NPC type: '%s'\n", str);
                        pause_function();
                    }
                    error = 1;
                }
                
                
                
                
                
                
                
                if (!error) {
                    if (npc == NULL) {
                        npc_null_error(name);
                    }
                
                    
                    else {
                        // final analysis.
                    
                    
                        char msg[DIALOGUE_BUFF];
                        char name[BUFF];
                    
                        read_str(f, name, BUFF);
                        read_str(f, msg, DIALOGUE_BUFF);
                        
                        
                        // work out defaults for above messages
                        if (!str_eq(name, NONE)) {
                        
                            if (str_eq(name, SHOPKEEPER_DEFAULT)) {
                                str_copy(SHOPKEEPER_AUTHOR, npc->base.msg);
                            }
                            else {
                                str_copy(name, npc->base.msg);
                            }
                        }
                        
                        
                        if (!str_eq(msg, NONE)) {
                            
                            if (str_eq(name, SHOPKEEPER_DEFAULT)) {
                                str_copy(SHOPKEEPER_MSG, npc->dialogue);
                            }
                            else {
                                str_copy(name, npc->dialogue);
                            }
                        }
                        
                        
                        
                        
                        
                    
                        flush_file_input(f);
                        if (feof(f)) {
                            end_of_file = 1;
                        }
                        
                        
                        
                        
                        if (!end_of_file) {
                            int end_of_block = 0;
                            
                            while (!end_of_block && item) {
                            
                                // read remaining lines of NPC input block
                                
                                
                                
                                c = fgetc(f);
                                
                                
                                // read until first '$' symbol indicating start of enemy list,
                                while (c != '$' && !feof(f) && c != '/' && c != '#') {
                                    c = fgetc(f);
                                }
                                
                                
                                if (c == '/') {;}
                                
                                else if (c == '#') {  end_of_block = 1;  }
                                
                                
                                
                                else if (!end_of_file && c == '$') {
                                    
                                    // see what npc type it is,
                                    char str[BUFF];
                                    
                                    fscanf(f, "%s", str);
                                    
                                    if (str_eq(str, NONE)) {;} // flush file input
                                    
                                    else if (!feof(f)) {
                                        
                                        
                                        // main item analysis
                                        
                                        char item_msg[BUFF];
                                        int x, y, cost, num;
                                        fscanf(f, "%d,%d %d %d", &x, &y, &cost, &num);
                                        read_str(f, item_msg, BUFF);
                                        
                                        
                                        Item* item = init_inv_item(str, num, item_msg, 1);
                                        item->base.x = x;
                                        item->base.y = y;
                                        
                                        set_entity_clip(&(item->base), 1);
                                        
                                        set_item_price(item, cost);
                                        
                                        
                                        npc->items = push_item_start(npc->items, item);
                                    }
                                }
                                
                                
                                // flush file input
                                flush_file_input(f);
                                if (feof(f)) {
                                    end_of_file = 1;
                                    end_of_block = 1;
                                }
                                
                            }
                        }
                        
                        
                        
                        // now append npc to block
                        
                        queue_npc(empty_room, npc);
                        
                        
                        /*
                        Npc_ls* tmpnpcs = empty_room->npcs;
                        while(tmpnpcs != NULL) {
                            printf("%d  ", tmpnpcs->character->base.status);
                            tmpnpcs = tmpnpcs->next;
                        }
                        
                        pause_function();
                         */ // REMOVE - useful only for debugging.
                    }
                }
            }
        }
    }
    
    return 0;
}












////////////////////////////////////////////////////


Npc* init_basic_npc(int x, int y, int hp, int id) {

    Npc* npc = allocate_npc(1);
    npc->base.x = x;
    npc->base.y = y;
    npc->base.health = hp;
    npc->base.max_health = hp;
    
    npc->character_id = id;
    
    return npc;
}






Npc* load_simple_npc(FILE* f, int* has_item) {

    char name[] = "load_simple_npc";
    
    if (f == NULL) {
        null_error(FILE_OBJECT, name);
        return NULL;
    }
    if (has_item == NULL) {
        null_error("Integer Pointer", name);
        return NULL;
    }
    
    int x, y, hp;
    fscanf(f, "%d,%d %d %d", &x, &y, has_item, &hp);
    
   return init_basic_npc(x, y, hp, SIMPLE_NPC_ID);
}





Npc* load_shopkeeper_npc(FILE* f, int* has_item) {
    
    char name[] = "load_shopkeeper_npc";
    
    if (f == NULL) {
        null_error(FILE_OBJECT, name);
        return NULL;
    }
    if (has_item == NULL) {
        null_error("Integer Pointer", name);
        return NULL;
    }
    
    int x, y, hp;
    fscanf(f, "%d,%d %d %d", &x, &y, has_item, &hp);
    
    return init_basic_npc(x, y, hp, SHOPKEEPER_ID);
}





# endif
