# ifndef SPECIALISING_IN_ENTITIES__
# define SPECIALISING_IN_ENTITIES__

# include "../Sounds/sounds.c"

// prototypes

//int increment_spc_entity_time(struct game_t*);
//int reset_spc_entity_time(struct game_t*);
// odd idea to reset entity time, hence endless bomb + spinning sword

int increment_spc_bomb_time(struct spc_entity_t*, struct game_t*);
int increment_spc_smoke_time(struct spc_entity_t*);
int increment_spc_sword_time(struct spc_entity_t*, struct game_t*);
int increment_spc_stick_time(struct spc_entity_t*, struct game_t*);
int increment_spc_arrow_time(struct spc_entity_t*, struct game_t*);


// future plans: make it be that enemies / player light cannot see through smoke.





// getters and setters

int get_telephone_ring_id(struct spc_entity_t*);
int set_telephone_ring_id(struct spc_entity_t*, int);
int get_telephone_dist(struct spc_entity_t*);
int set_telephone_dist(struct spc_entity_t*, int);
int get_telephone_trig_id(struct spc_entity_t*);
int set_telephone_trig_id(struct spc_entity_t*, int);
int get_telephone_activated(struct spc_entity_t*);
int set_telephone_activated(struct spc_entity_t*,int);
int get_telephone_trig_activate(struct spc_entity_t*);
int set_telephone_trig_activate(struct spc_entity_t*, int);
int get_telephone_invisible(struct spc_entity_t*);
int set_telephone_invisible(struct spc_entity_t*, int);

int get_push_block_dir(struct spc_entity_t*);
int set_push_block_dir(struct spc_entity_t*, int);
int get_push_block_max_push(struct spc_entity_t*);
int set_push_block_max_push(struct spc_entity_t*, int);
int get_push_block_push_num(struct spc_entity_t*);
int set_push_block_push_num(struct spc_entity_t*, int);
int get_push_block_strength(struct spc_entity_t*);
int set_push_block_strength(struct spc_entity_t*, int);

int get_pop_block_up(struct spc_entity_t*);
int set_pop_block_up(struct spc_entity_t*, int);
int get_pop_block_orginal_up(struct spc_entity_t*);
int set_pop_block_orginal_up(struct spc_entity_t*, int);
int get_pop_block_trig_id(struct spc_entity_t*);
int set_pop_block_trig_id(struct spc_entity_t*, int);

int get_switch_closed(Spc_ent*);
int set_switch_closed(Spc_ent*, int);
int get_switch_trig_id(Spc_ent*);
int set_switch_trig_id(Spc_ent*, int);
int get_switch_default_closed(Spc_ent*) ;
int set_switch_default_closed(Spc_ent*, int);
int get_switch_type(struct spc_entity_t*);
int set_switch_type(struct spc_entity_t*, int);

int get_lamp_trig_id(Spc_ent*);
int set_lamp_trig_id(Spc_ent*, int);
int get_lamp_default_on(struct spc_entity_t*);
int set_lamp_default_on(struct spc_entity_t*, int);
int get_lamp_on(struct spc_entity_t*);
int set_lamp_on(struct spc_entity_t*, int);



int get_arrow_type(Spc_ent*);
int set_arrow_type(Spc_ent*, int);




//errors;

int spc_entity_null_error(char* function) {
    return null_error(SPECIAL_ENTITY_OBJECT, function);
}

int spc_entity_ls_null_error(char* function) {
    return null_error(SPECIAL_ENTITY_LS_OBJECT, function);
}






int clean_up_spc_entities(struct room_t*, int);



////////////////////////////////////////////////


// incrmenet the time of all the special entities in the room, compute actions and decay.

int increment_spc_entity_time(struct game_t* g) {

    if (g == NULL) {
        null_error(GAME_OBJECT, "increment_spc_entity_time");
        return 1;
    }
    
    if (g->player == NULL) {
        null_error(PLAYER_OBJECT, "increment_spc_entity_time");
        return 1;
    }
    
    Room* r = g->player->room;
    if (r == NULL) {
        room_null_error("increment_spc_entity_time");
        return 1;
    }

    
    // see whether there are any entities to increment.
    
    if (r->spc_weapon_entities != NULL) {
    
        // make sure first in que
        while (r->spc_weapon_entities->prev != NULL) {
            r->spc_weapon_entities = r->spc_weapon_entities->prev;
        }
        
        
        Spc_ent_ls* s_ent = r->spc_weapon_entities;
        
        while (s_ent != NULL) {
        
            if (s_ent->spc_entity == NULL) {
                spc_entity_null_error("increment_spc_entity_time");
            }
            
            else {
                
                if (s_ent->spc_entity->wait_update) {
                
                    s_ent->spc_entity->wait_update = 0;
                
                }
                
                else {
                    int e_id = s_ent->spc_entity->entity_id;
                
                    if (e_id == SPC_SMOKE_ID) {
                        increment_spc_smoke_time(s_ent->spc_entity);
                    }
                
                    else if (e_id == SPC_STICK_ID) {
                        increment_spc_stick_time(s_ent->spc_entity, g);
                    }
                
                
                    else if (e_id == SPC_SWORD_ID) {
                        increment_spc_sword_time(s_ent->spc_entity, g);
                    }
                
                    else if (e_id == SPC_BOMB_ID) {
                        increment_spc_bomb_time(s_ent->spc_entity, g);
                    }
                
                    else if (e_id == SPC_ARROW_ID) {
                        increment_spc_arrow_time(s_ent->spc_entity, g);
                    }

                
                    else {
                        printf("ERROR: unknown special entity with id: %d\n", e_id);
                        pause_function();
                        s_ent->spc_entity->base.timer = 0;
                    }
                }
            }
            
            s_ent = s_ent->next;
        }
    
        
        clean_up_spc_entities(r, 1);
        
        //clean_up_spc_entities(r, 0);
        
    }
    return 0;
}

















int clean_up_spc_entities(struct room_t* r, int weapon) {

    // clean up all the special entities who's timers have reached zero
    // if below zero, save them
    
    Spc_ent_ls* s_ent;
    Spc_ent_ls* tmp_ls;
    
    if (weapon) {
        s_ent = r->spc_weapon_entities;
        tmp_ls = r->spc_weapon_entities;
    }
    
    else {
        s_ent = r->spc_room_entities;
        tmp_ls = r->spc_room_entities;
    }
    
    int prev_temp = 0;
    
    
    
    
    while (s_ent != NULL) {
        int free_ptr = 0;
        
        if (!prev_temp) {
            // which it should do on the first run.
            
            
            if (s_ent->spc_entity != NULL) {
                if (s_ent->spc_entity->base.timer == 0) {
                    free_ptr = 1;
                }
                
                else if (s_ent->spc_entity->wait_update) {
                    if (s_ent->spc_entity->entity_id == SPC_BOMB_ID) {
                        s_ent->spc_entity->wait_update = 0;
                    }
                }
            }
            else {
                free_ptr = 1;
            }
            
            
            if (free_ptr) {
                kill_special_entity(r, s_ent, weapon);
                
                if (weapon) {
                    s_ent = r->spc_weapon_entities;
                }
                else {
                    s_ent = r->spc_room_entities;
                }
            }
            
            else {
                prev_temp = 1;
                tmp_ls = s_ent;
                s_ent = s_ent->next;
            }
            
        }
        
        
        
        
        else {
            // this implies that there is a previous pointer to point to:
            
            if (s_ent->spc_entity != NULL) {
                if (s_ent->spc_entity->base.timer == 0) {
                    free_ptr = 1;
                }
                
                else if (s_ent->spc_entity->wait_update) {
                    if (s_ent->spc_entity->entity_id == SPC_BOMB_ID) {
                        s_ent->spc_entity->wait_update = 0;
                    }
                }
                
            }
            else {
                free_ptr = 1;
            }
            
            
            if (free_ptr) {
                kill_special_entity(r, s_ent, weapon);
                s_ent = tmp_ls->next;
            }
            
            else {
                tmp_ls = s_ent;
                s_ent = s_ent->next;
            }
        }
    }
    
    
    return 0;
}









///////////////////////////////////////////////////////////


int reset_spc_room_entities(struct player_t* p) {

    char name[] = "reset_spc_room_entities";

    if (p == NULL) {
        null_error(PLAYER_OBJECT, name);
        return 1;
    }
    
    if (p->room == NULL) {
        room_null_error(name);
        return 1;
    }
    
    Room* r = p->room;
    
    if (r->spc_room_entities != NULL) {
    
        while (r->spc_room_entities->prev != NULL) {
            r->spc_room_entities = r->spc_room_entities->prev;
        }
        
        Spc_ent_ls* tmp_ls = r->spc_room_entities;
        
        while (tmp_ls != NULL) {
        
            if (tmp_ls->spc_entity == NULL) {
                null_error(SPECIAL_ENTITY_OBJECT, name);
            }
            
            else {
                int ent_id = tmp_ls->spc_entity->entity_id;
                
                
                if (ent_id == SPC_FLAG_ID) {
                    tmp_ls->spc_entity->base.health = 1;
                }
                
                else if (ent_id == SPC_TELEPHONE_ID) {
                    tmp_ls->spc_entity->base.health = 1;
                }
                
                else if (ent_id == SPC_PUSH_BLOCK_ID) {
                    tmp_ls->spc_entity->base.x = tmp_ls->spc_entity->base.vel_x;
                    tmp_ls->spc_entity->base.y = tmp_ls->spc_entity->base.vel_y;
                    
                    set_push_block_push_num(tmp_ls->spc_entity,
                                            get_push_block_max_push(tmp_ls->spc_entity));
                }
                
                else if (ent_id == SPC_SWITCH_ID) {
                    /*
                    set_switch_open(tmp_ls->spc_entity,
                                    get_switch_default_open(tmp_ls->spc_entity));
                     */
                    // currently, when exiting a room etc, switches will not reset since triggers
                    // do not reset, hence possibly confusing for those who play the game.
                }
            }
            tmp_ls = tmp_ls->next;
        }
    }



    return 0;
}

























///////////////////////////////////////////////////////////


// main time increment functions:



int increment_spc_bomb_time(struct spc_entity_t* e, struct game_t* g) {

    if (e == NULL) {
        spc_entity_null_error("increment_spc_bomb_time");
        return 1;
    }
    if (g->player->room == NULL) {
        room_null_error("increment_spc_bomb_time");
        return 1;
    }
    
    if(e->base.timer > 0) {
        e->base.timer -= 1;
    }
    
    if (e->base.timer <= 0) {
        
        explode_sound();
        
        // find the max,min x,y to scroll through the manhattan metrics
        // damage drops linearly with distance (light_dist);
        
        int base_x = e->base.x;
        int base_y = e->base.y;
        
        int max_x = base_x + e->base.light_dist;
        int max_y = base_y + e->base.light_dist;
        int min_x = base_x - e->base.light_dist;
        int min_y = base_y - e->base.light_dist;
        
        //printf("x,y: %x,%d,  min_x,min_y: %d,%d,  max_x,max_y: %d,%d\n",
               //base_x, base_y, min_x, min_y, max_x, max_y);
        
        if (min_x < 0) { min_x = 0;}
        if (min_y < 0) { min_y = 0;}
        if (max_x >= g->player->room->width) { max_x = g->player->room->width-1;}
        if (max_y >= g->player->room->height) { max_y = g->player->room->height-1;}
        
        
        
        // now we have the square to compute the manhattan metric in.
        for (int i = min_y; i <= max_y; i++) {
        
            for (int j = min_x; j <= max_x; j++) {
            
                
                // see whether the squares being tested are inside the manhattan metric.
                // that is, inside the light_dist bomb radius.
                
                int dist = manhattan_metric(base_x, base_y, j, i);
                if (dist <= e->base.light_dist) {
                
                    
                    // explode bomb:
                    weapon_damage(g, j, i, e->base.health - dist, e->player_id, BLAST_DMG);
                
                    
                    // turn radius to smoke if time == zero
                
                    if (e->base.timer == 0) {
                        
                        
                        if (j == base_x && i == base_y) {
                            //e->base.timer = BOMB_SMOKE_LINGER;
                            // this is causing the above boolean expression to fail after reaching centre point
                            
                            e->entity_id = SPC_SMOKE_ID;
                        }
                        
                        
                        else if (BOMB_SMOKE_LINGER > 0) {
                            
                            // create new special entities
                            Spc_ent* tmp_spc_ent = allocate_special_entity(1);
                            
                            tmp_spc_ent->entity_id = SPC_SMOKE_ID;
                            tmp_spc_ent->base.timer = BOMB_SMOKE_LINGER;
                            
                            tmp_spc_ent->base.x = j;
                            tmp_spc_ent->base.y = i;
                            tmp_spc_ent->base.health = 1;
                            
                            
                            if (g->player->room->spc_weapon_entities == NULL) {
                                g->player->room->spc_weapon_entities =
                                push_special_entity_end(NULL, tmp_spc_ent);
                            }
                            else {
                                push_special_entity_end(g->player->room->spc_weapon_entities, tmp_spc_ent);
                            }
                        }
                    
                    }
                }
            
            }
        }
        if (e->base.timer == 0) {
            e->base.timer = BOMB_SMOKE_LINGER;
        }
    }

    return 0;
}









int increment_spc_smoke_time(struct spc_entity_t* e) {

    if (e == NULL) {
        spc_entity_null_error("increment_spc_smoke_time");
        return 1;
    }
    
    e->base.timer -= 1;
    
    return 0;
}









int increment_spc_sword_time(struct spc_entity_t* e, struct game_t* g) {
    
    if (e == NULL) {
        spc_entity_null_error("increment_spc_sword_time");
        return 1;
    }
    if (g->player->room == NULL) {
        room_null_error("increment_spc_sword_time");
        return 1;
    }
    
    int hit;
    hit = weapon_damage(g, e->base.x, e->base.y, e->base.health, e->player_id, SWORD_DMG);
    
    if (hit < 0) {
        e->base.timer = 0;
        return 0;
    }
    
    e->base.timer -= 1;
    
    
    
    // move entitiy based on current direction
    /*
     107
     2@6
     345
     */
    // hence odd directions are corner pieces and will turn left
    int cur_dir = e->base.direction;
    
    if (e->base.eyesight == 0) {
        
        int move_dir;
        
        if (cur_dir % 2 == 0) {
    
            // even
            // moving anti-clockwise
            move_dir = (cur_dir / 2) + 1;
            move_dir = move_dir % 4;
        }
        
        else {
        
            // odd
            // turn left
            move_dir = (cur_dir + 3) / 2;
            move_dir = move_dir % 4;
        }
        
        
        int tmp_x = e->base.x;
        int tmp_y = e->base.y;
        
        dir_to_xy(move_dir, &tmp_x, &tmp_y);
        
        if (tmp_x < 0 || tmp_y < 0 || tmp_x >= g->player->room->width ||
            tmp_y >= g->player->room->height)
        {
            e->base.timer = 0; // hence force despawn.
        }
        
        else {
            e->base.x = tmp_x;
            e->base.y = tmp_y;
            
            cur_dir++;
            cur_dir = cur_dir % 8;
            e->base.direction = cur_dir;
        }
    }
    

    
    else {
        printf("ERROR: undefined 'eyesight' value for sword special entity, 'increment_spc_sword_time'.\n");
        pause_function();
        return 1;
    }
    
    return 0;
}






int increment_spc_stick_time(struct spc_entity_t* e, struct game_t* g) {
    
    if (e == NULL) {
        spc_entity_null_error("increment_spc_stick_time");
        return 1;
    }
    if (g->player->room == NULL) {
        room_null_error("increment_spc_stick_time");
        return 1;
    }
    int hit;
    hit = weapon_damage(g, e->base.x, e->base.y, e->base.health, e->player_id, SWORD_DMG);
    
    if (hit < 0) {
        e->base.timer = 0;
        return 0;
    }
    
    e->base.timer -= 1;
    
    return 0;
}







int increment_spc_arrow_time(struct spc_entity_t* e, struct game_t* g) {
    
    char name[] = "increment_spc_arrow_time";
    
    if (e == NULL) {
        spc_entity_null_error(name);
        return 1;
    }
    if (g->player->room == NULL) {
        room_null_error(name);
        return 1;
    }
    

    
    int hit;
    int arrow_dmg = e->base.health;
    if (get_arrow_type(e) == BOMB_ARROW_TYPE) {
        arrow_dmg = 0;
    }
    
    hit = weapon_damage(g, e->base.x, e->base.y, arrow_dmg, e->player_id, ARROW_DMG);
    
    
    int explode = 0;
    if (hit < 0) {
        explode = 1;
    }
    
    else {
    
        // assume not hit anything, hence incrmenent place
        int new_x = e->base.x;
        int new_y = e->base.y;
        
        increment_entity_move(&(e->base), g->player->room, &new_x, &new_y);
        
        
        if (entity_room_collide(&(e->base), g->player->room, new_x, new_y)) {
            
            // set explode to 1.
            explode = 1;
            
            // now see if collided with any spc_room_entities
            weapon_hit_spc_room_entities(g, new_x, new_y, arrow_dmg,
                                         e->player_id, ARROW_DMG);
        }
        
        else {
            e->base.x = new_x;
            e->base.y = new_y;
        }
    }
    
    
    
    
    if (explode) {
        e->base.timer = 0;
        
        
        if (get_arrow_type(e) == BOMB_ARROW_TYPE) {
            // setup bomb to explode.
            
            // initialise bomb arrow bomb:
            
            Spc_ent* s_ent = allocate_special_entity(1);
            s_ent->entity_id = SPC_BOMB_ID;
            
            s_ent->base.fly = 0;
            set_entity_clip(&(s_ent->base), 1);
            
            
            s_ent->base.x = e->base.x;
            s_ent->base.y = e->base.y;
            
            // set to 1 so it explodes imediately / on next turn
            // should append to end of spc_weapon_entities list, hence explode immediately!!!
            
            s_ent->player_id = 1;
            s_ent->base.health = SIMPLE_BOMB_DAMAGE;
            s_ent->base.timer = 1; // explode immediately
            s_ent->base.light_dist = 1;
            
            s_ent->wait_update = 0;
            
            // now put item onto queue
            g->player->room->spc_weapon_entities = push_special_entity_end(
                                                   g->player->room->spc_weapon_entities, s_ent);
            

        }
    }
    
    return 0;
}












// suppose a switch type object is hit, activate it!


int activate_switch(struct spc_entity_t* e, struct game_t* g) {

    char name[] = "activate_swtich";
    
    if (g == NULL) {
        game_null_error(name);
        return 1;
    }
    if (e == NULL) {
        spc_entity_null_error(name);
        return 1;
    }
    
    
    int activated = get_switch_closed(e);
    
    if (activated) {
        activated = 0;
    }
    
    else {
        activated = 1;
    }
    

    set_switch_closed(e, activated);
    
    
    int trig_id = get_switch_trig_id(e);
    if ( trig_id > 0) {

        set_game_trig(g, trig_id, activated, get_switch_type(e));

        // blocks are updated automatically.
    }
    
    return 0;
}











/////////////////





// telephone getters and setters.


int get_telephone_ring_id(Spc_ent* e) {
    if (e == NULL) {
        spc_entity_null_error("get_telephone_ring_id");
        return -1;
    }
    
    return e->base.eyesight;
}

int set_telephone_ring_id(Spc_ent* e, int ring_id) {
    if (e == NULL) {
        spc_entity_null_error("set_telephone_ring_id");
        return 1;
    }
    
    e->base.eyesight = ring_id;
    return 0;
}




int get_telephone_dist(Spc_ent* e) {
    if (e == NULL) {
        spc_entity_null_error("get_telephone_dist");
        return -1;
    }
    
    return e->base.light_dist;
}

int set_telephone_dist(Spc_ent* e, int dist) {
    if (e == NULL) {
        spc_entity_null_error("set_telephone_dist");
        return 1;
    }
    
    e->base.light_dist = dist;
    return 0;
}




int get_telephone_trig_id(Spc_ent* e) {
    if (e == NULL) {
        spc_entity_null_error("get_telephone_trig_id");
        return -1;
    }
    
    return e->base.mana;
}

int set_telephone_trig_id(Spc_ent* e, int trigger) {
    if (e == NULL) {
        spc_entity_null_error("set_telephone_trig_id");
        return 1;
    }
    
    e->base.mana = trigger;
    return 0;
}




// returns the trigger id in which the telephone will activate if the telephone is used.

int get_telephone_trig_activate(Spc_ent* e) {
    if (e == NULL) {
        spc_entity_null_error("get_telephone_trig_active");
        return -1;
    }
    
    return e->base.max_mana;
}

int set_telephone_trig_activate(Spc_ent* e, int trig_id) {
    if (e == NULL) {
        spc_entity_null_error("set_telephone_trig_active");
        return 1;
    }
    
    e->base.max_mana = trig_id;
    return 0;
}




int get_telephone_invisible(Spc_ent* e) {
    if (e == NULL) {
        spc_entity_null_error("get_telephone_invisible");
        return -1;
    }
    
    return e->base.direction;
}

int set_telephone_invisible(Spc_ent* e, int b) {
    if (e == NULL) {
        spc_entity_null_error("set_telephone_invisible");
        return 1;
    }
    
    e->base.direction = b;
    return 0;
}




int get_telephone_activated(struct spc_entity_t* e) {
    
    if (e == NULL) {
        spc_entity_null_error("get_telephone_activated");
        return -1;
    }
    if (e->base.max_health) {
        return 1;
    }
    else {
        return 0;
    }
}

int set_telephone_activated(struct spc_entity_t* e, int b) {

    if (e == NULL) {
        spc_entity_null_error("set_telephone_activated");
        return 1;
    }
    
    if (b) {
        e->base.max_health = 1;
    }
    else {
        e->base.max_health = 0;
    }
    return 0;
}






// push block getters and setters

int get_push_block_dir(Spc_ent* e) {
    if (e == NULL) {
        spc_entity_null_error("get_push_block_dir");
        return -1;
    }
    
    return e->base.direction;
}

int set_push_block_dir(Spc_ent* e, int dir) {
    if (e == NULL) {
        spc_entity_null_error("set_push_block_dir");
        return 1;
    }
    
    e->base.direction = dir % 16;
    return 0;
}



int get_push_block_max_push(Spc_ent* e) {
    if (e == NULL) {
        spc_entity_null_error("get_push_block_max_push");
        return -1;
    }
    
    return e->base.max_mana;
}

int set_push_block_max_push(Spc_ent* e, int push) {
    if (e == NULL) {
        spc_entity_null_error("set_push_block_max_push");
        return 1;
    }
    
    e->base.max_mana = push;
    return 0;
}




int get_push_block_push_num(Spc_ent* e) {
    if (e == NULL) {
        spc_entity_null_error("get_push_block_push_num");
        return -1;
    }
    
    return e->base.mana;
}

int set_push_block_push_num(Spc_ent* e, int push) {
    if (e == NULL) {
        spc_entity_null_error("set_push_block_push_num");
        return 1;
    }
    
    e->base.mana = push;
    return 0;
}



int get_push_block_strength(Spc_ent* e) {
    if (e == NULL) {
        spc_entity_null_error("get_push_block_strength");
        return -1;
    }
    
    return e->base.eyesight;
}

int set_push_block_strength(Spc_ent* e, int strength) {
    if (e == NULL) {
        spc_entity_null_error("set_push_block_strength");
        return 1;
    }
    
    e->base.eyesight = strength;
    return 0;
}





///////////////////////////////////////////

// POP BLOCK

int get_pop_block_up(Spc_ent* e) {
    if (e == NULL) {
        spc_entity_null_error("get_pop_block_up");
        return -1;
    }
    
    return e->base.mana;
}

int set_pop_block_up(Spc_ent* e, int type) {
    if (e == NULL) {
        spc_entity_null_error("set_pop_block_up");
        return 1;
    }
    
    e->base.mana = type;
    return 0;
}




int get_pop_block_original_up(Spc_ent* e) {
    if (e == NULL) {
        spc_entity_null_error("get_pop_block_original_up");
        return -1;
    }
    
    return e->base.eyesight;
}

int set_pop_block_original_up(Spc_ent* e, int type) {
    if (e == NULL) {
        spc_entity_null_error("set_pop_block_original_up");
        return 1;
    }
    
    e->base.eyesight = type;
    return 0;
}



int get_pop_block_trig_id(Spc_ent* e) {
    if (e == NULL) {
        spc_entity_null_error("get_pop_block_trig_id");
        return -1;
    }
    
    return e->base.max_mana;
}

int set_pop_block_trig_id(Spc_ent* e, int trig_id) {
    if (e == NULL) {
        spc_entity_null_error("set_pop_block_trig_id");
        return 1;
    }
    
    e->base.max_mana = trig_id;
    return 0;
}






//////////////////////////////////////////////////////////////

int get_switch_closed(Spc_ent* e) {
    if (e == NULL) {
        spc_entity_null_error("get_switch_closed");
        return -1;
    }
    return e->base.eyesight;
}

int set_switch_closed(Spc_ent* e, int b) {
    if (e == NULL) {
        spc_entity_null_error("set_switch_closed");
        return 1;
    }
    if (b)  {
        e->base.eyesight = 1;
    }
    else {
        e->base.eyesight = 0;
    }
    return 0;
}




int get_switch_default_closed(Spc_ent* e) {
    if (e == NULL) {
    spc_entity_null_error("get_switch_default_closed");
    return -1;
}
    return e->base.light_dist;
}

int set_switch_default_closed(Spc_ent* e, int b) {
    if (e == NULL) {
        spc_entity_null_error("set_switch_default_closed");
        return 1;
    }
    if (b)  {
        e->base.light_dist = 1;
    }
    else {
        e->base.light_dist = 0;
    }
    return 0;
}





int get_switch_trig_id(Spc_ent* e) {
    if (e == NULL) {
        spc_entity_null_error("get_switch_trig_id");
        return -1;
    }
    return e->base.direction;
}

int set_switch_trig_id(Spc_ent* e, int trig_id) {
    if (e == NULL) {
        spc_entity_null_error("set_switch_trig_id");
        return 1;
    }
    e->base.direction = trig_id;
    return 0;
}



int get_switch_type(struct spc_entity_t* e) {
    if (e == NULL) {
        spc_entity_null_error("get_swtich_type");
        return -1;
    }
    
    return e->base.fly;
}

int set_switch_type(struct spc_entity_t* e, int type) {
    if (e == NULL) {
        spc_entity_null_error("set_switch_type");
        return 1;
    }
    
    
    if (type == AND_TYPE) {;}
    
    else if (type == OR_TYPE) {;}
    
    else if (type == XOR_TYPE) {;}
    
    else if (type == NOR_TYPE) {;}
    
    else if (type == NAND_TYPE) {;}
    
    else if (type == XNOR_TYPE) {;}
    
    else if (type == EQUALITY_TYPE) {;}
    
    else {
        type = SIMPLE_SWITCH_TYPE;
    }
    
    e->base.fly = type;
    return 0;
}















int get_lamp_trig_id(Spc_ent* e) {
    if (e == NULL) {
        spc_entity_null_error("get_lamp_trig");
        return -1;
    }
    return e->base.max_mana;
}


int set_lamp_trig_id(Spc_ent* e, int trig_id) {
    if (e == NULL) {
        spc_entity_null_error("set_lamp_trig_id");
        return 1;
    }
    
    e->base.max_mana = trig_id;
    return 0;
}




int get_lamp_default_on(struct spc_entity_t* e) {
    if (e == NULL) {
        spc_entity_null_error("get_lamp_default_on");
        return -1;
    }
    
    return e->base.direction;
}


int set_lamp_default_on(struct spc_entity_t* e, int on) {
    if (e == NULL) {
        spc_entity_null_error("set_lamp_default_on");
        return 1;
    }
    
    if (on) {
        e->base.direction = 1;
    }
    
    else {
        e->base.direction = 0;
    }
    return 0;
}




int get_lamp_on(struct spc_entity_t* e) {
    if (e == NULL) {
        spc_entity_null_error("get_lamp_on");
        return -1;
    }
    
    return e->base.mass;
}


int set_lamp_on(struct spc_entity_t* e, int on) {
    if (e == NULL) {
        spc_entity_null_error("set_lamp_on");
        return 1;
    }
    
    if (on) {
        e->base.mass = 1;
    }
    
    else {
        e->base.mass = 0;
    }
    return 0;
}








//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////


//////  WEAPON SPECIAL ENTITY GETTERS / SETTERS FUNCTIONS.


int get_arrow_type(Spc_ent* e) {

    if (e == NULL) {
        spc_entity_null_error("get_arrow_type");
        return -1;
    }
    
    return e->base.mana;
}


            
            
int set_arrow_type(Spc_ent* e, int type) {

    char name[] = "set_arrow_type";
    
    if (e == NULL) {
        spc_entity_null_error(name);
        return 1;
    }
    
    if (type == BASIC_ARROW_TYPE) {;}
    
    else if (type == BOMB_ARROW_TYPE) {;}
    
    
    else {
        printf("VALUE ERROR: unknown arrow type: %d, for function: '%s'\n.", type, name);
        type = BASIC_ARROW_TYPE;
    }
    
    
    
    e->base.mana = type;
    return 0;
}









//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////




int connect_spc_ent_pos(struct room_t* r, int ent_id, int tile_id, char tile_val,
                        char* obj_name, int vel) {

    char name[] = "connect_spc_ent_pos";
    
    if (r == NULL) {
        room_null_error(name);
        return 1;
    }
    
    
    Spc_ent_ls* tmp_ls = r->spc_room_entities;
    int x = 0, y = 0;
    
    
    
    // sort through all the telephones first
    
    while (tmp_ls != NULL) {
        
        
        int found_ent = 0;
        while (!found_ent && tmp_ls != NULL) {
            if (tmp_ls->spc_entity == NULL) {
                spc_entity_null_error(name);
            }
            
            else {
                if (tmp_ls->spc_entity->entity_id == ent_id) {
                    found_ent = 1;
                    
                }
                
                else {
                    tmp_ls = tmp_ls->next;
                }
            }
        }
        
        
        
        if (found_ent) {
            
            found_ent = 1;
            char tile = get_room_tile(r, x, y);
            
            while (tile != tile_id) {
                
                x++;
                if (x == r->width) {
                    y++;
                    x = 0;
                    if (y == r->height) {
                        found_ent = 0;
                        break;
                    }
                }
                tile = get_room_tile(r, x, y);
            }
            
            
            
            if (found_ent) {
                tmp_ls->spc_entity->base.x = x;
                tmp_ls->spc_entity->base.y = y;
                if (vel) {
                    tmp_ls->spc_entity->base.vel_x = x;
                    tmp_ls->spc_entity->base.vel_y = y;
                }
                
                
                // now remove the special entity from the room and set it to floor tile.
                set_room_tile(r, x, y, FLOOR_N);
                
                
                // now to not count the same pointer twice, move onto the next pointer
                tmp_ls = tmp_ls->next;
            }
            
            
            
            else {
                printf("WARNING: no '%s' with tile '%c', found in room layout\n",
                       obj_name, tile_val);
                pause_function();
                kill_special_entity(r, tmp_ls, 0);
                tmp_ls = NULL;
            }
            
        }
    }
    return 0;
}












int find_special_entities(struct room_t* r, int* telephone, int* pop_block, int* push_block,
                          int* switch_block, int* lamp) {

    char name[] = "find_special_entities";
    
    if (r == NULL) {
        room_null_error(name);
        return 1;
    }
    
    if (telephone == NULL || pop_block == NULL || push_block == NULL || switch_block == NULL
        || lamp == NULL) {
        null_error("Int Pointer", name);
        return 1;
    }
    
    *telephone = 0;
    *pop_block = 0;
    *push_block = 0;
    *switch_block = 0;
    *lamp = 0;
    
    
    if (r->spc_room_entities != NULL) {
    
        while (r->spc_room_entities->prev != NULL) {
            r->spc_room_entities = r->spc_room_entities->prev;
        }
        
        Spc_ent_ls* tmp_ls = r->spc_room_entities;
        
        
        while (tmp_ls != NULL) {
        
            if (tmp_ls->spc_entity == NULL) {
                spc_entity_null_error(name);
            }
            
            
            else {
            
                int ent_id = tmp_ls->spc_entity->entity_id;
                
                
                // now see whether any of the above exist
                
                if (ent_id == SPC_TELEPHONE_ID) {
                    if (! *telephone) { *telephone = 1;}
                }
                
                
                else if (ent_id == SPC_PUSH_BLOCK_ID) {
                    if (! *push_block) {*push_block = 1;}
                }
            
                
                else if (ent_id == SPC_POP_BLOCK_ID) {
                    if (! *pop_block) { *pop_block = 1;}
                }
                
                
                else if (ent_id == SPC_SWITCH_ID) {
                    if (! *switch_block) {*switch_block = 1;}
                }
                
                
                else if (ent_id == SPC_LAMP_ID) {
                    if (! *lamp) {*lamp = 1;}
                }
            }
            
        
            tmp_ls = tmp_ls->next;
        }
    }
    

    return 0;
}











/////////////////////////////////////////////


// main



// given special entities set up for each room, find the x,y values and turn into floor tiles

int connect_special_entities(struct game_t* g) {

    char name[] = "connect_special_entities";
    
    if (g == NULL) {
        null_error(GAME_OBJECT, name);
        return 1;
    }
    
    
    if (g->room_len > 0) {
    
        if (g->rooms == NULL) {
            null_error("Room_ls Pointer", name);
            return 1;
        }
        
        
        
        for (int i = 0; i < g->room_len; i++) {
        
            Room_ls* r_ls= g->rooms[i];
            
            if (r_ls == NULL) {
                null_error(ROOM_LS_OBJECT, name);
            }
        
            
            
            else {
                Room* r = r_ls->room;
                
                if (r == NULL) {
                    room_null_error(name);
                }
                
                
                else if (r->spc_room_entities != NULL) {
                    
                    // ANALYSIS BEGINS HERE!
                    
                    
                    while (r->spc_room_entities->prev != NULL) {
                        r->spc_room_entities = r->spc_room_entities->prev;
                    }
                    
                    // do a preliminary check to see if there any member of certain special
                    // entity types
                    
                    int telephone = 0, pop_block = 0, push_block = 0, switch_block = 0, lamp = 0;
                    
                    find_special_entities(r, &telephone, &pop_block, &push_block, &switch_block,
                                          &lamp);
                    
                    
                    // first connect the telephones
                    
                    if (telephone) {
                        connect_spc_ent_pos(r, SPC_TELEPHONE_ID, TELEPHONE_N,
                                            TELEPHONE_T, "Telephone", 0);
                    }
                    
                    
                    if (pop_block) {
                        connect_spc_ent_pos(r, SPC_POP_BLOCK_ID, POP_BLOCK_UP_N, POP_BLOCK_T,
                                            "Pop block", 0);
                    }
                    
                    
                    // then sort through the push blocks
                    if (push_block) {
                        connect_spc_ent_pos(r, SPC_PUSH_BLOCK_ID, PUSH_BLOCK_N, PUSH_BLOCK_T,
                                            "Push block", 1);
                    }
                    
                    
                    if (switch_block) {
                        connect_spc_ent_pos(r, SPC_SWITCH_ID, OPEN_SWITCH_N, SWITCH_T, "Switch", 0);
                    }
                    
                    
                    if (lamp) {
                        connect_spc_ent_pos(r, SPC_LAMP_ID, LAMP_OFF_N, LAMP_T, "Lamp", 0);
                    }
                }
            }

        }
    }
    
    
    return 0;
}


# endif
