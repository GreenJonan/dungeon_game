# ifndef ENEMY_TURN_
# define ENEMY_TURN_


int compute_enemy_turn(struct enemy_t*, struct game_t*);

// assume game and game->player is not null, null checked in 'start game'



int enemy_turn(Game* game) {
    
    game->player_turn = 0;
    
    Room* room = game->player->room;
    
    if (room->enemies != NULL) {
    
        while (room->enemies->prev != NULL) {
            room->enemies = room->enemies->prev;
        }
        
        // compute turn
        
        Enemy_ls* tmp_ls = room->enemies;
        
        while (tmp_ls != NULL) {
        
            if (tmp_ls->enemy == NULL) {
                enemy_null_error("enemy_turn");
            }
            
            else {
                if (tmp_ls->enemy->base.timer > 0) {
                    tmp_ls->enemy->base.timer -= 1;
                }
                
                if (tmp_ls->enemy->base.timer <= 0) {
                    
                    if (tmp_ls->enemy->enemy_id != ZOMBIE_ID) {
                        tmp_ls->enemy->player_x = game->player->base.x;
                        tmp_ls->enemy->player_y = game->player->base.y;
                    }
                    
                    tmp_ls->enemy->base.timer = tmp_ls->enemy->base.clock;
                    compute_enemy_turn(tmp_ls->enemy, game);
                }

            }
            
            tmp_ls = tmp_ls->next;
        }
        
        
        
        
        // see if any enemies have died
        
        tmp_ls = room->enemies;
        while (tmp_ls != NULL) {
            
            int delete = 0;
            if (tmp_ls->enemy == NULL) {
                enemy_null_error("enemy_turn");
            }
            
            else {
            
                if (tmp_ls->enemy->base.health == 0) {
                    // only kill health at zero, leave negative health
                    delete = 1;
                    tmp_ls = kill_enemy_ls(tmp_ls, room);
                }
                
                else if (tmp_ls->enemy->enemy_id == ORB_ID) {
                    // see whether it is clipping any thing, or player
                    // if so, delete it
                    // in particular, orbs entities!
                    
                    int x = tmp_ls->enemy->base.x;
                    int y = tmp_ls->enemy->base.y;
                    
                    
                    if (entity_entity_collide(&(tmp_ls->enemy->base), x, y,
                                              &(game->player->base))) {
                        delete = 1;
                        // deal damage to the player
                        player_damage(game->player, tmp_ls->enemy->touch_dmg);
                        
                    }
                    else if (entity_room_collide(&(tmp_ls->enemy->base),
                                                 room, x, y)){
                        delete = 1;
                    }
                }
                
            }
            if (delete) {
                tmp_ls = kill_enemy_ls(tmp_ls, room);
            }
            else {
                tmp_ls = tmp_ls->next;
            }

        }
    }
    
    
    if (player_is_dead(game->player)) {
        game->game_over = 1;
        return gameover(game);
    }
    
    else if (room->enemies == NULL) {
        if (room->room_lock == 1) {
            room->room_lock = 0;
        }
    }
    
    
    
    return 0;
    
}



















int compute_enemy_turn(struct enemy_t* e, struct game_t* g) {

    char name[] = "compute_enemy_turn";
    if (e == NULL) {
        enemy_null_error(name);
        return 1;
    }
    if (g == NULL) {
        null_error(GAME_OBJECT, name);
        return 1;
    }
    if (g->player == NULL) {
        player_null_error(name);
        return 1;
    }
    if (g->player->room == NULL) {
        room_null_error(name);
        return 1;
    }
    if (g->player->room->room_array == NULL) {
        null_error("Room_array", name);
        return 1;
    }
    
    
    move_enemy(e, g);
    
    
    
    if (entity_room_tile_collide(&(e->base), g->player->room, SPIKE_N,
                                 e->base.x, e->base.y, NULL, NULL)) {
        
        enemy_damage(e, 1);
    }
    
    
    return 0;
}

# endif
