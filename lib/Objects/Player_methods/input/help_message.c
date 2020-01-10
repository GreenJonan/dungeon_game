# ifndef HELP_MESSAGE_
# define HELP_MESSAGE_

int is_valid_move(char c) {
    int output = 0;
    

    if (c == MOVE_UP_C) {
        output = 1;
    }
    else if (c == MOVE_LEFT_C) {
        output = 1;
    }
    else if (c == MOVE_DOWN_C) {
        output = 1;
    }
    else if (c == MOVE_RIGHT_C) {
        output = 1;
    }
    else if (c == MENU_C) {
        output = 1;
    }
    else if (c == INTERACT_C) {
        output = 1;
    }
    else if (c == QUICK_ITEM_C) {
        output = 1;
    }
    else if (c == REST_C) {
        output = 1;
    }
    else if (c == TOGGLE_C) {
        output = 1;
    }
    
    else if (c == ACTIVE_SWITCH_C) {
        output = 1;
    }
    else if (c == CONSUMABLE_SWITCH_C) {
        output = 1;
    }
    else if (c == PASSIVE_SWITCH_C) {
        output = 1;
    }
    
    /*else if (c == WAIT_C) {
        output = 1;
    }*/
    /*else if (c == 'p') {
        output = 1;
    }*/
    
    
    return output;
}










void print_help_message(int command_debug) {

    printf(
           "\n"
           "\n"
           "Game commands:\n"
                  
           "\n"
           "Movement:\n"
           "\tw  -  face/move upwards      ^^^\n"
           "\ta  -  face/move to the left  <--\n"
           "\ts  -  face/ move downwards   vvv\n"
           "\td  -  face/move to the right -->\n"
                  
           "\n"
           "e  -  interact with object currently facing / use active item\n"
           "q  -  use consumable item\n"
           "p  -  pause/unpause game\n"
                  
           "\n"
           "j  -  quick switch between current and previously held ACTIVE item\n"
           "k  -  quick switch between current and previously held CONSUMABLE item\n"
           "l  -  quick switch between current and previously held PASSIVE item\n"
           "\n"
           "Menu\n"
           "\tm  -  open player menu\n"
                  
           "\n"
           "\n");
           
           /*
           "Special commands:\n"
           "\t-help  --  bring up this help menu.\n"
           "\t-save  --  saves current state of the game. (NOT IMPLEMENTED)\n"
           "\t-load  --  load a game file. (NOT IMPLEMENTED)\n"
           "\t-exit  --  force quit, and exit without saving.\n"
           "\n"
           "\n"
           */

    if (command_debug) {
        print_debug_commands();
    }


}






void print_debug_commands() {

    printf("Debug Commands:\n"
           "\n"
           "Simple Commands:\n"
           "/DEBUG     --  set debug commands on/off.\n"
           "/clear     --  clear the screen.\n"
           "/time      --  return the current time.\n"
           
           "\n"
           "\n"
           
           "Teleport:\n"
           "\t/move <x> <y>      --  move to point (x,y) in current room.\n"
           "\t/room <m>          --  move to room number m, default is centre of room.\n"
           "\t/door <m> <n>      --  move to the n-th door of room m.\n"
           "\t/door_pos <m> <n>  --  return position of door n in room m.\n"
           
           "\n"
           
           "Status:\n"
           "\t/health      --  display current health.\n"
           "\t/max_health  --  display max health.\n"
           "\t/room_num    --  display current room_number.\n"
           "\t/clip_stat   --  display if clip is on/off.\n"
           
           "\n"
           
           "Player:\n"
           "\t/pos                 --  return current player position.\n"
           "\t/no_clip             --  toggle on/off wall clip.\n"
           "\t/sword               --  toggle on/off sword sprite.\n"
           "\t/set_health <n>      --  set health to be n.\n"
           "\t/set_max_health <n>  --  set max health to be n.\n"
           "\t/die                 --  set health to be 0.\n"
           "\t/player_vis <n>      --  set the player vision to n.\n"
           "\t/give_item <id> <n>  --  give player item with item_id 'id', 'n' times.\n"
           
           "\n"
           
           "Room:\n"
           "/room_num           --  return current room num.\n"
           "/set_room_dark <n>  --  toggle on/off is_dark for room n.\n"
           
           "\n"
           
           "Utility Commands:\n"
           "/set_time <n>  -- set the game time to n.\n"
           "\n"
           "\n"
           );
}



# endif
