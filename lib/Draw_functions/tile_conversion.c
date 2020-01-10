# ifndef TILE_CONVERSION_
# define TILE_CONVERSION_

# define NONE_N 126


// convert item into coded char value

int item_to_code(Item* item) {
    
    if (item == NULL) {
        null_error(ITEM_OBJECT, "item_to_code");
        return -1;
    }
    
    int i_id = item->identity;
    
    if (i_id < 100) {
        if (i_id == HEART_ID) { return HEART_N;}
    
        if (i_id == KEY_ID) { return KEY_N;}
    
        if (i_id == BOMB_ID) { return BOMB_N;}
    
        if (i_id == COIN_ID) { return COIN_N;}
    
        if (i_id == ARROW_ID) { return ARROW_N;}
    
        if (i_id == MANA_ID) { return MANA_N;}
    
        if (i_id == HEALTH_CONTAINER_ID) { return HEART_CONTAINER_N;}
        
        if (i_id == MANA_CONTAINER_ID) { return MANA_CONTAINER_N;}
        
        if (i_id == FREEZE_ID) { return FREEZE_N;}
        
        else {
            printf("Undefined item identity: %d\n", i_id);
        }
    }
    
    else if (i_id < 200) {
        if (i_id == POINTER_ID) { return INV_POINTER_N;}
        
        if (i_id == BASIC_SWORD_ID) { return INV_SWORD_N;}
        
        if (i_id == STAFF_ID) { return INV_STAFF_N;}
        
        if (i_id == MAGIC_STAFF_ID) { return INV_MAGIC_STAFF_N;}
        
        if (i_id == BOW_ID) { return INV_BOW_N;}
        
        if (i_id == STOPWATCH_ID) { return INV_STOPWATCH_N;}
        
        
        else { printf("Undefined item ientity: %d\n", i_id);}
    }
    
    
    else if (i_id < 300) {
    
        if (i_id == BOMB_BAG_ID) { return INV_BOMB_N;}
        
        if (i_id == PRESENT_ID) { return INV_PRESENT_N;}
        
        if (i_id == BOTTLE_EMPTY_ID) { return INV_EMP_BOT_N;}
        
        if (i_id == BOTTLE_FULL_DARK_ID) { return INV_DARK_BOT_FULL_N;}
        
        if (i_id == BOTTLE_HALF_FULL_DARK_ID) { return INV_DARK_BOT_HFULL_N;}
        
        if (i_id == BOTTLE_FULL_MED_ID) { return INV_MED_BOT_FULL_N;}
        
        if (i_id == BOTTLE_HALF_FULL_MED_ID) { return INV_MED_BOT_HFULL_N;}
        
        if (i_id == BOTTLE_FULL_LIGHT_ID) { return INV_LIGHT_BOT_FULL_N;}
        
        if (i_id == BOTTLE_HALF_FULL_LIGHT_ID) { return INV_LIGHT_BOT_HFULL_N;}
        
        
        else { printf("Undefined item identity: %d\n", i_id);}
    }
    
    
    else {
    
        if (i_id == BASIC_SHIELD_ID) { return INV_SHIELD_N;}
        
        if (i_id == HOURGLASS_ID) { return INV_HOURGLASS_N;}
        
        if (i_id == ANTI_HOURGLASS_ID) { return INV_ANTI_HOURGLASS_N;}
        
        else { printf("Undefined item identity: %d\n", i_id);}
    }
        
    return -1;
}

// works since identity is defined to be <ITEM>_N
// No changed to be different incase of items that arent displayed on screen.






// convert enemy into coded char value

int enemy_to_code(Enemy* e) {
    
    if (e == NULL) {
        enemy_null_error("enemy_to_code");
        return -1;
    }
    
    int e_id = e->enemy_id;
    
    if (e_id == ORB_ID) { return ORB_N;}
    
    else if (e_id == SLIME_ID) { return SLIME_N;}
    
    else if (e_id == KNIGHT_ID) { return KNIGHT_N;}
    
    else if (e_id == GHOST_ID) { return GHOST_N;}
    
    else if (e_id == BABY_SLIME_ID) { return BABY_SLIME_N;}
    
    else if (e_id == SKELETON_ID) { return SKELETON_N;}
    
    else if (e_id == ZOMBIE_ID) { return ZOMBIE_N;}
    
    
    else {
        printf("ERROR: unknown enemy id: %d\n", e_id);
        pause_function();
        return -1;
    }
}








char sword_to_code(int dir) {
    char output = 0;
    if (dir == 0) {
        output = SWORD_VERTICAL_N;
    }
    else if (dir == 1) {
        output = SWORD_DIAG_LEFT_N;
    }
    else if (dir == 2) {
        output = SWORD_HORIZONTAL_N;
    }
    else if (dir == 3) {
        output = SWORD_DIAG_RIGHT_N;
    }
    else if (dir == 4) {
        output = SWORD_VERTICAL_N;
    }
    else if (dir == 5) {
        output = SWORD_DIAG_LEFT_N;
    }
    else if (dir == 6) {
        output = SWORD_HORIZONTAL_N;
    }
    else if (dir == 7) {
        output = SWORD_DIAG_RIGHT_N;
    }

    return output;
}





int arrow_to_code(int dir) {
    int output = SPC_ARROW_UP_N;
    
    if (dir == UP_DIR) {;}
    
    else if (dir == LEFT_DIR) {
        output = SPC_ARROW_LEFT_N;
    }
    
    else if (dir == DOWN_DIR) {
        output = SPC_ARROW_DOWN_N;
    }
    
    else if (dir == RIGHT_DIR) {
        output = SPC_ARROW_RIGHT_N;
    }
    
    return output;
}








//////////////////////////////////////////////////


/////
/////   MAIN FUNCTION
/////


int print_str(char* str) {
    return printf("%s", str);
}

int print_tile_sprite(int c, int p_dir) {

    //printf("%d", c);
    if (c == FLOOR_N) {print_str(FLOOR_S);}
    
    else if (c == DARK_N) {print_str(DARK_S);}
    
    else if (c == WALL_N) {print_str(WALL_S);}
    
    else if (c == PLAYER_N) {
        if (p_dir == 0) {print_str(PLAYER_UP);}
        
        else if (p_dir == 1) {print_str(PLAYER_LEFT);}
        
        else if (p_dir == 2) {print_str(PLAYER_DOWN);}
        
        else if (p_dir == 3) {print_str(PLAYER_RIGHT);}
        
        else {
            printf("ERROR: unknown player direction: %d\n", p_dir);
        }
    }
    
    else if (c == SWORD_VERTICAL_N){print_str(SWORD_VERTICAL_S);}
    
    else if (c == SWORD_DIAG_LEFT_N){print_str(SWORD_DIAG_LEFT_S);}
    
    else if (c == SWORD_DIAG_RIGHT_N){print_str(SWORD_DIAG_RIGHT_S);}
    
    else if (c == SWORD_HORIZONTAL_N){print_str(SWORD_HORIZONTAL_S);}
    
    
    
    
    else if (c == DOOR_N) {
        printf("ERROR: door not converted to sprite\n");
    }
    
    else if (c == OPEN_DOOR_N) {print_str(OPEN_DOOR_S);}
    
    else if (c == LOCKED_DOOR_N ) {print_str(LOCKED_DOOR_S);}
    
    else if (c == OPEN_SWITCH_DOOR_N) {print_str(OPEN_SWITCH_DOOR_S);}
    
    else if (c == CLOSED_SWITCH_DOOR_N) {print_str(CLOSED_SWITCH_DOOR_S);}
    
    else if (c == OPEN_PORTAL_N) {print_str(OPEN_PORTAL_S);}
    
    else if (c == CLOSED_PORTAL_N) {print_str(CLOSED_PORTAL_S);}
    
    else if (c == OPEN_BOMB_DOOR_N) {print_str(OPEN_BOMB_DOOR_S);}
    
    else if (c == CLOSED_BOMB_DOOR_N) {print_str(CLOSED_BOMB_DOOR_S);}
    
    else if (c == SPIKE_N) {print_str(SPIKE_S);}
    
    // remaining building blocks
    
    else if (c == DARK_WATER_N) {print_str(DARK_WATER_S);}
    
    else if (c == LIGHT_WATER_N) {print_str(LIGHT_WATER_S);}
    
    else if (c == REFLECT_WALL_N) {print_str(REFLECT_WALL_S);}
    
    else if (c == INVISIBLE_WALL_N) {print_str(INVISIBLE_WALL_S);}
    
    else if (c == OPAQUE_WALL_N) {print_str(OPAQUE_WALL_S);}
        
        
    // entities
    
    else if (c == HEART_N) {print_str(HEART_S);}
    
    else if (c == KEY_N) {print_str(KEY_S);}
    
    else if (c == COIN_N) {print_str(COIN_S);}
    
    else if (c == BOMB_N) {print_str(BOMB_S);}
    
    else if (c == ARROW_N) {print_str(ARROW_S);}
    
    else if (c == MANA_N) {print_str(MANA_S);}
    
    else if (c == HEART_CONTAINER_N) { print_str(HEART_CONTAINER_S);}
    
    else if (c == MANA_CONTAINER_N) { print_str(MANA_CONTAINER_S);}
    
    else if (c == FREEZE_N) { print_str(FREEZE_S);}
    
    
    else if (c == ORB_N) {print_str(ORB_S);}
    
    else if (c == SLIME_N) {print_str(SLIME_S);}
    
    else if (c == KNIGHT_N) {print_str(KNIGHT_S);}
    
    else if (c == TURRET_N) {print_str(TURRET_S);}
    
    else if (c == GHOST_N) {print_str(GHOST_S);}
    
    else if (c == BABY_SLIME_N) {print_str(BABY_SLIME_S);}
    
    else if (c == SKELETON_N) { print_str(SKELETON_S);}
    
    else if (c == ZOMBIE_N) { print_str(ZOMBIE_S);}
    
    
    
    else if (c == OPEN_SWITCH_N) {print_str(OPEN_SWITCH_S);}
    else if (c == CLOSED_SWITCH_N) {print_str(CLOSED_SWITCH_S);}
    
    
    
    //else if (c == TRAPDOOR_N) {print_str(TRAPDOOR_S);}

    
    else if (c == CHEST_N) {putchar('C');}
    
    else if (c == CHEST_OPEN_N) {print_str(CHEST_OPEN_S);}
    
    else if (c == CHEST_CLOSED_N) {print_str(CHEST_CLOSED_S);}
    
    else if (c == CHEST_LOCKED_N) {print_str(CHEST_LOCKED_S);}
    
    else if (c == FLAG_N) {print_str(FLAG_S);}
    
    else if (c == FLAG_DEAD_N) {print_str(FLAG_DEAD_S);}
    
    else if (c == CRACKED_WALL_N) {print_str(CRACKED_WALL_S);}
    
    else if (c == LADDER_N) { print_str(LADDER_S);}
    
    else if (c == POP_BLOCK_UP_N) {print_str(POP_BLOCK_UP_S);}
    
    else if (c == POP_BLOCK_DOWN_N) { print_str(POP_BLOCK_DOWN_S);}
    
    
    else if (c == HOLE_N) { print_str(HOLE_S);}
    
    
    
    
    
    
    else if (c == PARTICLE_N) { print_str(PARTICLE_S);}
    
    else if (c == SPC_BOMB_N) { print_str(SPC_BOMB_S);}
    
    else if (c == SPC_BOMB_FLASH_N) { print_str(SPC_BOMB_FLASH_S);}
    
    else if (c == SPC_BOMB_BLOW_N) { print_str(SPC_BOMB_BLOW_S);}
    
    
    
    else if (c == TELEPHONE_N) {print_str(TELEPHONE_S);}
    
    else if (c == PUSH_BLOCK_N) { print_str(PUSH_BLOCK_S);}
    
    else if (c == LAMP_ON_N) { print_str(YES_LAMP_S);}
    
    else if (c == LAMP_OFF_N) { print_str(NO_LAMP_S);}
    
    
    else if (c == SPC_ARROW_UP_N) { print_str(ARROW_UP_S);}
    else if (c == SPC_ARROW_LEFT_N) { print_str(ARROW_LEFT_S);}
    else if (c == SPC_ARROW_DOWN_N) { print_str(ARROW_DOWN_S);}
    else if (c == SPC_ARROW_RIGHT_N) {print_str(ARROW_RIGHT_S);}
    
    
    
    
    else if (c == SHOPKEEPER_N) { print_str(SHOPKEEPER_S); }
    
    else if (c == SIMPLE_NPC_N) { print_str(SIMPLE_NPC_S); }
    
    
    
    else if (c == INV_SWORD_N) { print_str(SWORD_S);}
    
    else if (c == INV_BOW_N) { print_str(BOW_S);}
    
    else if (c == INV_SHIELD_N) { print_str(SHIELD_S);}
    
    else if (c == INV_BOMB_N) { print_str(BOMB_BAG_S);}
    
    else if (c == INV_PRESENT_N) { print_str(PRESENT_S);}
    
    else if (c == INV_RING_N) { print_str(RING_S);}
    
    else if (c == INV_CROWN_N) { print_str(BOW_S);}
    
    else if (c == INV_TORCH_N) { print_str(BOW_S);}
    
    else if (c == INV_HOURGLASS_N) { print_str(BOW_S);}
    
    else if (c == INV_STAFF_N) { print_str(BOW_S);}
    
    else if (c == INV_MAGIC_STAFF_N) { print_str(BOW_S);}
    
    else if (c == INV_EMP_BOT_N) { print_str(BOTTLE_S);}
    
    else if (c == INV_DARK_BOT_FULL_N) { print_str(POTION_S);}
    
    else if (c == INV_DARK_BOT_HFULL_N) { print_str(POTION_S);}
    
    else if (c == INV_MED_BOT_FULL_N) { print_str(HEALTH_POTION_S);}
    
    else if (c == INV_MED_BOT_HFULL_N) { print_str(HEALTH_POTION_S);}
    
    else if (c == INV_LIGHT_BOT_FULL_N) { print_str(MANA_POTION_S);}
    
    else if (c == INV_LIGHT_BOT_HFULL_N) { print_str(MANA_POTION_S);}
    
    else if (c == INV_POINTER_N) { print_str(POINTER_S);}
    
    
    
    else {print_str(UNKNOWN);}
    
    return 0;
}












// see what type of door the door is.

int door_number(Exit* exit) {
    
    int closed = door_is_locked(exit);
    
    if (closed) {
        if (door_is_portal(exit)) {
            return CLOSED_PORTAL_N;
        }
        else if (door_is_bombable(exit)) {
            return CLOSED_BOMB_DOOR_N;
        }
        else if (door_is_switch(exit)) {
            return CLOSED_SWITCH_DOOR_N;
        }
        else {
            return LOCKED_DOOR_N;
        }
        
    }
    
    else {
        if (door_is_portal(exit)) {
            return OPEN_PORTAL_N;
        }
        else if (door_is_bombable(exit)) {
            return OPEN_BOMB_DOOR_N;
        }
        else if (door_is_switch(exit)) {
            return OPEN_SWITCH_DOOR_N;
        }
        else {
            return OPEN_DOOR_N;
        }
    }
}








// given a special entity, find the corresponding tile number for tmp_array

int spc_entity_to_tile(struct spc_entity_t* e) {

    if (e == NULL) {
        null_error(SPECIAL_ENTITY_OBJECT, "spc_entity_to_tile");
        return NONE_N;
    }
    int ent_id = e->entity_id;
    
    
    if (ent_id == SPC_LAMP_ID) {
    
        if (get_lamp_on(e)) { return LAMP_ON_N;}
        
        else { return LAMP_OFF_N;}
    }
    
    
    
    else if (ent_id == SPC_ARROW_ID) {
        return arrow_to_code(e->base.direction);
    }
    
    
    
    
    else if (ent_id == SPC_FLAG_ID) {
        
        if (e->base.health) { return FLAG_N;}
        
        else { return FLAG_DEAD_N;}
    }
    
    
    else if (ent_id == SPC_SWORD_ID) { return sword_to_code(e->base.direction);}
    
    
    else if (ent_id == SPC_STICK_ID) {
        
        if (e->base.direction % 2 == 0) { return SWORD_VERTICAL_N;}
        
        else { return SWORD_HORIZONTAL_N;}
    }
    
    
    
    else if (ent_id == SPC_BOMB_ID) {
        if (e->base.timer <= 0) {
            return SPC_BOMB_BLOW_N;
        }
        
        else {
            int time = e->base.timer / 3;
            
            if (time <= 5 && ((time % 2) == 0)) { return SPC_BOMB_FLASH_N;}
            
            else {return SPC_BOMB_N;}
        }
    }
    
    
    
    else if (ent_id == SPC_PUSH_BLOCK_ID) { return PUSH_BLOCK_N;}
    
    
    else if (ent_id == SPC_TELEPHONE_ID) {
        if (!get_telephone_invisible(e)) {
            return TELEPHONE_N;
        }
        return NONE_N;
    }
    
    
    else if (ent_id == SPC_SWITCH_ID) {
        
        if (get_switch_closed(e)) { return CLOSED_SWITCH_N;}
        
        else { return OPEN_SWITCH_N;}
    }
    
    
    
    
    
    else if (ent_id == SPC_SMOKE_ID) { return PARTICLE_N;}
    
    
    // do this one as last priority
    
    else if (ent_id == SPC_POP_BLOCK_ID) {
        
        if (get_pop_block_up(e)) { return POP_BLOCK_UP_N;}
        
        else { return POP_BLOCK_DOWN_N;}
    }
    
    
    
    else {
        return NONE_N;
    }
}














int npc_to_tile(struct npc_t* n) {

    if (n == NULL) {
        npc_null_error("npc_to_tile");
        return NONE_N;
    }
    
    int c_id = n->character_id;
    
    
    
    if (c_id == SIMPLE_NPC_ID) {
        return SIMPLE_NPC_N;
    }
    
    
    else if (c_id == SHOPKEEPER_ID) {
        return SHOPKEEPER_N;
    }
    
    
    
    
    
    else {
        return NONE_N;
    }
}

# endif
