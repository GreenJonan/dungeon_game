# ifndef UTILITY_FUNCS_
# define UTILITY_FUNCS_

# include "utility_error.c"


//////////////////////////////////////////////////////

// mathematical metric function

int manhattan_metric(int x1, int y1, int x2, int y2) {
    int del_x = x1 - x2;
    if (del_x < 0) {
        del_x = -del_x;
    }
    
    int del_y = y1 - y2;
    if (del_y < 0) {
        del_y = -del_y;
    }
    
    //printf("metric: %d\n", del_x + del_y);
    return del_x + del_y;
}















///////////////////////////////////////////////////////


// I/O function


char flush_input() {
    return flush_file_input(stdin);
}


char flush_file_input(FILE* f) {
    char c = fgetc(f);
    return dynamic_flush(f, c);
}


char dynamic_flush(FILE* f, char c)
{
    while (c != '\n' && !feof(f)) {
        c = fgetc(f);
    }
    
    return c;
}








///////////////////////////////////////////////////////

// char_bool function reads and transforms the bits of the 1-byte depending on the index specified
// In particular, the function treates the 1-bytes ==> 8 bits as an array 8 long


int set_char_bool_true(char* c, int i) {
    if (i < 0 || i >= 8) {
        printf("Invalid index given to 'set_char_bool' function.\n");
        return 1;
    }
    if (c == NULL) {
        printf("given char pointer to 'set_char_bool' is NULL.\n");
        return 1;
    }
    
    *c = *c | (1 << i);
    
    return 0;
}



int set_char_bool_false(char* c, int i) {
    if (i < 0 || i >= 8) {
        printf("Invalid index given to 'set_char_bool' function.\n");
        return 1;
    }
    if (c == NULL) {
        printf("given char pointer to 'set_char_bool' is NULL.\n");
        return 1;
    }
    
    char d = 1 << i;
    d = ~d;
    
    *c = *c & d;
    
    return 0;
}




//x: 2, i: 1, r: 0
//x: 5, i: 2, r: 0
//x: 8, i: 3, r: 0

// error was, I FORGOT TO REMEMBER numbers are read 00001, not 10000, hence << not >>


int read_char_bool(char c, int i) {
    if (i < 0 || i >= 8) {
        printf("Invalid index '%d' given to 'read_char_bool' function.\n", i);
        return -1;
    }

    return c & (1 << i);
}






int set_bool_array_bool(char* c, int i, int b) {
    if (c == NULL) {
        null_error("Char_Bool_Array", "set_bool_array_bool");
        return 1;
    }
    
    int index = i / 8;
    int pos = i % 8;
    
    if (b) {
        return set_char_bool_true(&(c[index]), pos);
    }
    else {
        return set_char_bool_false(&(c[index]), pos);
    }
}



int read_bool_array(char* c, int i) {
    if (c == NULL) {
        null_error("Char_Bool_Array", "read_bool_array");
        return -1;
    }
    
    int index = i / 8;
    int pos = i % 8;
    
    int val = 0;
    if (read_char_bool(c[index], pos)) {
        val = 1;
    }
    
    return val;
}








// the following function reads a file and stores the characters into a buffer string.
// it does so until it reaches end of line, end of the buffer length (with null included), or reaches char c.


int read_file(FILE* f, char* str, char c, int len) {
    
    if (f == NULL || str == NULL) {
        null_error("file or string", "read_file");
        return 1;
    }
    int i = 0;
    char d = fgetc(f);
    while (!feof(f) && d != c && i < (len-1)) {
        str[i] = d;
        d = fgetc(f);
        i++;
    }
    str[i] = 0;
    
    return 0;
}






// the following function finds the present working directrory and stores it in string, with max_len

int find_pwd(char* string, int max_len) {
    FILE* in = popen("pwd", "r");
    int error;
    
    error = read_file(in, string, '\n', max_len);
    pclose(in);
    
    return error;
}















//// STRING CONCATENATION FUNCTION

int simple_str_concat(char* new_string, char* str1, char* str2) {
    if (new_string == NULL || str1 == NULL || str2 == NULL) {
        null_error(STRING_OBJECT,"simple_str_concat function");
        return 1;
    }
    int i = 0;
    char c = str1[i];
    while (c != '\0') {
        new_string[i] = c;
        i++;
        c = str1[i];
    }
    int j = 0;
    c = str2[j];
    while (c != '\0') {
        new_string[i] = c;
        j++;
        i++;
        c = str2[j];
    }
    new_string[i] = '\0';
    
    return 0;
}


//// STRING COPY FUNCTION

// assume second string is equal to or longer than the first string

int str_copy(char* str1, char* str2) {
    if (str1 == NULL || str2 == NULL) {
        null_error(STRING_OBJECT, "str_copy");
        return 1;
    }
    
    int i = 0;
    char c = str1[i];
    
    while (c != '\0') {
        
        str2[i] = c;
        i++;
        c = str1[i];
    }
    
    return 0;
}





// string equality

int str_eq(char* str1, char* str2) {
    int i = 0;
    int b = 1;
    int end = 0;
    
    while (b && !end) {
        char c = str1[i];
        if (c == str2[i]) {
            if (c == '\0') {
                end = 1;
            }
        }
        else {
            b = 0;
        }
        i++;
    }
    
    return b;
}




int read_str(FILE* f, char* str, int max_len) {
    
    if (f == NULL || str == NULL) {
        printf("NULL ERROR: 'file' or 'str' is null in ");
    }
    
    char c = fgetc(f);
    while (c == ' ' || c == '\n' || c =='\t') {
        c = fgetc(f);
    }
    
    char d = '`'; // which quote system is used.
    
    if (c == d) {
    
        c = fgetc(f);
        int i = 0;
        
        while (c != d && i < max_len - 1 && !feof(f)) {
        
            str[i] = c;
            c = fgetc(f);
            i++;
        }
        
        str[i] = 0;
    }
    
    else  {
        char str2[BUFF];
        char str1[BUFF];
        str1[0] = c;
        str1[1] = 0;
        fscanf(f, "%s", str2);
        
        simple_str_concat(str, str1, str2);
    }
    
    return 0;
}













//////////////////////////////////////////////////


// take in the original x,y and given a facing direction, find the tile directly in front.

int dir_to_xy(int dir, int* x, int* y) {
    //// direction, W=0, A=1, S=2, D=3
    
    if (x == NULL || y == NULL) {
        null_error("int pointer", "dir_to_xy");
        return 1;
    }
    if (dir == NO_DIR) {
        return 0;
    }
    
    int del_x = 0;
    int del_y = 0;
    
    if ((dir % 2) == 0) {
        del_y = dir - 1;
    }
    else {
        del_x = dir - 2;
    }
    
    *x = *x + del_x;
    *y = *y + del_y;
    
    return 0;
}






int num_len(int n) {
    int num = 0;
    
    if (n < 0) {
        n = -n;
        num++;
    }
    
    while (n > 0) {
        n = n / 10;
        num++;
    }
    return num;
}








//////////////////////////////////////////////////////////////////////


// Non-drawing print functions

int print_dialogue_msg(char* msg, char* author, struct game_t* g) {
    char name[] = "print_dialogue_msg";
    
    if (msg == NULL) {
        null_error("String", name);
        return 1;
    }
    if (g == NULL) {
        game_null_error(name);
        return 1;
    }
    
    draw_screen(g);
    if (author != NULL) {
        if (author[0] != 0) {
            printf("%s: ", author);
        }
    }
    
    int i = 0;
    char c = msg[i];
    
    while (c != 0) {
        
    
        if (c == PARAGRAPH_SEPARATOR) {
            putchar('\n');
            putchar('\n');
            pause_function();
            
            draw_screen(g);
            
            if (author != NULL) {
                if (author[0] != 0) {
                    printf("%s: ", author);
                }
            }
        }
        
        else {
            putchar(c);
        }
        
        i++;
        c = msg[i];
    }
    return 0;
}



int print_buy_item_msg(int i_id, int cost, int num) {
    putchar('\n');
    
    // find name to print out:
    print_item_name(i_id);
    
    if (num != 0 && num != 1) {
        printf(" x%d", num);
    }
    printf(",  %d coin", cost);
    if (i_id == 1) {;}
    else { putchar('s');}
    putchar('\n');
    printf("Enter 'y' to confirm purchase:  ");
    
    return 0;
}









int print_win_msg(struct game_t* g) {
    char name[] = "print_win_msg";
    
    if (g == NULL) {
        game_null_error(name);
        return 1;
    }
    
    printf("Congratualtions! You finished the game.\n");
    putchar('\n');
    pause_function();

    return 0;
}
# endif
