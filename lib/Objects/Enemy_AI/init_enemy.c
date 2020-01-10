# ifndef INITIALISE_ALL_THE_ENEMIES___
# define INITIALISE_ALL_THE_ENEMIES___

int init_enemy_default(struct enemy_t*);


///////
/*
 ABOUT:
 
 Enemy AI:
 SP: scared of spikes
 
 IDLE AI:
 (0) SM:  static motion
 (1) RJ:  Random jiggling
 
 ACTIVE AI:
 (0) N:   No active ai
 (1) CV:  Corner vision motion
 (2) SCV: Sees around corners, but also can see through all tiles.
 (3) PV:  path finder vision motion
 (4) SPV: path finder, but can see through all tiles.
 
 
 AI is given by a single number, odd ==> SP, even ==> !SP, AI = (AI - (AI % 2)) / 2;
 which is decomposed into two numbers by the digits of the AI number in base AI_LEN = 6;
 
 The two digits refer sequentially to idle ai and player seen ai
 
 If scared of spikes, then the tile counts as a blocked tile, ie the enemy will not try to go through it.
 
 

 
 
 
 
 */
///////



int get_ai_num(int, int, int);





int init_orb(struct enemy_t* e) {
    
    int i = init_enemy_default(e);
    if (i) { return i;}
    
    e->ai = get_ai_num(0, STATIC_AI, STATIC_AI);
    e->enemy_id = ORB_ID;
    
    e->touch_dmg = 1;
    e->base.clock = SLIME_SPEED;
    e->base.timer = e->base.clock;
    
    e->base.health = -1;
    e->base.max_health = -1;
    
    e->base.light_dist = ORB_LIGHT_DIST;
    e->base.eyesight = ORB_EYESIGHT;
   
    
    set_entity_clip(&(e->base), 1);
    e->base.fly = 1;
    e->item_rnd = 0;
    
    return 0;
}






int init_slime(struct enemy_t* e) {

    int i = init_enemy_default(e);
    if (i) { return i;}
    
    e->ai = get_ai_num(0, RANDOM_AI, RANDOM_AI);
    e->enemy_id = SLIME_ID;
    
    e->touch_dmg = 1;
    e->base.clock = SLIME_SPEED;
    e->base.timer = e->base.clock;
    
    e->base.health = 2;
    e->base.max_health = 2;
    
    e->base.light_dist = SLIME_LIGHT_DIST;
    e->base.eyesight = SLIME_EYESIGHT;
    
    e->wait_rnd = 0.25;
    e->item_rnd = 0.65;
    
    set_entity_clip(&(e->base), 1);
    
    return 0;
}



int init_baby_slime(struct enemy_t* e) {
    
    int i = init_enemy_default(e);
    if (i) { return i;}
    
    e->ai = get_ai_num(0, STATIC_AI, RANDOM_AI);
    e->enemy_id = BABY_SLIME_ID;
    
    e->touch_dmg = 1;
    e->base.clock = BABY_SLIME_SPEED;
    e->base.timer = e->base.clock;
    
    e->base.health = 1;
    e->base.max_health = 1;
    
    e->base.light_dist = BABY_SLIME_LIGHT_DIST;
    e->base.eyesight = BABY_SLIME_EYESIGHT;
    
    e->wait_rnd = 0.25;
    e->item_rnd = 0;
    
    set_entity_clip(&(e->base), 1);
    
    return 0;
}






int init_knight(struct enemy_t* e) {
    
    int i = init_enemy_default(e);
    if (i) { return i;}
    
    e->ai = get_ai_num(1, RANDOM_TURN_AI, CORNER_TURN_AI);
    e->enemy_id = KNIGHT_ID;
    
    e->touch_dmg = 2;
    
    if (e->champion) {
        e->base.clock = KNIGHT_SPEED;
    }
    else {
        e->base.clock = (3 * KNIGHT_SPEED) / 2;
    }
    e->base.timer = e->base.clock;
    
    e->base.health = 4;
    e->base.max_health = 4;
    
    e->base.light_dist = KNIGHT_LIGHT_DIST;
    e->base.eyesight = KNIGHT_EYESIGHT;
    
    e->wait_rnd = 0.5;
    e->turn_rnd = 0.5;
    e->item_rnd = 0.7;
    
    set_entity_clip(&(e->base), 1);
    
    return 0;
}



int init_ghost(struct enemy_t* e) {
    
    int i = init_enemy_default(e);
    if (i) { return i;}
    
    e->ai = get_ai_num(1, STATIC_AI, CORNER_AI);
    e->enemy_id = GHOST_ID;
    
    e->touch_dmg = 1;
    e->base.clock = GHOST_SPEED;
    e->base.timer = e->base.clock;
    
    e->base.health = 3;
    e->base.max_health = 3;
    
    e->base.light_dist = GHOST_LIGHT_DIST;
    e->base.eyesight = GHOST_EYESIGHT;
    
    e->wait_rnd = 0;
    e->item_rnd = 0.8;
    
    e->base.fly = 1;
    
    return 0;
}






int init_skeleton(struct enemy_t* e) {
    
    int i = init_enemy_default(e);
    if (i) { return i;}
    
    e->ai = get_ai_num(1, RANDOM_TURN_AI, CORNER_TURN_AI);
    e->enemy_id = SKELETON_ID;
    
    e->touch_dmg = 1;
    e->base.clock = SKELETON_SPEED;
    e->base.timer = e->base.clock;
    
    e->base.health = 3;
    e->base.max_health = 3;
    
    e->base.light_dist = SKELETON_LIGHT_DIST;
    e->base.eyesight = SKELETON_EYESIGHT;
    
    e->wait_rnd = 0;
    e->turn_rnd = 0.5;
    e->item_rnd = 0.3;
    
    set_entity_clip(&(e->base), 1);
    
    return 0;
}






int init_zombie(struct enemy_t* e) {
    
    int i = init_enemy_default(e);
    if (i) { return i;}
    
    e->ai = get_ai_num(1, STATIC_AI, CORNER_TURN_AI);
    e->enemy_id = ZOMBIE_ID;
    
    e->touch_dmg = 1;
    e->base.clock = ZOMBIE_SPEED;
    e->base.timer = e->base.clock;
    
    e->base.health = 4;
    e->base.max_health = 4;
    
    e->base.light_dist = ZOMBIE_LIGHT_DIST;
    e->base.eyesight = ZOMBIE_EYESIGHT;
    
    e->wait_rnd = 0;
    e->turn_rnd = 0.5;
    e->item_rnd = 0.2;
    set_entity_clip(&(e->base), 1);
    
    return 0;
}





///////////////////////////////////////////


int init_enemy_default(struct enemy_t* e) {
    if (e == NULL) {
        enemy_null_error("init_enemy_default");
        return 1;
    }
    
    // do something
    
    e->shield = 0;
    
    e->base.clock = PLAYER_CLOCK;
    e->base.timer = 0;
    
    e->player_x = -1;
    e->player_y = -1;
    return 0;
}






int get_ai_num(int scared, int idle, int active) {

    return scared + ((idle % AI_PAS_NUM) * SCARED_NUM) + ((active % AI_ACT_NUM) * SCARED_NUM*AI_PAS_NUM);
}

int get_ai_scared(int ai) {
    return ai % SCARED_NUM;
}

int get_ai_idle(int ai) {
    return (ai / SCARED_NUM) % AI_PAS_NUM;
}


int get_ai_active(int ai) {
    return (ai / (AI_PAS_NUM * SCARED_NUM)) % AI_ACT_NUM;
}


# endif
