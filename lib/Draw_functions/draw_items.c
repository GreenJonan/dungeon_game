# ifndef DRAW_ITEMS_____
# define DRAW_ITEMS_____


// mini header
void print_basic_sword(int);
void print_pointer(int);
void print_staff(int);
void print_magic_staff(int);
void print_bow(int);


void print_bomb_bag(int);

//  bottles
void print_empty_bottle(int);
void print_full_dark_bottle(int);
void print_half_full_dark_bottle(int);
void print_full_med_bottle(int);
void print_half_full_med_bottle(int);
void print_full_light_bottle(int);
void print_half_full_light_bottle(int);




void print_basic_shield(int);
void print_hourglass(int);



void print_none(int);








///////////////////////////////////////////

int print_item_sprite(int i_id, int line) {
    
    if (i_id == POINTER_ID) {    print_pointer(line);  }
    
    else if (i_id == BASIC_SWORD_ID) {    print_basic_sword(line);  }
    
    else if (i_id < 0) {    printf("    ");  }
    
    else if (i_id == NONE_ID) {    print_none(line);  }
    
    else if (i_id == STAFF_ID) {    print_staff(line); }
    
    else if (i_id == MAGIC_STAFF_ID) {    print_magic_staff(line); }
    
    else if (i_id == BOW_ID) {    print_bow(line); }
    
    else if (i_id == BOMB_BAG_ID) {    print_bomb_bag(line); }
    
    else if (i_id == BASIC_SHIELD_ID) {    print_basic_shield(line); }
    
    else if (i_id == HOURGLASS_ID) {    print_hourglass(line);}
    
    
    
    else if (i_id == BOTTLE_EMPTY_ID) {    print_empty_bottle(line); }
    
    else if (i_id == BOTTLE_FULL_DARK_ID) {    print_full_dark_bottle(line); }
    
    else if (i_id == BOTTLE_HALF_FULL_DARK_ID) {    print_half_full_dark_bottle(line); }
    
    else if (i_id == BOTTLE_FULL_MED_ID) {    print_full_med_bottle(line); }
    
    else if (i_id == BOTTLE_HALF_FULL_MED_ID) {    print_half_full_med_bottle(line); }
    
    else if (i_id == BOTTLE_FULL_LIGHT_ID) {    print_full_light_bottle(line); }
    
    else if (i_id == BOTTLE_HALF_FULL_LIGHT_ID) {    print_half_full_light_bottle(line); }
    
    
    
    
    
    
    
    
    else {
        if (line == 0) {
            printf("%4d", i_id);
        }
        else if ((line % 2) == 1) {
            printf(" ?? ");
        }
        else {
            printf("    ");
        }
    }
    return 0;
}










/////////////////////////////////////////////
/*
int print_str(char* func) {
    return printf("%s", func);
}*/
void line_error(int line, int i_id) {
    printf("ERROR: unknown line value %d for item id: %d\n", line, i_id);
    pause_function();
}

void print_pointer(int line) {

    if (line == 0) {        print_str(POINTER_0);   }
    
    else if (line == 1) {   print_str(POINTER_1);   }
    
    else if (line == 2) {   print_str(POINTER_2);   }
    
    else {   line_error( line, POINTER_ID);  }
}




void print_basic_sword(int line) {

    if (line == 0) {        print_str(BASIC_SWORD_0);   }
    
    else if (line == 1) {   print_str(BASIC_SWORD_1);   }
    
    else if (line == 2) {   print_str(BASIC_SWORD_2);   }
    
    else {   line_error(line, BASIC_SWORD_ID);   }
}



void print_none(int line) {

    if (line == 0) {        print_str(NONE_0);   }
    
    else if (line == 1) {   print_str(NONE_1);   }
    
    else if (line == 2) {   print_str(NONE_2);   }
    
    else {   line_error( line, NONE_ID);   }
}








void print_staff(int line){

    if (line == 0) {         print_str(STAFF_0); }
    else if (line == 1) {    print_str(STAFF_1); }
    else if (line == 2) {    print_str(STAFF_2); }
    else {    line_error(line, STAFF_ID); }
}



void print_magic_staff(int line) {
    if (line == 0) {         print_str(MAGIC_STAFF_0); }
    else if (line == 1) {    print_str(MAGIC_STAFF_1); }
    else if (line == 2) {    print_str(MAGIC_STAFF_2); }
    else {    line_error(line, MAGIC_STAFF_ID); }
}



void print_bow(int line) {
    if (line == 0) {         print_str(BOW_0); }
    else if (line == 1) {    print_str(BOW_1); }
    else if (line == 2) {    print_str(BOW_2); }
    else {    line_error(line, BOW_ID); }
}





void print_bomb_bag(int line) {
    if (line == 0) {         print_str(BOMB_BAG_0); }
    else if (line == 1) {    print_str(BOMB_BAG_1); }
    else if (line == 2) {    print_str(BOMB_BAG_2); }
    else {    line_error(line, BOMB_BAG_ID); }
}




//  bottles
void print_empty_bottle(int line) {
    if (line == 0) {         print_str(BOTTLE_EMPTY_0); }
    else if (line == 1) {    print_str(BOTTLE_EMPTY_1); }
    else if (line == 2) {    print_str(BOTTLE_EMPTY_2); }
    else {    line_error(line, BOTTLE_EMPTY_ID); }
}



void print_full_dark_bottle(int line) {
    if (line == 0) {         print_str(BOTTLE_FULL_DARK_0); }
    else if (line == 1) {    print_str(BOTTLE_FULL_DARK_1); }
    else if (line == 2) {    print_str(BOTTLE_FULL_DARK_2); }
    else {    line_error(line, BOTTLE_FULL_DARK_ID); }
}



void print_half_full_dark_bottle(int line) {
    if (line == 0) {         print_str(BOTTLE_HALF_FULL_DARK_0); }
    else if (line == 1) {    print_str(BOTTLE_HALF_FULL_DARK_1); }
    else if (line == 2) {    print_str(BOTTLE_HALF_FULL_DARK_2); }
    else {    line_error(line, BOTTLE_HALF_FULL_DARK_ID); }
}



void print_full_med_bottle(int line) {
    if (line == 0) {         print_str(BOTTLE_FULL_MED_0); }
    else if (line == 1) {    print_str(BOTTLE_FULL_MED_1); }
    else if (line == 2) {    print_str(BOTTLE_FULL_MED_2); }
    else {    line_error(line, BOTTLE_FULL_MED_ID); }
}



void print_half_full_med_bottle(int line) {
    if (line == 0) {         print_str(BOTTLE_HALF_FULL_MED_0); }
    else if (line == 1) {    print_str(BOTTLE_HALF_FULL_MED_1); }
    else if (line == 2) {    print_str(BOTTLE_HALF_FULL_MED_2); }
    else {    line_error(line, BOTTLE_HALF_FULL_MED_ID); }
}



void print_full_light_bottle(int line) {
    if (line == 0) {         print_str(BOTTLE_FULL_LIGHT_0); }
    else if (line == 1) {    print_str(BOTTLE_FULL_LIGHT_1); }
    else if (line == 2) {    print_str(BOTTLE_FULL_LIGHT_2); }
    else {    line_error(line, BOTTLE_FULL_LIGHT_ID); }
}



void print_half_full_light_bottle(int line) {
    if (line == 0) {         print_str(BOTTLE_HALF_FULL_LIGHT_0); }
    else if (line == 1) {    print_str(BOTTLE_HALF_FULL_LIGHT_1); }
    else if (line == 2) {    print_str(BOTTLE_HALF_FULL_LIGHT_2); }
    else {    line_error(line, BOTTLE_HALF_FULL_LIGHT_ID); }
}







void print_basic_shield(int line) {
    if (line == 0) {         print_str(BASIC_SHIELD_0); }
    else if (line == 1) {    print_str(BASIC_SHIELD_1); }
    else if (line == 2) {    print_str(BASIC_SHIELD_2); }
    else {    line_error(line, BASIC_SHIELD_ID); }
}



void print_hourglass(int line) {
    if (line == 0) {         print_str(HOURGLASS_0); }
    else if (line == 1) {    print_str(HOURGLASS_1); }
    else if (line == 2) {    print_str(HOURGLASS_2); }
    else {    line_error(line, HOURGLASS_ID); }
}





















//////////////////////////////////////////////////

// -1 ==> empty box, -2 ==> left arrow, -3 ==> right arrow


void print_left_arrow(int, int);
void print_right_arrow(int, int);


int print_item_box(int i_id, int line, int indent, int cursor) {

    if (i_id == LEFT_ARROW_ID) {  print_left_arrow(line, indent);  }
    
    else if (i_id == RIGHT_ARROW_ID) {   print_right_arrow(line, indent);  }
    
    else {
        int style = 4;
        if (cursor) {
            style = 2;
        }
        if (line == 0) {
            print_box_top(style, 6, indent, 0);
        }
        else if (line == 4) {
            print_box_bot(style, 6, indent, 0);
        }
        else {
            print_box_left(style, indent); print_item_sprite(i_id, line - 1); print_box_left(style, 0);
        }
    }
    return 0;
}




void print_left_arrow(int line, int indent) {

    for (int i = 0; i < indent; i++) {
        putchar(' ');
    }
    
    if (line == 0) {    printf("%s", LEFT_ARROW_0); }
    
    else if (line == 1) {    printf("%s", LEFT_ARROW_1); }
    
    else if (line == 2) {    printf("%s", LEFT_ARROW_2); }
    
    else if (line == 3) {    printf("%s", LEFT_ARROW_3); }
    
    else if (line == 4) {    printf("%s", LEFT_ARROW_4); }
    
    else {
        printf("ERROR: unknown line value '%d' for 'left-arrow' draw function.\n", line);
    }
}





void print_right_arrow(int line, int indent) {

    for (int i = 0; i < indent; i++) {
        putchar(' ');
    }
    
    if (line == 0) {    printf("%s", RIGHT_ARROW_0); }
    
    else if (line == 1) {    printf("%s", RIGHT_ARROW_1); }
    
    else if (line == 2) {    printf("%s", RIGHT_ARROW_2); }
    
    else if (line == 3) {    printf("%s", RIGHT_ARROW_3); }
    
    else if (line == 4) {    printf("%s", RIGHT_ARROW_4); }

    else {
        printf("ERROR: unknown line value '%d' for 'left-arrow' draw function.\n", line);
    }
}


# endif
