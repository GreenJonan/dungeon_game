# ifndef I_CAN_SEE_EVERYTHING__
# define I_CAN_SEE_EVERYTHING__

# include "entity_header.h"

// these functions are a boolean function that returns whether an object is in the field of view
// of an entity




// full vision, can see radially around it, i.e. everything within the manhattan metric.

int radial_vision(Entity* e, int x, int y) {
    
    if (e == NULL) {
        entity_null_error("radial_vision");
        return -1;
    }
    
    
    if (manhattan_metric(e->x, e->y, x, y) <= e->light_dist) {
        return 1;
    }
    else {
        return 0;
    }
}



/////////////////////////////////////////////////////////////////////////



// HALF_RADIAL_VISION ==> can only see in the hemicircle infront of them

int half_radial_vision(Entity* e, int x, int y, int forward) {

    if (e == NULL) {
        entity_null_error("half_radial_vision");
        return -1;
    }
    
    int is_y = ( (e->direction % 2) == 0);
    int val;
    int valid_xy = 0;
    
    if (is_y) {
        val = e->direction - 1;
        int tmp_y = y - e->y;
        int tmp_dir = tmp_y * val;
        
        if (forward) {
            if (tmp_dir >= 0) {
                valid_xy = 1;
            }
        }
        
        else if (tmp_dir <= 0) {
            valid_xy = 1;
        }
    }
    
    else {
        val = e->direction - 2;
        int tmp_x = x - e->x;
        int tmp_dir = tmp_x * val;
        
        if (forward) {
            if (tmp_dir >= 0) {
                valid_xy = 1;
            }
        }
        
        else if (tmp_dir <= 0) {
            valid_xy = 1;
        }
    }
    
    if (valid_xy) {
        if (manhattan_metric(e->x, e->y, x, y) <= e->light_dist) {
            return 1;
        }
    }
    return 0;
}







//////////////////////////////////////////////////////////////////////////


int half_radial_forward_vision(Entity* e, int x, int y) {
    return half_radial_vision(e, x, y, 1);
}

int half_radial_backward_vision(Entity* e, int x, int y) {
    return half_radial_vision(e, x, y, 0);
}





////////////////////////////////////////////////////////////////////////////

/*
 ```*```
 ``***``
 `*****`
 `*****` <- 2 = 5 / 2
 ``***``
 ```P```
 ```````
 
 ```*```
 ``***``
 `*****` <- 2 = 4 / 2
 ``***``
 ```P```
 ```````
 
 ```*```
 ``***``
 `*****`
 ``***``
 ``*P*``
 ```*```
*/


int cone_vision(Entity* e, int x, int y, int dir) {
    
    
    if (e == NULL) {
        entity_null_error("cone_vision");
        return -1;
    }

    
    // dir can be 0,1,2,3 wasd (relative to direction entity is facing) as convention
    
    int rel_y =  y - e->y;
    int rel_x =  x - e->x;
    
    int abs_dir = (e->direction + dir) % 4; // direction is like turning a clock, hence modular arithmentic
    int y_dir = (abs_dir % 2) == 0;
    int max_val = e->light_dist / 2;
    
    int output = 0;
    
    
    
    if (y_dir) {
        // x-axis, i.e. horizontal, options, 0, 2
        
        // reuse abs_dir variable ==> -1,1
        abs_dir = abs_dir - 1;
        rel_y = rel_y * abs_dir;
        
        if (rel_y >= 0) {
            // this implies direction and diplacement vector are the same direction
            
            
            if (rel_y > max_val) {
                // if greater than this critcal value, simple return manhattan metric
                
                if (manhattan_metric(e->x, e->y, x, y) <= e->light_dist) {
                    output = 1;
                }
            }
            else {
                // else, test to see whether in the 'cone'
                
                if (rel_x < 0) {
                    rel_x = -rel_x;
                }
                
                if (rel_x <= (2* rel_y + 1)) {
                    output = 1;
                }
            }
        }
    }
    
    
    
    else {
        // x-axis, i.e. horizontal, options, 1, 3
        
        // reuse abs_dir variable ==> -1,1
        abs_dir = abs_dir - 2;
        rel_x = rel_x * abs_dir;
        
        if (rel_x >= 0) {
            // this implies direction and diplacement vector are the same direction
            
            
            if (rel_x > max_val) {
                if (manhattan_metric(e->x, e->y, x, y) <= e->light_dist) {
                    output = 1;
                }
            }
            else {
                if (rel_y < 0) {
                    rel_y = -rel_y;
                }
                
                if (rel_y <= (2* rel_x + 1)) {
                    output = 1;
                }
            }
        }
    }
    
    
    
    return output;
}






///////////////////////////////////////////////////////////////////////////////////////

// eyesight takes three classes of values, negatives, 0, positives.
//   -  positives ==> which cones values
//   -  zero implies no vision, except on player
//   -  negative implies some type of radial vision.

int entity_eyesight(Entity* e, int x, int y) {

    if (e == NULL) {
        entity_null_error("entity_eyesight");
        return -1;
    }
    
    int eyesight = e->eyesight;
    
    if (eyesight == 0) {
        return 0;
    }
    
    else if (radial_vision(e, x, y)) {
        
        if (eyesight < 0) {
            if (eyesight == -1) {
                return radial_vision(e, x, y);
            }
        
            if (eyesight == -2) {
                return half_radial_forward_vision(e, x, y);
            }
            else {
                return half_radial_backward_vision(e, x, y);
            }
        }
    
    
        
        else if (manhattan_metric(e->x, e->y, x, y) <= 1){
            return 1;
        }
        
        
        else {
            int w_dir, a_dir, s_dir, d_dir;
            //eyesight = (eyesight - 1) % 16; // not sure what this does, only confuses things!!!!
            
            w_dir = read_char_bool((char)eyesight, 0);
            a_dir = read_char_bool((char)eyesight, 1);
            s_dir = read_char_bool((char)eyesight, 2);
            d_dir = read_char_bool((char)eyesight, 3);
            
            
            
            int result = 0;
            if (w_dir) {
                if (cone_vision(e, x, y, 0)) { result = 1;}
            }
            if (a_dir && !result) {
                if (cone_vision(e, x, y, 1)) { result = 1;}
            }
            if (s_dir && !result) {
                if (cone_vision(e, x, y, 2)) { result = 1;}
            }
            if (d_dir && !result) {
                if (cone_vision(e, x, y, 3)) { result =  1;}
            }
            
            
            if (VISION_DEBUG) {
                printf("direction: %d, vision directions (w,a,s,d): %d,%d,%d,%d\n", e->direction,
                       w_dir, a_dir, s_dir, d_dir);
                printf("result: %d\n", result);
                pause_function();
            }
            
        
            return result;
        }
        
        
    }
    return 0;
}

# endif
