# ifndef EXIT_BOOL_
# define EXIT_BOOL_

# include "room_header.h"
# include "../../utility_functions.c"


// door boolean methods


//locked

int set_door_locked(Exit* exit, int b) {
    if (NULL == exit) {
        printf("NULL type passed to 'set_door_locked' function.\n");
        return 2;
    }
    
    if (b) {
        return set_char_bool_true(&(exit->status), 0);
    }
    return set_char_bool_false(&(exit->status), 0);
}

int door_is_locked(Exit* exit) {
    if (NULL == exit) {
        printf("NULL type passed to 'door_is_locked' function.\n");
        return 2;
    }
    
    return read_char_bool(exit->status, 0);
}




//switch

int set_door_switch(Exit* exit, int b) {
    if (NULL == exit) {
        null_error(EXIT_OBJECT, "set_door_switch");
        return 2;
    }
    
    if (b) {
        return set_char_bool_true(&(exit->status), 1);
    }
    return set_char_bool_false(&(exit->status), 1);
}

int door_is_switch(Exit* exit) {
    if (NULL == exit) {
        null_error(EXIT_OBJECT, "door_is_switch");
        return 2;
    }
    
    return read_char_bool(exit->status, 1);
}




// bomb

int set_door_bombable(Exit* exit, int b) {
    if (NULL == exit) {
        null_error(EXIT_OBJECT, "set_door_bombable");
        return 2;
    }
    
    if (b) {
        return set_char_bool_true(&(exit->status), 2);
    }
    return set_char_bool_false(&(exit->status), 2);
}

int door_is_bombable(Exit* exit) {
    if (NULL == exit) {
        null_error(EXIT_OBJECT, "door_is_bombable");
        return 2;
    }
    
    return read_char_bool(exit->status, 2);
}




// portal

// bomb

int set_door_portal(Exit* exit, int b) {
    if (NULL == exit) {
        null_error(EXIT_OBJECT, "set_door_portal");
        return 2;
    }
    
    if (b) {
        return set_char_bool_true(&(exit->status), 3);
    }
    return set_char_bool_false(&(exit->status), 3);
}

int door_is_portal(Exit* exit) {
    if (NULL == exit) {
        null_error(EXIT_OBJECT, "door_is_portal");
        return 2;
    }
    
    return read_char_bool(exit->status, 3);
}





// default closed/open

int set_door_default_locked(struct exit_t* e, int b) {
    if (e == NULL) {
        null_error(EXIT_OBJECT, "set_door_default_locked");
        return 1;
    }
    
    if (b) {
        return set_char_bool_true(&(e->status), 5);
    }
    else {
        return set_char_bool_false(&(e->status), 5);
    }
}

int get_door_default_locked(struct exit_t* e) {
    if (e == NULL) {
        null_error(EXIT_OBJECT, "get_door_default_locked");
        return -1;
    }
    
    return read_char_bool(e->status, 5);
}




// hidden

int set_door_hidden(struct exit_t* e, int b) {
    if (e == NULL) {
        null_error(EXIT_OBJECT, "set_door_hidden");
        return 1;
    }
    
    if (b) {
        return set_char_bool_true(&(e->status), 4);
    }
    else {
        return set_char_bool_false(&(e->status), 4);
    }
}

int get_door_hidden(struct exit_t* e) {
    if (e == NULL) {
        null_error(EXIT_OBJECT, "get_door_hidden");
        return -1;
    }
    
    return read_char_bool(e->status, 4);
}



# endif
