// define 'sprites'

# ifndef SPRITES
# define SPRITES

// box drawing

// three box sizes, s <==> small, m <==> mid, b <==> big
// lt, left top corner, lb, left bottom corner, rt, right top corner, rb, right bottom corner
// lw,  left wall, c, ceiling, f, floor, rw, right wall

# define CS "─"
# define CM "═"
# define CB "▄"
# define FS "─"
# define FM "═"
# define FB "▀"

# define LWS "│"
# define LWM "║"
# define LWB "▐"
# define RWS "│"
# define RWM "║"
# define RWB "▌"

# define LTS "┌"
# define LTM "╔"
# define LTB "▗"
# define LTR "╭"
# define LBS "└"
# define LBM "╚"
# define LBB "▝"
# define LBR "╰"
# define RTS "┐"
# define RTM "╗"
# define RTB "▖"
# define RTR "╮"
# define RBS "┘"
# define RBM "╝"
# define RBB "▘"
# define RBR "╯"

# define LPS "├"
# define LPM "╠"
# define RPS "┤"
# define RPM "╣"

# define TPS "┬"
# define BPS "┴"
# define PS  "┼"



///////////////////////////////////////////////////



# define UNKNOWN "?"


//HUD

# define EMPTY_HEART "♡"
# define FULL_HEART "♥︎"
# define EMPTY_MANA "┉"
# define FULL_MANA "▆"


//environemt

# define PLAYER_UP "W"//"👤"'W'
# define PLAYER_LEFT "A"//"🚶‍"//'A'
# define PLAYER_DOWN "S"//"🕴"//'S'
# define PLAYER_RIGHT "D"//"💃"//'D'


# define FLOOR_S " "              //0
# define WALL_S "█"               //1
# define DARK_S "▓"               //

# define REFLECT_WALL_S "▨"       //2
# define INVISIBLE_WALL_S FLOOR_S  //3
# define OPAQUE_WALL_S WALL_S     //20

# define LIGHT_WATER_S "░"              //22
# define DARK_WATER_S "▒"           //5

# define OPEN_DOOR_S "◯"           //21 &0000
# define LOCKED_DOOR_S "❂"         //21 &1000
# define CLOSED_SWITCH_DOOR_S "☗"  //21 &1100
# define OPEN_SWITCH_DOOR_S "☖"     //21 &0100
# define OPEN_PORTAL_S "◎"         //21 &0001
# define CLOSED_PORTAL_S "◉"       //21 &1001
# define OPEN_BOMB_DOOR_S OPEN_DOOR_S        //21 &0010
# define CLOSED_BOMB_DOOR_S "#"  //"▧" //"█"     //21 &1010
// preference of sprites works by the right 1, e.g. 0101 <==> 0001, open portal

# define CRACKED_WALL_S "#"
# define LADDER_S "H"
# define HOLE_S "🕳"



# define CHEST_CLOSED_S "📬"//"☺︎" //"C"☻☹☺︎
# define CHEST_OPEN_S "📭"//"☻"   //"c"
# define CHEST_LOCKED_S "📫"//"☹"


# define SPIKE_S "∧"



// technical blocks
# define CLOSED_SWITCH_S "x"     //10
# define OPEN_SWITCH_S "o"       //11


# define POP_BLOCK_UP_S "■"
# define POP_BLOCK_DOWN_S "□"

# define YES_LAMP_S "✓"
# define NO_LAMP_S "✗"




// in text files, all doors are given by '2', and have unique number values not indicated above
// need to redo-values for doors.


// enemies

# define SLIME_S "♙"              //s
# define POINTER_S "☞"            //p
# define KNIGHT_S "♘"             //k
# define CHAMPTION_KNIGHT_S "♞"
# define TURRET_S "♖"             //t
# define ORB_S "*"                // o
# define GHOST_S "👻"
# define BABY_SLIME_S "●"
# define SKELETON_S "♗"
# define ZOMBIE_S "🤖"




// items

# define HEART_S "❤︎"         //'H'
# define KEY_S "🔑"//"%"
# define COIN_S "💎"//"$"
# define BOMB_S "💣"//"&"
# define ARROW_S "📌"//"!"
# define MANA_S "💊"//"m"
# define MANA_CONTAINER_S "⚗"
# define HEART_CONTAINER_S "❤️"
# define FREEZE_S "⏲"


// inventory items

# define POINTER_S "☞"
# define SWORD_S "🗡"
# define BOW_S "🏹"
# define POTION_S "🍷"
# define HEALTH_POTION_S "☕️"
# define MANA_POTION_S "🍵"
# define SHIELD_S "🛡"
# define BOMB_BAG_S "🎒"
# define PRESENT_S "🎁"
# define RING_S "💍"
# define CROWN_S "👑"
# define TORCH_S "🔦"
# define HOURGLASS_S "⌛️"
# define STAFF_S "/"
# define MAGIC_STAFF_S "♐︎"
# define BOTTLE_S "🍶"
# define STOPWATCH_S "⏱"
# define ANTI_HOURGLASS_S "⏳"



// special entities

# define PARTICLE_S "✻"
# define SPC_BOMB_S "♣︎"
# define SPC_BOMB_FLASH_S "♧"
# define SPC_BOMB_BLOW_S "✧"
# define SWORD_VERTICAL_S "|"
# define SWORD_HORIZONTAL_S "-"
# define SWORD_DIAG_LEFT_S "\\"
# define SWORD_DIAG_RIGHT_S "/"

# define ARROW_UP_S "▲"
# define ARROW_LEFT_S "◀︎"
# define ARROW_DOWN_S "▼"
# define ARROW_RIGHT_S "►"



// misc


# define TELEPHONE_S "☏"
# define TRAPDOOR_S "❍"

# define FLAG_S "⚐"
# define FLAG_DEAD_S "⚑"

# define PUSH_BLOCK_S "@"//"❒"


// not implemented:

# define LEFT_SHIELD_S "<"
# define RIGHT_SHIELD_S ">"
# define UP_SHIELD_S "^"
# define DOWN_SHIELD_S "v"






// NPCS

# define SIMPLE_NPC_S "🐝"
# define SHOPKEEPER_S "☃"













//////////////////////////////////////////

/// HUD ITEM SPRITES

# define BASIC_SWORD_0  "  ╱ "  //"    "
# define BASIC_SWORD_1  "╲╱  "  //"  ╱ "
# define BASIC_SWORD_2  "╱╲  "  //" ╳  "

# define POINTER_0  " │  "   //" ___"
# define POINTER_1  " ├┴┤"   //"╱  ▕"
# define POINTER_2  "─┴─╯"   //"╲__▕"

# define MAGIC_STAFF_0  "  ● "
# define MAGIC_STAFF_1  " ╱  "
# define MAGIC_STAFF_2  "╱   "

# define STAFF_0  "  ╱ "
# define STAFF_1  " ╱  "
# define STAFF_2  "╱   "

# define BOMB_BAG_0  " _% "
# define BOMB_BAG_1  "/  \\"
# define BOMB_BAG_2  "\\__/"

# define BOW_0  " ╱‾|"
# define BOW_1  "◀──<"
# define BOW_2  " ╲_|"

# define BOTTLE_EMPTY_0  " == "
# define BOTTLE_EMPTY_1  "│‾‾│"
# define BOTTLE_EMPTY_2  "│__│"

# define BOTTLE_FULL_DARK_0  " == "
# define BOTTLE_FULL_DARK_1  "│▓▓│"
# define BOTTLE_FULL_DARK_2  "│▓▓│"

# define BOTTLE_HALF_FULL_DARK_0  " == "
# define BOTTLE_HALF_FULL_DARK_1  "│‾‾│"
# define BOTTLE_HALF_FULL_DARK_2  "│▓▓│"

# define BOTTLE_FULL_MED_0  " == "
# define BOTTLE_FULL_MED_1  "│▒▒│"
# define BOTTLE_FULL_MED_2  "│▒▒│"

# define BOTTLE_HALF_FULL_MED_0  " == "
# define BOTTLE_HALF_FULL_MED_1  "│‾‾│"
# define BOTTLE_HALF_FULL_MED_2  "│▒▒│"

# define BOTTLE_FULL_LIGHT_0  " == "
# define BOTTLE_FULL_LIGHT_1  "│░░│"
# define BOTTLE_FULL_LIGHT_2  "│░░│"

# define BOTTLE_HALF_FULL_LIGHT_0  " == "
# define BOTTLE_HALF_FULL_LIGHT_1  "│‾‾│"
# define BOTTLE_HALF_FULL_LIGHT_2  "│░░│"

# define BASIC_SHIELD_0  "╱‾‾╲"
# define BASIC_SHIELD_1  "╲++╱"
# define BASIC_SHIELD_2  " ╲╱ "

# define HOURGLASS_0  "╲‾╱ "
# define HOURGLASS_1  " ╳  "
# define HOURGLASS_2  "╱▲╲ "


# define ANTI_HOURGLASS_0  "╲▼╱ "
# define ANTI_HOURGLASS_1  " ╳  "
# define ANTI_HOURGLASS_2  "╱_╲ "


# define STOPWATCH_0  " __ "
# define STOPWATCH_1  "╱ /╲"
# define STOPWATCH_2  "╲__╱"



# define NONE_0  "    "
# define NONE_1  "NONE"
# define NONE_2  "    "


//                      |++++++|        ╲ ╱
# define RIGHT_ARROW_0  "  ╲   "// +
# define RIGHT_ARROW_1  "   ╲  "// +
# define RIGHT_ARROW_2  "   ╱  "// +
# define RIGHT_ARROW_3  "  ╱   "// +
# define RIGHT_ARROW_4  "      "// +

# define LEFT_ARROW_0   "   ╱  "
# define LEFT_ARROW_1   "  ╱   "
# define LEFT_ARROW_2   "  ╲   "
# define LEFT_ARROW_3   "   ╲  "
# define LEFT_ARROW_4   "      "



# define PRESENT_0  "_%%_"
# define PRESENT_1  "│  │"
# define PRESENT_2  "‾‾‾‾"


/* items to include:
 
    - Head lamp --> extends vision / light dist.
 */


# endif
