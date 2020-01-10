# ifndef DRAW_MAP__
# define DRAW_MAP__

# include "tile_conversion.c"


int print_phone_ring_msg(struct room_t*, struct game_t*);
int overlay_dark_screen(struct game_t*, int*);
int append_entity_to_room_array(int*, int, int, struct entity_t*, int, int*, int);
int simple_append_entity_to_room_array(struct entity_t*, int*, struct room_t*, int);





int draw_map_error(char* object) {
    return null_error(object, "draw_map");
}


int draw_map(Game* game) {
    
    
    if (game == NULL) {
        draw_map_error(GAME_OBJECT);
        return 1;
    }
    
    Player* p = game->player;
    if (p == NULL) {
        draw_map_error(PLAYER_OBJECT);
        return 1;
    }
    
    
    Room* room = p->room;
    if (room == NULL) {
        draw_map_error(ROOM_OBJECT);
        return 1;
    }
    char* array = room->room_array;
    if (array == NULL) {
        draw_map_error(STRING_OBJECT);
        return 1;
    }
    
    int size = room->width * room->height;
    int tmp_array[size];
    
    
    
    // copy the elements from the room_array into the tmp_aray;
    for (int i = 0; i < size; i++) {
        tmp_array[i] = array[i];
    }
    
    
    append_items_to_room_array(room, tmp_array);
    
    append_spc_entities_to_room_array(room, tmp_array);
    
    
    // append exit objects;
    append_exits_to_room_array(room, tmp_array);
    
    append_chests_to_room_array(room, tmp_array);
    
    
    append_npcs_to_room_array(room, tmp_array);
    
    
    if (game->player_turn) {
        // likewise as above for enemies
        append_enemies_to_room_array(room, tmp_array);
    
    
        // last of all, copy over the player and their sword if being held
        append_player_to_room_array(room, tmp_array, p);
    }
    else {
        append_player_to_room_array(room, tmp_array, p);
        append_enemies_to_room_array(room, tmp_array);
    }
    
    
    
    // if the room is dark, for all tiles not 1 tile in front of player, set the room tiles dark.
    overlay_dark_screen(game, tmp_array);
    
    
    // finally, print the tmp_array:
    print_room_layout(tmp_array, room->width, room->height, p->base.direction);
    putchar('\n');
    
    
    
    
    print_phone_ring_msg(room, game);
    
    
    return 0;
}








// print the tmp_array room layout


int print_room_layout(int* tmp_array, int width, int height, int p_dir) {
    
    for (int i = 0; i < height; i++) {
        
        putchar(' ');
        putchar(' ');
        for (int j = 0; j < width; j++) {
            
            // player position and direction are translated into different sprites through this function.
            print_tile_sprite(tmp_array[j + i*width], p_dir);
        }
        putchar('\n');
        
    }
    return 0;
}







int append_dark_room(int*, int, int, int, int, int);


int overlay_dark_screen(struct game_t* g, int* tmp_array) {

    char* name = "overlay_dark_screen";
    
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
    
    Room* r = g->player->room;
    
    
    
    if (r->is_dark) {
        
        
        int dark_array[r->width * r->height];
        for (int i = 0; i < r->width * r->height; i++) {
            dark_array[i] = 0;
            // pre-set 0 <==> dark
        }
    
    
        // find the light radius around the player
        int p_x = g->player->base.x;
        int p_y = g->player->base.y;
        int light_dist = get_player_light_dist(g->player);
    
        dir_to_xy(g->player->base.direction, &p_x, &p_y);
    
        append_dark_room(dark_array, r->width, r->height, p_x, p_y, light_dist);
    
    
    
        // now find all lamps
    
    
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
            
                    if (tmp_ls->spc_entity->entity_id == SPC_LAMP_ID) {
                        
                        // see if lamp is turned on, else dont give light
                        if (get_lamp_on(tmp_ls->spc_entity)) {
                            
                            
                            int lx = tmp_ls->spc_entity->base.x;
                            int ly = tmp_ls->spc_entity->base.y;
                            light_dist = tmp_ls->spc_entity->base.light_dist;
                    
                            // annoying but sort through all room x,y
                            append_dark_room(dark_array, r->width, r->height, lx, ly, light_dist);
                        }
                    }
                }
        
                tmp_ls = tmp_ls->next;
            }
        }
        
     
        ///////////////////////////////////////////////
        
        
        // now give dark_array, overlay dark/visible
        
        for (int i = 0; i < r->height * r->width; i++) {
            if (!dark_array[i]) {
                // hence not lit up
                tmp_array[i] = DARK_N;
            }
        }
        
        
        
    }
    
    return 0;
}






int append_dark_room(int* array, int width, int height, int x, int y, int light_dist) {
    
    for (int i = 0; i < height; i++) {
        
        for (int j = 0; j < width; j++) {
            
            if (manhattan_metric(x, y, j, i) <= light_dist) {
                array[j + i*width] = 1;
                
                //printf("x,y: %d,%d;    ", j, i);
                
            }
        }
    }
    return 0;
}









// print_phone_messages

int print_phone_ring_msg(struct room_t* room, struct game_t* g) {

    char name[] = "print_phone_ring_msg";
    
    if (g == NULL) {
        game_null_error(name);
        return 1;
    }
    
    if (g->player == NULL) {
        player_null_error(name);
        return 1;
    }
    
    
    if (room == NULL) {
        room_null_error(name);
        return 1;
    }
    
    
    // final sort through special room entities to see if there exits a phone,
    // see if player is in rang and if so print ringing message
    
    if (room->spc_room_entities != NULL) {
        
        while (room->spc_room_entities->prev != NULL) {
            room->spc_room_entities = room->spc_room_entities->prev;
        }
        
        Spc_ent_ls* tmp_ls = room->spc_room_entities;
        
        while (tmp_ls != NULL) {
            
            if (tmp_ls->spc_entity != NULL) {
                
                
                if (tmp_ls->spc_entity->entity_id == SPC_TELEPHONE_ID) {
                    
                    int ring_id = get_telephone_ring_id(tmp_ls->spc_entity);
                    
                    
                    if (ring_id != NO_RING_ID) {
                        
                        
                        
                        int connected = 1;
                        int phone_trigger = get_telephone_trig_id(tmp_ls->spc_entity);
                        
                        if (phone_trigger > 0) {
                        
                            if (! get_game_trig(g, phone_trigger)) {
                                connected = 0;
                            }
                        }
                        
                        
                        if (connected) {
                        
                            if (ring_id == SIMPLE_RING_ID) {
                                print_str(SIMPLE_RING_MSG);
                            }
                        
                            else if (ring_id == LOCAL_SIMPLE_RING_ID) {
                            
                                if (manhattan_metric(tmp_ls->spc_entity->base.x,
                                                     tmp_ls->spc_entity->base.y,
                                                     g->player->base.x, g->player->base.y)
                                    <= get_telephone_dist(tmp_ls->spc_entity)) {
                                
                                print_str(SIMPLE_RING_MSG);
                                }
                            
                            }
                            
                            
                            else {
                                printf("ERROR: invalid ring_id value: %d\n", ring_id);
                            }
                        }
                    }
                }
            }
            
            tmp_ls = tmp_ls->next;
        }
    }
    return 0;
}












// do null-checks prior to being given to below functions


// APPEND ITEM SPRITES ONTO TEMPORARY ROOM ARRAY

int append_items_to_room_array(struct room_t* room, int* tmp_array) {

    // sort through entities and copy them onto the tmp_array, overwriting room tiles
    int cont = 1;
    Item_ls* items_ = room->items;
    if (items_ == NULL) {
        cont = 0;
    }
    
    while (cont) {
        
        if (items_->item == NULL) {
            item_null_error("append_items_to_room_array");
        }
        
        else {
        
            int tile = item_to_code(items_->item);
            if (tile >= 0) {
            
                simple_append_entity_to_room_array(&(items_->item->base), tmp_array, room, tile);
            }
        }
        
        if (items_->next == NULL) {
            cont = 0;
        }
        else {
            items_ = items_->next;
            
        }
    }

    
    return 0;
}





// APPEND ENEMY SPRITES ONTO TEMPORARY ROOM ARRAY

// need to factor in enemy directions, havent done so yet.
// possible implementation, an array/linked list of tiles (index) and char values
// possibly reimplement enemies so that they are a linked list themselves.

int append_enemies_to_room_array(struct room_t* room, int* tmp_array) {

    // sort through entities and copy them onto the tmp_array, overwriting room tiles
    
    int cont = 1;
    Enemy_ls* enemies_ = room->enemies;
    if (enemies_ == NULL) {
        cont = 0;
    }
    
    while (cont) {
        
        if (enemies_->enemy == NULL) {
            enemy_null_error("append_enemies_to_room_array");
        }
        
        else {
        
            int tile = enemy_to_code(enemies_->enemy);
            if (tile >= 0) {
                simple_append_entity_to_room_array(&(enemies_->enemy->base), tmp_array, room, tile);
            }
        }
        
        if (enemies_->next == NULL) {
            cont = 0;
        }
        else {
            enemies_ = enemies_->next;
        }
    }

    return 0;
}















//////////////////////////////////////////////////////////////////////////////////////////

Exit_ls* exit_loop(Exit_ls*, int*, int);


// append exits from room, to the tmp_array

int append_exits_to_room_array(struct room_t* room, int* tmp_array) {
    //int output = 0;
    
    if (room->exits != NULL) {
    
        Exit_ls* exit_list = room->exits;
        
        if (exit_list->exit == NULL) {
            null_error(EXIT_OBJECT, "append_exits_to_room_array");
            return 1;
        }
        else {
            Exit* ext = exit_list->exit;
            int real_key = ext->key;
            int tmp_key = 0;
            
            exit_list = exit_loop(exit_list, tmp_array, room->width);
            if (exit_list == NULL) {
                return 1;
            }
            
            tmp_key = exit_list->exit->key;
            
            while (tmp_key != real_key) {
            //loop above
            
                exit_list = exit_loop(exit_list, tmp_array, room->width);
                
                if (exit_list == NULL) {
                    return 1;
                }
                
                tmp_key = exit_list->exit->key;
            }
            
        }
        
    }
    
    return 0;
}



Exit_ls* exit_loop(Exit_ls* exit_list, int* tmp_array, int width) {

    if (!get_door_hidden(exit_list->exit)) {
        tmp_array[exit_list->exit->x + exit_list->exit->y * width] = door_number(exit_list->exit);
    }
    else if ((door_is_bombable(exit_list->exit) && door_is_locked(exit_list->exit)) ||
             (door_is_switch(exit_list->exit) && door_is_locked(exit_list->exit))) {
        tmp_array[exit_list->exit->x + exit_list->exit->y * width] = WALL_N;
    }
    // door number function is in "tile conversion"
    
    
    
    if (exit_list->next == NULL) {
        null_error(EXIT_LS_OBJECT, "append_exits_to_room_array");
        return NULL;
    }
    
    
    Exit_ls* output = exit_list->next;
    Exit* ext = output->exit;
    if (ext == NULL) {
        null_error(EXIT_OBJECT, "append_exits_to_room_array");
        return NULL;
    }

    return output;
}










int append_chests_to_room_array(struct room_t* r, int* array) {

    if (r == NULL) {
        room_null_error("append_chests_to_room_array");
        return 1;
    }
    if (array == NULL) {
        null_error(STRING_OBJECT, "append_chests_to_room_array");
        return 1;
    }
    
    
    if (r->chests != NULL) {
        
    
        int i = 0;
        int cont = 1;
        Chest_ls* tmp_p = r->chests;
        
        while (i < r->width * r->height && cont) {
    
            if (r->room_array[i] == CHEST_N) {
                
                
                if (tmp_p->chest->locked) {
                    array[i] = CHEST_LOCKED_N;
                }
                else {
                    if (tmp_p->chest->item == NULL) {
                        array[i] = CHEST_OPEN_N;
                    }
                    
                    else {
                        array[i] = CHEST_CLOSED_N;
                    }
                }
                
                tmp_p = tmp_p->next;
                if (tmp_p == NULL) {
                    cont = 0;
                }
            }
            
            i++;
        }
    }

    return 0;
}








////////////////////////////////////////////////////////////////////////////////////////////////

//
int simple_sword_to_code(int);

int append_player_to_room_array(struct room_t* room, int* tmp_array, struct player_t* p) {

    int px = p->base.x;
    int py = p->base.y;
    //int player_pos = room->width*py + px;
    
    int dir = p->base.direction;
    
    int sx = px;
    int sy = py;
    
    dir_to_xy(dir, &sx, &sy);
    
    
    
    if (player_equipped_sword(p)) {
    
        // sword (x,y), let this be the square the player is facing;
        
        int c = tmp_array[sx + sy * room->width];
        if (c == FLOOR_N || c == INVISIBLE_WALL_N) {  //(!is_clip_tile(c)) {
            tmp_array[sx + sy * room->width] = simple_sword_to_code(dir);
        }
    }
    
    
    simple_append_entity_to_room_array(&(p->base), tmp_array, room, PLAYER_N);
    return 0;
}






int simple_sword_to_code(int dir) {
    char output = 0;
    if (dir == 0) {
        output = SWORD_VERTICAL_N;
    }
    else if (dir == 1) {
        output = SWORD_DIAG_LEFT_N;
    }
    else if (dir == 2) {
        output = SWORD_VERTICAL_N;
    }
    else if (dir == 3) {
        output = SWORD_DIAG_RIGHT_N;
    }

    return output;
}








////////////////////////////////////////////////////////////////////////////////////////////////

//




int append_spc_entities_to_room_array(struct room_t* r, int* tmp_array) {

    if (tmp_array == NULL) {
        null_error("temporary room_array", "append_spc_entities_to_room_array");
        return 1;
    }
    if (r == NULL) {
        room_null_error("append_spc_entities_to_room_array");
        return 1;
    }
    
    
    
    // now for the room objects
    if (r->spc_room_entities != NULL) {
        
        while (r->spc_room_entities->prev != NULL) {
            r->spc_room_entities = r->spc_room_entities->prev;
        }
        
        Spc_ent_ls* tmp_ls = r->spc_room_entities;
        while (tmp_ls != NULL) {
            
            
            if (tmp_ls->spc_entity == NULL) {
                null_error(SPECIAL_ENTITY_OBJECT, "append_spc_entities_to_room_array");
            }
            
            else {
                int tmp_x = tmp_ls->spc_entity->base.x;
                int tmp_y = tmp_ls->spc_entity->base.y;
                
                if (tmp_x < 0 || tmp_x >= r->width || tmp_y < 0 || tmp_y >= r->height) {
                    printf("WARNING: special entity with id: %d, is out of bounds, x: %d, y: %d\n",
                           tmp_ls->spc_entity->entity_id, tmp_x, tmp_y);
                    pause_function();
                }
                
                
                else {
                    int tile = spc_entity_to_tile(tmp_ls->spc_entity);
                    if (tile != NONE_N) {
                        
                        simple_append_entity_to_room_array(&(tmp_ls->spc_entity->base),
                                                           tmp_array, r, tile);
                    }
                }
            }
            
            tmp_ls = tmp_ls->next;
        }
    }

    
    
    
        // weapon entities last.
    
    if (r->spc_weapon_entities != NULL) {
    
        while (r->spc_weapon_entities->prev != NULL) {
            r->spc_weapon_entities = r->spc_weapon_entities->prev;
        }
        
        Spc_ent_ls* tmp_ls = r->spc_weapon_entities;
        while (tmp_ls != NULL) {
            
            if (tmp_ls->spc_entity == NULL) {
                null_error(SPECIAL_ENTITY_OBJECT, "append_spc_entities_to_room_array");
            }
            
            else {
                int cont = 1;
                int tmp_x = tmp_ls->spc_entity->base.x;
                int tmp_y = tmp_ls->spc_entity->base.y;
                
                if (tmp_x < 0 || tmp_x >= r->width || tmp_y < 0 || tmp_y >= r->height) {
                    printf("WARNING: special entity with id: %d, is out of bounds, x: %d, y: %d\n",
                           tmp_ls->spc_entity->entity_id, tmp_x, tmp_y);
                    pause_function();
                    cont = 0;
                }
                    
                if (cont && tmp_ls->spc_entity->entity_id == SPC_SMOKE_ID) {
                    
                    int tmp_tile = get_room_tile(r, tmp_x, tmp_y);
                    
                    if (tmp_tile != CRACKED_WALL_N) {
                        if (is_clip_tile(tmp_tile)) {
                            cont = 0;
                        }
                    }
                }
                
                if (cont) {
                    int tile = spc_entity_to_tile(tmp_ls->spc_entity);
                    if (tile != NONE_N) {
                        simple_append_entity_to_room_array(&(tmp_ls->spc_entity->base),
                                                           tmp_array, r, tile);
                    }
                }
            }
            
            tmp_ls = tmp_ls->next;
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////











int append_npcs_to_room_array(struct room_t* r, int* tmp_array) {

    char name[] = "append_npcs_to_room_array";
    if (r == NULL) {
        room_null_error(name);
        return -1;
    }
    if (tmp_array == NULL) {
        null_error("Room tmp_array", name);
        return -1;
    }
    
    
    if (r->npcs != NULL) {
    
        while (r->npcs->prev != NULL) {
            r->npcs = r->npcs->prev;
        }
        
        Npc_ls* tmp_ls = r->npcs;
        
        
        
        while (tmp_ls != NULL) {
        
            if (tmp_ls->character == NULL) {
                npc_null_error(name);
            }
            
            
            
            
            else {
                int tile = npc_to_tile(tmp_ls->character);
                
                
                
                
                if (tmp_ls->character->character_id == SHOPKEEPER_ID) {
                
                    // sort through items held in inventory and dislpay them
                    if (tmp_ls->character->items != NULL) {
                    
                        while (tmp_ls->character->items->prev != NULL) {
                            tmp_ls->character->items = tmp_ls->character->items->prev;
                        }
                        
                        
                        Item_ls* tmp_item_ls = tmp_ls->character->items;
                        
                        
                        while (tmp_item_ls != NULL) {
                            
                            if (tmp_item_ls->item == NULL) {
                                item_null_error(name);
                            }
                            
                            
                            
                            else {
                                int item_tile = item_to_code(tmp_item_ls->item);
                                simple_append_entity_to_room_array(&(tmp_item_ls->item->base),
                                                                   tmp_array, r, item_tile);
                            
                            
                            }
                            tmp_item_ls = tmp_item_ls->next;
                        }
                    }
                }
                
                
                
                
                
                simple_append_entity_to_room_array(&(tmp_ls->character->base),
                                                       tmp_array, r, tile);
                
            }
            
            
        
        
            tmp_ls = tmp_ls->next;
        }
    }



    return 0;
}













//simple_append_entity_to_room_array(e, tmp_array, r, tile);


int simple_append_entity_to_room_array(struct entity_t* e, int* array, struct room_t* r, int tile) {

    if (r == NULL) {
        room_null_error("simple_append_entity_to_room_array");
        return 1;
    }
    if (tile == NONE_N) {
        return 0;
    }
    
    else {
        int tiles[] = {tile};
        return append_entity_to_room_array(array, r->width, r->height, e, e->direction, tiles, 1);
    }
                                       
}








int append_entity_to_room_array(int* array, int room_w, int room_h, struct entity_t* e, int dir,
                                int* tiles, int len) {

    char name[] = "append_entity_to_room_array";
    
    
    if (e == NULL) {
        entity_null_error(name);
        return 1;
    }
    
    int x = e->x;
    int y = e->y;
    
    if (x < 0 || y < 0 || x >= room_w || y >= room_h) {
        return 0;
    }
    

    
    if (array == NULL) {
        null_error("TMP Room Array", name);
        return 1;
    }
    if (len <= 0) {
        printf("VALUE ERROR: invalid char tile length %d, for function: '%s'.\n", len, name);
        return 1;
    }
    if (tiles == NULL) {
        null_error("Tile Chars", name);
        return 1;
    }
    
    
    
    if (e->default_hit_box == NULL || e->hit_box == NULL) {
        
        array[x + room_w * y] = tiles[0];
    }
    
    else {
    
    
    
        // main function for large entities
        
        int h = e->tmp_height;
        int w = e->tmp_width;
        int ex = e->e_x;
        int ey = e->e_y;
 
        
        // appending the array
        int count = 0;
        
        for (int iy = 0; iy < h; iy ++) {
            
            for (int ix = 0; ix < w; ix++) {
                
                if (e->hit_box[ix + iy * w]) {
                    
                
                    // now append to the array
                    //printf("Tmpx,y: %d,%d\n", x + ix - ex, y + iy - ey);
                    
                    int tmp_x = x + ix - ex;
                    int tmp_y = y + iy - ey;
                    
                    if (tmp_x < 0 || tmp_y < 0 || tmp_x >= room_w || tmp_y >= room_h) {;}
                    
                    else {
                    
                        array[tmp_x + room_w * tmp_y] = tiles[count];
                    
                        count++;
                        if (count == len) {
                            count = 0;
                        }
                    }
                }
            }
        
        }
    }
    
    
    return 0;
}





# endif
