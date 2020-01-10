# ifndef GAME_TIME_
# define GAME_TIME_

int game_time_null_error(char* str) {
    return null_error(str, "increment_game_time");
}

int increment_game_time(Game* game) {

    if (game == NULL) {
        game_time_null_error(GAME_OBJECT);
        return 1;
    }
    if (!game->inventory) {
        if (game->player == NULL) {
            game_time_null_error(PLAYER_OBJECT);
            return 1;
        }
        if (game->player->room == NULL) {
            game_time_null_error(ROOM_OBJECT);
            return 1;
        }
    
        // now update, player and room clocks;
    
        increment_player_clock(game->player);
        increment_room_clock(game->player->room, 1);
    }
    return 0;
}









// player clock

int increment_player_clock(Player* p) {

    increment_entity_clock(&(p->base), 1);
    return 0;
}


int increment_room_clock(Room* room, int t) {
    room->update_time += t;
    
    if (room->items != NULL) {
        increment_room_items_clock(first_item_node(room->items), t);
    }
    
    if (room->enemies != NULL) {
        increment_room_enemies_clock(first_enemy_node(room->enemies), t);
    }
    return 0;
}


// item list, and item

int increment_room_items_clock(Item_ls* items, int t) {
    if (items == NULL) {
        return 0;
    }
    
    increment_room_items_clock(items->next, t);
    
    
    if (items->item == NULL) {
        null_error(ITEM_OBJECT, "increment_room_items");
        return 1;
    }
    
    return increment_item_clock(items->item, t);
}

int increment_item_clock(Item* item, int t) {
    increment_entity_clock(&(item->base), t);
    return 0;
}



// enemy list, and enemy

int increment_room_enemies_clock(Enemy_ls* enemies, int t) {
    if (enemies == NULL) {
        return 0;
    }
    
    increment_room_enemies_clock(enemies->next, t);
    
    
    if (enemies->enemy == NULL) {
        null_error(ENEMY_OBJECT, "increment_room_enemies");
        return 1;
    }
    
    return increment_enemy_clock(enemies->enemy, t);
}

int increment_enemy_clock(Enemy* enemy, int t) {
    return increment_entity_clock(&(enemy->base), t);
}







# endif
