# ifndef ENEMY_METH__
# define ENEMY_METH__

int get_enemy_room_clip_array(struct enemy_t*, char*, struct room_t*);



///////////////////////////////////////////////////////////////

///// movement
/*
int move_enemy_up(struct enemy_t* e) {
    return move_entity_up(&(e->base));
}

int move_enemy_left(struct enemy_t* e) {
    return move_entity_left(&(e->base));
}

int move_enemy_down(struct enemy_t* e) {
    return move_entity_down(&(e->base));
}

int move_enemy_right(struct enemy_t* e) {
    return move_entity_right(&(e->base));
}*/


int move_enemy_direction(struct enemy_t* e, int dir, struct player_t* p) {
    char name[] = "move_enemy_direction";
    
    if (e == NULL) {
        enemy_null_error(name);
        return -1;
    }
    if (p == NULL) {
        player_null_error(name);
        return -1;
    }
    if (p->room == NULL) {
        room_null_error(name);
        return -1;
    }
    
    else {

        
        int tmp_x = e->base.x;
        int tmp_y = e->base.y;
        int blocked = 0;
        

        dir_to_xy(dir, &tmp_x, &tmp_y);

        
        if (get_ai_scared(e->ai)) {
            
            if (!e->base.fly) {
                if (entity_room_tile_collide(&(e->base), p->room, HOLE_N,
                                             tmp_x, tmp_y, NULL, NULL)) {
                blocked =  1;
                e->base.health = 0;
                }
            }
            
            if (!blocked && entity_room_tile_collide(&(e->base), p->room, SPIKE_N,
                                                     tmp_x, tmp_y, NULL, NULL)) {
                blocked =  1;
            }
            
        }
        
        
        
        // calculate if hit player, if so don't move and deal damage.


        if (entity_entity_collide(&(e->base), tmp_x, tmp_y, &(p->base)) && !blocked) {
            
            // DEAL DAMAGE
            
            player_damage(p, e->touch_dmg);
            
            if (e->enemy_id == ORB_ID) {
                return 1;
            }
            else {
                return 0;
            }
            
        }
        
        if (!blocked) {
            // use pre-defined entity move, to move the player, and see if collide with
            // room, plus move depending on x,y velocities
            
            blocked = entity_move(&(e->base), p->room, dir);
        }

        
        return blocked;
    }
}











///////////////////////////////////////////////////////////////


int set_enemy_light_dist(Enemy* e, int d) {
    if (e == NULL) {
        enemy_null_error("set_enemy_light_dist");
        return 1;
    }
    
    return set_entity_light_dist(&(e->base), d);
}

int get_enemy_light_dist(Enemy* e) {
    if (e == NULL) {
        enemy_null_error("get_enemy_light_dist");
        return -1;
    }
    return get_entity_light_dist(&(e->base));
}








//////////////////////////////////////////////////////////

// use entity eyesight methods, to see if the enemy sees the player

int enemy_sees_player(struct enemy_t* e, struct player_t* p) {
    if (p == NULL) {
        player_null_error("enemy_sees_player");
        return -1;
    }
    if (e == NULL) {
        enemy_null_error("enemy_sees_player");
        return -1;
    }
    return entity_eyesight(&(e->base), p->base.x, p->base.y);
}








int enemy_sees_player_room(struct enemy_t* e, struct player_t* p, struct room_t* r) {
   char name[] = "enemy_sees_player";
    
    if (r == NULL) {
        room_null_error(name);
        return -1;
    }
    if (e == NULL) {
        enemy_null_error(name);
        return 1;
    }
    if (p == NULL) {
        player_null_error(name);
        return -1;
    }
    
    int dir = 0;
    

    
    
    
    if (entity_eyesight(&(e->base), p->base.x, p->base.y) > 0) {
        // implies true and no errors;
        
        
        // set position if don't known where player is else, memory
        if (e->player_x < 0 && e->player_y < 0) {
            e->player_x = p->base.x;
            e->player_y = p->base.y;
        }
        
        
        
        
        
        // given enemy ai, define the temporary ai function.
        char tmp_array[r->width * r->height];
        
        get_enemy_room_clip_array(e, tmp_array, r);
        
        
        //  dir refers to which direction, 1,2,3,4,5 <==> W,A,S,D,same
        dir = simple_clear_path(tmp_array, r->width, r->height, e->base.x, e->base.y,
                                e->player_x, e->player_y);//p->base.x, p->base.y);
        
        
        if (dir == NO_DIR + 1) {
            e->player_x = -1;
            e->player_y = -1;
        }
    }
    
    
    return dir;
}










/////////

// damage and healing

int enemy_damage(struct enemy_t* e, int d) {

    if (e == NULL) {
        enemy_null_error("enemy_damage");
        return 1;
    }
    
    e->base.health = e->base.health - d;
    
    return 0;
}







int enemy_heal(struct enemy_t* e, int h){

    int error;
    error = enemy_absolute_heal(e, h);
    
    if (error) {
        return error;
    }
    
    if (e->base.health > e->base.max_health) {
        e->base.health = e->base.max_health;
    }
    
    return 0;
}






int enemy_absolute_heal(struct enemy_t* e, int h) {

    if (e == NULL) {
        enemy_null_error("enemy_absolute_heal");
        return 1;
    }
    
    e->base.health += h;
    return 0;
}




Enemy_ls* kill_enemy_ls(struct e_list* e_ls, struct room_t* r) {

    if (e_ls == NULL) {
        null_error(ENEMY_LS_OBJECT, "kill_enemy_ls");
        return NULL;
    }
    
    Enemy_ls* tmp_ls = e_ls->next;
    kill_enemy(r, e_ls);
    
    return tmp_ls;
}










/////////////////////////////////////////

////
////    MEATY FUNCTION  ---  transform the room into binary tiles, whether clip / no-clip


int blacken_entity_pos(struct entity_t*, struct entity_t*, char*, struct room_t*);


int get_enemy_room_clip_array(struct enemy_t* e, char* tmp_array, struct room_t* r) {

    char name[] = "get_enemy_room_clip";
    
    if (e == NULL) {
        enemy_null_error(name);
        return 1;
    }
    if (tmp_array == NULL) {
        null_error("Temp-room_array", name);
        return 1;
    }
    if (r == NULL) {
        room_null_error(name);
        return 1;
    }
    
    
    
  
    for (int i = 0; i < r->width* r->height; i++) {
        char tile = r->room_array[i];
        if (is_clip_tile(tile) && is_entity_clip(&(e->base))) {
            tmp_array[i] = 1;
        }
        else if (get_ai_scared(e->ai) && tile == SPIKE_N){
            tmp_array[i] = 1;
        }
        else if (!e->base.fly && tile == HOLE_N) {
            tmp_array[i] = 1;
        }
        else {
            tmp_array[i] = 0;
        }
    }
    
    
    
    
    
    // sort through room special entities
    
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
            
                // Main Analysis
                
                // see if the two objects would clip with each other
                
                int ent_id = tmp_ls->spc_entity->entity_id;
                int blacken = 1;
                
                if (ent_id == SPC_POP_BLOCK_ID) {
                    if (get_pop_block_up(tmp_ls->spc_entity)) {
                    
                        // now need to sort through all pop blocks to see if standing on
                        // pop block
                        
                        
                        Spc_ent_ls* t_ls = r->spc_room_entities;
                        blacken = 0;
                        while (t_ls != NULL && !blacken) {
                        
                            if (t_ls->spc_entity->entity_id == SPC_POP_BLOCK_ID) {
                            
                                // see if collides with entity
                                if (entity_entity_collide(&(e->base), e->base.x, e->base.y,
                                                          &(t_ls->spc_entity->base))) {
                                    blacken = 1;
                                }
                                
                            }
                            
                            t_ls = t_ls->next;
                        }
                    }
                }
                
                
                
                if (blacken) {
                    blacken_entity_pos(&(e->base), &(tmp_ls->spc_entity->base),
                                       tmp_array, r);
                }

            }
            
            
            tmp_ls = tmp_ls->next;
        }
    }
    
    
    
    // if scared, black out room weapon entities;
    
    if ((get_ai_scared(e->ai) == WEAPON_SCARED_AI) && r->spc_weapon_entities != NULL) {
        
        while (r->spc_weapon_entities->prev != NULL) {
            r->spc_weapon_entities = r->spc_weapon_entities->prev;
        }
        
        Spc_ent_ls* tmp_ls = r->spc_weapon_entities;
        
        while (tmp_ls != NULL) {
            
            if (tmp_ls->spc_entity == NULL) {
                spc_entity_null_error(name);
            }
            
            else {
                
                int tmp_status = tmp_ls->spc_entity->base.status;
                set_entity_clip(&(tmp_ls->spc_entity->base), 1);
                
                blacken_entity_pos(&(e->base), &(tmp_ls->spc_entity->base), tmp_array, r);
                
                tmp_ls->spc_entity->base.status = tmp_status;
            }
            
            tmp_ls = tmp_ls->next;
        }
    }
    
    
    
    return 0;
}






int blacken_entity_pos(struct entity_t* e1, struct entity_t* e2,
                       char* tmp_array, struct room_t* r) {

    char name[] = "blacken_entity_pos";
    if (e1 == NULL || e2 == NULL) {
        entity_null_error(name);
        return 1;
    }
    if (tmp_array == NULL) {
        null_error("Tmp room_array", name);
        return 1;
    }
    if (r == NULL) {
        room_null_error(name);
        return 1;
    }
    
    
    int x_pos = e2->x;
    int y_pos = e2->y;
    
    if ((e2->default_hit_box == NULL || e2->hit_box == NULL) &&
        (e1->default_hit_box == NULL || e1->hit_box == NULL)) {
        
        if (x_pos >= 0 && x_pos < r->width && y_pos >= 0 && y_pos < r->height) {
        
            tmp_array[x_pos + y_pos * r->width] = 1;
        }
    }
    
    else if (entity_entity_collide(e1, x_pos, y_pos, e2)) {
        
        
        int e_x = e2->e_x;
        int e_y = e2->e_y;
        int w = e2->width;
        int h = e2->height;
        
        int inited = 0;
        char* matrix = e2->hit_box;
        
        if (matrix == NULL) {
            inited = 1;
            matrix = (char*) malloc(sizeof(char));
            w = 1;
            h = 1;
            e_x = 0;
            e_y = 0;
            
            if (matrix == NULL) {
                null_error("Hit Box Matrix", name);
                return 1;
            }
            matrix[0] = 1;
        }
        
        
        
        for (int iy = 0; iy < h; iy++) {
            for (int ix = 0; ix < w; ix++) {
                
                
                if (matrix[w*iy + ix]) {
                
                    int tmp_x = x_pos + ix - e_x;
                    int tmp_y = y_pos + iy - e_y;
                    
                    
                    
                    if (tmp_x >= 0 && tmp_x < r->width &&
                        tmp_y >= 0 && tmp_y < r->height) {
                    
                        
                        tmp_array[tmp_x + tmp_y * r->width] = 1;
                    }
                }
                
            }
        }
        
        if (inited) {
            free(matrix);
        }
    }
    return 0;
}



# endif
