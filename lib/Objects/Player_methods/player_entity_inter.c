# ifndef PLAYER_ENEMY_INTERACTIONS__
# define PLAYER_ENEMY_INTERACTIONS__

int collect_items_error(char* object) {
    return null_error(object, "player_collect_items");
}





int player_collect_items(struct game_t* g, int interact) {
    char name[] = "player_collect_items";
    
    if (g == NULL) {
        game_null_error(name);
        return 1;
    }
    if (g->player == NULL) {
        player_null_error(name);
        return 1;
    }
    
    Room* room = g->player->room;
    if (room == NULL) {
        room_null_error(name);
        return 1;
    }
    
    if (room->items == NULL) {
        return 0;
    }
    
    
    Item_ls* items = first_item_node(room->items);
    
    while (items != NULL) {
        Item_ls* tmp_item = items->next;
        item_player_interaction(g, g->player, items, interact);
    
        items = tmp_item;
    }

    return 0;
}








///////////////////////////////////////////////////////////////////

int item_player_interaction(Game* g, Player* p, Item_ls* i, int interaction) {

    if (i->item == NULL) {
        null_error(ITEM_OBJECT, "item_player_interaction");
        return 1;
    }

    int in = 0;
    
    int px = player_x_pos(p);
    int py = player_y_pos(p);
    int ix = item_x_pos(i->item);
    int iy = item_y_pos(i->item);
    
    //int collide = is_entity_clip(&(i->item));
    
    if (px == ix && py == iy) {
    //if (entity_entity_collide(&(p->)))
        in = 1;
        
        int stop;
        stop = pickup_item(g, i->item);
        
        if (stop >= 0) {
            kill_item(p->room, i);
        }
        
        else {
            
            if (stop < -1) {
                // pop item off, i.e. dont free item, but free item list.
                pop_item_ls_room(i, p->room);
            }
        }
        
    }

    
    
    else if (!in && interaction) {
        
        dir_to_xy(p->base.direction, &px, &py);
        
        
        if (px == ix && py == iy) {
            // this means an interaction should occur, i.e. print item entity string if not null.
            
            if (1) { //(i->item->base.msg != NULL) {

                if (i->item->base.msg[0] != 0) {
                    printf("%s", i->item->base.msg);
                    pause_function();
                }
            }
        }
    }
    return 0;
}



////////////////////////////////////////////////////////////////////

// item pick up



int pickup_item(struct game_t* g, Item* i) {
    if (g == NULL) {
        game_null_error("pickup_item");
        return 1;
    }
    
    Player* p = g->player;
    if (p == NULL) {
        player_null_error("pickup_item");
        return 1;
    }
    if (i == NULL) {
        item_null_error("pickup_item");
        return 1;
    }
    
    
    int i_id = i->identity;
    
    if (i_id < 100) {
        if (i_id == HEART_ID) {
            if (p->base.health >= p->base.max_health) {
                // implemented so the player does not pick up the heart if they have full health.
                return -1;
            }
            player_heal(p, i->num);
        }
        else if (i_id == KEY_ID) {
            p->inventory->key_num += i->num;
        }
        else if (i_id == COIN_ID) {
            p->inventory->coin_num += i->num;
            if (p->inventory->coin_num > MAX_PURSE) {
                p->inventory->coin_num = MAX_PURSE;
            }
        }
    
        else if (i_id == BOMB_ID) {
            if (has_item(p->inventory, BOMB_BAG_ID)) {
                p->inventory->bomb_num += i->num;
            }
            else {
                return -1;
            }
        }
    
        else if (i_id == ARROW_ID) {
            if (has_item(p->inventory, BOW_ID)) {
                p->inventory->arrow_num += i->num;
            }
            else {
                return -1;
            }
        }
    
        else if (i_id == MANA_ID) {
            if (p->base.mana >= p->base.max_mana) {
                return -1;
            }
            player_gain_mana(p, i->num);
        }
        
        else if (i_id == HEALTH_CONTAINER_ID) {
            player_gain_health_container(p, i->num);
        }
        
        else if (i_id == MANA_CONTAINER_ID) {
            player_gain_mana_container(p, i->num);
            if (!p->has_mana && p->base.max_mana > 0) {
                p->has_mana = 1;
            }
        }
        
        else if (i_id == FREEZE_ID) {
            p->loop = FREEZE_LOOP_LEN * i->num;
        }
    
        else {
            printf("Item pickup not implemented for: %d\n", i_id);
            pause_function();
            return -1;
        }
    }
    
    
    
    
    
    
    
    else {
        // this implies that it is an inventory item
    
        give_player_item(g, i);
        if (i->base.msg[0] != 0) {
            print_dialogue_msg(i->base.msg, NULL, g);
            putchar('\n'); putchar('\n');
            pause_function();
        }
        return -2;
    }

    return 0;
}








/*
int item_interaction(struct item_t* i) {
    if (i->msg != NULL) {
        printf("%s\n", i->msg);
        pause_function();
    }
    return 0;
}*/

///////////////////////////////////////////////////////////////





int player_spc_entity_interaction(struct game_t* g, int interact) {

    char f_name[] = "player_spc_entity_interaction";
    
    if (g == NULL) {
        game_null_error(f_name);
        return 1;
    }
    if (g->player == NULL) {
        player_null_error(f_name);
        return 1;
    }
    
    Room* r = g->player->room;
    if (r ==  NULL) {
        room_null_error(f_name);
        return 1;
    }
    
    int exit = 0;
    
    int p_x = g->player->base.x;
    int p_y = g->player->base.y;
    
    int tmp_x = p_x;
    int tmp_y = p_y;
    dir_to_xy(g->player->base.direction, &tmp_x, &tmp_y);
    
    
    if (r->spc_weapon_entities != NULL) {
        
        Spc_ent_ls* tmp_ls = r->spc_weapon_entities;
        
        while (tmp_ls != NULL) {
        
            if (tmp_ls->spc_entity != NULL) {
                if (tmp_ls->spc_entity->base.x == p_x && tmp_ls->spc_entity->base.y == p_y) {
                
                    // do something
                }
                
                
                else {
                    
                    if (tmp_x == tmp_ls->spc_entity->base.x && tmp_x == tmp_ls->spc_entity->base.x) {
                    
                        if (interact) {
                            
                            // do something...
                        }
                    }
                }
            }
            
            if (tmp_ls != NULL) {
                tmp_ls = tmp_ls->next;
            }
        }
    }
    
    
    
    // now for the room specific special entities
    
    if (r->spc_room_entities != NULL) {
        
        
        Spc_ent_ls* tmp_ls = r->spc_room_entities;
        
        while (tmp_ls != NULL) {
            
            if (tmp_ls->spc_entity != NULL) {
                int ent_id = tmp_ls->spc_entity->entity_id;
                
                if (tmp_ls->spc_entity->base.x == p_x && tmp_ls->spc_entity->base.y == p_y) {
                    
                    // do something
                    
                    // in this case, check if the item is a flag:
                    
                    if (ent_id == SPC_FLAG_ID) {
                        if (tmp_ls->spc_entity->base.health) {
                            exit = -1;
                            tmp_ls = NULL;
                        }
                        
                        else {
                            printf("The flag seems to have been cut...\n");
                            pause_function();
                        }
                    }
                }
                
                
                else {
                    
                    if (tmp_x == tmp_ls->spc_entity->base.x && tmp_y == tmp_ls->spc_entity->base.y) {
                        
        
                        if (interact) {
                            
                            // do something...
                            
                            
                            // check if the item is a telephone and if so answer it.
                            if (ent_id == SPC_TELEPHONE_ID) {
                            
                                if (tmp_ls->spc_entity->base.health > 0) {
                                
                                    
                                    if (get_telephone_activated(tmp_ls->spc_entity)) {
                                   
                                        
                                        // main function
                                    
                                    
                                        // see if the telephone is switched on
                                        int trig_id = get_telephone_trig_id(tmp_ls->spc_entity);
                                        int is_open = 1;
                                    
                                        if (trig_id > 0) {
                                            is_open = get_game_trig(g, trig_id);
                                        }
                                    
                                    
                                        if (is_open) {
                                            // FIRST set ring id to zero so it doesn't ring again
                                            set_telephone_ring_id(tmp_ls->spc_entity, NO_RING_ID);
                                            
                                            
                                            print_dialogue_msg(tmp_ls->spc_entity->base.msg,
                                                               MYSTERY_VOICE, g);
                                            
                                            putchar('\n');
                                            putchar('\n');
                                            pause_function();
                                        
                                        
                                            // now activate trig ids
                                        
                                            trig_id = get_telephone_trig_activate(tmp_ls->spc_entity);
                                        
                                            if (trig_id > 0) {
                                                set_game_trig(g, trig_id, 1, SIMPLE_SWITCH_TYPE);
                                            }
                                        }
                                    }
                                    
                                    else {
                                        printf("The phone seems to be disconnected...\n");
                                        pause_function();
                                    }
                                }
                                
                                else {
                                    printf("The phone seems to be broken...\n");
                                    pause_function();
                                }
                            }
                            
                            
                            
                            else if (ent_id == SPC_SWITCH_ID) {
 
                                activate_switch(tmp_ls->spc_entity, g);
                            }
                            
                            else {;}
                        }
                    }
                }
            }
            
            if (tmp_ls != NULL) {
                tmp_ls = tmp_ls->next;
            }
        }
    }

    return exit;
}



/////////////////////////////////////////////////////////////











int player_npc_interaction(struct game_t* g, int interact) {

    char name[] = "player_npc_interaction";
    
    if (g == NULL) {
        game_null_error(name);
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
    
    
    int cont = 1;
    
    if (interact) {
    
        if (g->player->room->npcs != NULL) {
    
            while (g->player->room->npcs->prev != NULL) {
                g->player->room->npcs = g->player->room->npcs->prev;
            }
        
        
            
            Npc_ls* tmp_ls = g->player->room->npcs;
            
            int x = g->player->base.x;
            int y = g->player->base.y;
            
            dir_to_xy(g->player->base.direction, &x, &y);
            
            
            if (x < 0 || y < 0 || x >= g->player->room->width || y >= g->player->room->height) {;}
            
            
            else {
            
    
                while (tmp_ls != NULL && cont) {
        
                    
                    if (tmp_ls->character == NULL) {
                        npc_null_error(name);
                    }
            
                    else {
            
                        ////
                        ////    MAIN ANALYSIS
                        ////
                    
                        int c_id = tmp_ls->character->character_id;
                    
                    
                        if (c_id == SIMPLE_NPC_ID) {
                    
                            if (entity_entity_collide(&(g->player->base), x, y, &(tmp_ls->character->base))) {
                                
                                print_dialogue_msg(tmp_ls->character->dialogue,
                                                   tmp_ls->character->base.msg, g);
                                putchar('\n');
                                putchar('\n');
                                pause_function();
                            }
                        }
                        
                        
                        
                        
                        else if (c_id == SHOPKEEPER_ID) {
                        
                            if (entity_entity_collide(&(g->player->base), x, y, &(tmp_ls->character->base))) {
                                
                                print_dialogue_msg(tmp_ls->character->dialogue,
                                                   tmp_ls->character->base.msg, g);
                                
                                putchar('\n');
                                putchar('\n');
                                pause_function();
                            }
                            
                            
                            
                            else {
                                
                                
                                if (tmp_ls->character->items != NULL) {
                                
                                    while (tmp_ls->character->items->prev != NULL) {
                                        tmp_ls->character->items = tmp_ls->character->items->prev;
                                    }
                                    
                                    
                                    Item_ls* tmp_item_ls = tmp_ls->character->items;
                                    
                                    // sort through the item list and see if there are any items that overlap.
                                    
                                    
                                    while (tmp_item_ls != NULL && cont) {
                                        int popped = 0;
                                        
                                        
                                        
                                        if (tmp_item_ls->item == NULL) {
                                            item_null_error(name);
                                        }
                                        
                                        
                                        else {
                                            int cost = get_item_price(tmp_item_ls->item);
                                            
                                            // if negative cost, reserve item as 'display' item
                                            // item is buyable
                                            
                                            if (cost >= 0) {
                                                
                                                
                                                if (entity_entity_collide(&(g->player->base), x, y,
                                                                          &(tmp_item_ls->item->base))) {
                                            
                                                
                                                    // since hit boxes of the item and player overlap,
                                                    // interact with item!!!
                                                
                                                    
                                                
                                                    // print message requesting to buy the item, and say cost
                                                
                                                    print_buy_item_msg(tmp_item_ls->item->identity, cost,
                                                                       tmp_item_ls->item->num);
                                                
                                                    char input = getchar();
                                                    if (input != '\n' && input != EOF) {
                                                        flush_input();
                                                    }
                                                    
                                                    cont = 0;
                                                    // don't interact / buy multiple items if they
                                                    // are in the same spot!
                                                    
                                                    
                                                    
                                                    if (input == 'y' || input == 'Y') {
                                                    
                                                        // CONFIRM ITEM PURCHAS:
                                                        
                                                        int player_coins = g->player->inventory->coin_num;
                                                        
                                                        if (cost > player_coins)  {
                                                            printf("Sorry insufficient coins\n");
                                                            pause_function();
                                                        }
                                                        
                                                        else {
                                                        
                                                            // buy item
                                                            //printf("Thank you!   ");
                                                            //pause_function();
                                                            
                                                            Item_ls* tmptmp_ls = tmp_item_ls;
                                                            tmp_item_ls = tmp_item_ls->next;
                                                            popped = 1;
                                                            
                                                            
                                                            Item* i = pop_item_ls_npc(tmptmp_ls,
                                                                                      tmp_ls->character);
                                                            
                                                            int not_pickup;
                                                            not_pickup = give_player_item(g, i);
                                                            
                                                            if (not_pickup) {
                                                                printf("Unable to receive item.\n\n");
                                                                pause_function();
                                                                
                                                                tmp_ls->character->items = push_item_start(
                                                                tmp_ls->character->items, i);
                                                                
                                                            }
                                                            
                                                            else {
                                                                g->player->inventory->coin_num -= cost;
                                                            }
                                                            
                                                        }
                                                    }
                                                
                                                
                                                }
                                            }
                                        
                                        
                                        
                                        }
                                    
                                        if (!popped) {
                                            tmp_item_ls = tmp_item_ls->next;
                                        }
                                    }
                                }
                            
                            }
                        }
                        
                        
                        
                        
                        
                        else {
                            printf("ERROR: unknown NPC with id: %d\n", c_id);
                            pause_function();
                        }
                
                    }
                    
                    tmp_ls = tmp_ls->next;
                }
            }
    
    
        }
    }

    return 0;
}










# endif
