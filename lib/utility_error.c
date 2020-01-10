# ifndef UTILITY_ERROR__
# define UTILITY_ERROR__



/////////////////////////////////////////////////////////

/////
/////   LOADING PROGRESS FUNCTIONS
/////

;
int loading_progress(int t) {
    t = t % 4;
    clear_screen();
    return printf("loading ... [%c]\n", "-\\|/"[t]);
}


int loading_progress_no_clr(int t) {
    t = t % 4;
    return printf("loading ... [%c]\n", "-\\|/"[t]);
}


int clear_screen() {
    if (DEBUG) {
        return 0;
    }
    return force_clear_screen();
}

int force_clear_screen() {
    return system("printf '\ec'");
}



int wait_msg() {
    return printf("Press enter to continue: ");
}


int pause_function() {
    wait_msg();
    return flush_input();
}


int null_error(char* object_n, char* function_n) {
    printf("Error: '%s' object given to '%s' function is Null.\n", object_n, function_n);
    return pause_function();
}

int file_error(char* str, char* str2) {
    printf("Error: unable to open file '%s' from '%s' function.\n", str, str2);
    return pause_function();
}

int null_warning(char* object_n, char* function_n) {
    if (SUPPRESS_WARNINGS) {return 0;}
    printf("Warning: '%s' object given to '%s' function is Null.\n", object_n, function_n);
    return pause_function();
}

int already_freed_warning(char* object_n, char* function_n) {
    if (SUPPRESS_WARNINGS) { return 0;}
    printf("Warning: '%s' object already freed from memory in '%s' function.\n", object_n, function_n);
    return pause_function();
}

int free_error(char* str) {
    printf("Error: unable to free all '%s' objects from memory.\n", str);
    return pause_function();
}




int player_null_error(char* function) {
    return null_error(PLAYER_OBJECT, function);
}


# endif
