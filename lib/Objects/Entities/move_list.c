# ifndef MOVE_LIST__
# define MOVE_LIST__


// memory freeing




int free_move_ls(Move_ls* moves) {
    if (moves != NULL) {
        free_move_ls(moves->next);
        free(moves);
    }
    return 0;
}


// free current move and return the next move in the sequence.

Move_ls* next_move(Move_ls* moves) {
    if (moves == NULL) {
        null_error(MOVE_LS_OBJECT, "free_move");
        return NULL;
    }
    
    Move_ls* p = moves->next;
    free(moves);
    return p;
}



char compute_next_action(Player* player) {
    // assume that player is not null, and moves is not null.
    
    char current_action = player->moves->action;
    player->moves = next_move(player->moves);
    return current_action;
}







// memory allocation


// add a new move to the move list, if next != NULL, then loop until end of current move list.

int add_new_move(Move_ls* moves, char move) {
    if (moves == NULL) {
        null_error(MOVE_LS_OBJECT, "add_new_move");
        return 1;
    }
    while (moves->next != NULL) {
        moves = moves->next;
    }
    moves->next = add_move(move);
    
    return 0;
}



// add the first move, or a new move in the sequence,

Move_ls* add_move(char move_) {
    
    Move_ls* output = (Move_ls*) malloc(sizeof(Move_ls));
    output->action = move_;
    output->next = NULL;
    return output;
}






int add_player_move(struct player_t* p, char c) {
    
    if (p == NULL) {
        null_error(PLAYER_OBJECT, "add_player_move");
        return 1;
    }
    
    
    Move_ls* m = p->moves;
    if (m == NULL) {
        p->moves = add_move(c);
        return 0;
    }
    
    else {
        return add_new_move(m, c);
    }
}



# endif
