# ifndef ITEM_AND_ENEMY_MEM__
# define ITEM_AND_ENEMY_MEM__


// free entities

int free_entity(Entity* entity) {
    if (NULL == entity) {
        null_warning(ENTITY_OBJECT, "free_entity");
        return 1;
    }
    
    if (entity->default_hit_box != NULL) {
        free(entity->default_hit_box);
    }
    if (entity->hit_box != NULL) {
        free(entity->hit_box);
    }
    
    free(entity);
    return 0;
}


//WARNING!!!!
// no need to free base, because its not a pointer and free() automatically frees it.


// free items

int free_item(Item* item) {
    if (NULL == item) {
        already_freed_warning(ITEM_OBJECT, "free_item");
        return 1;
    }
    
    if (item->base.default_hit_box != NULL) {
        free(item->base.default_hit_box);
    }
    if (item->base.hit_box != NULL) {
        free(item->base.hit_box);
    }
    
    free(item);
    return 0;
}


// free enemy

int free_enemy(Enemy* enemy) {
    if (NULL == enemy) {
        already_freed_warning(ENEMY_OBJECT, "free_enemy");
        return 1;
    }
    
    if (enemy->base.default_hit_box != NULL) {
        free(enemy->base.default_hit_box);
    }
    if (enemy->base.hit_box != NULL) {
        free(enemy->base.hit_box);
    }
    
    
    if (enemy->item != NULL) {
        free_item(enemy->item);
    }
    
    free(enemy);
    return 0;
}



// free special entities

int free_special_entity(Spc_ent* e) {
    if (e == NULL) {
        already_freed_warning(SPECIAL_ENTITY_OBJECT, "free_special_entity");
        return 1;
    }
    
    if (e->base.default_hit_box != NULL) {
        free(e->base.default_hit_box);
    }
    if (e->base.hit_box != NULL) {
        free(e->base.hit_box);
    }
    
    free(e);
    return 0;
}




// free npcs

int free_npc(Npc* n) {
    if (n == NULL) {
        null_error(NPC_OBJECT, "free_npc");
        return 1;
    }
    
    if (n->base.default_hit_box != NULL) {
        free(n->base.default_hit_box);
    }
    if (n->base.hit_box != NULL) {
        free(n->base.hit_box);
    }
    
    // free items
    if (n->items != NULL) {
        free_item_ls(n->items);
    }
    
    free(n);
    return 0;
}







///////////////////////////////////////////////////////////////

//// FREE LISTS

// assume the lists are not circular.


// ITEM LIST

int free_item_ls(Item_ls* items) {
    if (NULL == items) {
        null_warning(ITEM_LS_OBJECT, "free_item_ls");
        return 1;
    }
    
    // first the first pointer in the item linked list.
    Item_ls* ptr = first_item_node(items);
    
    return free_item_nodes(ptr);
}




// ENEMY LIST

int free_enemy_ls(Enemy_ls* enemies) {
    if (NULL == enemies) {
        null_warning(ENEMY_LS_OBJECT, "free_enemy_ls");
        return 1;
    }
    
    // first the first pointer in the enemy linked list.
    Enemy_ls* ptr = first_enemy_node(enemies);
    
    return free_enemy_nodes(ptr);

}



// SPECIAL ENTITY LIST

int free_special_entity_ls(Spc_ent_ls* e_ls) {

    if (NULL == e_ls) {
        null_warning(SPECIAL_ENTITY_LS_OBJECT, "free_special_entity_ls");
        return 1;
    }
    
    Spc_ent_ls* ptr = first_special_entity_node(e_ls);
    return free_special_entity_nodes(ptr);
}




// NPC LIST

int free_npc_ls(Npc_ls* e_ls) {
    
    if (NULL == e_ls) {
        null_warning(NPC_LS_OBJECT, "free_npc_ls");
        return 1;
    }
    
    while (e_ls->prev != NULL) {
        e_ls = e_ls->prev;
    }
    return free_npc_nodes(e_ls);
}









/// FREE NODES FUNCTIONS

// items

int free_item_nodes(Item_ls* item_node) {
    if (NULL == item_node) {
        null_error(ITEM_LS_OBJECT, "free_item_nodes");
        return 1;
    }
    if (NULL != item_node->next) {
        free_item_nodes(item_node->next);
    }
    free_item(item_node->item);
    free(item_node);
    return 0;
}



// enemies

int free_enemy_nodes(Enemy_ls* enemy_node) {
    if (NULL == enemy_node) {
        null_error(ENEMY_LS_OBJECT, "free_enemy_nodes");
        return 1;
    }
    if (NULL != enemy_node->next) {
        free_enemy_nodes(enemy_node->next);
    }
    free_enemy(enemy_node->enemy);
    free(enemy_node);
    return 0;
}




// special entities

int free_special_entity_nodes(Spc_ent_ls* e_node) {
    if (NULL == e_node) {
        null_error(SPECIAL_ENTITY_LS_OBJECT, "free_special_entity_nodes");
        return 1;
    }
    if (NULL != e_node->next) {
        free_special_entity_nodes(e_node->next);
    }
    free_special_entity(e_node->spc_entity);
    free(e_node);
    return 0;
}




// NPCS

int free_npc_nodes(Npc_ls* e_node) {
    if (NULL == e_node) {
        null_error(NPC_LS_OBJECT, "free_npc_nodes");
        return 1;
    }
    if (NULL != e_node->next) {
        free_npc_nodes(e_node->next);
    }
    free_npc(e_node->character);
    free(e_node);
    return 0;
}








/////////////////////////////////////////////////////

// KILL ITEM / ENEMY   -->   Remove one node from the doubly linked list of enemies.

// assume given the node pointer,
// recall each node has a next and prev node

int kill_enemy(Room* room, Enemy_ls* enemy_ptr) {
    char name[] = "kill_enemy";
    
    if (NULL == enemy_ptr){
        null_error(ENEMY_LS_OBJECT,name);
        return 1;
    }
    if (NULL == enemy_ptr->enemy) {
        enemy_null_error(name);
        return 1;
    }
    if (room == NULL) {
        room_null_error(name);
        return 1;
    }
    
    
    // if can drop item, drop it
    if (enemy_ptr->enemy->drop_item) {
    
        enemy_ptr->enemy->item->base.x = enemy_ptr->enemy->base.x;
        enemy_ptr->enemy->item->base.y = enemy_ptr->enemy->base.y;
        
        room->items = push_item_start(room->items, enemy_ptr->enemy->item);
        enemy_ptr->enemy->item = NULL; // so does free item.
        
    }
    
    else {
        // appeal to some rnd process to generate random items to drop
        float p = rand();
        p = p / RAND_MAX;
        
        if (p < enemy_ptr->enemy->item_rnd) {
        
            // find item of item to randomlly drop.
            // order of most likely to drop
            // coin, heart, mana, bomb, arrow
            // 0.4    0.2    0.2   0.1   0.1
            
            float drop_num = rand();
            drop_num = drop_num / RAND_MAX;
            
            Item* i = allocate_item(1);
            int num = 1;
            
            if (drop_num < 0.4) {
                init_coin(i, DEFAULT_MSG);
                
                float q = rand();
                q = q / RAND_MAX;
                if (q < 0.6) {  num = 1;}
                
                else if (q < 0.9) {  num = 5;}
                
                else if (q < 1.0) { num = 10;}
                
                else { num = 100;}
            }
            
            else if (drop_num < 0.6) {  init_heart(i, DEFAULT_MSG);  }
            
            else if (drop_num < 0.8) {  init_mana(i, DEFAULT_MSG);  }
            
            else if (drop_num < 0.9) {  init_arrow(i, DEFAULT_MSG); }
            
            else if (drop_num < 1.0) {  init_bomb(i, DEFAULT_MSG);  }
            
            else { //hence rand() == RAND_MAX
                
                // need to think of some special item to drop, at the moment drop free item
                init_freeze(i, DEFAULT_MSG);
                num = 10;
            }
            

            i->num = num;
            i->base.x = enemy_ptr->enemy->base.x;
            i->base.y = enemy_ptr->enemy->base.y;
            
            room->items = push_item_start(room->items, i);
            
        }
    }
    
    free_enemy(enemy_ptr->enemy);
    
    
    
    
    
    int forward_null = (NULL == enemy_ptr->next);
    int backward_null = (NULL == enemy_ptr->prev);
    
    if (backward_null && forward_null) {
        free(enemy_ptr);
    
        room->enemies = NULL;
        return 0;
    }
    
    else {
        if (backward_null) {
            enemy_ptr->next->prev = NULL;
        }
        else if (forward_null) {
            enemy_ptr->prev->next = NULL;
        }
        else {
            enemy_ptr->next->prev = enemy_ptr->prev;
            enemy_ptr->prev->next = enemy_ptr->next;
        }
        
        
        // make sure the room does not point to a freed varaible
        if (room->enemies == enemy_ptr) {
            if (enemy_ptr->prev == NULL) {
                room->enemies = enemy_ptr->next;
            }
            else {
                room->enemies = enemy_ptr->prev;
            }
        }
        
        free(enemy_ptr);
    }
    return 0;
}





int kill_item(Room* room, Item_ls* item_ptr) {
    
    if (NULL == item_ptr){
        null_error(ITEM_LS_OBJECT, "kill_item");
        return 1;
    }
        
    free_item(item_ptr->item);
        
    int forward_null = (NULL == item_ptr->next);
    int backward_null = (NULL == item_ptr->prev);
        
    if (backward_null && forward_null) {
        free(item_ptr);
        if (room == NULL) {
            null_warning(ROOM_OBJECT, "kill_item");
        }
        else {
            room->items = NULL;
        }
        return 0;
    }
        
    else {
        if (backward_null) {
            item_ptr->next->prev = NULL;
            
        }
        else if (forward_null) {
            item_ptr->prev->next = NULL;
        }
        else {
            item_ptr->next->prev = item_ptr->prev;
            item_ptr->prev->next = item_ptr->next;
        }
        
        
        // make sure the room does not point to a freed varaible
        if (room->items == item_ptr) {
            if (item_ptr->prev == NULL) {
                room->items = item_ptr->next;
            }
            else {
                room->items = item_ptr->prev;
            }
        }
        
        
        free(item_ptr);
    }
    return 0;
}







int kill_special_entity(Room* room, Spc_ent_ls* ptr, int weapon) {
    
    if (NULL == ptr){
        null_error(SPECIAL_ENTITY_LS_OBJECT, "kill_special_entity");
        return 1;
    }
    
    free_special_entity(ptr->spc_entity);
    
    int forward_null = (NULL == ptr->next);
    int backward_null = (NULL == ptr->prev);
    
    if (backward_null && forward_null) {
        free(ptr);
        if (room == NULL) {
            null_warning(ROOM_OBJECT, "kill_special_entity");
        }
        else {
            if (weapon) {
                room->spc_weapon_entities = NULL;
            }
            else {
                room->spc_room_entities = NULL;
            }
        }
        return 0;
    }
    
    else {
        if (backward_null) {
            ptr->next->prev = NULL;
        }
        else if (forward_null) {
            ptr->prev->next = NULL;
        }
        else {
            ptr->next->prev = ptr->prev;
            ptr->prev->next = ptr->next;
        }
        
        
        // make sure the room does not point to a freed varaible
        if (weapon) {
            if (room->spc_weapon_entities == ptr) {
                if (ptr->prev == NULL) {
                    room->spc_weapon_entities = ptr->next;
                }
                else {
                    room->spc_weapon_entities = ptr->prev;
                }
            }
        }
        else {
            if (room->spc_room_entities == ptr) {
                if (ptr->prev == NULL) {
                    room->spc_room_entities = ptr->next;
                }
                else {
                    room->spc_room_entities = ptr->prev;
                }
            }
        }
        
        free(ptr);
    }
    return 0;
}







int kill_npc(Room* room, Npc_ls* ptr) {
    
    char name[] = "kill_npc";
    
    if (NULL == ptr){
        null_error(NPC_LS_OBJECT, name);
        return 1;
    }
    if (NULL == ptr->character) {
        npc_null_error(name);
        return 1;
    }
    if (NULL == room) {
        room_null_error(name);
        return 1;
    }
    
    
    // need to pop-out item_ls && append it to room item_ls
    int popped = 0;
    
    Item_ls* npc_items = ptr->character->items;
    if (npc_items != NULL) {
        
        while (npc_items->prev != NULL) {
            npc_items = npc_items->prev;
        }
    
        Item_ls* room_items = room->items;
        if (room_items == NULL) {
            room->items = npc_items;
        }
        else {
            while (room_items->next != NULL) {
                room_items = room_items->next;
            }
        
            
            // now at end and start of both lists
            room_items->next = npc_items;
            npc_items->prev = room_items;
            
            popped = 1;
        }
    }
    
    
    if (popped) {
        free(ptr->character);
    }
    
    else {
        free_npc(ptr->character);
    }
    
    
    
    
    int forward_null = (NULL == ptr->next);
    int backward_null = (NULL == ptr->prev);
    
    if (backward_null && forward_null) {
        free(ptr);
        
        room->npcs = NULL;
        return 0;
    }
    
    else {
        if (backward_null) {
            ptr->next->prev = NULL;
            
        }
        else if (forward_null) {
            ptr->prev->next = NULL;
        }
        else {
            ptr->next->prev = ptr->prev;
            ptr->prev->next = ptr->next;
        }
        
        
        // make sure the room does not point to NULL
        if (room->npcs == ptr) {
            if (ptr->prev == NULL) {
                room->npcs = ptr->next;
            }
            else {
                room->npcs = ptr->prev;
            }
        }
        
        
        free(ptr);
    }
    return 0;
}











/////////////////////////////////////////////////////////



// take an item out of the room_ls.

Item* pop_item_ls_room(Item_ls* i_ls, Room* r) {

    char name[] = "pop_item_ls_room";
    
    if (i_ls == NULL) {
        null_error(ITEM_LS_OBJECT, name);
        return NULL;
    }
    
    if (r == NULL) {
        room_null_error(name);
        return NULL;
    }
    
    Item* i = i_ls->item;
    
    int is_head = 0;
    if (r->items == i_ls) { is_head = 1;}
    
    
    int prev_null = 0;
    int next_null = 0;
    if (i_ls->prev == NULL) { prev_null = 1;}
    if (i_ls->next == NULL) { next_null = 1;}
    
    if (!prev_null) {
        i_ls->prev->next = i_ls->next;
    }
    else {
        /*
        if (!is_head) {
            printf("ERROR: item should be head\n");
            pause_function();
        }
        else {*/
            r->items = i_ls->next;
        //}
    }
    
    if (!next_null) {
        i_ls->next->prev = i_ls->prev;
    }
    
    free(i_ls);

    return i;
}





// take an item out of an NPC's inventory / item_ls

Item* pop_item_ls_npc(Item_ls* i_ls, Npc* n) {
    
    char name[] = "pop_item_ls_npc";
    
    if (i_ls == NULL) {
        null_error(ITEM_LS_OBJECT, name);
        return NULL;
    }
    
    if (n == NULL) {
        npc_null_error(name);
        return NULL;
    }
    
    Item* i = i_ls->item;
    
    int is_head = 0;
    if (n->items == i_ls) { is_head = 1;}
    
    
    int prev_null = 0;
    int next_null = 0;
    if (i_ls->prev == NULL) { prev_null = 1;}
    if (i_ls->next == NULL) { next_null = 1;}
    
    if (!prev_null) {
        i_ls->prev->next = i_ls->next;
    }
    else {
        n->items = i_ls->next;
    }
    
    if (!next_null) {
        i_ls->next->prev = i_ls->prev;
    }
    
    free(i_ls);
    
    return i;
}










/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////



// ALLOCATE FUNCTIONS

int default_entity_base(Entity* e) {
    if (e == NULL) {
        entity_null_error("default_entity_base");
        return 1;
    }
    e->vel_x = 0;
    e->vel_y = 0;
    
    e->hit_box = NULL;
    e->default_hit_box = NULL;
    e->e_x = 0;
    e->e_y = 0;
    e->tmp_height = 1;
    e->tmp_width = 1;
    e->msg[0] = 0;
    e->status = 0;
    set_entity_override_clip(e, 0);
    return 0;
}


// entity

Entity* allocate_entity(int num) {
    Entity* e = malloc(sizeof(Entity) * num);
    for (int i = 0; i < num; i++) {
        default_entity_base(&(e[i]));
    }
    return e;
}


// item

Item* allocate_item(int num) {
    Item* i = malloc(sizeof(Item) * num);
    for (int j = 0; j < num; j++) {
        default_entity_base(&(i[j].base));
    }
    return i;
}

// enemy

Enemy* allocate_enemy(int num) {
    Enemy* e = malloc(sizeof(Enemy)*num);
    for (int j = 0; j < num; j++) {
        default_entity_base(&(e[j].base));
        
        (e[j]).item = NULL;
        (e[j]).wait_rnd = 0;
        (e[j]).turn_rnd = 0;
        (e[j]).item_rnd = 0;
    }
    return e;
}


// special entity

Spc_ent* allocate_special_entity(int num) {
    Spc_ent* se = malloc(sizeof(Spc_ent) * num);
    for (int j = 0; j < num; j++) {
        default_entity_base(&(se[j].base));
    }
    return se;
}



// npc

Npc* allocate_npc(int num) {
    Npc* ne = malloc(sizeof(Npc) * num);
    for (int j = 0; j < num; j++) {
        default_entity_base(&(ne[j].base));
        
        (ne[j]).items = NULL;
        set_entity_clip(&((ne[j]).base), 1);
    }
    return ne;
}








// Allocate lists functions

// items

Item_ls* allocate_item_ls(Item* item_) {
    Item_ls* ptr = malloc(sizeof(Item_ls));
    ptr->item = item_;
    ptr->prev = NULL;
    ptr->next = NULL;
    return ptr;
}


// enemies

Enemy_ls* allocate_enemy_ls(Enemy* enemy_) {
    Enemy_ls* ptr = malloc(sizeof(Enemy_ls));
    ptr->enemy = enemy_;
    ptr->prev = NULL;
    ptr->next = NULL;
    return ptr;
}


Spc_ent_ls* allocate_special_entity_ls(Spc_ent* e) {
    Spc_ent_ls* ptr= malloc(sizeof(Spc_ent_ls));
    ptr->spc_entity = e;
    ptr->prev = NULL;
    ptr->next = NULL;
    return ptr;
}



Npc_ls* allocate_npc_ls(Npc* e) {
    Npc_ls* ptr= malloc(sizeof(Npc_ls));
    ptr->character = e;
    ptr->prev = NULL;
    ptr->next = NULL;
    return ptr;
}






// ADD ITEMS AND ENEMIES,
// The functions for each function are the same, only difference is their type
// hence similar data structure objects will have the same function

// METHOD: push new element to the begging of the list


// ITEM

Item_ls* push_item_start(Item_ls* old_head, Item* item) {
    
    Item_ls* new_head = allocate_item_ls(item);
    
    new_head->next = old_head;
    if (NULL != old_head) {
        old_head->prev = new_head;
    }
    
    return new_head;
}



// ENEMY

Enemy_ls* push_enemy_start(Enemy_ls* old_head, Enemy* enemy) {
    
    Enemy_ls* new_head = allocate_enemy_ls(enemy);
    
    new_head->next = old_head;
    if (NULL != old_head) {
        old_head->prev = new_head;
    }
    
    return new_head;
}




// SPECIAL ENTITY - PUSH NEW OBJECT TO END OF LINE

Spc_ent_ls* push_special_entity_end(Spc_ent_ls* head, Spc_ent* e) {
    
    Spc_ent_ls* new_obj = allocate_special_entity_ls(e);
    
    if (head == NULL) {
        return new_obj;
    }
    
    else {
        Spc_ent_ls* end = head;
        
        while (end->next != NULL) {
            end = end->next;
        }
        
        // now found end of queue.
        end->next = new_obj;
        new_obj->prev= end;
        
        return head;
    }
}


int queue_npc(struct room_t* r, struct npc_t* n) {
    char name[] = "queue_npc";
    
    if (r == NULL) {
        room_null_error(name);
        return 1;
    }
    if (n == NULL) {
        npc_null_error(name);
        return 1;
    }
    
    Npc_ls* n_ls = allocate_npc_ls(n);
    
    if (n_ls == NULL) {
        null_error(NPC_LS_OBJECT, name);
        return 1;
    }
    
    if (r->npcs == NULL) {
        r->npcs = n_ls;
    }
    
    
    else {
    
        Npc_ls* ptr = r->npcs;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        
        ptr->next = n_ls;
        n_ls->prev = ptr;
    }
    
    
    return 0;
}


# endif
