# ifndef LINKED_LIST_TRAV__
# define LINKED_LIST_TRAV__

// the following linked_lists will have the following strucure:
/*
 struct p{
    Base* base;
    struct p* next;
    struct p* prev;
 }*/


// ITEM LIST

Item_ls* first_item_node(Item_ls* item_list) {
    if (item_list == NULL) {
        null_error(ITEM_LS_OBJECT, "first_item_node");
        return NULL;
    }
    
    Item_ls* output = item_list;
    Item_ls* prev_ls = output->prev;
    
    while (prev_ls != NULL) {
        output = prev_ls;
        prev_ls = output->prev;
    }
    return output;
}




Item_ls* last_item_node(Item_ls* item_list) {
    
    if (item_list == NULL) {
        null_error(ITEM_LS_OBJECT, "last_item_node");
        return NULL;
    }
    
    Item_ls* output = item_list;
    Item_ls* next_ls = output->next;
    
    while (next_ls != NULL) {
        output = next_ls;
        next_ls = output->next;
    }
    return output;
}







// ENEMY LIST

Enemy_ls* first_enemy_node(Enemy_ls* l_list) {
    if (l_list == NULL) {
        null_error(ENEMY_LS_OBJECT, "first_enemy_node");
        return NULL;
    }
    
    Enemy_ls* output = l_list;
    Enemy_ls* prev_ls = output->prev;
    
    while (prev_ls != NULL) {
        output = prev_ls;
        prev_ls = output->prev;
    }
    return output;
}




Enemy_ls* last_enemy_node(Enemy_ls* l_list) {
    
    if (l_list == NULL) {
        null_error(ENEMY_LS_OBJECT, "last_enemy_node");
        return NULL;
    }
    
    Enemy_ls* output = l_list;
    Enemy_ls* next_ls = output->next;
    
    while (next_ls != NULL) {
        output = next_ls;
        next_ls = output->next;
    }
    return output;
}




// SPECIAL ENTITY LIST

Spc_ent_ls* first_special_entity_node(Spc_ent_ls* l_list) {
    if (l_list == NULL) {
        null_error(SPECIAL_ENTITY_LS_OBJECT, "first_special_entity_node");
        return NULL;
    }
    
    Spc_ent_ls* output = l_list;
    Spc_ent_ls* prev_ls = output->prev;
    
    while (prev_ls != NULL) {
        output = prev_ls;
        prev_ls = output->prev;
    }
    return output;
}




Spc_ent_ls* last_special_entity_node(Spc_ent_ls* l_list) {
    
    if (l_list == NULL) {
        null_error(SPECIAL_ENTITY_LS_OBJECT, "last_special_entity_node");
        return NULL;
    }
    
    Spc_ent_ls* output = l_list;
    Spc_ent_ls* next_ls = output->next;
    
    while (next_ls != NULL) {
        output = next_ls;
        next_ls = output->next;
    }
    return output;
}


# endif
