# ifndef OUCH_IT_HURTS__
# define OUCH_IT_HURTS__




// take player damage, and dont react. (what do I mean by react???, dont move?);

int player_damage(struct player_t* p, int damage) {
    if (p == NULL) {
        player_null_error("player_damage");
        return 1;
    }
    
    if (!p->hit) {
        p->base.health = p->base.health - damage;
        player_hurt_sound(damage);
        p->hit = 1;
    }
    return 0;
}





// healing functions

// if health > max health, cap at max-health

int player_heal(struct player_t* p, int heal) {
    if (p == NULL) {
        player_null_error("player_heal");
        return 1;
    }
    player_absolute_heal(p, heal);
    
    if (p->base.health > p->base.max_health) {
        p->base.health = p->base.max_health;
    }
    
    return 0;
}


// even if heal > max health, add additional health

int player_absolute_heal(struct player_t* p, int heal) {
    if (p == NULL) {
        player_null_error("player_absolute_heal");
        return 1;
    }
    p->base.health = p->base.health + heal;
    player_heal_sound(heal);
    return 0;
}



// revive player, i.e. set health to max

int revive_player(struct player_t* p) {
    if (p == NULL) {
        player_null_error("revive_player");
        return 1;
    }
    p->base.health = p->base.max_health;
    return 0;
}





// take damage depending on whether in inventory/menu or on map

int game_player_damage(struct game_t* game, int damage) {
    if (game == NULL) {
        null_error(GAME_OBJECT, "game_player_damage");
        return 1;
    }
    if (!game->inventory) {
        player_damage(game->player, damage);
        return draw_screen(game);
    }
    return 0;
}


//int game_player_












// test whether the player is dead or not, ie health <= 0

int player_is_dead(struct player_t* p) {
    if (p == NULL) {
        player_null_error("player_is_dead");
        return -1;
    }
    
    int health = p->base.health;
    
    if (health <= 0) {
        return 1;
    }
    
    return 0;
}










////////////////////////////

// functions related to mana points.



// take player damage, and dont react. (what do I mean by react???, dont move?);

int player_use_mana(struct player_t* p, int points) {
    if (p == NULL) {
        player_null_error("player_use_mana");
        return 1;
    }
    
    p->base.mana = p->base.health - points;
    return 0;
}





// healing functions

// if health > max health, cap at max-health

int player_gain_mana(struct player_t* p, int points) {
    if (p == NULL) {
        player_null_error("player_mana_gain");
        return 1;
    }
    player_gain_absolute_mana(p, points);
    
    if (p->base.mana > p->base.max_mana) {
        p->base.mana = p->base.max_mana;
    }
    
    return 0;
}


// even if heal > max health, add additional health

int player_gain_absolute_mana(struct player_t* p, int points) {
    if (p == NULL) {
        player_null_error("player_gain_absolute_mana");
        return 1;
    }
    p->base.mana = p->base.mana + points;
    player_heal_sound(points);
    return 0;
}












int player_gain_health_container(struct player_t* p, int h) {

    char name[] = "player_gain_health_container";
    
    if (p == NULL) {
        player_null_error(name);
        return 1;
    }
    
    p->base.max_health += h;
    return 0;
}

int player_gain_mana_container(struct player_t* p, int h) {

    char name[] = "player_gain_mana_container";
    
    if (p == NULL) {
        player_null_error(name);
        return 1;
    }
    
    p->base.max_mana += h;
    return 0;
}


#endif
