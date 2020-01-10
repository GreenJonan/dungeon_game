# ifndef INTIALISE_SPECIAL_ENTITIES____
# define INTIALISE_SPECIAL_ENTITIES____


# include "special_entity_methods.c"

///////////////////////////////////////////////////////////





int init_spc_basic_sword(struct player_t* p) {
    
    if (p == NULL) {
        player_null_error("init_spc_basic_sword");
        return 1;
    }
    if (p->room == NULL) {
        room_null_error("init_spc_basic_sword");
        return 1;
    }
    
    int tmp_x = p->base.x;
    int tmp_y = p->base.y;
    dir_to_xy(p->base.direction, &tmp_x, &tmp_y);
    
    if (tmp_x < 0 || tmp_y < 0 || tmp_x >= p->room->width ||
        tmp_y >= p->room->height) {
        return 0;
    }
    
    
    
    Spc_ent* s_ent = allocate_special_entity(1);
    s_ent->entity_id = SPC_SWORD_ID;
    
    s_ent->base.x = tmp_x;
    s_ent->base.y = tmp_y;
    
    s_ent->base.direction = 2* p->base.direction;
    s_ent->player_id = PLAYER_DMG_ID;
    
    s_ent->base.health = 1;
    s_ent->base.eyesight = 0;
    s_ent->base.timer = 3;
    
    s_ent->wait_update = 0;
    
    set_entity_clip(&(s_ent->base), 1);
    
    // now put item onto queue
    p->room->spc_weapon_entities = push_special_entity_end(p->room->spc_weapon_entities, s_ent);
    
    return 0;
}










int init_spc_basic_staff(struct player_t* p) {
    
    if (p == NULL) {
        player_null_error("init_spc_basic_staff");
        return 1;
    }
    if (p->room == NULL) {
        room_null_error("init_spc_basic_staff");
        return 1;
    }
    
    int tmp_x = p->base.x;
    int tmp_y = p->base.y;
    dir_to_xy(p->base.direction, &tmp_x, &tmp_y);
    
    if (tmp_x < 0 || tmp_y < 0 || tmp_x >= p->room->width ||
        tmp_y >= p->room->height) {
        return 0;
    }
    
    
    
    Spc_ent* s_ent = allocate_special_entity(1);
    s_ent->entity_id = SPC_SWORD_ID;
    
    s_ent->base.x = tmp_x;
    s_ent->base.y = tmp_y;
    
    
    s_ent->base.direction = p->base.direction;
    s_ent->player_id = PLAYER_DMG_ID;
    
    s_ent->base.health = 1;
    s_ent->base.timer = 2;
    s_ent->base.eyesight = 0;
    
    s_ent->wait_update = 0;
    
    set_entity_clip(&(s_ent->base), 1);
    
    // now put item onto queue
    p->room->spc_weapon_entities = push_special_entity_end(p->room->spc_weapon_entities, s_ent);
    
    return 0;
}










int init_spc_basic_bomb(struct player_t* p) {
    
    if (p == NULL) {
        player_null_error("init_spc_basic_sword");
        return 1;
    }
    if (p->room == NULL) {
        room_null_error("init_spc_basic_sword");
        return 1;
    }
    
    
    
    
    int tmp_x = p->base.x;
    int tmp_y = p->base.y;
    
    dir_to_xy(p->base.direction, &(tmp_x), &(tmp_y));
    
    
    Spc_ent* s_ent = allocate_special_entity(1);
    s_ent->entity_id = SPC_BOMB_ID;
    
    s_ent->base.fly = 0;
    s_ent->base.default_hit_box = NULL;
    set_entity_clip(&(s_ent->base), 1);
    
    
    // see whether clip tile or not.
    
    if (entity_room_collide(&(s_ent->base), p->room, tmp_x, tmp_y)) {
        tmp_x = p->base.x;
        tmp_y = p->base.y;
    }
    
    s_ent->base.x = tmp_x;
    s_ent->base.y = tmp_y;
    
    
    s_ent->base.direction = p->base.direction;
    s_ent->player_id = 1;
    
    s_ent->base.health = SIMPLE_BOMB_DAMAGE;
    s_ent->base.timer = BOMB_CLOCK;
    s_ent->base.light_dist = 2;
    
    s_ent->wait_update = 0;
    
    // now put item onto queue
    p->room->spc_weapon_entities = push_special_entity_end(p->room->spc_weapon_entities, s_ent);
    
    return 0;
    
}









Spc_ent* init_spc_arrow(struct player_t* p, int type) {

    char name[] = "init_spc_arrow";
    
    if (p == NULL) {
        player_null_error(name);
        return NULL;
    }
    
    int tmp_x = p->base.x;
    int tmp_y = p->base.y;
    
    
    //
    
    Spc_ent* s_ent = allocate_special_entity(1);
    s_ent->entity_id = SPC_ARROW_ID;
    set_arrow_type(s_ent, type);
    
    
    s_ent->base.fly = 1;
    set_entity_clip(&(s_ent->base), 1);
    
    
    // find direction player is facing in, x,y?
    int x_dir = 0;
    int y_dir = 0;
    int dir = p->base.direction;
    
    if (dir == UP_DIR) {  y_dir = -1;  }
    else if (dir == LEFT_DIR) {  x_dir = -1;  }
    else if (dir == DOWN_DIR) {  y_dir = 1;  }
    else if (dir == RIGHT_DIR) {  x_dir = 1;  }
    else {
        printf("ERROR: unknown player direction: %d, for function: '%s'\n", dir, name);
        pause_function();
    }
    
    
    s_ent->base.vel_x = x_dir;
    s_ent->base.vel_y = y_dir;
    s_ent->base.vel_x_timer = 0;
    s_ent->base.vel_y_timer = 0;
    
    s_ent->base.timer = -1;
    
    s_ent->base.x = tmp_x;
    s_ent->base.y = tmp_y;
    
    s_ent->player_id = PLAYER_DMG_ID;
    s_ent->base.direction = dir;
    s_ent->wait_update = 0;
    
    s_ent->base.health = ARROW_DMG_NUM;
    
    
    return s_ent;
}






int init_spc_slow_arrow(struct player_t* p, int type) {

    char name[] = "init_spc_slow_arrow";
    
    if (p == NULL) {
        player_null_error(name);
        return 1;
    }
    
    Spc_ent* s_ent = init_spc_arrow(p, type);
    
    // now put item onto queue
    p->room->spc_weapon_entities = push_special_entity_end(p->room->spc_weapon_entities, s_ent);
    
    return 0;
}










int init_spc_fast_arrow(struct game_t* g, int type) {

    char name[] = "init_spc_fast_arrow";
    
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
    
    
    init_spc_slow_arrow(g->player, type);
    
    // find the last item in the player room weapon list
    Spc_ent_ls* tmp_ls = g->player->room->spc_weapon_entities;
    
    if (tmp_ls == NULL) {
        null_error(SPECIAL_ENTITY_LS_OBJECT, name);
        return 1;
    }
    
    
    
    while (tmp_ls->next != NULL) {
        tmp_ls = tmp_ls->next;
    }
    
    if (tmp_ls->spc_entity == NULL) {
        printf("NULL ERROR: last weapon entity is NULL, in function: '%s'\n", name);
        pause_function();
        return 1;
    }
    
    else if (tmp_ls->spc_entity->entity_id != SPC_ARROW_ID) {
        printf("ERROR: last weapon entity is not ARROW, instead is: %d, in function: '%s'\n",
               tmp_ls->spc_entity->entity_id, name);
        pause_function();
        return 1;
    }
    
    
    
        
    while (tmp_ls->spc_entity->base.timer != 0) {
        
        increment_spc_arrow_time(tmp_ls->spc_entity, g);
            
        // draw the screen after every increment of time
        draw_screen(g);
            
        usleep(SLEEP_TIME);
    }
        
        
    // free arrow
    kill_special_entity(g->player->room, tmp_ls, 1);
    
    
    
    return 0;
}

//Spc_ent* tmp_arrow = init_spc_arrow(g->player, type);






///////////////////////////////////////////////////////////////////////



int init_spc_flag(struct room_t* r, int x, int y) {

    if (r == NULL) {
        room_null_error("init_spc_flag");
        return 1;
    }
    
    Spc_ent* tmp_ent = allocate_special_entity(1);
    tmp_ent->base.x = x;
    tmp_ent->base.y = y;
    tmp_ent->base.timer = -1; //so that it does not despawn.
    tmp_ent->base.health = 1;
    
    tmp_ent->entity_id = SPC_FLAG_ID;
    
    set_entity_clip(&(tmp_ent->base), 1);
    
    r->spc_room_entities = push_special_entity_end(r->spc_room_entities, tmp_ent);
    
    return 0;
}






int init_spc_telephone(struct room_t* r, char* msg, int x, int y,
                       int ring_id, int local_dist, int trig_id, int is_trig, int invisible) {

    if (r == NULL) {
        room_null_error("init_spc_telephone");
        return 1;
    }

    Spc_ent* tmp_ent = allocate_special_entity(1);
    tmp_ent->base.x = x;
    tmp_ent->base.y = y;

    tmp_ent->base.timer = -1; //so that it does not despawn.
    tmp_ent->base.health = 1;
    
    set_telephone_ring_id(tmp_ent, ring_id);
    set_telephone_dist(tmp_ent, local_dist);
    set_telephone_trig_id(tmp_ent, trig_id);
    set_telephone_trig_activate(tmp_ent, is_trig);
    set_telephone_invisible(tmp_ent, invisible);
    
    if (trig_id > 0) {
        set_telephone_activated(tmp_ent, 0);
    }
    else {
        set_telephone_activated(tmp_ent, 1);
    }

    tmp_ent->entity_id = SPC_TELEPHONE_ID;
    
    tmp_ent->base.msg[0] = 0;
    if (!str_eq(msg, NONE)) {
        str_copy(msg, tmp_ent->base.msg);
    }
    
    set_entity_clip(&(tmp_ent->base), 1);
    
    
    r->spc_room_entities = push_special_entity_end(r->spc_room_entities, tmp_ent);

    return 0;
}






int init_spc_push_block(struct room_t* r, int x, int y, int dir, int push_num, int strength) {
    
    if (r == NULL) {
        room_null_error("init_spc_push_block");
        return 1;
    }
    
    Spc_ent* tmp_ent = allocate_special_entity(1);
    tmp_ent->base.x = x;
    tmp_ent->base.y = y;
    
    // default positions.
    tmp_ent->base.vel_x = x;
    tmp_ent->base.vel_y = y;
    
    tmp_ent->base.timer = -1;
    tmp_ent->base.health = -1;
    
    set_push_block_dir(tmp_ent, dir);
    set_push_block_push_num(tmp_ent, push_num);
    set_push_block_max_push(tmp_ent, push_num);
    set_push_block_strength(tmp_ent, strength);
    
    tmp_ent->entity_id = SPC_PUSH_BLOCK_ID;
    
    set_entity_clip(&(tmp_ent->base), 1);
    
    
    r->spc_room_entities = push_special_entity_end(r->spc_room_entities, tmp_ent);
    
    return 0;
}



int init_spc_pop_block(struct room_t* r, int x, int y, int up, int trig_id) {

    if (r == NULL) {
        room_null_error("init_spc_pop_block");
        return 1;
    }
    
    Spc_ent* tmp_ent = allocate_special_entity(1);
    tmp_ent->base.x = x;
    tmp_ent->base.y = y;
    
    // default positions.
    tmp_ent->base.timer = -1;
    tmp_ent->base.health = -1;
    
    
    if (up) {
        up = 1;
    }
    set_pop_block_up(tmp_ent, up);
    set_pop_block_original_up(tmp_ent, up);
    
    set_pop_block_trig_id(tmp_ent, trig_id);
    
    tmp_ent->entity_id = SPC_POP_BLOCK_ID;
    
    set_entity_clip(&(tmp_ent->base), 1);
    
    r->spc_room_entities = push_special_entity_end(r->spc_room_entities, tmp_ent);
    
    return 0;
}






int init_spc_switch(struct room_t* r, int x, int y, int closed, int trig_id, int type) {

    if (r == NULL) {
        room_null_error("init_spc_switch");
        return 1;
    }
    
    Spc_ent* tmp_ent = allocate_special_entity(1);
    tmp_ent->base.x = x;
    tmp_ent->base.y = y;
    
    tmp_ent->base.timer = -1;
    tmp_ent->base.health = -1;
    
    
    if (trig_id < 0 || trig_id > sizeof(char) * TRIG_NUM) { trig_id = 0;}
    
    set_entity_clip(&(tmp_ent->base), 1);
    
    set_switch_closed(tmp_ent, closed);
    set_switch_default_closed(tmp_ent, closed);
    set_switch_trig_id(tmp_ent, trig_id);
    
    set_switch_type(tmp_ent, type);
    
    
    tmp_ent->entity_id = SPC_SWITCH_ID;
    r->spc_room_entities = push_special_entity_end(r->spc_room_entities, tmp_ent);
    
    return 0;
}





int init_spc_lamp(struct room_t* r, int x, int y, int trig_id, int on, int light_dist) {
    
    if (r == NULL) {
        room_null_error("init_spc_lamp");
        return 1;
    }
    
    Spc_ent* tmp_ent = allocate_special_entity(1);
    tmp_ent->base.x = x;
    tmp_ent->base.y = y;
    
    tmp_ent->base.timer = -1;
    tmp_ent->base.health = -1;
    
    
    if (trig_id < 0 || trig_id > sizeof(char) * TRIG_NUM) { trig_id = 0;}
    
    set_entity_clip(&(tmp_ent->base), 1);
    
    set_lamp_trig_id(tmp_ent, trig_id);
    set_lamp_default_on(tmp_ent, on);
    set_lamp_on(tmp_ent, on);
    
    tmp_ent->base.light_dist = light_dist;
    
    
    tmp_ent->entity_id = SPC_LAMP_ID;
    r->spc_room_entities = push_special_entity_end(r->spc_room_entities, tmp_ent);
    
    return 0;
}


# endif


