#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "ui.h"
#include "asciijong.h"

#ifndef _config_h
#include "config.h"
#define _config_h
#endif

int main(int argc, const char **argv){
    board_t *board;
    tile_t *tile0,*tile1;
    board = readBoardFromFile( (char *)argv[1] );
    if(!board){
        showErrorMessageToUser("Could not read board data from file.");
        exit(-1);
    }
    while(1){
        /* Print Board */
        refreshBoard( &board, NULL);
        do{
            tile0 = getTileFromUser( &board );
        }while( !tile0 );
        if ( canRemoveTile( &board, &tile0) ){
            /* Redraw the board, this time highlighting the selected tile. */
            refreshBoard( &board, &tile0);
            tile1 = getTileFromUser( &board );
            while( !tilesMatch( &board, &tile0, &tile1) && !canRemoveTile( &board, &tile1) ){
                if( !tilesMatch( &board, &tile0, &tile1) ){
                    showErrorMessageToUser("Tiles do not match.");
                }
                if( !canRemoveTile( &board, &tile1) ){
                    showErrorMessageToUser("This tile cannot be removed.");
                }
                tile1 = getTileFromUser( &board);
            }
            /* The user may deselect the first tile and choose a whole new pair. */
            if( *tile1 == *tile0 ){
                continue;
            }
            rmTile( &board, &tile0);
            rmTile( &board, &tile1);
        } else {
            /* Print an error if the user selected an invalid tile*/
            showErrorMessageToUser("This tile cannot be removed.");
        }
    }
    return 0;
}
