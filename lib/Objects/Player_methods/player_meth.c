# ifndef PLAYER_HAS_METH___
# define PLAYER_HAS_METH___

////////////////////////////////////////////////////

int move_null_error(char* object) {
    return null_error(object, "move_player");
}


//int move_player_up(p);
//int move_player_left(p);
//int move_player_right(p);
int player_door_action(Game* game, int, int);
int room_spc_ent_move(struct player_t*, int, int);


int move_player(Game* game, int dir) {

    char name[] = "move_player";
    
    if (game == NULL) {
        null_error(GAME_OBJECT, name);
        return 1;
    }
        
        
    Player* p = game->player;
    if (p == NULL) {
        move_null_error(PLAYER_OBJECT);
        game->error = 1;
        return 1;
    }

    if (p->room == NULL) {
        move_null_error(ROOM_OBJECT);
        game->error = 1;
        return 1;
    }
    
    if (p->room->room_array == NULL) {
        move_null_error("Room array");
        game->error = 1;
        return 1;
    }
    
    if (dir < 0 || dir >=4) {
        printf("Invalid direction %d for 'move_player'\n", dir);
        pause_function();
        return 1;
    }
    
    
    // if not facing the direction give, use the move to face the direction.
    if (p->base.direction != dir) {
        turn_entity_dir(&(p->base), dir);
    }
    
    else {
        int x_tmp = p->base.x;
        int y_tmp = p->base.y;
        
        dir_to_xy(dir, &x_tmp, &y_tmp);

        
        
        
        
        int x_found = 0;
        int y_found = 0;
        
        
        // see whether new position is a HOLE_N;
        
        // TO DO: update room_spc_ent_move function to include entity matrices
        
        
        if (room_spc_ent_move(p, x_tmp, y_tmp)) {;} // do nothing
        
        else if (!p->base.fly && entity_room_tile_collide(&(p->base), p->room, HOLE_N, x_tmp, y_tmp,
                                                          NULL, NULL)) {
            
            player_damage(p, HOLE_DAMAGE);
            
            printf("You fell into the hole!\n");
            pause_function();
        }
        
        
        else if (entity_room_collide(&(p->base), p->room, x_tmp, y_tmp)) {
            player_blocked_sound();
        }
        
        
        else {
        
            if (entity_room_tile_collide(&(p->base), p->room, DOOR_N, x_tmp, y_tmp,
                                         &x_found, &y_found)) {
                
                // IMPORTANT NOTE: re-doing a lot of the same code with the function above, and the
                // start of the function below.
                
                player_door_action(game, x_found, y_found);
            }
            
            else {
                // this assumes the player will not walk into a clip tile.
                
                
                // now see if the player will walk into any enemy enemies, if so, deal damage
                
                int set_player = 1;
                
                
                if (p->room->enemies != NULL) {
                    
                
                    while (p->room->enemies->prev != NULL) {
                        p->room->enemies = p->room->enemies->prev;
                    }
                    
                    
                    Enemy_ls* tmp_en_ls = p->room->enemies;
                    
                    while (tmp_en_ls != NULL) {
                    
                        
                        if (tmp_en_ls->enemy == NULL) {
                            enemy_null_error(name);
                        }
                        
                        
                        else {
                            
                            
                            if (entity_entity_collide(&(p->base), x_tmp, y_tmp, &(tmp_en_ls->enemy->base))) {
                            
                                set_player = 0;
                                // deal damage
                                
                                player_damage(p, tmp_en_ls->enemy->touch_dmg);
                            }
                        }
                    
                    
                    
                        tmp_en_ls = tmp_en_ls->next;
                    }
                
                }
                
                
                
                // set player x,y position.
                
                if (set_player) {
                    set_player_xy(p, x_tmp, y_tmp);
                }
            }
        }
    }

    return 0;
}









            
            
            
            
            
            




int player_door_action(Game* game, int x_tmp, int y_tmp) {

    char name[] = "player_door_action";
    
    if (game == NULL) {
        game_null_error(name);
        return 1;
    }
    if (game->player == NULL) {
        player_null_error(name);
        return 1;
    }
    if (game->player->room == NULL) {
        room_null_error(name);
        return 1;
    }
    if (game->player->room->room_array == NULL) {
        null_error("Room Array", name);
        return 1;
    }
    
    Exit* tmp_exit = find_exit_point(game->player->room, x_tmp, y_tmp);
    
    
    
    if (tmp_exit == NULL) {
        printf("ERROR: no exit at co-ordinates: %d,%d\n", x_tmp, y_tmp);
        pause_function();
    }
    
    
    else {
        // need to look over code, but why 2?, is 1 error message?
        int broken = 2;
    
        
        if (game->player->room->enemies == NULL ||  !game->player->room->room_lock) {
            broken = teleport_player_exit(game->player, tmp_exit);
        }
    
    
    
    
        if (!broken) {
            increment_game_time(game);
            draw_screen(game);
        }

    
        else {
    
            player_blocked_sound();
        
        
            if (broken == 2) {
                printf("The door is locked, kill all enemies to continue.\n");
                pause_function();
            }
        
            else if (broken > 0) {
                printf("The door appears to be broken...\n");
                pause_function();
            }
            else if (broken == -1){
                printf("The door apears to be locked on the other side...\n");
                //flush_input();
                pause_function();
            }
    
            else {
                // if no_clip, allow the player to fly onto the wall
                if (!is_player_clip(game->player)) {
                    set_player_xy(game->player, x_tmp, y_tmp);
                    return 0;
                }
            
                
                if ( broken == -2) { //door is locked.
                    if (game->player->inventory->key_num > 0) {
                        // this implies the door is unlocked
                    
                        printf("The door is locked.\nEnter 'y' to open the door: ");
                        char c = getchar();
                        if (c != EOF && c != '\n') {
                            flush_input();
                        }
                    
                        if (c == 'y' || c == 'Y') {
                            set_door_locked(tmp_exit, 0);
                            game->player->inventory->key_num --;
                        }
                        return 0;
                    }
                    else {
                        printf("The door is locked.\n");
                    }
                }
            
                else if (broken == -3) {
                    printf("The door is closed.\n");
                }
                else if (broken == -4) {
                    player_blocked_sound();
                    return 0;
                }
                else {
                    printf("ERROR: undefined return type 'door_action'.\n");
                }
            
                pause_function();
            }
        }
    }
    
    return 0;
}











int room_spc_ent_move(struct player_t* p, int new_x, int new_y) {

    int move = 0;
    char name[] = "room_spc_ent_move";
    
    if (p == NULL) {
        player_null_error(name);
        return 0;
    }
    
    if (p->room == NULL) {
        room_null_error(name);
        return 0;
    }
    
    
    if (p->room->spc_room_entities != NULL) {
    
        while (p->room->spc_room_entities->prev != NULL) {
            p->room->spc_room_entities = p->room->spc_room_entities->prev;
        }
        
        Spc_ent_ls* tmp_ls = p->room->spc_room_entities;
        
        while (tmp_ls != NULL) {
        
            // see if freed variable
            int free = 0;
            
            
            if (tmp_ls->spc_entity == NULL) {
                special_entity_null_error(name);
            }
            
            else {
                int ent_id = tmp_ls->spc_entity->entity_id;
                int obj_x = tmp_ls->spc_entity->base.x;
                int obj_y = tmp_ls->spc_entity->base.y;
                
                
                
                if (ent_id == SPC_PUSH_BLOCK_ID) {
                
                    if (entity_entity_collide(&(p->base), new_x, new_y, &(tmp_ls->spc_entity->base))) {
                    
                        
                        int push_num = get_push_block_push_num(tmp_ls->spc_entity);
                        
                        if (push_num != 0) {

                        
                            // see if block is pushable from the direction the player is facing
                        
                            if (read_char_bool(get_push_block_dir(tmp_ls->spc_entity),
                                p->base.direction % 4)) {
                        
                                
                                
                                // block is movable
                                
                                
                                // now find the block directly in front that the block should
                                // move into
                                
                                int tmp_x = obj_x, tmp_y = obj_y;
                                dir_to_xy(p->base.direction, &tmp_x, &tmp_y);
                                
                                
                                
                                if (!entity_room_collide(&(tmp_ls->spc_entity->base), p->room,
                                                      tmp_x, tmp_y)) {
                                
                                    if (push_num > 0) {
                                        set_push_block_push_num(tmp_ls->spc_entity, push_num - 1);
                                    }
                                
                                    tmp_ls->spc_entity->base.x = tmp_x;
                                    tmp_ls->spc_entity->base.y = tmp_y;
                                    
                                    move = 1;
                                }
                                    
                                else if (entity_room_tile_collide(&(tmp_ls->spc_entity->base), p->room,
                                                                  HOLE_N, tmp_x, tmp_y, NULL, NULL)) {
                                    
                                    
                                    Spc_ent_ls* temporary_ls = tmp_ls->next;
                                    free = 1;
                                            
                                    kill_special_entity(p->room, tmp_ls, 0);
                                    tmp_ls = temporary_ls;
                                            
                                    set_room_tile(p->room, tmp_x, tmp_y, FLOOR_N);
                                
                                    move = 1;
                                }
                            }
                        }
                    }
                }
                
                // here goes another thing to test against.
                else if (0) {;}
            
            }
        
            if (!free) {
                tmp_ls = tmp_ls->next;
            }
        }
        
    
    
    }

    return move;
}

            
            
            
            
            
            
            
            
            
            

//////////////////////////////////////////////////////////////////////////

////
////        TELEPORT METHOD
////


// set the player's position given an x,y

int set_player_xy(struct player_t* p, int x_, int y_) {
    if (p == NULL) {
        null_error(PLAYER_OBJECT, "set_player_xy");
        return 1;
    }
    
    p->base.x = x_;
    p->base.y = y_;
    return 0;
}





// knowing that the player is standing on an exit, but unknown which one,
// find the appropriate exit, and teleport them.

int teleportp_null_error(char* object) {
    return null_error(object, "teleport_player_exit");
}







int teleport_player_exit(Player* p, Exit* e) {
    
    
    if (p == NULL) {
        teleportp_null_error(PLAYER_OBJECT);
        return 1;
    }
    if (e == NULL) {
        teleportp_null_error(EXIT_OBJECT);
        return 1;
    }
    
    // set player's position to be the new exit;
    
    Exit* tmp_door = e->door;
    
    if (tmp_door == NULL) {
        return -1;
        // this is if the exit is not connected to any other exit.
    }
    // see if the current door is open.
    if (door_is_locked(e)) {
        if (door_is_switch(e) || door_is_portal(e)) {
            
            if (get_door_hidden(e)) { return -4;}
            else {return -3;}
        }
        
        else if (door_is_bombable(e)) {return -4;}
       
        else { return -2;}
    }
    
    reset_spc_room_entities(p);
    
    p->room = tmp_door->room;
    
    p->base.x = tmp_door->x;
    p->base.y = tmp_door->y;
    
    
    // set the door last exited from.
    p->last_door = tmp_door;

    
    return 0;
    
}






/*
 if (ptr->exit == NULL) {
 teleportp_null_error(EXIT_OBJECT);
 return 1;
 }
 
 
 int exit_num = p->room->exit_len;
 int found = 0;
 
 if (ptr->exit->x == x && ptr->exit->y == y) {
 found = 1;
 }
 
 
 int i = 0;
 while (!found) {
 ptr = ptr->next;
 
 if (ptr == NULL) {
 teleportp_null_error(EXIT_LS_OBJECT);
 return 1;
 }
 if (ptr->exit == NULL) {
 teleportp_null_error(EXIT_OBJECT);
 return 1;
 }
 
 if (ptr->exit->x == x && ptr->exit->y == y) {
 found = 1;
 }
 
 i++;
 if (i > exit_num) {
 return 1;
 }
 }
 
 */













//////////////////////////////////////////////////////

// SWORD METHODS

/*
int player_null_error(char* function) {
    return null_error(PLAYER_OBJECT, function);
} */ //defined in utility error

int player_equipped_sword(struct player_t* p) {
    return p->has_sword;
}


int give_player_sword(struct player_t* p) {
    if (p == NULL) {
        player_null_error("give_player_sword");
    }
    set_player_sword(p, 1);
    return 0;
}


int take_player_sword(struct player_t* p) {
    if (p == NULL) {
        player_null_error("give_player_sword");
    }
    set_player_sword(p, 0);
    return 0;
}



int set_player_sword(struct player_t* p, int t) {
    if (p == NULL) {
        player_null_error("give_player_sword");
        return 1;
    }
    p->has_sword = t;
    return 0;
}







//////////////////////////////////////////////////////////////

// player_status

int set_player_default_status(struct player_t* p) {

    if (p == NULL) {
        player_null_error("set_player_default_status");
        return 1;
    }
    
    set_player_clip(p, 1);
    set_player_paralysed(p, 0);
    set_player_poisoned(p, 0);
    return 0;
}



int set_player_clip(struct player_t* p, int b) {
    if (p == NULL) {
        player_null_error("set_player_clip");
        return 1;
    }
    return set_entity_clip(&(p->base), b);
}
int set_player_paralysed(struct player_t* p, int b) {
    if (p == NULL) {
        player_null_error("set_player_paralysed");
        return 1;
    }
    return set_entity_paralysed(&(p->base), b);
}
int set_player_poisoned(struct player_t* p, int b) {
    if (p == NULL) {
        player_null_error("set_player_poisoned");
        return 1;
    }
    return set_entity_poisoned(&(p->base), b);
}


// getters

int is_player_clip(struct player_t* p) {
    if (p == NULL) {
        player_null_error("is_player_clip");
        return 1;
    }
    return is_entity_clip(&(p->base));
}
int is_player_paralysed(struct player_t* p) {
    if (p == NULL) {
        player_null_error("is_player_paralysed");
        return 1;
    }
    return is_entity_paralysed(&(p->base));
}
int is_player_poisoned(struct player_t* p) {
    if (p == NULL) {
        player_null_error("is_player_poisoned");
        return 1;
    }
    return is_entity_poisoned(&(p->base));
}













////////////////////////////////////////////////////////////

int player_x_pos(struct player_t* p) {
    if (p == NULL) {
        player_null_error("player_x_pos");
        return -1;
    }
    return entity_x_pos(&(p->base));
}

int player_y_pos(struct player_t* p) {
    if (p == NULL) {
        player_null_error("player_y_pos");
        return -1;
    }
    return entity_y_pos(&(p->base));
}








///////////////////////////////////////////////////////////////

int set_player_light_dist(Player* e, int d) {
    if (e == NULL) {
        player_null_error("set_player_light_dist");
        return 1;
    }
    
    return set_entity_light_dist(&(e->base), d);
}

int get_player_light_dist(Player* e) {
    if (e == NULL) {
        player_null_error("get_player_light_dist");
        return -1;
    }
    return get_entity_light_dist(&(e->base));
}







# endif
