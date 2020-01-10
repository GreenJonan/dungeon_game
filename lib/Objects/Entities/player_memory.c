# ifndef PLAYER_MEM_
# define PLAYER_MEM_

# include "entity_header.h"

int free_player(Player* p) {
    
    if (p != NULL) {
        free_inventory(p->inventory);
    
        //free_entity(&(p->base)); //commenting this out solves everything!!!, it's because p is partly dealloc'
        
        free_move_ls(p->moves);
        
        
        if (p->base.hit_box != NULL) {
            free(p->base.hit_box);
        }
        if (p->base.default_hit_box != NULL) {
            free(p->base.default_hit_box);
        }
        
        
        
        free(p);

    }
    
    return 0;
}









// free inventory function

int free_inventory(Inventory* inv) {
    
    if (inv != NULL) {
        
        if (inv->active != NULL) {
            while(inv->active->prev != NULL) {
                inv->active = inv->active->prev;
            }
            free_item_nodes(inv->active);
        }
        
        
        if (inv->passive != NULL) {
            while(inv->passive->prev != NULL) {
                inv->passive = inv->passive->prev;
            }
            free_item_nodes(inv->passive);
        }
        
        
        if (inv->consumable != NULL) {
            while(inv->consumable->prev != NULL) {
                inv->consumable = inv->active->prev;
            }
            free_item_nodes(inv->consumable);
        }
        
        free(inv);
    }
    return 0;
}







////////////////////////////////////////////////////////////////

///
///     Memory Allocate Functions
///

// look at player_init() for initialisation implementation.


Player* allocate_player() {
    
    Player* ptr = (Player*) malloc(sizeof(Player));
    ptr->inventory = init_inventory();

    ptr->moves = (Move_ls*) malloc(sizeof(Move_ls));
    ptr->base.default_hit_box = NULL;
    ptr->base.hit_box = NULL;
    ptr->hit = 0;
    ptr->loop = 0;
    return ptr;
}







    
Item_ls* init_none_list();



// initialise empty_inventory;

Inventory* init_inventory() {
    
    Inventory* ptr = (Inventory*) malloc(sizeof(Inventory));
    
    ptr->eq_active_item = NULL;
    ptr->eq_consumable_item = NULL;
    ptr->eq_passive_item = NULL;
    
    ptr->prev_active = NULL;
    ptr->prev_consumable = NULL;
    ptr->prev_passive = NULL;
    
    ptr->active = init_none_list();
    ptr->passive = init_none_list();
    ptr->consumable = init_none_list();

    
    ptr->active_len = 0;
    ptr->passive_len = 0;
    ptr->consumable_len = 0;
    
    for (int i = 0; i < 3; i++) {
        ptr->inv_item_pos[i] = 0;
        ptr->inv_item_cursors[i] = 0;
    }
    ptr->inv_cursor = 400;
    
    ptr->key_num = 0;
    ptr->coin_num = 0;
    
    return ptr;
}
    





Item_ls* init_none_list() {
    Item_ls* i = (Item_ls*) malloc(sizeof(Item_ls));
    i->prev = NULL;
    i->next = NULL;
    i->item = init_none_item();
    return i;
}
# endif
