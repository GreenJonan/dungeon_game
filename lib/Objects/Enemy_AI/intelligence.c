# ifndef THEY_ARE_SMARTER_THAN_YOU
# define THEY_ARE_SMARTER_THAN_YOU

int ai_method(struct enemy_t*, struct game_t*, int, int);


// static ai, that is the enemy does nothing, except drift

int static_enemy(struct enemy_t* e, struct player_t* p) {
    if (e == NULL) {
        enemy_null_error("static_enemy");
        return -1;
    }
    
    return move_enemy_direction(e, NO_DIR, p);
    
    //return entity_move(&(e->base), r, NO_DIR);
}




// random wondering
int rnd_enemy_wondering(struct enemy_t* e, struct player_t* p) {
    char name[] = "rnd_enemy_wondering";
    
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
    
    
    
    float rnd_num = rand();
    float p_val = rnd_num / RAND_MAX;
    int blocked = 0;
    
    
    if (p_val > e->wait_rnd) {
        // this means the enemy is free to move
        int dir = rand() % 4;

        
        blocked = move_enemy_direction(e, dir, p);
    
        
        // move enemy automatically calculates whether position is clip/ not clip, hence no need to test for
        // clipping
    }
    
    return blocked;
}







int rnd_enemy_turn(struct enemy_t* e, struct player_t* p) {
    
    char name[] = "rnd_enemy_turn";
    
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
    }

    
    
    float rnd_num = rand();
    float p_val = rnd_num / RAND_MAX;
    int turn  = 0;
    int blocked = 0;
    
    
    
    if (p_val > e->turn_rnd) {
        turn = 1;
        
    }
        
    else if (move_enemy_direction(e, e->base.direction, p)) {

        blocked = 1;
        turn = 1; //non-zero return implies hit obstacle and cannot move.
    }
    
 
    
    
    
    if (turn) {
        
        int dir = e->base.direction;
        while (dir == e->base.direction) {
            dir = rand() % 4;
        }
        
        turn_entity_dir(&(e->base), dir);
    }
    
    
    
    return blocked;
}










// use the ai and seeing functions to move the player

int move_enemy(struct enemy_t* e, struct game_t* g) {

    char name[] = "move_enemy";
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
    
    int passive_ai = get_ai_idle(e->ai);
    int active_ai = get_ai_active(e->ai);
    
    
    
    // first see if searching AI
    
    int dir = enemy_sees_player_room(e, g->player, g->player->room);
    if (dir) {
        dir = dir - 1;
        
        ai_method(e, g, dir, active_ai);
        
    }
    
    
    
    else {
        // enemy does not see the player, use idle ai
        
        ai_method(e, g, -1, passive_ai);
    }

    return 0;
}






// move the enemy entirely by the ai functions.

int ai_method(struct enemy_t* e, struct game_t* g, int dir, int ai) {

    char name[] = "ai_method";
    if (e == NULL) {
        enemy_null_error(name);
        return 1;
    }
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
    
    
    int blocked = 0;
    
    
    
    if (ai == STATIC_AI) {
        blocked = static_enemy(e, g->player);
    }
    
    else if (ai == RANDOM_AI) {
        blocked = rnd_enemy_wondering(e, g->player);
    }
    
    else if (ai == RANDOM_TURN_AI) {
        blocked = rnd_enemy_turn(e, g->player);
    }

    
    else if (dir >= 0) {

        
        if (e->base.direction != dir && (ai == CORNER_TURN_AI) && dir != NO_DIR) {
            turn_entity_dir(&(e->base), dir);
        }
        else {
            
            blocked = move_enemy_direction(e, dir, g->player);
        }
    }
    
    
    
    else {
        printf("VALUE ERROR: unknown ai-value: %d, or idle-enemy_ai, function: '%s'\n", ai, name);
        return 1;
    }
    
    
    
    
    
    if (blocked && e->enemy_id == ORB_ID) {
        // i.e. kill entity
        e->base.health = 0;
    }
    
    
    
    return 0;
}

# endif
