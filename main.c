# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# include "lib/lib.h"
# include "lib/lib.c"


# define HARD 0          // 0 ==> player turn first, 1 ==> enemy turn first




/////
/////       MAIN
/////


int main()
{
    int exit = 0;
    
    
    // set up game
    
    Game game;
    game.is_hard = HARD;
    game.options.command_debug = COMMAND_DEBUG;
    
    exit = start_game(&game);
    

    // start the real game game
    
    
    if (game.loaded_rooms && game.loaded_player && !exit) {
        
        srand(time(NULL));
        
        exit = play_game(&game);
    }
    
    
    
    
    exit_game(&game, exit);
    
    
    return 0;
}



