# ifndef DRAW_SCREEN_
# define DRAW_SCREEN_

# include "draw_map.c"


int draw_screen(Game* game) {

    if (DRAW_SCREEN) {
        clear_screen();
    
        if (game->inventory) {
            // technically should never be in here, only access menu within 'player_turn()' function
            return draw_inventory(game);
        }
    
        draw_hud(game);
        return draw_map(game);
    }
    return 0;
}














int print_health(Player*);
int print_mana(Player*);
int draw_hud_items(Inventory*);


int draw_hud(Game* game) {

    if (game->player == NULL) {
        return 1;
    }
    
    putchar('\n');
    print_health(game->player);
    if (game->player->has_mana) {
        putchar(' '); putchar(' ');
        print_mana(game->player);
    }
    putchar('\n');
    
    // if coins, and keys > 0, print them
    int coin_num = game->player->inventory->coin_num;
    int key_num = game->player->inventory->key_num;
    int bomb_num = game->player->inventory->bomb_num;
    int arrow_num = game->player->inventory->arrow_num;
    
    if (coin_num > 0) {  printf("  Coins: %4d", coin_num); }
    
    if (key_num > 0) {  printf("  Keys: %2d", key_num); }
    
    if (bomb_num > 0) {  printf("  Bombs: %3d", bomb_num); }
    
    if (arrow_num > 0) {  printf("  Arrows: %3d", arrow_num);}
    
    
    //if (coin_num > 0 || key_num > 0 || bomb_num > 0 || arrow_num > 0) {
        putchar('\n');
    //} // always putch '\n' so map doesn't suddenly move
    
    
    if (game->draw_hud_items) {
        draw_hud_items(game->player->inventory);
    }
    
    putchar('\n');
    
    return 0;
}






// draw the player's current health

int print_health(Player* p) {
    int i = 0;
    
    if (p == NULL) {
        player_null_error("print_health");
        return 1;
    }
    
    //putchar(' ');
    printf("  Health:");
    for (;i < p->base.health; i++) {
        printf(" %s", FULL_HEART);
    }
    for (;i < p->base.max_health; i++) {
        printf(" %s", EMPTY_HEART);
    }

    return 0;
}





int print_mana(Player* p) {
    
    if (p == NULL) {
        player_null_error("print_mana");
        return 1;
    }
    
    printf("  Mana:   ");
    int i = 0;
    for (; i < p->base.mana; i++) {
        printf("%s", FULL_MANA);
    }
    for (; i < p->base.max_mana; i++) {
        printf("%s", EMPTY_MANA);
    }
    return 0;
}








int draw_hud_items(Inventory* i ) {
    
    if (i == NULL) {
        return 0;
    }
    putchar('\n');


    int active_id = EMPTY_ID;
    int consumable_id = EMPTY_ID;
    int passive_id = EMPTY_ID;
    
    if (i->eq_active_item != NULL) {
        active_id = i->eq_active_item->identity;
        if (active_id == NONE_ID) {
            active_id = EMPTY_ID;
        }
    }
    
    if (i->eq_consumable_item != NULL) {
        consumable_id = i->eq_consumable_item->identity;
        if (consumable_id == NONE_ID) {
            consumable_id = EMPTY_ID;
        }
    }
    
    if (i->eq_passive_item != NULL) {
        passive_id = i->eq_passive_item->identity;
        if (passive_id == NONE_ID) {
            passive_id = EMPTY_ID;
        }
    }
    
    
    // header
    //printf("  ACTIVE  CONSUMABLE  PASSIVE\n");
    printf("  A╭────╮    C╭────╮    P╭────╮\n");
    
    // first line
    printf("   │"); print_item_sprite(active_id, 0); printf("│     │");
    print_item_sprite(consumable_id, 0); printf("│     │");
    print_item_sprite(passive_id, 0); printf("│\n");
    
    // second line
    printf("   │"); print_item_sprite(active_id, 1); printf("│     │");
    print_item_sprite(consumable_id, 1); printf("│     │");
    print_item_sprite(passive_id, 1); printf("│\n");
    
    // third line
    printf("   │"); print_item_sprite(active_id, 2); printf("│     │");
    print_item_sprite(consumable_id, 2); printf("│     │");
    print_item_sprite(passive_id, 2); printf("│\n");
    
    // footer
    printf("   ╰────╯     ╰────╯     ╰────╯\n");
    
    return 0;

}









# endif
