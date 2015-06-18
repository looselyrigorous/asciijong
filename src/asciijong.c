#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "asciijong.h"

int main(int argc, const char **argv){
    board_t board;
    tile_t tile0,tile1;
    board = readBoardFromFile( (char *)argv[1] );
    while(1){
        /* Print Board */
        refreshBoard( *board, NULL);
        /* Accept input from the user */
        tile0 = getTileFromUser( void );
        validateTileFromUser( *tile0 );
        /* If the user selected a valid tile */
        if ( canRemoveTile( *tile0 ) ){
            /* Redraw the board, this time highlighting the selected tile */
            refreshBoard( *board, *tile0 );
            tile1 = getTileFromUser( void );
            if ( tilesMatch( *tile0, *tile1 ) ){
                rmTile( *board, *tile0, *tile1);
            }
            continue;
        /* If the user selected an invalid tile print an error */
        } else {
            showErrorMessageToUser("This tile can't be remove. Please select another one. :)");
        }



    }
    
    return 0;
}
