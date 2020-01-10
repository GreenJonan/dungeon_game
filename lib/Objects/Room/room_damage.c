# ifndef TAKE_ALL_DAMAGE
# define TAKE_ALL_DAMAGE

# include "../special_entity_methods.c"


int lock_threshold = 1;
int crack_threshold = 1;



// h ==> health, d_id ==> damage id.

// so far two types of damage 0 ==> swords, 1 ==> bomb blasts


// TO DO: rework so is entity_entity_clip, not just x,y positions overlap.


int weapon_damage(struct game_t* g, int x, int y, int h, int d_id, int type) {

    int hit = 0;
    
    if ( g == NULL) {
        game_null_error("weapon_damage");
        return 1;
    }
    if (g->player == NULL) {
        player_null_error("weapon_damage");
        return 1;
    }

    
    Room* r = g->player->room;
    
    if (d_id != PLAYER_DMG_ID) {
        // this means, the object may damage the player
        
        if (g->player->base.x == x && g->player->base.y == y) {
            player_damage(g->player, h);
            
            if (g->player->base.health <= 0) {
                g->game_over = 1;
            }
        }
        // if already dead, i'll let you escape.
    
    }
    
    if (r == NULL) {
        room_null_error("weapon_damage");
        return 1;
    }
    
    
    // now compute damage for all other entities
    
    if (type == BLAST_DMG) {
    
        //////////////////////////////////////////////////////////////////
        
        // if there are any bombable exits to open;
        if (r->exits != NULL) {
            
            if (r->exits->exit == NULL) {
                null_error(EXIT_OBJECT, "weapon_damage");
            }
            
            else {
            
                Exit_ls* tmp_ls = r->exits;
                int door_key = -1; //tmp_ls->exit->key;
                int tmp_key = 1;
                
                while (tmp_key != door_key) {
                    
                
                    Exit* tmp_exit = tmp_ls->exit;
                    
                    if (tmp_exit == NULL) {
                        null_error(EXIT_OBJECT, "weapon_damage");
                    }
                    else {
                        if (door_key == -1) {
                            tmp_key = -1;
                            door_key = tmp_exit->key;
                        }
                        else {
                            tmp_key = tmp_exit->key;
                        }
                
                        
                        
                        if (x == tmp_exit->x && y == tmp_exit->y) {

                            if (h >= lock_threshold) {
                            
                                if (door_is_bombable(tmp_exit)) {
                                    
                                    // unlock door
                                    set_door_locked(tmp_exit, 0);
                                }
                            }
                        }
                        
                        if (tmp_key == 0) {
                            tmp_key = door_key;
                        }
                    }
                    
                    tmp_ls = tmp_ls->next;
                    if (tmp_ls == NULL) {
                        null_error(EXIT_LS_OBJECT, "weapon_damage");
                        break;
                    }
                    
                    
                }
            }
        }
        
        // now sort through all special entities and blow up all the other bombs if timer > 1;
        
        // that is, all bombs within mutual distances will all blow up at the same time.
        
        
        
        Spc_ent_ls* tmp_ent_ls = r->spc_weapon_entities;
        if (tmp_ent_ls != NULL) {
            
            while (tmp_ent_ls->prev != NULL) {
                tmp_ent_ls = tmp_ent_ls->prev;
            }
            
            while (tmp_ent_ls != NULL) {
                if (tmp_ent_ls->spc_entity == NULL) {
                    null_error(SPECIAL_ENTITY_OBJECT, "weapon_damage");
                }
            
                else {
                    
                    if (tmp_ent_ls->spc_entity->entity_id == SPC_BOMB_ID) {
                        
                        if (h != 0) {
                            if (tmp_ent_ls->spc_entity->base.x == x && tmp_ent_ls->spc_entity->base.y == y) {
                                if (tmp_ent_ls->spc_entity->base.timer >1) {//> 2) {//> 1) {
                                
                                
                                    tmp_ent_ls->spc_entity->base.timer = 1;
                                    //increment_spc_bomb_time(tmp_ent_ls->spc_entity, g);
                                    tmp_ent_ls->spc_entity->wait_update = 1;
                                
                                
                                    //tmp_ent_ls->spc_entity->base.timer = 2;
                                    // this causes it to explode on the next round, not imediately.
                                
                                }
                            }
                        }
                    }
                }
                tmp_ent_ls = tmp_ent_ls->next;
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        
        // now see if there are any CRACKED_WALL tiles to explode
        
        if (r->room_array == NULL) {
            null_error("Room array", "weapon_damage");
        }
        
        else {
        
            char tile = r->room_array[r->width* y + x];
            
            if (tile == CRACKED_WALL_N) {
                if (h >= crack_threshold) {
                    
                    // wall has opened
                    r->room_array[r->width* y + x] = FLOOR_N;
                    
                }
            }
        }
        
        
        
        ////////////////////////////////////////////////////////////////////////
        
    }
    
    // PICKUP ITEMS!!
    
    
    else if (type == SWORD_DMG && d_id == PLAYER_DMG_ID) {
        // d_id == 0 ==> player's
        // now see if player can pickup items
        
        if (r->items != NULL) {
        
            Item_ls* tmp_items = r->items;
            
            while (tmp_items->prev != NULL) {
                tmp_items = tmp_items->prev;
            }
            
            while (tmp_items != NULL) {
            
                Item_ls* tmp_tmp_items = NULL;
                
                if (tmp_items->item == NULL) {
                    item_null_error("weapon_damage");
                    tmp_tmp_items = tmp_items;
                }
                
                else if (tmp_items->item->identity < 100) {
                    
                    if (x == tmp_items->item->base.x && y == tmp_items->item->base.y) {
                        // pickup the items
                        tmp_tmp_items = tmp_items->next;
                        
                        
                        int kill = 0;
                        kill = pickup_item(g, tmp_items->item);
                        
                        if (kill >= 0) {
                            kill_item(g->player->room, tmp_items);
                        }
                        
                        else {
                            if (kill < -1) {
                                // pop item off, i.e. dont free item, but free item list.
                                pop_item_ls_room(tmp_items, g->player->room);
                            }
                        }
                        
                        tmp_items = tmp_tmp_items;
                    }
                }
                
                
                if (tmp_items != NULL) {
                    tmp_items = tmp_items->next;
                }
            }
        }
    }
    ////////////////////////////////////////////////////////////////////////
    
    
    
    
    
    
    // now deal damage to all enemies
    
    if (r->enemies != NULL) {
        
        Enemy_ls* tmp_enemies = r->enemies;
        
        while (tmp_enemies->prev != NULL) {
            tmp_enemies = tmp_enemies->prev;
        }
        
        while (tmp_enemies != NULL) {
            
            // preset the enemy to not be dead.
            Enemy_ls* dead_enemy = NULL;
            
            if (tmp_enemies->enemy == NULL) {
                enemy_null_error("weapon_damage");
                dead_enemy = tmp_enemies;
            }
            
            else if (x == tmp_enemies->enemy->base.x && y== tmp_enemies->enemy->base.y) {
                
                // hurt the enemy
                if (tmp_enemies->enemy->base.health >= 0) {
                    
                    int hurt = 1;
                    // for various enemies, hitting them will not hurt them, but trigger things
                    
                    
                    
                    // zombies, hurt but forget previous player postion if hit with arrow
                    if (tmp_enemies->enemy->enemy_id == ZOMBIE_ID) {
                    
                        if (type == ARROW_DMG) {
                            tmp_enemies->enemy->player_x = -1;
                            tmp_enemies->enemy->player_y = -1;
                        }
                    }
                    
                    // should a bomb instantly kill a ghost?
                    
                    
                    
                    if (hurt) {
                        enemy_damage(tmp_enemies->enemy, h);
                    
                        hit = 1;
                
                        if (tmp_enemies->enemy->base.health <= 0) {
                            dead_enemy = tmp_enemies;
                        }
                    }
                }
            }
            
            tmp_enemies = tmp_enemies->next;
            if (dead_enemy != NULL) {
                kill_enemy(r, dead_enemy);
            }
        }
    }
    
   
    
    
    // final check to see if all enemies are kileed
    if (r->enemies == NULL) {
        if (r->room_lock == 1) {
            r->room_lock = 0;
        }
    }
    
    
    ////////////////////////////////////////////////////////////////////////
    
    
    
    
    // now for room_entities, temporarily kill certain entities.
    
    int tmp_hit;
    tmp_hit = weapon_hit_spc_room_entities(g, x, y, h, d_id, type);
    
    if (!hit) {
        hit = tmp_hit;
    }
    
    
    
    ////////////////////////////////////////////////////////////////////////

    
    // check to see if player has zero, health, if so gameover
    if (g->player->base.health <= 0) {
        g->game_over = 1;
    }
    
    
    
    
    if (hit) {
        return -1;
    }
    return 0;
}










int weapon_hit_spc_room_entities(struct game_t* g, int x, int y, int h, int d_id, int type) {

    char name[] = "weapon_hit_spc_room_entities";
    
    if (g == NULL) {
        game_null_error(name);
        return -1;
    }
    
    if (g->player == NULL) {
        player_null_error(name);
        return -1;
    }
    
    struct room_t* r = g->player->room;
    
    if (r== NULL) {
        room_null_error(name);
        return -1;
    }
    
    
    
    int hit = 0;
    
    Spc_ent_ls* tmp_ent_ls = r->spc_room_entities;
    if (tmp_ent_ls != NULL) {
        
        while (tmp_ent_ls->prev != NULL) {
            tmp_ent_ls = tmp_ent_ls->prev;
        }
        
        while (tmp_ent_ls != NULL) {
            if (tmp_ent_ls->spc_entity == NULL) {
                null_error(SPECIAL_ENTITY_OBJECT, name);
            }
            
            else {
                if (tmp_ent_ls->spc_entity->base.x == x && tmp_ent_ls->spc_entity->base.y == y){
                    
                    
                    int ent_id = tmp_ent_ls->spc_entity->entity_id;
                    
                    if (ent_id == SPC_TELEPHONE_ID) {
                        if (h > 0) {
                            if (type == BLAST_DMG){
                                tmp_ent_ls->spc_entity->base.health = 0;
                            }
                        }
                    }
                    
                    else if (ent_id == SPC_FLAG_ID) {
                        if (h > 0) {
                            if (type == SWORD_DMG) {
                                tmp_ent_ls->spc_entity->base.health = 0;
                            }
                        }
                    }
                    
                    
                    // activate switch entities with all items that are not bombs
                    // currently only sword, would like to introduce arrows
                    
                    else if (ent_id == SPC_SWITCH_ID) {
                        
                        
                        if (h > 0) {
                            if (type == SWORD_DMG || type == ARROW_DMG) {
                                
                                activate_switch(tmp_ent_ls->spc_entity, g);
                                hit = 1;
                            }
                        }
                    }
                    
                }
            }
            tmp_ent_ls = tmp_ent_ls->next;
        }
    }

    
    
    return hit;
}


# endif
