# ifndef PLAYER_COMMANDS__
# define PLAYER_COMMANDS__

# define WAIT_C 0
# define MOVE_UP_C 'w'
# define MOVE_LEFT_C 'a'
# define MOVE_DOWN_C 's'
# define MOVE_RIGHT_C 'd'

# define INTERACT_C 'e'
# define QUICK_ITEM_C 'q'
# define MENU_C 'm'
# define REST_C 'r'
# define TOGGLE_C 't'

# define ACTIVE_SWITCH_C 'j'
# define CONSUMABLE_SWITCH_C 'k'
# define PASSIVE_SWITCH_C 'l'

# define SPECIAL_LOWER 10
# define EXIT_C 10
# define SAVE_C 11
# define LOAD_C 12
# define WIN_GAME_C 13

# define SPECIAL_UPPER 20




// special commands  --  p for phrase
# define HELP_P "help"
# define SAVE_P "save"
# define EXIT_P "exit"
# define LOAD_P "load"






// debug commands

# define DEBUG_P "DEBUG"
# define CLEAR_P "clear"
# define TIME_P "time"
# define MOVE_P "move"
# define ERROR_P "error"
# define SET_TIME_P "set_time"
# define CLIP_P "no_clip"
# define ROOM_P "room"
# define DOOR_P "door"
# define SWORD_P "sword"
# define POS_P "pos"
# define DOOR_POS_P "door_pos"
# define ROOM_DARK_P "set_room_dark"
# define ROOM_NUM_P "room_num"
# define PLAYER_VIS "player_vis"
# define GIVE_ITEM "give_item"


/*
 Here is a list of all the current commands:
 
 "\n" --> wait --> do nothing the current turn
 
 "w/W" --> move up
 "a/A" --> move left
 "s/S" --> move down
 "d/D" --> move right
 
 
 
 
 
 
 */



# endif
