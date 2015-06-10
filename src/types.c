#include "type.h"
#include "stdlib.h"
#include "assert.h"
#include "config.h"

/*
 *	A basic tile
 */

struct tile_s{
    double x;				/* X Coordinate */
    double y;				/* Y Coordinate */
    int height;				/* Z Coordinate */
    unsigned int ttype;		/* Index of tile type in config array */
    tile_t *next;			/* The next tile in the single linked list */
};

/*
 *  A board
 */

struct board_s{
	tile_t *begin;			/* The first tile in the board */
};

/*
 *	Read a Mahjong Board from  a  file
 *	and return it in a board_t format.
 *
 *	The function returns NULL  if  the
 *	file is invalid or something  else
 *	happens.
 */
board_t *readBoardFromFile(FILE *f);

/*
 *	Check if a  tile  can  be  removed
 *	from a board.
 *
 *	The function returns 1 if the tile
 *	can be removed or 0 otherwise.
 */
int canRemoveTile(board_t *board, tile_t *tile);

/*
 *	Get the tile to the  left  of  the
 *	tile passed,  including  tiles  in
 *	offset +- 0.5 in a board.
 *
 *	The function returns the  tile  to
 *	the left or NULL if none found.
 */
tile_t *getLeftTile(board_t *board, tile_t *tile);

/*
 *	Get the tile to the  right of  the
 *	tile passed,  including  tiles  in
 *	offset +- 0.5 in a board.
 *
 *	The function returns the  tile  to
 *	the right or NULL if none found.
 */
tile_t *getRightTile(board_t *board, tile_t *tile);

/*
 *	Get the tile to  the  top  of  the
 *	tile passed in a board.
 *
 *	The function returns the  tile  to
 *	the top or NULL if none found.
 */
tile_t *getTopTile(board_t *board, tile_t *tile);

/*
 *	Check if two tiles are of the same
 *	type in a board.
 *
 *	The function returns 1 if the  are
 *	of the same type, or 0 otherwise.
 */
int tilesMatch(board_t *board, tile_t *a, tile_t *b);

/*
 *	Add a tile to the specified board.
 */
tile_t *addTile(board_t *board, tile_t *tile){
    tile_t *tmp;
    
    assert(board != NULL);
    assert(tile != NULL);
    
    tmp = board.begin;
    
    if (tmp == NULL) {
        board.begin = malloc(1 * sizeof(tile_t));
        assert(board.begin != NULL);
        board.begin.next = NULL;
        return board.begin;
    }
    
    while (tmp != NULL && tmp.next != NULL) {
        tmp = tmp.next;
    }
    
    tmp.next = malloc(1 * sizeof(tile_t));
    assert(tmp.next != NULL);
    tmp.next.next = NULL;
    return board.begin;
    
}

/*
 *	Remove a tile from a board.
 */
void rmTile(board_t *board, tile_t *tile){
    tile_t *tmp, *before;
    
    assert(board != NULL);
    assert(tile != NULL);
    
    tmp = board.begin;
    before = board.begin;
    
    if (tmp == NULL) {
        return;
    }
    
    while (before != NULL && tmp != NULL) {
        before = tmp;
        tmp = before.next;
        
        if (tmp != NULL && tmp == tile) {
            break;
        }
    }
    
    if (tmp.next == NULL) {
        before.next = NULL;
        free(tmp);
        return;
    }
    
    before.next = tmp.next;
    free(tmp);
    return;
    
}

/*
 *	Get  the  tile  at  the  specified
 *	position in the board.
 *
 *	This function returns the tile, or
 *	NULL if it doesn't exist.
 */
tile_t *getTileAt(board_t *board, double x, double y){
    
    assert(board != NULL);
    assert(x >= 0.0);
    assert(y >= 0.0);
    return getHighestTileInPosition(board, x, y);
    
}

/*
 *	Get all tiles of  a  specific type
 *	in a board.
 *
 *	Returns a  new  board_t  with  all
 *	tiles of that specific type.
 */
board_t *getTilesOfType(board_t *board, unsigned int ttype);

/*
 *	Check if a tile entered  from  the
 *	user  is  valid,  and  if  it  is,
 *	return it.
 *
 *	Returns the tile_r if it is valid,
 *	otherwise returns NULL.
 */
tile_t *validateTileFromUser(board_t *board, double x, double y);

/*
 *	Get  the  tile's  value  from  the
 *	configuration array.
 */
char *getTileName(tile_t *tile){
    assert(tile != NULL);
    assert(tile.ttype < TotalTileValues);
    return TileValues[tile.ttype];
}


/*
 *  Get  the  highest  tile  in   this
 *  position.
 *
 *  Returns the highest tile.
 */
tile_t *getHighestTileInPosition(board_t *board, double x, double y){
    
    tile_t *search;
    
    assert(board != NULL);
    assert(x >= 0.0);
    assert(y >= 0.0);
    
    while (search != NULL) {
        if (search.x == x && search.y = y) {
            if (getTopTile == NULL) {
                return search;
            }
        }
        search = search.next;
    }
    
    return NULL;
    
}