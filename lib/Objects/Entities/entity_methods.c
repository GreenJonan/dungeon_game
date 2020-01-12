# ifndef ENTITY_METHODOLOGIES__
# define ENTITY_METHODOLOGIES__

// this file outlines methods for pure entity objects. All structures that inherent
// entities will have their own methods, that may use these methods.



/////////////////////////////////////////////////////

// DIRECTION MOVEMENT


/*
int move_entity_up(Entity* a) {
    if (a == NULL) {
        entity_null_error("move_entity_up");
        return 1;
    }
    
    a->y--;
    return 0;
}


int move_entity_left(Entity* a) {
    if (a == NULL) {
        entity_null_error("move_entity_left");
        return 1;
    }
    
    a->x--;
    return 0;
}


int move_entity_down(Entity* a) {
    if (a == NULL) {
        entity_null_error("move_entity_down");
        return 1;
    }
    
    a->y++;
    return 0;
}

int move_entity_right(Entity* a) {
    if (a == NULL) {
        entity_null_error("move_entity_right");
        return 1;
    }
    
    a->x++;
    return 0;
}*/






/*
int move_entity(struct entity_t* e, int dir, struct room_t* r) {

    char name[] = "move_entity";
    
    if (dir == NO_DIR) {
        return 0; // no movement, hence no calculations
    }
    
    
    if (e == NULL) {
        entity_null_error(name);
        return -1;
    }
    if (r == NULL) {
        room_null_error(name);
        return -1;
    }
    if (dir != UP_DIR && dir != LEFT_DIR && dir != DOWN_DIR && dir != RIGHT_DIR) {
        printf("Error: invalid direction: %d, function: '%s'\n", dir, name);
        return -1;
    }
    
    
    int x = e->x;
    int y = e->y;
    
    dir_to_xy(dir, &x, &y);
    
    if (entity_room_collide(e, r, x, y)) {
        
        // return 1 if the entity collides in the new position x,y
        return 1;
    }
    
    
    else {
        
        e->x = x;
        e->y = y;
        
        return 0;
    }
}*/










int turn_entity_dir(Entity* e, int dir) {
    if (e == NULL) {
        entity_null_error("turn_entity_dir");
        return 1;
    }
    
    if (dir == UP_DIR || dir == LEFT_DIR || dir == DOWN_DIR || dir == RIGHT_DIR) {
    
        e->direction = dir;
        // to do: form hit box collision detection with room, to see if it is
        //possible to turn or not, currently allowed to clip.
        // this will allow large objects to move through walls
        
        set_entity_hit_box(e, dir);
    }
    
    else {
        printf("ERROR: unknown direction: %d. Function: 'turn_entity_dir.\n", dir);
        pause_function();
        return 1;
    }
    
    return 0;
}














// find x,y position
int entity_x_pos(struct entity_t* a) {
    if (a == NULL) {
        entity_null_error("entity_x_pos");
        return -1;
    }
    return a->x;
}
int entity_y_pos(struct entity_t* a) {
    if (a == NULL) {
        entity_null_error("entity_y_pos");
        return -1;
    }
    return a->y;
}
// set x,y
int set_entity_pos(Entity* e, int x, int y) {
    if (e == NULL) {
        entity_null_error("set_entity_pos");
        return 1;
    }
    e->x = x;
    e->y = y;
    return 0;
}






// find for enenmy and items

//enemy
int enemy_x_pos(Enemy* e) {
    if (e == NULL) {
        null_error(ENEMY_OBJECT, "enemy_x_pos");
        return -1;
    }
    return entity_x_pos(&(e->base));
}
int enemy_y_pos(Enemy* e) {
    if (e == NULL) {
        null_error(ENEMY_OBJECT, "enemy_y_pos");
        return -1;
    }
    return entity_y_pos(&(e->base));
}

//item
int item_x_pos(Item* i) {
    if (i == NULL) {
        null_error(ITEM_OBJECT, "item_x_pos");
        return -1;
    }
    return entity_x_pos(&(i->base));
}
int item_y_pos(Item* i) {
    if (i == NULL) {
        null_error(ITEM_OBJECT, "item_y_pos");
        return -1;
    }
    return entity_y_pos(&(i->base));
}


// set x,y
int set_item_pos(Item* e, int x, int y) {
    if (e == NULL) {
        item_null_error("set_item_pos");
        return 1;
    }
    
    return set_entity_pos(&(e->base), x, y);
}


int set_enemy_pos(Enemy* e, int x, int y) {
    if (e == NULL) {
        enemy_null_error("set_enemy_pos");
        return 1;
    }
    
    return set_entity_pos(&(e->base), x, y);
}







/*

int entity_room_clip(struct room_t* room, struct entity_t* e, int x, int y) {
    if (e == NULL) {
        entity_null_error("entity_room_clip");
        return -1;
    }
    if (room == NULL) {
        null_error(ROOM_OBJECT, "entity_room_clip");
        return -1;
    }
    
    int w = room->width;
    int h = room->height;

    
    int blocked = 0;
    
    if ( x >= w || x < 0 || y < 0 || y >= h) {
        blocked = 1;
    }
    else if (  is_entity_clip(e)  &&  is_clip_position(room, e, x, y)  ) {
        blocked = 1;
    }
    
    return blocked;
}*/

/*
 if (x < 0 || x >= w) {
 x = e->x;
 }
 
 if ( y < 0 || y >= h) {
 y = e->y;
 }*/ //superfluous functions.
/*else if (x < 0 || y < 0) {
 printf("Value Error: %d %d in 'entity_room_clip'\n", x, y);
 return -1;
 }*/




int increment_entity_move(struct entity_t* e, struct room_t* r, int* new_x, int* new_y) {

    char name[] = "increment_entity_move";
    
    if (e == NULL) {
        entity_null_error(name);
        return 1;
    }
    
    if ( r == NULL) {
        room_null_error(name);
        return 1;
    }
    
    if (new_x == NULL || new_y == NULL) {
        null_error("Integer Pointers", name);
        return 1;
    }
    
    
    // TO DO: implement sliding and friction based on the surface, e.g. ice, make it have constant, x,y vel,
    // but with stone, slide say only two interations
    
    // Currently, if fly, act as ice

    
    
    if (e->fly) {
        //int ticks_per_x = e->x_vel;
        //int ticks_per_y = e->y_vel;
        
        
        int dir = 0;
        
        /*
         @--> +x
         |
         v +y
         */
        
        
        if (e->vel_x_timer > 0) {
            e->vel_x_timer --;
        }
        
        if (e->vel_x_timer <= 0) {
            if (e->vel_x != 0) {
                
        
                if (e->vel_x > 0) {  dir = 3; }// right
                
                else {  dir = 1; }// left
            
                dir_to_xy(dir, new_x, new_y);
                
                
                if (e->vel_x_timer == 0) {
                    if (e->vel_x >= 0) {
                        e->vel_x_timer = e->vel_x;
                    }
                    else {
                        e->vel_x_timer = - e->vel_x;
                    }
                }
                
            }
            
        }
        
        
        
        
        
        if (e->vel_y_timer > 0) {
            e->vel_y_timer --;
        }
        
        
        if (e->vel_y_timer <= 0) {
            if (e->vel_y != 0) {
                
                
                if (e->vel_y > 0) {  dir = 2; }// down
                
                else {  dir = 0; } // up
                
                dir_to_xy(dir, new_x, new_y);
                
                
                if (e->vel_y_timer == 0) {
                    if (e->vel_y >= 0) {
                        e->vel_y_timer = e->vel_y;
                    }
                    else {
                        e->vel_y_timer = - e->vel_y;
                    }
                }
            }
            
        }
        
    
    }
    
    
    return 0;
}








// TODO: implement entity_move function, which should work just like player_move function.

// AT THE MOMENT: mostly implemented, working fine as long as no assumptions with touching certain
// objects / tiles, e.g. pits or portals.


int entity_move(struct entity_t* e, struct room_t* r, int dir) {

    char name[] = "entity_move";
        
    if (e == NULL) {
        entity_null_error(name);
        return -1;
    }
    
    if (r == NULL) {
        room_null_error(name);
        return -1;
    }
    
    
    if (dir != UP_DIR && dir != LEFT_DIR && dir != DOWN_DIR && dir != RIGHT_DIR && dir != NO_DIR) {
        printf("VALUE ERROR: Invalu direction %d for function: '%s'", dir, name);
        return -1;
    }
    
    
    int tmp_x = e->x;
    int tmp_y = e->y;
    
    
    increment_entity_move(e, r, &tmp_x, &tmp_y);
    
    
    // now given direction, move in the direction
    dir_to_xy(dir, &tmp_x, &tmp_y);
    
    
    
    // see if collision
    
    if (tmp_x < 0 || tmp_y < 0 || tmp_x >= r->width || tmp_y >= r->height) {
    
        // blocked
        return 1;
    }

    
    
    // see if it collides with hole
    
    
    if (!e->fly) {
        
        if (entity_room_tile_collide(e, r, HOLE_N, tmp_x, tmp_y, NULL, NULL)) {
            e->health = 0;
        }
    }
    // TO DO idea is to cause the entity to despawn / die if fall into the hole.
    
    
    
    if (entity_room_collide(e, r, tmp_x, tmp_y)) {;
        // no more progress and cannot move
        return 1;
    }
    
    else {
        e->x = tmp_x;
        e->y = tmp_y;
    }

    return 0;
}






/////////////////////////////////////////////////

// ENTITY_STATUS



// setters


// clip

int set_entity_clip(Entity* a, int b) {
    if (a == NULL) {
        entity_null_error("set_entity_clip");
        return 1;
    }
    
    if (b) {
        return set_char_bool_true(&(a->status), 0);
    }
    else {
        return set_char_bool_false(&(a->status), 0);
    }
}




// paralysis

int set_entity_paralysed(Entity* a, int b) {
    if (a == NULL) {
        entity_null_error("set_entity_paralysis");
        return 1;
    }
    
    if (b) {
        return set_char_bool_true(&(a->status), 1);
    }
    else {
        return set_char_bool_false(&(a->status), 1);
    }
}




// poison

int set_entity_poisoned(Entity* a, int b) {
    if (a == NULL) {
        entity_null_error("set_entity_poisoned");
        return 1;
    }
    
    if (b) {
        return set_char_bool_true(&(a->status), 2);
    }
    else {
        return set_char_bool_false(&(a->status), 2);
    }
}



// getters


// clip

int is_entity_clip(Entity* a) {
    return read_char_bool(a->status, 0);
}


// paralysis

int is_entity_paralysed(Entity* a) {
    return read_char_bool(a->status, 1);
}


// poison

int is_entity_poisoned(Entity* a) {
    return read_char_bool(a->status, 2);
}






int get_entity_override_clip(Entity* e) {
    if (e == NULL) {
        entity_null_error("get_entity_player_clip");
        return 1;
    }
    return read_char_bool(e->status, 3);
}

int set_entity_override_clip(Entity* e, int b) {
    if (e == NULL) {
        entity_null_error("set_entity_player_clip");
        return 1;
    }
    if (b) {
        return set_char_bool_true(&(e->status), 3);
    }
    else {
        return set_char_bool_false(&(e->status), 3);
    }
}








////////////////////////////////////////////////////////////////

// increment entity 'a''s clock by time t.
// clock is a cooldown timer, with time remaining and reset time.

int increment_entity_clock(Entity* a, int t) {
    
    if (a->timer == 0) {
        a->timer = a->clock;
    }
    else  {
        a->timer = a->timer - 1;
    }
    return 0;
}







//////////////////////////////////////////////////////////////////

// methods related to vision, and light distance from entities



int set_entity_light_dist(Entity* e, int d) {
    if (e == NULL) {
        entity_null_error("set_entity_light_dist");
        return 1;
    }
    
    e->light_dist = d;
    return 0;
}

int get_entity_light_dist(Entity* e) {
    if (e == NULL) {
        entity_null_error("get_entity_light_dist");
        return -1;
    }
    return e->light_dist;
}


int in_vision_cone(struct entity_t*, int, int, int);
# endif
