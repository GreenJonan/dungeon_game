# ifndef ENEMY_AI_CLOCK_RATE__
# define ENEMY_AI_CLOCK_RATE__

# define PLAYER_CLOCK 4
# define FREEZE_LOOP_LEN 5
//# define HIT_COOLDOWN 5

# define TICK 100000     //micro-seconds    // let 1 tick = 1/10-th of a second

# define SLEEP_TIME (TICK * 2) / PLAYER_CLOCK



# define BOMB_CLOCK 5 * PLAYER_CLOCK

// enemy cooldown clocks, that is how long until they can perform an action again.

//# define SPIKE_CLOCK PLAYER_CLOCK
//--> have it set so every time the player performs an action, see if on spike tile, if so take damage

# define BASE_DAMAGE 1



# define SPIKE_DAMAGE BASE_DAMAGE



/*
 ENEMY AIS:
 
 three classes, scred, passive, active
 */

# define WEAPON_SCARED_AI 2

# define STATIC_AI 0
# define RANDOM_AI 1
# define RANDOM_TURN_AI 2

# define CORNER_AI 3
# define CORNER_TURN_AI 4



# define SCARED_NUM 3
# define AI_ACT_NUM 5
# define AI_PAS_NUM 3






# define SLIME_SPEED 6
# define KNIGHT_SPEED 4 * 2
# define GHOST_SPEED 5
# define BABY_SLIME_SPEED 3
# define SKELETON_SPEED 7
# define ZOMBIE_SPEED 3






# define PLAYER_THREE_SQUARE {1, 1, 1, 1, 1, 1, 1, 1, 1}
# define PLAYER_THREE_TRIANGLE {0, 1, 0, 1, 1, 1, 1, 1, 1,}
# define PLAYER_THREE_CIRCLE { 0, 1, 0, 1, 1, 1, 0, 1, 0}


// rotation styles
# define ROT_CORNER_STYLE 0
# define ROT_CENTRE_STYLE 1

# define ROT_DEFAULT_STYLE ROT_CORNER_STYLE


/*
 Game idea:
 
 Block / array of player characters
 
 Together they move as a single character. Player has to control all of the characters
 
 When player takes damage, one of the array elements are deleted.
 These entities act as 'health', hence 0 characters ==> zero health
 
 However, lower health allows the player to move through smaller places and reach locked items
 Hence risk / reward mechanic for having lower health.
 
 However, if you use a sword as a block of characters, then they all attack all once separately.
 */

# endif
