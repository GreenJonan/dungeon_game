# ifndef MAZE_SOLVER__
# define MAZE_SOLVER__



///////////////////////////////////////////////////////////////////////////////////
int clear_path_simple_maze_solver(char* int, int, int, int, int, int);

int clear_path_simple_maze(struct room_t* r, int x1, int y1, int x2, int y2) {
    
    if (r == NULL) {
        room_null_error("clear_path");
        return -1;
    }
    if (r->room_array == NULL) {
        null_error(STRING_OBJECT, "clear_path");
        return -1;
    }
    
    // function should be symmetric for (x1,y1) and (x2,y2)
    
    // test if within bounds
    if (x1 < 0 || x1 >= r->width)  { return 0;}
    if (x2 < 0 || x2 >= r->width)  { return 0;}
    if (y1 < 0 || y1 >= r->height) { return 0;}
    if (y2 < 0 || y2 >= r->height) { return 0;}
    
    // return true if same point
    if (x1 == x2 && y1 == y2) { return 5; }
    
    
    // if (x2,y2) is a blocked tile, return false
    char tile = get_room_tile(r, x2, y2);
    if (tile != 0 && tile <= MAX_VIS_BLOCK_T) { return 0;}
    
    
    int rel_x = x2 - x1;
    int rel_y= y2 - y1;
    
    
    // initialise tmp_array:
    int size = r->width * r->height
    char tmp_array[size];
    for (int i = 0; i < size; i++) {
        char tile = r->room_array[i];
        
        if (tile != 0 && tile <= MAX_CLIP_T) {
            tmp_array[i] = 1;
        }
        else {
            tmp_array[i] = 0;
        }
    }
    
    
    
    if (rel_y >= 0) {
        
        if (rel_x >= 0) {
            return clear_path_simple_maze_solver(tmp_array, r->width, x1, y1, x2, y2, 1);
        }
        else {
            return clear_path_simple_maze_solver(tmp_array, r->width, x1, y1, x2, y2, 3);
        }
    }
    
    else {
        if (rel_x >= 0) {
            return clear_path_simple_maze_solver(tmp_array, r->width, x1, y1, x2, y2, 2);
        }
        else {
            return clear_path_simple_maze_solver(tmp_array, r->width, x1, y1, x2, y2, 4);
        }
    }
}






// here is a function for fun that I shouldn't use because it is way too inefficient, maze solver
// try up right, down left
// direction refers to which quadrant relative to x1,y1 x2,y2 exits

int clear_path_simple_maze_solver(char* array, int w, int x1, int y1, int x2, int y2, int dir) {
    
    // assume no nulls and (x1,y1), (x2,y2) are within bounds
    
    char tile = array[x1 + y1 * w];
    if (tile != 0) {
        // this means this path is blocked
        return 0;
    }
    else {
        // else block the path, so to reduce computation time:
        array[x1 + w * y1] = 1;
    
    }
    
    
    if (y1 == y2 && x2 == y2) {
        // found end points
        return 1;
    }
    
    
    // intialise result:
    int result = 0;
    
    
    // compute which directions to go depending on dir.
    int del_x = 1;
    int del_y = 1;
    
    if (dir == 2) { del_y = -1;}
    else if (dir == 3) { del_x = -1;}
    else if (dir == 4) { del_x = -1; del_y = -1;}
    
    
    // see whether exceeded bounds
    if (del_y * (y1 - y2) > 0) {return 0;}
    if (del_x * (x1 - x2) > 0) {return 0;}
    
    
    
    // now combinatorically find the path horizontally and vertically
    // assume x1,x2 and y1,y2 will never exceed each other.
    
    
    
    
    int clr;
    clr = clear_path_simple_maze_solver(r, x1, y1 + del_y, x2, y2, dir);
    
    if (clr) {
        if (del_y > 0) { result = 3;}
        else {           result = 1;}
    }
    
    
    if (!result) {
        
        clr = clear_path_simple_maze_solver(r, x1 + del_x, y1, x2, y2, dir);
        
        if (clr) {
            if (del_x > 0) { result = 4;}
            else {           result = 2;}
        }
    }
    
    if (!result) {
        clr = clear_path_simple_maze_solver(r, x1, y1 - del_y, x2, y2, dir);
        
        if (clr) {
            if (del_y > 0) { result = 1;}
            else {           result = 3;}
        }
    }
    
    
    if (!result) {
        
        clr = clear_path_simple_maze_solver(r, x1 - del_x, y1, x2, y2, dir);
        
        if (clr) {
            if (del_x > 0) { result = 2;}
            else {           result = 4;}
        }
    }
    
    return result;
}






















////////////////////////////////////////////////////////////////////

// this method cannot solve the maze, as if the algorithm reaches a corner, it will eat itself, e.g.
/*
 #####
 #/-\#
 #|#v#
 #|# #
 
 next step:
 #####
 #/->#
 #|# #
 #|# #
 
 then
 #####
 #/-\#
 #|#v#
 #|# #
 
 hence infinite loop
 
 
 An idea for how to solve it,
 after successfuly passing through a tile, turn it into a clip tile, ie cannot pass through,
 can be solved by creating a tmp room array before beginning the first instance of the recursive function.
 
 Modified version is below this function
 */

int clear_path_arbitrary_maze_solver(struct room_t* r, int x1, int y1, int x2, int y2) {
    
    // assume no nulls
    
    // see if exceeded boundaries
    if (x1 < 0 || x1 >= r->width)  { return 0;}
    if (y1 < 0 || y1 >= r->height) { return 0;}
    

    char tile = get_room_tile(r, x1, y1);
    if (tile != 0 && tile < MAX_CLIP_T) {
        // this means this path is blocked
        return 0;
    }
    
    
    if (y1 == y2 && x2 == y2) {
        // found end points
        return 1;
    }
    
    
    
    // now combinatorically find the path horizontally and vertically
    // assume x1,x2 and y1,y2 will never exceed each other.
    
    // directions WASD <==> 1234
    
    
    if ( clear_path_arbitrary_maze_solver(r, x1, y1 - 1, x2, y2) ) { return 1;}
    
    
    if ( clear_path_arbitrary_maze_solver(r, x1 + 1, y1, x2, y2) ) { return 4;}
    
    
    if ( clear_path_arbitrary_maze_solver(r, x1, y1 + 1, x2, y2) ) { return 3;}
    
    
    if ( clear_path_arbitrary_maze_solver(r, x1 - 1, y1, x2, y2) ) { return 2;}
    
    return 0;
}















int maze_solver(char* tmp_array, int h, int w, int x1, int y1, int x2, int y2) {
    
    // assume no nulls
    
    // see if exceeded boundaries
    if (x1 < 0 || x1 >= w)  { return 0;}
    if (y1 < 0 || y1 >= h) { return 0;}
    
    
    char tile = tmp_array[x1 + w*y1];
    if (tile != 0 && tile <= MAX_CLIP_T) {
        // this means this path is blocked
        return 0;
    }
    
    else {
        tmp_array[x1 + w * y1] = 1; // blocking path already gone down.
    }
    
    
    if (y1 == y2 && x2 == y2) {
        // found end points
        return 1;
    }
    
    
    int result = 0;
    int solved = 0;
    
    // now combinatorically find the path horizontally and vertically
    // assume x1,x2 and y1,y2 will never exceed each other.
    
    // directions WASD <==> 1234
    
    
    if ( maze_solver(r, x1, y1 - 1, x2, y2) ) { result = 1;}
    
    
    else if ( maze_solver(r, x1 - 1, y1, x2, y2) ) { result = 2;}
    
    
    else if ( maze_solver(r, x1, y1 + 1, x2, y2) ) { result = 3;}
    
    
    else if ( maze_solver(r, x1 + 1, y1, x2, y2) ) { result = 4;}
    
    
    tmp_array[x1 + w*y1] = result;
    
    return 0;
}

# endif
