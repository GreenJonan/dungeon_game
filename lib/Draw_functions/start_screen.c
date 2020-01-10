# ifndef STARTING_SCREEN__
# define STARTING_SCREEN__

# include "box_draw.c"


# define START_MSG "START GAME"
# define START_MSG_LEN 10
# define NEW_GAME_MSG "DEFAULT GAME" //"NEW GAME"
# define NEW_GAME_MSG_LEN 12 //8
# define OPTIONS_MSG "OPTIONS"
# define OPTIONS_MSG_LEN 7
# define EXIT_GAME_MSG "QUIT GAME"
# define EXIT_GAME_MSG_LEN 9
# define LOAD_GAME_MSG "LOAD GAME"
# define LOAD_GAME_MSG_LEN 9

# define BOT_W 20 // botton width
# define BOT_H 5  // botton height;
# define SM_W 42  // start menu width;
# define OP_W 30










void draw_start_screen(int cursor) {

    clear_screen();
    
    char* strings[] = {GAME_NAME, START_MSG, OPTIONS_MSG, EXIT_GAME_MSG};
    int lengths[] = {GAME_NAME_LEN, START_MSG_LEN, OPTIONS_MSG_LEN, EXIT_GAME_MSG_LEN};
    int len = 4;
    
    draw_menu_box(strings, lengths, len, cursor, 2, BOT_W, SM_W);
}






void draw_game_select_screen(struct game_t* g, int cursor) {

    clear_screen();
    
    
    
    char* strings[] = {
        "Game Select:",
        NEW_GAME_MSG,
        LOAD_GAME_MSG,
        "BACK"
    };
    
    int lengths[] = {12, NEW_GAME_MSG_LEN, LOAD_GAME_MSG_LEN, 4};
    int len = 4;
    
    draw_menu_box(strings, lengths, len, cursor, 2, BOT_W, SM_W);
}







/////////////////////////////////////////////////////////////////////


void draw_options_screen(Game* game, int botton) {
    clear_screen();
    
    
    if (game == NULL) {
        game_null_error("draw_options_screen");
        return;
    }
    if (botton <= 0 || botton > MAX_OPTIONS) {
        printf("ERROR: botton in 'draw_options_screen' is too large: %d\n", botton);
        pause_function();
        return;
    }
    
    int op_ind = 3; //option indent
    
    print_options_header(1, OP_W, 2);
    
    
    int exit_box = 1;
    char boxes[MAX_OPTIONS - 1] = {'-', '-', '-', '-', '-'};
    
    if (botton == MAX_OPTIONS) {
        exit_box = 2;
    }
    else {
        boxes[botton - 1] = '*';
    }
    
    
    // options table
    
    
    // difficulty
    print_box_empty(1, OP_W, 2, 1);
    print_box_left(1, 2);
    for (int i = 0; i < op_ind; i++) {
        putchar(' ');
    }
    putchar(boxes[0]); putchar(' ');
    printf("Difficulty:");  //length = 11
    int diff = game->options.difficulty;
    if (diff == 0) {
        printf(" < NOMRAL >");
    }
    else if (diff < 0) {
        printf("   EASY >  ");
    }
    else {
        printf(" < HARD    ");
    
    }
    print_box_right(1, 1, 1);


    
    // cmd debug:
    print_box_empty(1, OP_W, 2, 1);
    print_box_left(1, 2);
    for (int i = 0; i < op_ind; i++) {
        putchar(' ');
    }
    putchar(boxes[1]); putchar(' ');
    printf("Cheats:"); // length = 7
    if (!game->options.command_debug){
        printf("         OFF >  ");
    }
    else {
        printf("          < ON  ");
    }
    print_box_right(1, 0, 1);
    
    
    
    
    // random / spare option value
    print_box_empty(1, OP_W, 2, 1);
    print_box_left(1, 2);
    for (int i = 0; i < op_ind; i++) {putchar(' ');}
    putchar(boxes[2]); putchar(' ');
    printf("Random 1:"); //length 9 ==> remaining space = 13
    printf(" %10d", game->options.rnd1);
    print_box_right(1, 3, 1);
    
    
    
    
    // random / spares
    print_box_empty(1, OP_W, 2, 1);
    print_box_left(1, 2);
    for (int i = 0; i < op_ind; i++) {putchar(' ');}
    putchar(boxes[3]); putchar(' ');
    printf("Random 2:"); //length 9 ==> remaining space = 13
    printf(" %10d", game->options.rnd2);
    print_box_right(1, 3, 1);
    
    
    
    
    // random / spares
    print_box_empty(1, OP_W, 2, 1);
    print_box_left(1, 2);
    for (int i = 0; i < op_ind; i++) {putchar(' ');}
    putchar(boxes[4]); putchar(' ');
    printf("Random 3:"); //length 9 ==> remaining space = 13
    printf(" %10d", game->options.rnd3);
    print_box_right(1, 3, 1);
    
    
    
    
    
    // exit botton
    print_box_empty(1, OP_W, 2, 1);
    print_box_left(1, 2); print_box_top(exit_box, 10, op_ind, 0); print_box_right(1, 15, 1);
    print_box_left(1, 2); print_box_internal(exit_box, 10, op_ind, "EXIT", 4, 0); print_box_right(1, 15, 1);
    print_box_left(1, 2); print_box_bot(exit_box, 10, op_ind, 0); print_box_right(1, 15, 1);
    
    
    
    // print bottom
    print_box_empty(1, OP_W, 2, 1);
    print_box_bot(1, OP_W, 2, 1);
}






int print_options_header(int style, int width, int indent) {
    return print_box_header(style, width, indent, "OPTIONS", 7);
}












///////////////////////////////////////////////////////////////

// format the button string, and internal strings, assume line by line.
// REMEMBER TO DEALLOC AFTER CALLING THE FUNCTION

//char*











/*
 void draw_start_screen(int botton) {
 clear_screen();
 
 
 if (botton > 3 || botton < 1) {
 printf("ERROR: botton value out of range: %d\n", botton);
 pause_function();
 return;
 }
 
 int bot[] = {1,1,1};
 bot[botton - 1] = 2;
 
 
 int bot_spc = (SM_W - BOT_W - 2) / 2; // botton space
 
 if (bot_spc % 2 != 0) {
 printf("ERROR: menu width should be even\n");
 pause_function();
 return;
 }
 
 // vertical distance / spacing between boxes
 int box_space = 1;
 
 
 
 
 // there are three bottons, start game, options, quit game
 putchar('\n'); putchar('\n');
 
 //print_box_top(1, SM_W, 2, 1);
 print_box_header(1, SM_W, 2, "DUNGEON GAME:", 13);
 
 // spacing between boxes;
 for (int i = 0; i < box_space; i++) {
 print_box_empty(1, SM_W, 2, 1);
 }
 
 
 
 
 
 // start game box
 print_box_left(1, 2); print_box_top(bot[0], BOT_W, bot_spc, 0); print_box_right(1, bot_spc, 1);
 print_box_left(1, 2); print_box_empty(bot[0], BOT_W, bot_spc, 0); print_box_right(1, bot_spc, 1);
 // msg
 print_box_left(1, 2);
 print_box_internal(bot[0], BOT_W, bot_spc, START_MSG, START_MSG_LEN, 0);
 print_box_right(1, bot_spc, 1);
 // botton of box
 print_box_left(1, 2); print_box_empty(bot[0], BOT_W, bot_spc, 0); print_box_right(1, bot_spc, 1);
 print_box_left(1, 2); print_box_bot(bot[0], BOT_W, bot_spc, 0); print_box_right(1, bot_spc, 1);
 
 
 
 
 
 // spacing between boxes;
 for (int i = 0; i < box_space; i++) {
 print_box_empty(1, SM_W, 2, 1);
 }
 
 
 
 
 // options box
 print_box_left(1, 2); print_box_top(bot[1], BOT_W, bot_spc, 0); print_box_right(1, bot_spc, 1);
 print_box_left(1, 2); print_box_empty(bot[1], BOT_W, bot_spc, 0); print_box_right(1, bot_spc, 1);
 // msg
 print_box_left(1, 2);
 print_box_internal(bot[1], BOT_W, bot_spc, OPTIONS_MSG, OPTIONS_MSG_LEN, 0);
 print_box_right(1, bot_spc, 1);
 // botton of box
 print_box_left(1, 2); print_box_empty(bot[1], BOT_W, bot_spc, 0); print_box_right(1, bot_spc, 1);
 print_box_left(1, 2); print_box_bot(bot[1], BOT_W, bot_spc, 0); print_box_right(1, bot_spc, 1);
 
 
 
 
 
 // spacing between boxes;
 for (int i = 0; i < box_space; i++) {
 print_box_empty(1, SM_W, 2, 1);
 }
 
 
 
 
 // quit game box
 print_box_left(1, 2); print_box_top(bot[2], BOT_W, bot_spc, 0); print_box_right(1, bot_spc, 1);
 print_box_left(1, 2); print_box_empty(bot[2], BOT_W, bot_spc, 0); print_box_right(1, bot_spc, 1);
 // msg
 print_box_left(1, 2);
 print_box_internal(bot[2], BOT_W, bot_spc, EXIT_GAME_MSG, EXIT_GAME_MSG_LEN, 0);
 print_box_right(1, bot_spc, 1);
 // botton of box
 print_box_left(1, 2); print_box_empty(bot[2], BOT_W, bot_spc, 0); print_box_right(1, bot_spc, 1);
 print_box_left(1, 2); print_box_bot(bot[2], BOT_W, bot_spc, 0); print_box_right(1, bot_spc, 1);
 
 
 
 
 
 
 // spacing between boxes;
 for (int i = 0; i < box_space; i++) {
 print_box_empty(1, SM_W, 2, 1);
 }
 print_box_bot(1, SM_W, 2, 1);
 putchar('\n'); putchar('\n');
 }
 
 */


# endif
