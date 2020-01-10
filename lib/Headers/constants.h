# ifndef CONSTANTS__
# define CONSTANTS__



// Constants

# define GAME_NAME "Dungeon Game:"
# define GAME_NAME_LEN 13


# define BUFF 512
# define DIALOGUE_BUFF 1024
# define MOVE_BUFF 1024



# define MAX_CLIP_T 19 // what the largest tile value that clips with entities
# define MAX_VIS_BLOCK_T 15
# define MAX_TIME -1 // if >= 0, then how many rounds before the game quits.

# define UP_DIR 0
# define LEFT_DIR 1
# define DOWN_DIR 2
# define RIGHT_DIR 3
# define NO_DIR 4

# define LIGHT_DIST 2
# define MAX_OPTIONS 6


# define MIN_MASS -1
# define MIN_EYE -5
# define MIN_AI 0

# define BOW_DIST 10
# define MAX_QUIVER 999
# define MAX_PURSE 999
# define MAX_BOMB_BAG 999

# define BOMB_SMOKE_LINGER 3

# define SWORD_DMG 0
# define BLAST_DMG 1
# define MAGIC_DMG 2
# define ARROW_DMG 3


# define PLAYER_DMG_ID 0

# define HOLE_DAMAGE 1


# define PARAGRAPH_SEPARATOR ';'
# define LAYOUT_FILE_ID 0
# define ITEM_FILE_ID 1
# define ENEMY_FILE_ID 2
# define NPC_FILE_ID 3



# define HEALTH_POTION_HEAL 4
# define MANA_POTION_HEAL 4


// debug
# define DEBUG 0
# define LOADING_PROGRESS 0
# define ROOM_DEBUG 0
# define COMMAND_DEBUG 1
# define SUPPRESS_WARNINGS 0
# define DRAW_SCREEN 1
# define HIT_BOX_ERROR 0
# define VISION_DEBUG 0



# define SRC_DIR "src/"
# define ROOM_MAP "room_map.txt"
# define ROOM_MAP_SLASH "/room_map.txt"
# define PLAYER_FILE "player.txt"
# define DEFAULT_SRC_DIR "src/default/"

# define LAYOUT_FILE "layout.txt"
# define ENEMY_FILE "enemy.txt"
# define ITEM_FILE "item.txt"
# define NPC_FILE "npcs.txt"


# define SIZE "SIZE"
# define EXIT "EXIT"
//# define DARK "DARK"
//# define LOCKED "LOCKED"
# define STATUS "STATUS"
# define CHEST "CHEST"
# define SPECIAL "SPECIAL"

# define NONE_MSG "NONE"
# define DEFAULT_MSG "DEFAULT"


# define ITEMS "ITEMS"
# define MOVES "MOVES"

// player status macros:
# define MAX_HEALTH "MAX_HEALTH"
# define HEALTH "HEALTH"
# define MANA "MANA"
# define MAX_MANA "MAX_MANA"
# define ROOM_NUM "ROOM"
# define POSITION "POSITION"
# define CLOCK "CLOCK"
# define TIMER "TIMER"
# define MASS "MASS"
# define VELOCITY "VELOCITY"
# define FLY "FLY"
# define PLAYER_STATUS "STATUS"
# define DIRECTION "DIRECTION"
# define LIGHT_DISTANCE "LIGHT_DIST"






# define REVIVE_P "revive"


// File Conversion constants



# define FLOOR_N 0
# define FLOOR_T '`'

# define WALL_N 1
# define WALL_T '0'

# define REFLECT_WALL_N 2
# define REFLECT_WALL_T '1'

# define INVISIBLE_WALL_N 3
# define INVISIBLE_WALL_T '2'

# define OPAQUE_WALL_N 20
# define OPAQUE_WALL_T '!'

# define DARK_WATER_N 5
# define DARK_WATER_T '4'

# define CRACKED_WALL_T '%'
# define CRACKED_WALL_N 6

# define OPEN_SWITCH_N '+'
# define CLOSED_SWITCH_N '-'
# define SWITCH_T '+'

# define LIGHT_WATER_N 21
# define LIGHT_WATER_T ':'

# define DOOR_N 22
# define DOOR_T '&'
// special door numbers for printing array
# define OPEN_DOOR_N 23
# define LOCKED_DOOR_N 24
# define OPEN_SWITCH_DOOR_N 25
# define CLOSED_SWITCH_DOOR_N 26
# define OPEN_PORTAL_N 27
# define CLOSED_PORTAL_N 28
# define OPEN_BOMB_DOOR_N 29
# define CLOSED_BOMB_DOOR_N 30


# define SPIKE_N 31
# define SPIKE_T '^'

# define FLAG_N 32
# define FLAG_DEAD_N '\''
# define FLAG_T 'F'

# define DARK_N 'd'
# define HOLE_N '='
# define HOLE_T 'h'

# define POP_BLOCK_DOWN_N '!'
# define POP_BLOCK_UP_N 16
# define POP_BLOCK_T 'U' //! is already taken!!!

# define LADDER_T 'L'
# define LADDER_N '"' // ie 33


# define CHEST_N 12
# define CHEST_OPEN_N 13
# define CHEST_CLOSED_N 14
# define CHEST_LOCKED_N 15
# define CHEST_T 'C'


# define TELEPHONE_T 'T'
# define TELEPHONE_N 17

# define PUSH_BLOCK_T 'P'
# define PUSH_BLOCK_N '#'

# define LAMP_ON_N '('
# define LAMP_OFF_N ')'
# define LAMP_T '?'


// NPC Tiles
# define SHOPKEEPER_N ';'
# define SIMPLE_NPC_N ':'





// entity tile conversions

# define PLAYER_N 'P'
# define HEART_N 1000//'H'
# define KEY_N 1001//'K'
# define BOMB_N 1002//'B'
# define COIN_N 1003//'C'
# define ARROW_N 1004//'A'
# define MANA_N 1005//'M'
# define HEART_CONTAINER_N 1006
# define MANA_CONTAINER_N 1007
# define FREEZE_N 1008

//# define TRAPDOOR_N ')'

# define ORB_N 2000//'*'
# define SLIME_N 2001//'s'
# define KNIGHT_N 2002//'k'
# define TURRET_N 2003//'t'
# define GHOST_N 2004//'g'
# define BABY_SLIME_N 2005
# define SKELETON_N 2006
# define CHAMPTION_KNIGHT_N 2007
# define ZOMBIE_N 2008




# define SWORD_VERTICAL_N '0'
# define SWORD_DIAG_LEFT_N '1'
# define SWORD_HORIZONTAL_N '2'
# define SWORD_DIAG_RIGHT_N '3'

# define PARTICLE_N '4'
# define SPC_BOMB_N '5'
# define SPC_BOMB_FLASH_N '6'
# define SPC_BOMB_BLOW_N '7'

# define SPC_ARROW_UP_N 200
# define SPC_ARROW_LEFT_N 201
# define SPC_ARROW_DOWN_N 202
# define SPC_ARROW_RIGHT_N 203



# define INV_POINTER_N 'Z'
# define INV_SWORD_N 'S'
# define INV_BOW_N 'Q'
# define INV_SHIELD_N 'W'
# define INV_BOMB_N 'E'
# define INV_PRESENT_N 'T'
# define INV_RING_N 'R'
# define INV_CROWN_N 'Y'
# define INV_TORCH_N 'U'
# define INV_HOURGLASS_N 'I'
# define INV_ANTI_HOURGLASS_N 3000
# define INV_STOPWATCH_N 3001
# define INV_STAFF_N 'O'
# define INV_MAGIC_STAFF_N 'D'



# define INV_DARK_BOT_FULL_N '['
# define INV_DARK_BOT_HFULL_N ']'
# define INV_MED_BOT_FULL_N '{'
# define INV_MED_BOT_HFULL_N '}'
# define INV_LIGHT_BOT_FULL_N ','
# define INV_LIGHT_BOT_HFULL_N '_'
# define INV_EMP_BOT_N '/'




// item Names

# define EMPTY "EMPTY"

# define NONE "NONE"
# define HEART "HEART"
# define COIN "COIN"
# define KEY "KEY"
# define BOMB "BOMB"
# define ARROW "ARROW"
# define MANA "MANA"
# define HEALTH_CONTAINER "HEALTH_CONTAINER"
# define MANA_CONTAINER "MANA_CONTAINER"
# define FREEZE "FREEZE"



# define POINTER "POINTER"
# define BASIC_SWORD "BASIC_SWORD"
# define STAFF "STAFF"
# define MAGIC_STAFF "MAGIC_STAFF"
# define BOW "BOW"



# define BOTTLE_EMPTY "EMPTY_BOTTLE"
# define BOTTLE_FULL_DARK "FULL_POTION"
# define BOTTLE_HALF_FULL_DARK "HALF-FULL_POTION"
# define BOTTLE_FULL_MED "FULL_HEALTH_POTION"
# define BOTTLE_HALF_FULL_MED "HALF-FULL_HEALTH_POTION"
# define BOTTLE_FULL_LIGHT "FULL_MANA_POTION"
# define BOTTLE_HALF_FULL_LIGHT "HALF-FULL_MANA_POTION"

# define BOMB_BAG "BOMB_BAG"
# define PRESENT "PRESENT"
# define STOPWATCH "STOPWATCH"



# define BASIC_SHIELD "BASIC_SHIELD"
# define HOURGLASS "HOURGLASS"
# define ANTI_HOURGLASS "ANTI_HOURGLASS"



// item ids

# define LEFT_ARROW_ID -2
# define RIGHT_ARROW_ID -3
# define EMPTY_ID -1


# define NONE_ID 0
# define HEART_ID 1
# define COIN_ID 2
# define KEY_ID 3
# define BOMB_ID 4
# define ARROW_ID 5
# define MANA_ID 6
# define HEALTH_CONTAINER_ID 7
# define MANA_CONTAINER_ID 8
# define FREEZE_ID 9




# define POINTER_ID 100
# define BASIC_SWORD_ID 101
# define STAFF_ID 102
# define MAGIC_STAFF_ID 103
# define BOW_ID 104



# define BOTTLE_EMPTY_ID 201
# define BOTTLE_FULL_DARK_ID 202
# define BOTTLE_HALF_FULL_DARK_ID 203
# define BOTTLE_FULL_MED_ID 204
# define BOTTLE_HALF_FULL_MED_ID 205
# define BOTTLE_FULL_LIGHT_ID 206
# define BOTTLE_HALF_FULL_LIGHT_ID 207

# define BOMB_BAG_ID 200
# define PRESENT_ID 208
# define STOPWATCH_ID 209



# define BASIC_SHIELD_ID 300
# define HOURGLASS_ID 301
# define ANTI_HOURGLASS_ID 302




# define HOURGLASS_TURN_NUM 2
# define ANTI_HOURGLASS_TURN_NUM 2
# define HOURGLASS_DRAIN 1
# define ANTI_HOURGLASS_GAIN 1






// enemy names
# define ORB "ORB"
# define SLIME "SLIME"
# define KNIGHT "KNIGHT"
# define GHOST "GHOST"
# define BABY_SLIME "BABY_SLIME"
# define SKELETON "SKELETON"
# define ZOMBIE "ZOMBIE"



// enemy ids
# define ORB_ID 1
# define SLIME_ID 2
# define KNIGHT_ID 3
# define GHOST_ID 4
# define BABY_SLIME_ID 5
# define SKELETON_ID 6
# define ZOMBIE_ID 7




// special entity ids
# define SPC_SMOKE_ID 0
# define SPC_SWORD_ID 1
# define SPC_STICK_ID 2
# define SPC_BOMB_ID 3
# define SPC_ARROW_ID 4



# define SPC_FLAG_ID 5
# define SPC_TELEPHONE_ID 6
# define SPC_PUSH_BLOCK_ID 7
# define SPC_POP_BLOCK_ID 8
# define SPC_SWITCH_ID 9
# define SPC_LAMP_ID 10

// should there be a shield_id that will block other entities from passing through and blast damage?






//////////////////////////

// enemy ai, light distance (vision distance) and eyesight values

# define ORB_LIGHT_DIST 0
# define SLIME_LIGHT_DIST 0
# define KNIGHT_LIGHT_DIST 5
# define GHOST_LIGHT_DIST 10
# define BABY_SLIME_LIGHT_DIST 4
# define SKELETON_LIGHT_DIST 1
# define ZOMBIE_LIGHT_DIST 4




# define NO_EYESIGHT 0
# define FULL_EYESIGHT -1
# define FRONT_HALF_EYESIGHT -2
# define BACK_HALF_EYESIGHT -3

# define FRONT_CONE_VIS 1
# define LEFT_CONE_VIS 2
# define BACK_CONE_VIS 4
# define RIGHT_CONE_VIS 8



# define ORB_EYESIGHT NO_EYESIGHT
# define SLIME_EYESIGHT NO_EYESIGHT
# define KNIGHT_EYESIGHT FRONT_CONE_VIS + LEFT_CONE_VIS + RIGHT_CONE_VIS
# define GHOST_EYESIGHT FULL_EYESIGHT
# define BABY_SLIME_EYESIGHT FULL_EYESIGHT
# define SKELETON_EYESIGHT FULL_EYESIGHT
# define ZOMBIE_EYESIGHT FULL_EYESIGHT










////////////////////////////

// special blocks / technical blocks


/*
 IDEAS:
 
 Pot - pickup and throw to break / deal damage.
 
 Block - pushable a certain number of times and will reset positon when exit room.
 
 Pressure plate - when entities of a certain mass step on it, it triggers
 
 Activable switch on/off, either interact or only weapon interact, e.g. use arrow
 
  --- as an aside, introduce blocks that are unable to be passed through, yet special entities can.
 
 Lamps - to signal on / off states.
 
  --- some way to do not gates.
 
 Pop up / down blocks - if stepping on a pop up block then can walk over adjacent pop-up blocks.
 
 
 Ice blocks - blocks that will slide until they colide with another block or wall when pushed.
 */


# define TELEPHONE "TELEPHONE"
# define NO_RING_ID 0
# define SIMPLE_RING_ID 1
# define LOCAL_SIMPLE_RING_ID 2

# define SIMPLE_RING_MSG "Ring... Ring... Ring...\n\n"
# define MYSTERY_VOICE "???"


# define PUSH_BLOCK "PUSH_BLOCK"

# define POP_BLOCK "POP_BLOCK"

# define SWITCH "SWITCH"
# define SIMPLE_SWITCH_TYPE 0
# define AND_TYPE 1
# define OR_TYPE 2
# define XOR_TYPE 3
# define NOR_TYPE 4
# define NAND_TYPE 5
# define XNOR_TYPE 6
# define EQUALITY_TYPE 7
# define ANTI_XOR_TYPE 8
# define ANTI_XNOR_TYPE 9


# define LAMP "LAMP"







# define BASIC_ARROW_TYPE 0
# define BOMB_ARROW_TYPE 1


# define ARROW_DMG_NUM 1
# define SIMPLE_BOMB_DAMAGE 3















////// NPC IDS

# define SIMPLE_NPC "SIMPLE_NPC"
# define SHOPKEEPER_NPC "SHOPKEEPER"

# define SHOPKEEPER_DEFAULT "DEFAULT" //"SHOPKEEPER_DEFAULT"




# define SIMPLE_NPC_ID 0
# define SHOPKEEPER_ID 1

# define SHOPKEEPER_AUTHOR "Shopkeer"


# define SHOPKEEPER_MSG "Welcome to the Store!\nIteract with items to buy them."




//////////////////////////////////////////

/*
 POSSIBLE CONVERSION KEYS:
 
 0
 1
 2
 3
 4
 5
 6
 7
 8
 9
 10
 11
 12
 13
 14
 15
 16
 17
 18
 19
 20
 21
 22
 23
 24
 25
 26
 27
 28
 29
 30
 31
 32 (SPACE)
 !
 "
 #
 $
 %
 &
 '
 (
 )
 *
 +
 ,
 -
 .
 /
 '0'
 '1'
 '2'
 '3'
 '4'
 '5'
 '6'
 '7'
 '8'
 '9'
 :
 ;
 <
 =
 >
 ?
 @
 A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
 [
 ]
 \
 ]
 ^
 _
 @
 a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z
 {
 |
 }
 ~
 
 */
# endif
