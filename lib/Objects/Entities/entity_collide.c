# ifndef ENEITY_COLLISION__
# define ENEITY_COLLISION__

# include "../special_entity_methods.c"

//////////////

/// ROOM AND ENTITY COLLISION, BOOLEAN FUNCTIONS

// if already colliding with object, only allow movement if next place is a non clip place.




int entity_room_collide(struct entity_t* e, struct room_t* r, int new_x, int new_y) {
    
    char name[] = "entity_room_collide";
    
    if (e == NULL) {
        entity_null_error(name);
        return -1;
    }
    
    if (r == NULL) {
        room_null_error(name);
        return -1;
    }
    
    
    int blocked = 0;
    int e1_override = get_entity_override_clip(e);
    
    
    if (new_x < 0 || new_y < 0 || new_x >= r->width || new_y >= r->height) {
        blocked = 1;
    }
    
    
    
    
    else if (is_entity_clip(e) || e1_override) {
        
        // main function
        
        
        ///////////////////////////////////////////
        
        ///
        ///     PRE-ANALYSIS
        ///
        
        
        char* entity_matrix = e->default_hit_box;
        int w = e->tmp_width;
        int h = e->tmp_height;
        
        
        int inited = 0;
        
        if (e->default_hit_box == NULL) {
            
            // assume point object.
            w = 1;
            h = 1;
            entity_matrix = (char*) malloc(sizeof(char));
            entity_matrix[0] = 1;
            inited = 1;
        }
        
        else if (entity_matrix == NULL) {
            null_error("Hit Box Matrix", name);
            return -1;
        }
        
        
        
        
        int ex = e->e_x;
        int ey = e->e_y;
        
        
        ///////////////////////////////////////////
        
        ///
        ///     ROOM TILES
        ///
        
        
        blocked = matrix_room_collide(entity_matrix, ex, ey, w, h, new_x, new_y, r, e->fly);
        
        
        
        
        
        ///////////////////////////////////////////
        
        ///
        ///     ENTITIES
        ///
        
        
        if (!blocked) {
            
            // not blocked with room tiles, hence test room entities
            
            // METHOD: go through all the spc_room_entities and then test if it clips
            
            
            if (r->spc_room_entities != NULL) {
                
                while (r->spc_room_entities->prev != NULL) {
                    r->spc_room_entities = r->spc_room_entities;
                }
                
                
                Spc_ent_ls* tmp_ls = r->spc_room_entities;
                
                while (tmp_ls != NULL && !blocked) {
                    
                    
                    if (tmp_ls->spc_entity == NULL) {
                        null_error(SPECIAL_ENTITY_OBJECT, name);
                    }
                    
                    else {
                        
                        
                        // entities to clip with.
                        
                        int ent_id = tmp_ls->spc_entity->entity_id;
                        
                        
                        
                        if (ent_id == SPC_TELEPHONE_ID) {
                            blocked = matrix_entity_collide(entity_matrix, ex, ey, w, h, new_x, new_y,
                                                            &(tmp_ls->spc_entity->base), e1_override);
                        }
                        
                        
                        
                        
                        else if (ent_id == SPC_PUSH_BLOCK_ID) {
                            blocked = matrix_entity_collide(entity_matrix, ex, ey, w, h, new_x, new_y,
                                                            &(tmp_ls->spc_entity->base), e1_override);
                        }
                        
                        
                        
                        else if (ent_id == SPC_SWITCH_ID) {
                            blocked = matrix_entity_collide(entity_matrix, ex, ey, w, h, new_x, new_y,
                                                            &(tmp_ls->spc_entity->base), e1_override);
                        }
                        
                        
                        
                        
                        else if (ent_id == SPC_POP_BLOCK_ID) {
                            
                            if (matrix_entity_collide(entity_matrix, ex, ey, w, h, new_x, new_y,
                                                      &(tmp_ls->spc_entity->base), e1_override)) {
                                
                                
                                // hence two collide
                                // see whether popped up, if so perform calculations
                                
                                if (get_pop_block_up(tmp_ls->spc_entity)) {
                                    
                                    
                                    // pop block being walked onto is popped up, check if currently standing
                                    // on a pop-up block, if so not blocked, else blocked
                                    
                                    
                                    int found_pop_up = 0;
                                    Spc_ent_ls* tmp_tmp_ls = r->spc_room_entities;
                                    while (tmp_tmp_ls != NULL && !found_pop_up) {
                                        
                                        
                                        // already reported null error
                                        if (tmp_tmp_ls->spc_entity != NULL) {
                                            
                                            
                                            if (get_pop_block_up(tmp_tmp_ls->spc_entity)) {
                                                
                                                
                                                if (matrix_entity_collide(entity_matrix, ex, ey, w, h,
                                                                          e->x, e->y,
                                                                          &(tmp_tmp_ls->spc_entity->base),
                                                                          e1_override)) {
                                                    
                                                    
                                                    // hence standing on pop-up block
                                                    found_pop_up = 1;
                                                }
                                            }
                                        }
                                        tmp_tmp_ls = tmp_tmp_ls->next;
                                    }
                                    
                                    if (!found_pop_up) {
                                        blocked = 1;
                                    }
                                }
                            }
                        }
                        
                        
                    }
                    
                    
                    tmp_ls = tmp_ls->next;
                }
            }
            
        }
        
        
        
        //////// NPCS
        
        
        if (!blocked) {
            
            
            // SEARCH THROUGH NPC LISTS
            
            if (r->npcs != NULL) {
            
                while (r->npcs->prev != NULL) {
                    r->npcs = r->npcs->prev;
                }
                
                
                Npc_ls* tmp_npcs = r->npcs;
                
                while (tmp_npcs != NULL && !blocked) {
                
                    if (tmp_npcs->character == NULL) {
                        npc_null_error(name);
                    }
                    
                    
                    
                    else {
                    
                        //int c_id = tmp_npcs->character->character_id;
                    
                        // for the moment, clip with ALL Npcs
                        
                        
                        blocked = matrix_entity_collide(entity_matrix, ex, ey, w, h, new_x, new_y,
                                                        &(tmp_npcs->character->base), e1_override);
                    
                       //printf("blocked: %d\n", blocked);
                    }
                
                    tmp_npcs = tmp_npcs->next;
                }
                
            }
        }
        
        
        // finally enemies:
        if (!blocked) {
        
            // SEARCH THROUGH ENEMY LISTS
            
            if (r->enemies != NULL) {
                
                while (r->enemies->prev != NULL) {
                    r->enemies = r->enemies->prev;
                }
                
                
                Enemy_ls* tmp_enemies = r->enemies;
                
                while (tmp_enemies != NULL && !blocked) {
                    
                    if (tmp_enemies->enemy == NULL) {
                        enemy_null_error(name);
                    }
                    
                    
                    
                    else {
                        
                        // for the moment, clip with ALL enemies
                        
                        
                        blocked = matrix_entity_collide(entity_matrix, ex, ey, w, h, new_x, new_y,
                                                        &(tmp_enemies->enemy->base), e1_override);
                        
                        //printf("blocked: %d\n", blocked);
                    }
                    
                    tmp_enemies = tmp_enemies->next;
                }
                
            }
        }
        
        
    
        if (inited) {
            free(entity_matrix);
        }
    }
    
    return blocked;
}








/*
 int iy_0 = 0;
 int ix_0 = 0;
 
 int iy_max = h;
 int ix_max = w;
 
 */



int matrix_room_collide(char* matrix, int ex, int ey, int w, int h, int new_x, int new_y, struct room_t* r, int fly) {
    
    char name[] = "matrix_room_collide";
    
    if (matrix == NULL) {
        null_error("Matrix String", name);
        return -1;
    }
    
    else if (r == NULL) {
        room_null_error(name);
        return -1;
    }
    
    else if (r->room_array == NULL) {
        null_error("Room Array", name);
        return -1;
    }
    
    
    
    
    
    int blocked = 0;
    
    for (int iy = 0; iy < h && !blocked; iy ++) {
        
        for (int ix = 0; ix < w && !blocked; ix++) {
            
            /*
             int tmp_x = new_x + rel_ix;     int rel_ix = ix - ex;
             int tmp_y = new_y + rel_iy;     int rel_iy = iy - ey;
             */
            
            // these are x,y points of the entity array/matrix mapped onto the game x,y map,
            // i.e. translated into the actual position in the room / game map.
            
            
            if (matrix[iy * w + ix]) {
                // blacked out point, hence part of entity structure.
                
                int tmp_x = new_x + ix - ex;
                int tmp_y = new_y + iy - ey;
                
                // see if any of these points are out of bounds
                
                if (tmp_x < 0 || tmp_y < 0 || tmp_y >= r->height || tmp_x >= r->width) {
                    blocked = 1;
                }
                
                
                else {
                    // now see if any of these points are clip points.
                    
                    char tile = get_room_tile(r, tmp_x, tmp_y);
                    
                    if (tile == HOLE_N) {
                        if (!fly) {
                            // hence cannot fly,
                            blocked = 1;
                        }
                    }
                    
                    else if (is_clip_tile(tile)) {
                        blocked = 1;
                    }
                }
            }
        }
    }
    
    
    return blocked;
}





int entity_room_tile_collide(struct entity_t* e, struct room_t* r, int tile, int new_x, int new_y,
                             int* x_pos, int* y_pos) {
    
    char name[] = "entity_room_tile";
    
    if (r == NULL) {
        room_null_error(name);
        return -1;
    }
    
    if (e == NULL) {
        entity_null_error(name);
        return -1;
    }
    
    
    if (new_x < 0 || new_y < 0 || new_x >= r->width || new_y >= r->height) {
        return 0;
    }
    
    
    if (r->room_array == NULL) {
        null_error("Room Array", name);
        return -1;
    }
    
    
    
    // first case is simple case.
    
    if (e->default_hit_box == NULL) {
        
        if (r->room_array[new_x + new_y * r->width] == tile) {
            
            if (x_pos != NULL && y_pos != NULL) {  *x_pos = new_x; *y_pos = new_y;}
            return 1;
        }
        
        else {
            return 0;
        }
    }
    
    
    else {
        
        if (e->hit_box == NULL) {
            null_error("Entity Hit Box", name);
            return -1;
        }
        
        
        int w = e->tmp_width;
        int h = e->tmp_height;
        
        int e_x = e->e_x;
        int e_y = e->e_y;
        
        
        
        int blocked = 0;
        
        for (int iy = 0; iy < h && !blocked; iy ++) {
            
            for (int ix = 0; ix < w && !blocked; ix++) {
                
                
                if (e->hit_box[iy * w + ix]) {
                    
                    int tmp_x = new_x + ix - e_x;
                    int tmp_y = new_y + iy - e_y;
                    
                    // see if any of these points are out of bounds
                    
                    if (tmp_x < 0 || tmp_y < 0 || tmp_y >= r->height || tmp_x >= r->width) {
                        ; // next element
                    }
                    
                    else {
                        // now see if any of these points are clip points.
                        
                        if (get_room_tile(r, tmp_x, tmp_y) == tile) {
                            blocked = 1;
                            
                            if (x_pos != NULL && y_pos != NULL) {
                                *x_pos = tmp_x;
                                *y_pos = tmp_y;
                            }
                        }
                    }
                }
            }
        }
        
        if (blocked) {
            return 1;
        }
        
    }
    
    
    return 0;
}














int matrix_entity_collide(char* matrix_1, int e1_x, int e1_y, int w1, int h1, int new_x, int new_y,
                          struct entity_t* e2, int e1_override) {
    
    char name[] = "matrix_entity_collide";
    
    if (e2 == NULL) {
        entity_null_error(name);
        return -1;
    }
    
    
    
    // see if entity is clippable
    
    if (is_entity_clip(e2) || get_entity_override_clip(e2) || e1_override) {
        
        
        
        if (matrix_1 == NULL) {
            null_error("Matrix String", name);
            return -1;
        }
        
        // MAIN FUNCTION
        
        
        
        char* matrix_2 = e2->hit_box;
        int inited = 0;
        
        int w2 = e2->tmp_width;
        int h2 = e2->tmp_height;
        
        
        if (e2->default_hit_box == NULL) {
            matrix_2 = (char*) malloc(sizeof(char));
            matrix_2[0] = 1;
            inited = 1;
            w2 = 1;
            h2 = 1;
        }
        
        else if (e2->hit_box == NULL) {
            null_error("Hit Box Matrix", name);
            return -1;
        }
        
        int e2_x = e2->e_x;
        int e2_y = e2->e_y;
        
        
        
        
        
        /////////////////////////////////////
        
        //// MAIN
        
        // varirable set up, now perform main analysis, for collision detection.
        // assume both matrices are in bounds, and test only if any of them overlap.
        
        // simple method: for each x in each matrix_1, see if it overlaps with any elements in matrix_2,
        // by testing each tile/point point by point
        // hence n^2 complexity.
        
        
        
        int blocked = 0;
        
        
        for (int iy_1 = 0; iy_1 < h1 && !blocked; iy_1++) {
            
            for (int ix_1 = 0; ix_1 < w1 && !blocked; ix_1++) {
                
                
                
                if (matrix_1[ix_1 + iy_1 * w1]) {
                    // hence blacked in point

                    
                    int tmp_x_1 = new_x + ix_1 - e1_x;
                    int tmp_y_1 = new_y + iy_1 - e1_y;
                    
                    
                    
                    for (int iy_2 = 0; iy_2 < h2 && !blocked; iy_2 ++) {
                        
                        for (int ix_2 = 0; ix_2 < w2 && !blocked; ix_2++) {
                            
                            
                            
                            if (matrix_2[ix_2 + iy_2 * w2]) {

                                
                                int tmp_x_2 = e2->x + ix_2 - e2_x;
                                int tmp_y_2 = e2->y + iy_2 - e2_y;
                                
                                
                                if (tmp_x_1 == tmp_x_2 && tmp_y_1 == tmp_y_2) {
                                    
                                    blocked = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        
        
        
        
        if (inited) {
            free(matrix_2);
        }
        
        return blocked;
    }
    
    return 0;
}





int entity_entity_collide(struct entity_t* e1, int x1, int y1, struct entity_t* e2) {

    char name[] = "entity_entity_collide";
    
    if (e1 == NULL || e2 == NULL) {
        entity_null_error(name);
        return -1;
    }
    
    int blocked = 0;
    
    
    if ((is_entity_clip(e1) && is_entity_clip(e2)) ||
        get_entity_override_clip(e1) || get_entity_override_clip(e2)) {
        // simple case, both are single points
        
    
        if (e1->default_hit_box == NULL && e2->default_hit_box == NULL) {
            return (x1 == e2->x && y1 == e2->y);
        }
    
    
        
        
        
        int inited1 = 0;
    
        
        char* matrix_1 = e1->hit_box;
    
        int w1 = e1->tmp_width;
        int h1 = e1->tmp_height;
    
    
        if (e1->default_hit_box == NULL) {
            inited1 = 1;
            w1 = 1;
            h1 = 1;
            matrix_1 = (char*) malloc(sizeof(char));
            matrix_1[0] = 1;
        }
        else if (matrix_1 == NULL) {
            null_error("Entity Hit Box", name);
            return -1;
        }
        
        
        //////
        
        int e1_x = e1->e_x;
        int e1_y = e1->e_y;
        
        
        blocked = matrix_entity_collide(matrix_1, e1_x, e1_y, w1, h1, x1, y1, e2,
                                        get_entity_override_clip(e1));
    
        
        
        if (inited1) {
            free(matrix_1);
        }
    }



    return blocked;
}



/*
 if (e2->default_hit_box == NULL) {
 inited2 = 1;
 w2 = 1;
 h2 = 1;
 matrix_2 = (char*) malloc(sizeof(char));
 matrix_2[0] = 1;
 }
 else if (matrix_2 == NULL) {
 null_error("Entity Hit Box", name);
 if (inited1) {
 free(matrix_1);
 }
 return -1;
 }
 
 
 int e2_x = 0;
 int e2_y = 0;
 
 if (dir2 == UP_DIR) {
 e2_x = w2 - 1;
 e2_y = h2 - 1;
 }
 
 else if (dir2 == LEFT_DIR) {  e2_x = w2 - 1;}
 
 else if (dir2 == DOWN_DIR) {;}
 
 else if (dir2 == RIGHT_DIR) {  e2_y = h2 - 1;}
 
 
 else {
 printf("VALUE ERROR: unknown direction: %d, in function '%s'\n", dir2, name);
 pause_function();
 return -1;
 }
 
 
 // set-up analysis is complete:
 
 
 
 for (int iy_1 = 0; iy_1 < h1 && !blocked; iy_1++) {
 
 for (int ix_1 = 0; ix_1 < w1 && !blocked; ix_1++) {
 
 if (matrix_1[w1*iy_1 + ix_1]) {
 
 int tmp_x_1 = x1 + ix_1 - e1_x;
 int tmp_y_1 = x1 + iy_1 - e1_y;
 
 
 for (int iy_2 = 0; iy_2 < h2 && !blocked; iy_2++) {
 
 for (int ix_2 = 0; ix_2 < w2 && !blocked; ix_2++) {
 
 
 if (matrix_2[w2 * iy_2 + ix_2]) {
 
 
 int tmp_x_2 = e2->x + ix_2 - e2_x;
 int tmp_y_2 = e2->y + iy_2 - e2_y;
 
 
 if (tmp_x_1 == tmp_x_2 && tmp_y_1 == tmp_y_2) {
 blocked = 1;
 }
 }
 }
 }
 }
 }
 
 }*/









/*
 // function calculates whether e1 moving to x1,y1 will collide with e2
 
 int entity_entity_collide(struct entity_t* e1, struct entity_t* e2, int x1, int y1, int dir) {
 
 char name[] = "entity_entity_collide";
 
 if (e1 == NULL || e2 == NULL) {
 entity_null_error(name);
 return -1;
 }
 int blocked = 0;
 
 
 
 
 
 // if already collide let them decouple
 // ALTERNATE IDEA:  if already collide, let them move so long as they remain colliding, hence
 // multiple boss like enemies forming a chain, of smaller enemies ==> one big boss enemy.
 
 // decoupling is only true for ENTITIES, not walls etc.
 
 
 
 int rel_x = e1->x - e2->x;
 int rel_y = e1->y - e2-y;
 
 
 
 char* e1_obj = e1->hit_box;
 char* e2_obj = e2->hit_box;
 
 
 if (e1_obj == NULL) {;}
 
 
 
 
 
 // now see if new posititon collides.
 
 // if char arrays for hit_box are given as null, assume hit box is a perfect rectangle and report no
 // errors, however do have hit_box_error / warning
 
 
 
 
 
 return blocked;
 }
 */ // function not useful at the moment, hence won't finish, but best if use the above function.






int set_entity_hit_box(struct entity_t* e, int dir) {
    
    char name[] = "set_entity_hit_box";
    if (e == NULL) {
        entity_null_error(name);
        return 1;
    }
    
    if (e->default_hit_box == NULL) {
        return 0;
    }
    
    else if (e->hit_box == NULL) {
        if (HIT_BOX_ERROR) {
            null_error("Entity Hit Box", name);
        }
        return 1;
    }
    
    if (dir < UP_DIR || dir > RIGHT_DIR) {
        printf("VALUE ERROR: invalid direction %d, for function: %s, min dir = 0, max dir = 3\n", dir, name);
        pause_function();
        return 1;
    }
    
    
    
    // recall orientations
    /*     0       1       2       3
     * ^ *   * * *   * * *   * * *
     * | *   < - *   * | *   * - >
     * * *   * * *   * v *   * * *
     
     
     e.g. say face up box orientation is:
     
     * * * * ^ (4 x 3), upwards rotation dir = 0.
     * * * * |
     * * * @ |
     <---
     
     1 2 3 4    4 8 @    @ b a 9    9 5 1
     5 6 7 8    3 7 b    8 7 6 5    a 6 2
     9 a b @    2 6 a    4 3 2 1    b 7 3
     1 5 9               @ 8 4
     
     
     Odd rotations will swap x,y, but even will not
     */
    
    
    if (dir % 2 == 0) {
        e->tmp_width = e->width;
        e->tmp_height = e->height;
    }
    else {
        e->tmp_width = e->height;
        e->tmp_height = e->width;
    }
    
    
    int w = e->tmp_width;
    int h = e->tmp_height;
    
    
    // use these values for calculations instead of deferencing constantly.
    

    
        
    // set up the rotation etc.
        
    // if dir = 0, i.e. up, simply copy paste
    // do similar for other directions, e.g. down, copy paste backwards.
        
    
    
    
    // UP DIRECTION ////////////////////
    
    if (dir == UP_DIR) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                e->hit_box[j + w*i] = e->default_hit_box[j + w* i];
            }
        }
        
        
        
        if (e->rot_style == ROT_CORNER_STYLE) {
            e->e_x = w - 1;
            e->e_y = h - 1;
        }
        
        else if (e->rot_style == ROT_CENTRE_STYLE) {
            e->e_x = w / 2;
            e->e_y = h / 2;
        }
        
        else {
            printf("ERROR: unknown rotation style for entities: %d, in function '%s'.\n", e->rot_style, name);
            return 1;
        }
    }
    
    
    // DOWN DIRECTION ////////////////////
    
    else if (dir == DOWN_DIR) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                e->hit_box[j + w*i] = e->default_hit_box[(w - 1 - j) + w* (h - 1 - i)];
            }
        }
        
        if (e->rot_style == ROT_CORNER_STYLE) {
            e->e_x = 0;
            e->e_y = 0;
        }
        
        else if (e->rot_style == ROT_CENTRE_STYLE) {
            e->e_x = w / 2;
            e->e_y = h / 2;
            if (w % 2 == 0) {
                e->e_x --;
            }
            if (h % 2 == 0) {
                e->e_y --;
            }
        }
        
        else {
            printf("ERROR: unknown rotation style for entities: %d, in function '%s'.\n", e->rot_style, name);
            return 1;
        }
    }
    
    
    
    
    // LEFT DIRECTION ////////////////////
    
    else if (dir == LEFT_DIR) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                e->hit_box[j + w*i] = e->default_hit_box[h* (w - 1 - j) + i];
            }
        }
        
        if (e->rot_style == ROT_CORNER_STYLE) {
            e->e_x = w - 1;
            e->e_y = 0;
        }
        
        else if (e->rot_style == ROT_CENTRE_STYLE) {
            e->e_x = w / 2;
            e->e_y = h / 2;
            if (h % 2 == 0) {
                e->e_y --;
            }
        }
        
        else {
            printf("ERROR: unknown rotation style for entities: %d, in function '%s'.\n", e->rot_style, name);
            return 1;
        }
    }
    
    
    
    
    // RIGHT DIRECTION ////////////////////
    
    else if (dir == RIGHT_DIR) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                e->hit_box[j + w*i] = e->default_hit_box[h*j + (h - 1 - i)];
            }
        }
        
        if (e->rot_style == ROT_CORNER_STYLE) {
            e->e_x = 0;
            e->e_y = h - 1;
        }
        
        else if (e->rot_style == ROT_CENTRE_STYLE) {
            e->e_x = w / 2;
            e->e_y = h / 2;
            if (w % 2 == 0) {
                e->e_x --;
            }
        }
        
        else {
            printf("ERROR: unknown rotation style for entities: %d, in function '%s'.\n", e->rot_style, name);
            return 1;
        }
    }
    
    
    
    
    else {
        printf("VALUE ERROR: unknown direction: %d, in function '%s'\n", dir, name);
        pause_function();
        return 1;
    }
    
    
    
    /*
    for (int i = 0; i < h; i ++) {
        for (int j = 0; j < w; j++) {
            printf(" %d", e->hit_box[i*w + j]);
        }
        putchar('\n');
    }
    pause_function();
    */ // THE ABOVE IS DEBUG ONLY
     
    return 0;
}


/*
 1 2 3 4    4 8 @    @ b a 9    9 5 1
 5 6 7 8    3 7 b    8 7 6 5    a 6 2
 9 a b @    2 6 a    4 3 2 1    b 7 3
 1 5 9               @ 8 4
 */







/*
 // assume w and height are the same as the entities base width, height
 // hence test
 
 if (*width != e->width) {
 printf("VALUE ERROR: width of entity: %d,  and width given: %d, are not identical.\n",
 e->width, *width);
 pause_function();
 return 1;
 }
 else if (*height != e->height) {
 printf("VALUE ERROR: height of entity: %d,  and height given: %d, are not identical.\n",
 e->height, *height);
 pause_function();
 return 1;
 }*/

/*
 if (dir % 2 != 0) {
 // hence odd 90 degree / 270 degree rotation
 // swap height, width
 
 int tmp_val = *width;
 *width = *height;
 *height = tmp_val;
 }*/

/*
 if (dir == UP_DIR) {
 w = e->width;
 h = e->height;
 }
 else if (dir == LEFT_DIR) {
 w = e->height;
 h = - e->width;
 }
 else if(dir == DOWN_DIR) {
 w = - e->width;
 h = - e->height;
 }
 else if (dir == RIGHT_DIR) {
 h = e->width;
 w = - e->height;
 }
 */














// player_door_action

/*
 int x_tmp = tmp_x;
 int y_tmp = tmp_y;
 
 
 if (game->player->base.default_hit_box != NULL) {
 
 if (game->player->base.hit_box == NULL) {
 null_error("Player Hit Box", name);
 return -1;
 }
 
 
 
 int found = 0;
 
 int w = game->player->base.w;
 int h = game->player->base.h;
 
 if (game->player->base.direction % 2 != 0) {
 int tmp = w;
 w = h;
 h = tmp;
 }
 
 int e_x = 0;
 int e_y = 0;
 int dir = game->player->base.direction;
 
 
 if (dir == UP_DIR) {
 e_x = w - 1;
 e_y = h - 1;
 }
 
 else if (dir == LEFT_DIR) {  e_x = w - 1;}
 
 else if (dir == DOWN_DIR) {;}
 
 else if (dir == RIGHT_DIR) {  e_y = h - 1;}
 
 
 else {
 printf("VALUE ERROR: unknown direction: %d, in function '%s'\n", name);
 pause_function();
 return -1;
 }
 
 
 for (int iy = 0; iy < h && !found; iy++) {
 for (int ix = 0; ix < w && !found; ix++) {
 
 if (game->player->hit_box[ix + w* iy]) {
 
 int trans_x = tmp_x + ix - e_x;
 int trans_y = tmp_y + iy - e_y;
 
 if (get_room_tile(r, trans_x, trans_y) == DOOR_N) {
 
 found = 1;
 x_tmp = trans_x;
 y_tmp = trans_y;
 
 }
 }
 }
 }
 
 if (!found) {
 printf("ERROR: unable to find door with player co-ordinates: %d,%d\n", tmp_x, tmp_y);
 pause_function();
 return 1;
 }
 }
 
 
 */













int init_entity_hit_box_block(struct entity_t* e, int w, int h, int style, int dir) {

    char name[] = "init_entity_hit_box_block";
    
    if (e == NULL) {
        entity_null_error(name);
        return 1;
    }
    
    
    e->default_hit_box = (char*) malloc(sizeof(char) * w * h);
    e->hit_box = (char*) malloc(sizeof(char) * w * h);
    e->width = w;
    e->height = h;
    
    for (int i = 0; i < w * h; i++) {
        e->default_hit_box[i] = 1;
    }
    //e->default_hit_box[0] = 1; // remember 0 ==> no clip, and no render.
    
    
    if (style == ROT_CORNER_STYLE) {;
    }
    else if (style == ROT_CENTRE_STYLE) {;}
    
    else {
        printf("VALUE ERROR: invalid rotation style %d, in function: '%s'\n", style, name);
        pause_function();
        style = ROT_DEFAULT_STYLE;
    }
    
    e->rot_style = style;
    
    
    // copy over default_hit_box to local hit_box
    return set_entity_hit_box(e, dir);
}

# endif
