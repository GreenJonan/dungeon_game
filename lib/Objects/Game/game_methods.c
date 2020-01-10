# ifndef GAME_METHODS
# define GAME_METHODS

int find_switch_type(struct game_t*, int, int, int, int);


// getters and setters

int get_game_trig(struct game_t* g, int trig_val) {
    
    if (trig_val <= 0 || trig_val > sizeof(char) * TRIG_NUM) {
        printf("VALUE ERROR: trigger value %d, out of range.\n", trig_val);
        pause_function();
        return -1;
    }
    
    if (g == NULL) {
        game_null_error("get_game_trig");
        return -1;
    }
    
    return read_bool_array(g->triggers, trig_val - 1);
}




int set_game_trig(struct game_t* g, int trig_val, int b, int type) {
    
    if (trig_val <= 0 || trig_val > sizeof(char) * TRIG_NUM) {
        printf("VALUE ERROR: trigger value %d, out of range.\n", trig_val);
        pause_function();
        return 1;
    }
    
    if (g == NULL) {
        game_null_error("set_game_trig");
        return 1;
    }
    
    /*
    int current = get_game_trig(g, trig_val);
    
    if (b && current) { return 0;}
    
    else if (!b && !current) { return 0;}
    
    */
    if (0) {;} // no efficient computing otherwise causes NOR, NAND to not work.
     
    else {
    
        int found;
        
        // this implies setting game triggers
        
        if (type == SIMPLE_SWITCH_TYPE) {
        
            found = b;
        }
        
        
        else if (type == AND_TYPE) {

            found = 1;
            int found_open = find_switch_type(g, AND_TYPE, trig_val, 0, 0);
            
            if (found_open) { found = 0;}
        }
        
        
        else if (type == OR_TYPE) {
            
            found = 0;
            int found_closed = find_switch_type(g, OR_TYPE, trig_val, 1, 0);
            
            if (found_closed) { found = 1;}
        }
        
        
        
        
        else if (type == NAND_TYPE) {
            
            found = 1;
            int found_open = find_switch_type(g, NAND_TYPE, trig_val, 0, 0);
            
            if (!found_open) { found = 0;}
        }
        
        
        
        else if (type == NOR_TYPE) {
            
            found = 0;
            int found_closed = find_switch_type(g, NOR_TYPE, trig_val, 1, 0);
            
            if (!found_closed) { found = 1;}
        }
        
        
        
        else if (type == XOR_TYPE) {
            
            // see how many switches are closed.
            int switch_closed_num = find_switch_type(g, XOR_TYPE, trig_val, 1, 1);
            
            found = 0;
            if (switch_closed_num == 1) {
                found = 1;
            }
        }
        
        
        else if (type == XNOR_TYPE) {
        
            int switch_closed_num = find_switch_type(g, XNOR_TYPE, trig_val, 1, 1);
            
            found = 1;
            if (switch_closed_num == 1) {
                found = 0;
            }
        }
        
        
        
        else if (type == EQUALITY_TYPE) {
            
            // find number of open and closed switches
            
            int switch_closed_num = find_switch_type(g, EQUALITY_TYPE, trig_val, 1, 1);
            int switch_open_num = find_switch_type(g, EQUALITY_TYPE, trig_val, 0, 1);

            
            found = 0;
            if (switch_closed_num == switch_open_num) {
                found = 1;
            }
        }
        
        
        /*
        else if (type == ANTI_XOR_TYPE) {
            
            int switch_open_num = find_switch)type(g, ANTI_XOR_TYPE, trig_val, 0, 1);
            
            found = 0;
            if (switch_open_num == 1) {
                found = 1;
            }
        }
        
        
        
        else if (type == ANTI_XNOR_TYPE) {
            
            int switch_open_num = find_switch)type(g, ANTI_XNOR_TYPE, trig_val, 0, 1);
            
            found = 1;
            if (switch_open_num == 1) {
                found = 0;
            }
        }*/
        
        
        
        
        else {
            printf("VALUE ERROR: unknown switch id number: %d\n", type);
            pause_function();
            return 1;
        }
        
        
        
        // update blocks now.
        
        set_bool_array_bool(g->triggers, trig_val - 1, found);
        update_switch_blocks(g);
    }
    

    return 0;
}














// update room switchs:

// CURRENT SWITCH OBJECTS ==> doors, telephone, pop_block



int update_switch_blocks(struct game_t* g) {

    char name[] = "update_switch_blocks";
    
    if (g == NULL) {
        game_null_error(name);
        return 1;
    }

    // why not just update all the switch blocks in all of the rooms?? -- that is the current implementation.
    
    
    
    for (int i = 0; i < g->room_len; i++) {
    
        if (g->rooms[i] == NULL) {
            printf("ERROR: Room number %d is NULL in function: %s.\n", i + 1, name);
            pause_function();
        }
        
        
        
        else {
            Room* r = g->rooms[i]->room;
            
            if (r == NULL) {
                printf("Room %d.\n", i);
                room_null_error(name);
            }
            
            
            else {
            
                // here are the linked lists to update
                // exits, Spc_room_entities
                
                if (r->exits != NULL) {
                
                    // a cricular linked list is sooooo painful to deal with for my purposes of updating all
                    // elements. It would be sort of useful in searching algorithms or a circular stack.
                    // i.e. a cyclical event, perform the action, then move to next node... until returning to
                    // start and begining all over again.
                    
                    Exit_ls* tmp_exits = r->exits;
                    
                    int exit_key = 0;
                    int tmp_key = -1;
                    if (tmp_exits->exit == NULL) {
                        printf("Room %d.\n", i);
                        null_error(EXIT_OBJECT, name);
                    }
                    
                    else {
                        // lazy but,
                        // dont bother to perform the algorithm if no key for first element
                        
                        while (tmp_key != exit_key) {
                    
                            if (exit_key == 0) {
                                tmp_key = exit_key;
                                exit_key = tmp_exits->exit->key;
                            }
                            
                            else if (tmp_exits->exit != NULL) {
                            
                                
                                
                                // MAIN ANALYSIS
                                
                                Exit* door = tmp_exits->exit;
                                
                                if (door->switch_id > 0 && door_is_switch(door)) {
                        

                                    int default_locked = get_door_default_locked(door);
                                    int activated = get_game_trig(g, door->switch_id);
                                    
                                    int new_locked = 0;
                                    if (default_locked) { new_locked = !new_locked;}
                                    if (activated) { new_locked = !new_locked;}
                                    
                                    //if (default_locked ^ activated) {new_locked = 1;}
                                    // this will always be true!
                                    
                                    // lock door if satisfy above criteria.
                                    set_door_locked(door, new_locked);
                                
                                }
                                
                                
                                // next elems
                                
                                tmp_key = tmp_exits->exit->key;
                            }
                            
                            else {
                                null_error(EXIT_OBJECT, name);
                            }
                            
                            
                            tmp_exits = tmp_exits->next;
                            if (tmp_exits == NULL) {
                                printf("Room %d.\n", i);
                                null_error(EXIT_LS_OBJECT, name);
                                
                                // break
                                tmp_key = 0;
                                exit_key = 0;
                            }
                        }
                    }
                }
                
                
                // now for analysis of spc_room_entities
                
                if (r->spc_room_entities != NULL) {
                
                    while (r->spc_room_entities->prev != NULL) {
                        r->spc_room_entities = r->spc_room_entities->prev;
                    }
                    
                    Spc_ent_ls* tmp_ent_ls = r->spc_room_entities;
                    
                    while (tmp_ent_ls != NULL) {
                    
                    
                        if (tmp_ent_ls->spc_entity == NULL) {
                            printf("Room %d.\n", i);
                            null_error(SPECIAL_ENTITY_OBJECT, name);
                        }
                        
                        else {
                        
                            // telephone and pop blocks
                            
                            int ent_id = tmp_ent_ls->spc_entity->entity_id;
                            
                            
                            
                            if (ent_id == SPC_TELEPHONE_ID) {
                             
                                int trig_id = get_telephone_trig_id(tmp_ent_ls->spc_entity);
                                if (trig_id > 0) {
                                
                                    trig_id = get_game_trig(g, trig_id);
                                    
                                    
                                    if (trig_id) {
                                        set_telephone_activated(tmp_ent_ls->spc_entity, 1);
                                    }
                                    else {
                                        set_telephone_activated(tmp_ent_ls->spc_entity, 0);
                                    }
                                }
                            }
                            
                            
                            
                            else if (ent_id == SPC_POP_BLOCK_ID) {
                            
                                int trig_id = get_pop_block_trig_id(tmp_ent_ls->spc_entity);
                                if (trig_id > 0) {
                                
                                    int popped = 0;
                                    
                                    trig_id = get_game_trig(g, trig_id);
                                    
                                    
                                    // trig_id and popped block must be 1/0 for XOR to work
                                    
                                    if (trig_id ^ get_pop_block_original_up(tmp_ent_ls->spc_entity)) {
                                        popped = 1;
                                    }
                                    
                                    set_pop_block_up(tmp_ent_ls->spc_entity, popped);
                                }
                            }
                            
                            
                            
                            else if (ent_id == SPC_SWITCH_ID) {
                            
                                int trig_id = get_switch_trig_id(tmp_ent_ls->spc_entity);
                                if (trig_id > 0 &&
                                    (get_switch_type(tmp_ent_ls->spc_entity) == SIMPLE_SWITCH_TYPE)) {
                                
                                    trig_id = get_game_trig(g, trig_id);
                                    
                                    
                                    int closed = get_switch_default_closed(tmp_ent_ls->spc_entity);
                                    
                                    if (closed ^ trig_id) { closed = 1;}
                                    else {closed = 0;}
                                        
                                        
                                    set_switch_closed(tmp_ent_ls->spc_entity, closed);
                                    
                                }
                            }
                            
                            
                            else if (ent_id == SPC_LAMP_ID) {
                            
                                int trig_id = get_lamp_trig_id(tmp_ent_ls->spc_entity);
                                
                                if (trig_id > 0) {
                                
                                    trig_id = get_game_trig(g, trig_id);
                                    
                                    int on = get_lamp_default_on(tmp_ent_ls->spc_entity);
                                    
                                    if (on ^ trig_id) { on = 1;}
                                    else { on = 0;}
                                    
                                    
                                    set_lamp_on(tmp_ent_ls->spc_entity, on);
                                }
                            }
                            
                        }
                    
                    
                    
                        tmp_ent_ls = tmp_ent_ls->next;
                    }
                }
            }
        }
    
    
    
    }
    
    
    
    
    return 0;
}


















int find_switch_type(struct game_t* g, int type, int trig_id, int closed, int count) {

    char name[] = "find_switch_type";
    
    if (g == NULL) {
        game_null_error(name);
        return -1;
    }
    
    int found = 0;
    
    
    
    if (g->room_len > 0) {
        
        if (g->rooms == NULL) {
            null_error("Room pointer array", name);
            return -1;
        }
        
        
        for (int i = 0; i < g->room_len && (!found || count); i++) {
        
            if (g->rooms[i] == NULL) {
                null_error(ROOM_LS_OBJECT, name);
            }
            
            else {
            
                Room* r = g->rooms[i]->room;
                
                if (r == NULL) {
                    room_null_error(name);
                }
                
                else {
                
                    
                    if (r->spc_room_entities != NULL) {
                    
                        
                        // front load
                        while (r->spc_room_entities->prev != NULL) {
                            r->spc_room_entities = r->spc_room_entities->prev;
                        }
                        
                        
                        Spc_ent_ls* tmp_ls = r->spc_room_entities;
                        
                        while (tmp_ls != NULL && (!found || count)) {
                        
                            
                            if (tmp_ls->spc_entity == NULL) {
                                spc_entity_null_error(name);
                            }
                            
                            else {
                            
                                if (tmp_ls->spc_entity->entity_id == SPC_SWITCH_ID) {
                                
                                    ////
                                    ////  MAIN ANALYSIS
                                    ////
                                    
                                    // see whether the trig_id is the same
                                    
                                    if (trig_id == get_switch_trig_id(tmp_ls->spc_entity) ) {
                                    
                                    
                                        // see whether switch type is the same
                                        if (type == get_switch_type(tmp_ls->spc_entity)) {
                                            
                                        
                                            // see whether it is open or closed
                                        
                                            int switch_closed = get_switch_closed(tmp_ls->spc_entity);

                                        
                                            if (closed == switch_closed) {
                                                found += 1;
                                            }
                                        }
                                    }
                                }
                            }
                            
                            tmp_ls = tmp_ls->next;
                        }
                    }
                }
            }
        }
    }
    

    
    return found;
}

# endif
