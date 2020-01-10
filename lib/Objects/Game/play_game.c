# ifndef START_GAME_
# define START_GAME_

# include "../../Draw_functions/draw.c"
# include <unistd.h>


int get_turn_cycle_len(struct game_t*, int*, int*);





//////////////////////////

int play_game(Game* game) {

    if (game == NULL) {
        printf("Error occured in receiving game.\n");
        return -1;
    }
    
    int exit = 0;
    if (game->error) {
        return exit;
    }
    
    // null checks
    
    if (game->rooms == NULL){
        null_error(ROOM_LS_POINTER, "play_game");
        return -1;
    }
    if (game->room_len > 0 && game->rooms[0] == NULL) {
        null_error(ROOM_LS_OBJECT, "play_game");
        return -1;
    }
    
    
    if (game->player == NULL) {
        player_null_error("player_game");
        return -1;
    }
    
    
    
    int player_turn_cycle = 1;
    int player_turn_num = player_turn_cycle;
    
    int other_turn_cycle = 1;
    int other_turn_num = other_turn_cycle;
    
    
    
    while (!exit) {
        
        if (game->time == MAX_TIME) {
            break;
        }
        
        draw_screen(game);
        
        
        player_turn_num--;
        if (player_turn_num <= 0) {
            
            player_turn_num = player_turn_cycle;
        
            exit = player_turn(game);
        
        
            // if menu option was chosen, enter the menu and stay in it until the menu is exited.
            while (!exit && game->inventory) {
                exit = player_turn(game);
            }
            
            
            get_turn_cycle_len(game, &player_turn_cycle, &other_turn_cycle);
        }
    
        
        
        // enemy and entity turns
    
        
        if (!exit && !game->inventory) {
            
            other_turn_num --;
            if (other_turn_num <= 0) {
            
                other_turn_num = other_turn_cycle;
            
                
                
                // if hard, replaced first player turn with a wait move.
                
                draw_screen(game);
                int spc_ent_wait = game->player->room->spc_weapon_entities != NULL;
                increment_spc_entity_time(game);
                
                
                //draw_screen(game);
                int enemy_wait = game->player->room->enemies != NULL;
                exit = enemy_turn(game);
                
                
                // sleep some time
                if (spc_ent_wait || enemy_wait){
                    // hence only sleep if there are enemies or room enemies.
                    usleep(SLEEP_TIME);
                }
                
                
                if (!exit) {
                    game->time++;
                }
            }
            
        }
    }

    if (game->options.command_debug) {
        printf("Game time: %ld\n", game->time);
    }
    return exit;
}










int get_turn_cycle_len(struct game_t* game, int* player_turn_cycle, int *other_turn_cycle) {

    if (player_turn_cycle == NULL || other_turn_cycle == NULL) {
        null_error("Integer Pointer", "get_turn_cycle");
        return 1;
    }
    if (game->player->room == NULL) {
        room_null_error("get_turn_cycle");
        return 1;
    }
    
    
    *other_turn_cycle = 1;
    *player_turn_cycle = 1;
    
    
    if (game->player->inventory->eq_passive_item != NULL) {
        
        int i_id = game->player->inventory->eq_passive_item->identity;
        
        
        if (i_id == HOURGLASS_ID) {
        
            if (game->player->base.mana > 0) {
                *other_turn_cycle = HOURGLASS_TURN_NUM;
                
                // if player is about to player a game, decrease mana. not every turn.
                if (game->player->base.timer <= 1) {
                    player_use_mana(game->player, HOURGLASS_DRAIN);
                }
            }
        }
        
        if (i_id == ANTI_HOURGLASS_ID) {
            
            if (game->player->base.mana < game->player->base.max_mana) {
                if (game->player->room->enemies != NULL) {
                    
                    *player_turn_cycle = ANTI_HOURGLASS_TURN_NUM;
                    
                    // if player is about to player a game, increase mana. not every turn.
                    if (game->player->base.timer <= 1) {
                        player_gain_mana(game->player, ANTI_HOURGLASS_GAIN);
                    }
                }
            }
        }
    }
    return 0;
}





# endif
