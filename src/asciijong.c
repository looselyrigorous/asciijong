#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "asciijong.h"

int main(int argc, const char **argv){
    board_t board;
    tile_t tile0,tile1;
    board = readBoardFromFile( (char *)argv[1] );
    while(1){
        refreshBoard( *board, *hl);
        tile0 = getTileFromUser( void );
        validateTileFromUser( *tile0 );
        while ( tilegetTilesLike( *tile0 ) ){

        }



    }
    
    return 0;
}
