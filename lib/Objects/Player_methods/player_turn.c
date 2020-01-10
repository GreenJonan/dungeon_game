# ifndef PLAYER_TURN_
# define PLAYER_TURN_

# include "input/commands.h"
# include "input/receive_input_command.c"

int use_bomb(struct player_t*);
int use_sword(struct player_t*);
int use_staff(struct player_t*);
int use_bow(struct game_t*, int);
//int use_potion



int use_empty_bottle(struct player_t*);
int use_full_dark_bottle(struct player_t*);
int use_half_full_dark_bottle(struct player_t*);
int use_full_med_bottle(struct player_t*);
int use_half_full_med_bottle(struct player_t*);
int use_full_light_bottle(struct player_t*);
int use_half_full_light_bottle(struct player_t*);


int take_player_enemy_damage(struct player_t*);







int inventory_null_error(char* function) {
    return null_error(INVENTORY_OBJECT, function);
}


/////////////////////////////////////////////////////



int player_turn(Game* game) {
    
    char name[] = "player_turn";
    
    
    if (game == NULL) {
        game_null_error(name);
        return 1;
    }
    if (game->player == NULL) {
        player_null_error(name);
        return 1;
    }
    if (game->player->inventory == NULL) {
        inventory_null_error(name);
        return 1;
    }
    
    
    game->player_turn = 1;
    
    if (game->player->base.timer > 0) {
        game->player->base.timer --;
    }
    
    
    
    
    if (game->player->base.timer <= 0 || game->inventory) {
    START:
    
        game->player->base.timer = game->player->base.clock;
        game->player->hit = 0;
    
        char input = receive_input_command(game);
    
        int obj_interact = 0;
        int chest_interact = 0;
        int use_weapon = 0;
        int use_quick_item = 0;
    
    
        if (input >= SPECIAL_LOWER && input <= SPECIAL_UPPER) {
            // this implies a special command has been entered, e.g. exit, save
            return input;
        }
    
        else if (input == TOGGLE_C) {
            // toggle the items hud
            if (game->draw_hud_items) {
                game->draw_hud_items = 0;
            }
            else { game->draw_hud_items = 1;}
            draw_screen(game);
            return player_turn(game);
        }
    
    
        else if (input == MENU_C) {
        
            if (game->inventory) {
                exit_inventory(game);
                draw_screen(game);
                return player_turn(game);
            }
            else {
                game->inventory = 1;
                draw_screen(game);
            }
        }
    
    
        else if (game->inventory) {
            int exit_ = 0;
        
            if (input == MOVE_DOWN_C) {   move_cursor_down(game);  }
        
            else if (input == MOVE_UP_C) {   move_cursor_up(game);  }
        
            else if (input == MOVE_LEFT_C) {   move_cursor_left(game);  }
        
            else if (input == MOVE_RIGHT_C) {  move_cursor_right(game);  }
        
            else if (input == WAIT_C || input == REST_C || input == INTERACT_C) {   exit_ = select_cursor(game);  }
            
            if (exit_) {
                exit_inventory(game);
                return exit_;
            }
            draw_screen(game);
        }
    
    
    
    
        else if (game->player->room != NULL) {
        
            // not in the game inventory:
        
        
            if (input != REST_C && input != WAIT_C) {
                // this implies the move is computable.
        

                if (input == MOVE_UP_C) {   move_player(game, UP_DIR);  }
            
                else if (input == MOVE_LEFT_C) {   move_player(game, LEFT_DIR);  }
           
                else if (input == MOVE_DOWN_C) {   move_player(game, DOWN_DIR);  }
            
                else if (input == MOVE_RIGHT_C) {   move_player(game, RIGHT_DIR); }
        
        
                else if (input == INTERACT_C && 1) {
                    // should have different methods depending on what the item being held is.
                
                    int inited = 0;
                    if (game->player->inventory != NULL) {
                
                        if (game->player->inventory->eq_active_item != NULL) {
                
                            if (game->player->inventory->eq_active_item->identity != POINTER_ID) {
                                use_weapon = 1;
                                inited = 1;
                            }
                        }
                    }
                    if (!inited) {
                        obj_interact = 1;
                        chest_interact = 1;
                    }
                
                
                }
                else if (input == QUICK_ITEM_C) {
                
                    if (game->player->inventory != NULL) {
                        if (game->player->inventory->eq_consumable_item != NULL) {
                            use_quick_item = 1;
                        }
                    }
                }
        
        
                
                
                // Quick swap / switch commands
                
                else if (input == ACTIVE_SWITCH_C) {
                    if (game->player->inventory != NULL) {
                     
                        Item* tmp_item = game->player->inventory->eq_active_item;
                        
                        game->player->inventory->eq_active_item = game->player->inventory->prev_active;
                        game->player->inventory->prev_active = tmp_item;
                    }
                }
                
                else if (input == CONSUMABLE_SWITCH_C) {
                    if (game->player->inventory != NULL) {
                        
                        Item* tmp_item = game->player->inventory->eq_consumable_item;
                        
                        game->player->inventory->eq_consumable_item = game->player->inventory->prev_consumable;
                        game->player->inventory->prev_consumable = tmp_item;
                    }
                }
                
                else if (input == PASSIVE_SWITCH_C) {
                    if (game->player->inventory != NULL) {
                        
                        Item* tmp_item = game->player->inventory->eq_passive_item;
                        
                        game->player->inventory->eq_passive_item = game->player->inventory->prev_passive;
                        game->player->inventory->prev_passive = tmp_item;
                    }
                }
                
                
                
                else {
                    printf("ERROR: unknown command: ascii: %d, char: %c\n", input, input);
                    game->error = 1;
                    pause_function();
                }
            }
        
        
        
            // last parametres

        
            int reach_flag = 0;
            reach_flag = player_spc_entity_interaction(game, obj_interact);
            if (reach_flag < 0) {
                return WIN_GAME_C;
            }

        
        
        
            int x = player_x_pos(game->player);
            int y = player_y_pos(game->player);
            Room* room = game->player->room;
        
        
            // check for tile damage with spike.
        
            if (get_room_tile(room, x, y) == SPIKE_N) {//room->room_array[room->width * y + x] == SPIKE_N) {
                game_player_damage(game, SPIKE_DAMAGE);
            }
        
            // see whether touch any enemies, and if so take damage
            take_player_enemy_damage(game->player);
            
        
        
            if (player_is_dead(game->player)) {
                game->game_over = 1;
                return gameover(game);
            }
        
        
            player_collect_items(game, obj_interact);
        
            if (chest_interact) {
                player_open_chest(game);
            }

            
            player_npc_interaction(game, obj_interact);
        
            
            
            ////////////
            
            // see what passive items are being held
            int passive_id = 0;
            if (game->player->inventory->eq_passive_item != NULL) {
            
                passive_id = game->player->inventory->eq_passive_item->identity;
            }
            
            
            ///////////
            
            
            
        
            // use weapons and consumable items
        
            if (use_quick_item) {
                int i_id = game->player->inventory->eq_consumable_item->identity;
            
                if (i_id == BOMB_BAG_ID) {
                    use_bomb(game->player);
                }
                
                
                else if (i_id == BOTTLE_EMPTY_ID) {  use_empty_bottle(game->player);}
                
                else if (i_id == BOTTLE_FULL_DARK_ID) { use_full_dark_bottle(game->player); }
                
                else if (i_id == BOTTLE_HALF_FULL_DARK_ID) { use_half_full_dark_bottle(game->player); }
                
                else if (i_id == BOTTLE_FULL_MED_ID) { use_full_med_bottle(game->player); }
                
                else if (i_id == BOTTLE_HALF_FULL_MED_ID) { use_half_full_med_bottle(game->player); }
                
                else if (i_id == BOTTLE_FULL_LIGHT_ID) { use_full_light_bottle(game->player); }
                
                else if (i_id == BOTTLE_HALF_FULL_LIGHT_ID) { use_half_full_light_bottle(game->player); }
                
                draw_screen(game);
            }
        
            
            
            
            
        
            if (use_weapon) {
                int i_id = game->player->inventory->eq_active_item->identity;
            
            
                if (i_id == BASIC_SWORD_ID) {
                    use_sword(game->player);
                }
            
                else if (i_id == STAFF_ID) {
                    use_staff(game->player);
                }
                
                
                if (i_id == BOW_ID) {
                    use_bow(game, passive_id);
                }
                
                draw_screen(game);
            }
        }
        
        
        if (game->player->loop > 0) {
            game->player->loop -= 1;
            draw_screen(game);
            
            goto START;
            // this means loop back to start of turn.
        }
    }
    
    
    return 0;
}













int use_bomb(struct player_t* p ) {

    if (p == NULL) {
        player_null_error("use_bomb");
        return 1;
    }
    if (p->inventory == NULL) {
        inventory_null_error( "use_bomb");
        return 1;
    }

    if (p->inventory->bomb_num > 0) {
        
        init_spc_basic_bomb(p);
        p->inventory->bomb_num -= 1;
    }
    
    return 0;
}










int use_sword(struct player_t* p) {
    return init_spc_basic_sword(p);
}
int use_staff(struct player_t* p) {
    return init_spc_basic_staff(p);
}






int use_bow(struct game_t* g, int passive_id) {
    char name[] = "use_bow";
    
    if (g->player == NULL) {
        player_null_error(name);
        return 1;
    }
    
    if (g->player->inventory == NULL) {
        inventory_null_error(name);
        return 1;
    }
    
    Inventory* i = g->player->inventory;
    
    if (i->arrow_num > 0) {
        int type = BASIC_ARROW_TYPE;
        
        if (i->eq_consumable_item != NULL) {
    
            if (i->eq_consumable_item->identity == BOMB_BAG_ID) {
 
                if (i->bomb_num > 0) {
                    type = BOMB_ARROW_TYPE;
                }
            }
        }
        
        
        // have fast / slow arrow types, slow ==> player, fast ==> game
        
        if (passive_id == HOURGLASS_ID) {
            init_spc_slow_arrow(g->player, type);
        }
        else {
            init_spc_fast_arrow(g, type);
        }
        i->arrow_num --;
        
        if (type == BOMB_ARROW_TYPE) {
            i->bomb_num --;
        }
    }
    
    return 0;
}








/////////////////////////////////////////////////////////



                      
                      




int use_empty_bottle(struct player_t* p) {

    // do nothing
    return 0;
}





int use_full_dark_bottle(struct player_t* p) {

    char name[] = "use_full_dark_bottle";
    
    if (p == NULL) {
        player_null_error(name);
        return 1;
    }
    if (p->inventory == NULL) {
        inventory_null_error(name);
        return 1;
    }
    if (p->inventory->eq_consumable_item == NULL) {
        item_null_error(name);
        return 1;
    }
    
    // heal/gain both health and mana
    player_heal(p, HEALTH_POTION_HEAL);
    player_gain_mana(p, MANA_POTION_HEAL);
    
    p->inventory->eq_consumable_item->identity = BOTTLE_HALF_FULL_DARK_ID;
    return 0;
}


int use_half_full_dark_bottle(struct player_t* p) {
    
    char name[] = "use_half_full_dark_bottle";
    
    if (p == NULL) {
        player_null_error(name);
        return 1;
    }
    if (p->inventory == NULL) {
        inventory_null_error(name);
        return 1;
    }
    if (p->inventory->eq_consumable_item == NULL) {
        item_null_error(name);
        return 1;
    }
    
    // heal/gain both health and mana
    player_heal(p, HEALTH_POTION_HEAL);
    player_gain_mana(p, MANA_POTION_HEAL);
    
    p->inventory->eq_consumable_item->identity = BOTTLE_EMPTY_ID;
    return 0;
}





int use_full_med_bottle(struct player_t* p) {
    
    char name[] = "use_full_med_bottle";
    
    if (p == NULL) {
        player_null_error(name);
        return 1;
    }
    if (p->inventory == NULL) {
        inventory_null_error(name);
        return 1;
    }
    if (p->inventory->eq_consumable_item == NULL) {
        item_null_error(name);
        return 1;
    }
    
    // heal health
    player_heal(p, HEALTH_POTION_HEAL);
    
    p->inventory->eq_consumable_item->identity = BOTTLE_HALF_FULL_MED_ID;
    return 0;
}


int use_half_full_med_bottle(struct player_t* p) {
    
    char name[] = "use_half_full_med_bottle";
    
    if (p == NULL) {
        player_null_error(name);
        return 1;
    }
    if (p->inventory == NULL) {
        inventory_null_error(name);
        return 1;
    }
    if (p->inventory->eq_consumable_item == NULL) {
        item_null_error(name);
        return 1;
    }
    
    // heal health
    player_heal(p, HEALTH_POTION_HEAL);
    
    p->inventory->eq_consumable_item->identity = BOTTLE_EMPTY_ID;
    return 0;
}





int use_full_light_bottle(struct player_t* p) {
    
    char name[] = "use_full_light_bottle";
    
    if (p == NULL) {
        player_null_error(name);
        return 1;
    }
    if (p->inventory == NULL) {
        inventory_null_error(name);
        return 1;
    }
    if (p->inventory->eq_consumable_item == NULL) {
        item_null_error(name);
        return 1;
    }
    
    // gain mana
    player_gain_mana(p, MANA_POTION_HEAL);
    
    p->inventory->eq_consumable_item->identity = BOTTLE_HALF_FULL_LIGHT_ID;
    return 0;
}


int use_half_full_light_bottle(struct player_t* p) {
    
    char name[] = "use_half_full_light_bottle";
    
    if (p == NULL) {
        player_null_error(name);
        return 1;
    }
    if (p->inventory == NULL) {
        inventory_null_error(name);
        return 1;
    }
    if (p->inventory->eq_consumable_item == NULL) {
        item_null_error(name);
        return 1;
    }
    
    // gain mana
    player_gain_mana(p, MANA_POTION_HEAL);
    
    p->inventory->eq_consumable_item->identity = BOTTLE_EMPTY_ID;
    return 0;
}






















//////////////////////////////////////////////

int take_player_enemy_damage(struct player_t* p) {

    char name[] = "take_player_enemy_damage";
    
    if (p == NULL) {
        player_null_error(name);
        return 1;
    }
    if (p->room == NULL) {
        room_null_error(name);
        return 1;
    }
    
    if (p->room->enemies != NULL) {
        
        // front load list
        while (p->room->enemies->prev != NULL) {
            p->room->enemies = p->room->enemies->prev;
        }
        
        Enemy_ls* tmp_ls = p->room->enemies;

        
        while (tmp_ls != NULL) {
            
            if (tmp_ls->enemy == NULL) {
                enemy_null_error(name);
            }
            
            else {
            
                if (p->base.x == tmp_ls->enemy->base.x && p->base.y == tmp_ls->enemy->base.y ) {
                
                    player_damage(p, tmp_ls->enemy->touch_dmg);
                }
            }
            
            
            tmp_ls = tmp_ls->next;
        }
    }
    
    
    return 0;
}
# endif
