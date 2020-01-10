# ifndef BOX_DRAWERS__
# define BOX_DRAWERS__

// string acronymns are defined in master header.




// helper functions

void print_box_top(int style, int width, int indent, int end) {
    print_box_topbot(style, width, 1, indent, end);
}
void print_box_bot(int style, int width, int indent, int end) {
    print_box_topbot(style, width, 0, indent, end);
}




void print_box_topbot(int style, int width, int top, int indent, int end) {
    
    // 3 styles, 1 <==>  small, 2 <==> double, 3 <==> thick
    char* left;
    char* right;
    char* line;
    
    for (int i = 0; i < indent; i++) {
        putchar(' ');
    }
    
    if (style == 4) {
    
    
    }
    
    if (style == 3) {
        line = CB;
        if (top) {
            left = LTB;
            right = RTB;
        }
        else {
            left = LBB;
            right = RBB;
        }
    }
    else if (style == 2) {
        line = CM;
        if (top) {
            left = LTM;
            right = RTM;
        }
        else {
            left = LBM;
            right = RBM;
        }
    }
    else {
        line = CS;
        if (top) {
            left = LTS;
            right = RTS;
        }
        else {
            left = LBS;
            right = RBS;
        }
    }
    
    printf("%s", left);
    for (int i = 0; i < width - 2; i++) {
        printf("%s", line);
    }
    printf("%s", right);
    
    if (end) {
        putchar('\n');
    }
}


/////////////////////////////////////////////////////


int print_box_empty(int style, int width, int indent, int end) {
    return print_box_internal(style, width, indent, NULL, 0, end);
}









int print_box_internal(int style, int width, int indent, char* str, int len, int end) {
    
    char* left;
    char* right;
    
    int print_str = 1;
    if (len == 0 || str == NULL) {
        print_str = 0;
    }
    
    // find amount of white space on each side of the string,
    int space = width - 2 - len;
    
    if (space < 0) {
        printf("ERROR: internal string too long for 'print_box_internal', white space length: %d\n", space);
        pause_function();
        return 1;
    }
    
    
    
    
    if (style == 3) {
        left = LWB;
        right = RWB;
    }
    else if (style == 2) {
        left = LWM;
        right = RWM;
    }
    else {
        left = LWS;
        right = RWS;
    }
    
    
    // indent;
    for (int i = 0; i < indent; i++) {
        putchar(' ');
    }
    
    
    // divide the white space into two,
    int odd = ( (space % 2) == 1);
    space = space / 2;
    
    printf("%s", left);
    
    for (int i = 0; i < space; i++) {
        putchar(' ');
    }
    
    
    // print internal string
    if (print_str) {
        printf("%s", str);
    }
    
    
    int j = 0;
    if (odd) {
        j = 1;
    }
    
    for (int i = 0; i < space + j; i++) {
        putchar(' ');
    }
    
    printf("%s", right);
    
    if (end) {
        putchar('\n');
    }
    return 0;
}










///////////////////////////////////////////////////////////////

void print_box_left(int style, int indent) {
    print_box_side(style, indent, 1, 0);
}
void print_box_right(int style, int indent, int end) {
    print_box_side(style, indent, 0, end);
}



void print_box_side(int style, int indent, int left, int end) {
    
    char* side;
    
    if (left) {
        if (style == 3) {
            side = LWB;
        }
        else if (style == 2) {
            side = LWM;
        }
        else {
            side = LWS;
        }
    }
    
    else {
        if (style == 3) {
            side = RWB;
        }
        else if (style == 2) {
            side = RWM;
        }
        else {
            side = RWS;
        }
    }
    
    
    for (int i = 0; i < indent; i++) {
        putchar(' ');
    }
    
    
    printf("%s", side);
    
    
    if (end) {
        putchar('\n');
    }
}

















int print_box_header(int style, int width, int indent, char* str, int len) {

    if (style < 1 || style > 2) {
        printf("ERROR: invalid style number.\n");
        pause_function();
        return 1;
    }
    int ind = 2; // how far str should be from the left wall.
    int blk_spc = width - len - 2 - ind;
    
    if (blk_spc < 0) {
        printf("ERROR: internal string too long for 'print_box_internal', white space length: %d\n", blk_spc);
        pause_function();
        return 1;
    }
    if (str == NULL) {
        str = "\0";
        len = 0;
    }
    ///////////////////////////////////

    
    print_box_top(style, width, indent, 1);
    print_box_empty(style, width, indent, 1);
    
    print_box_left(style, indent);
    
    for (int i = 0; i < ind; i++) {
        putchar(' ');
    }
    printf("%s", str);
    
    print_box_right(style, blk_spc, 1);
    
    
    // now the unique bottom piece
    for (int i = 0; i < indent; i++) {
        putchar(' ');
    }
    
    if (style == 1) {
        printf("%s", LPS);
    
        for (int i = 0; i < width - 2; i++) {
            printf("%s", CS);
        }
        
        printf("%s", RPS);
    }
    
    else {
        printf("%s", LPM);
        
        for (int i = 0; i < width - 2; i++) {
            printf("%s", CM);
        }
        
        printf("%s", RPM);
    }
    putchar('\n');
    
    return 0;
}






//////////////////////////////////////////////////////////////////////////



int draw_menu_section(char* str, int str_len, int box_width, int botton_width, int cursor,
                      int indent, int box_spacing, int bot_spacing) {

    if (str == NULL) {
        str_len = 0;
        // print_blank string
    }
    
    int bot_spc = (box_width - botton_width - 2) / 2;
    if (bot_spc % 2 != 0) {
        printf("ERROR: box_width: %d, and botton_width: %d, should both be even or odd.\n",
               box_width, botton_width);
        // no need for pause_function();
    }
    
    
    print_box_left(1, indent);
    print_box_top(cursor, botton_width, bot_spc, 0);
    print_box_right(1, bot_spc, 1);
    
    for (int i = 0; i < bot_spacing; i++) {
        print_box_left(1, indent);
        print_box_empty(cursor, botton_width, bot_spc, 0);
        print_box_right(1, bot_spc, 1);
    }
    
    
    
    print_box_left(1, indent);
    print_box_internal(cursor, botton_width, bot_spc, str, str_len, 0);
    print_box_right(1, bot_spc, 1);
    
    
    
    for (int i = 0; i < bot_spacing; i++) {
        print_box_left(1, indent);
        print_box_empty(cursor, botton_width, bot_spc, 0);
        print_box_right(1, bot_spc, 1);
    }
    
    print_box_left(1, indent);
    print_box_bot(cursor, botton_width, bot_spc, 0);
    print_box_right(1, bot_spc, 1);
    
    
    
    
    for (int i = 0; i < box_spacing; i++) {
        print_box_empty(1, box_width, indent, 1);
    }
    
    return 0;
}









// draw boxes like the start screen

// inputs, pointer to array of strings, pointer to array of string lengths, length of arrays




int draw_menu_box(char** strings, int* lengths, int array_len, int cursor,
                  int indent, int botton_width, int menu_width) {

    char name[] = "draw_menu_box";
    
    if (strings == NULL) {
        null_error("String Array", name);
        return 1;
    }

    if (lengths == NULL) {
        null_error("Integer Array", name);
        return 1;
    }
    
    if (cursor >= array_len) {
        printf("VALUE ERROR: menu cursor: %d, is too large, must be less than %d. Function: '%s'.\n",
               cursor, array_len, name);
        pause_function();
        return 1;
    }
    else if (cursor < 1) {
        printf("VALUE ERROR: menu cursor: %d, is too small, minimum is 1. Function: '%s'.\n",
               cursor, name);
        pause_function();
        return 1;
    }
    
    
    
    int box_outline[array_len - 1];
    for (int i = 0; i < array_len - 1; i++) {
        box_outline[i] = 4;
    }
    box_outline[cursor - 1] = 2;
    
    
    int vertical_space = 1;
    int bot_vert_spacing = 1;
    
    
    
    putchar('\n'); putchar('\n');
    
    
    print_box_header(1, menu_width, indent, strings[0], lengths[0]);
    
    for (int i = 0; i < vertical_space; i++) {
        print_box_empty(1, menu_width, indent, 1);
    }
    
    
    
    // print bottons
    for (int i = 1; i < array_len; i++) {
        draw_menu_section(strings[i], lengths[i], menu_width, botton_width, box_outline[i - 1],
                          indent, vertical_space, bot_vert_spacing);
    }
    
    
    
    
    print_box_bot(1, menu_width, indent, 1);
    putchar('\n'); putchar('\n');
    
    return 0;
}


# endif
