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
 *  A Dimensions Object
 */

struct dimensions_s{
    double minX;
    double minY;
    double maxX;
    double maxY;
    int minZ;
    int maxZ;
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
int canRemoveTile(board_t *board, tile_t *tile){
    
    assert(board != NULL);
    assert(tile != NULL);
    
    if (getTopTile(board, tile) == NULL) {
        if (getLeftTile(board, tile) == NULL || getRightTile(board, tile) == NULL) {
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
    
}

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
 *	The function returns 1 if they are
 *	of the same type, or 0 otherwise.
 */
int tilesMatch(board_t *board, tile_t *a, tile_t *b){
    assert(board != NULL);
    assert(a != NULL);
    assert(b != NULL);
    assert(a.ttype < TotalTileValues);
    assert(b.ttype < TotalTileValues);
    
    if (a.ttype == b.ttype) {
        return 1;
    }else{
        return 0;
    }
}

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
board_t *getTilesOfType(board_t *board, unsigned int ttype){
    
    board_t *new;
    tile_t *search;
    tile_t *end;
    
    assert(board != NULL);
    assert(ttype < TotalTileValues);
    
    new = malloc(1 * sizeof(board_t));
    assert(new != NULL);
    new.begin = NULL;
    end = NULL;
    
    search = board.begin;
    
    while (search != NULL) {
        if (search.ttype == ttype) {
            if (end == NULL) {
                new.begin = copyTile(search);
                end = new.begin;
            }else{
                end.next = copyTile(search);
                end = end.next;
            }
        }
        search = search.next;
    }
    
    end.next = NULL;
    return new;
    
}

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

/*
 *  Create a new tile from an existing
 *  with the same properties.
 *
 *  Returns the new tile.
 */
tile_t *copyTile(tile_t *tile){
    
    tile_t *new;
    
    assert(tile != NULL);
    
    new = malloc(1 * tile_t);
    assert(new != NULL);
    
    assert(tile.x >= 0.0);
    new.x = tile.x;
    assert(tile.y >= 0.0);
    new.y = tile.y;

    new.height = tile.height;
    assert(tile.ttype < TotalTileValues);
    new.ttype = tile.ttype;
    
    new.next = tile.next;
    
    return new;
    
}

/*
 *  Remove a board and delete all its
 *  elements.
 */
void deleteBoard(board_t *board){
    
    tile_t *search, *next;
    
    assert(board != NULL);
    
    search = board.begin;
    next = search.next;
    
    while (search != NULL) {
        next = search.next;
        free(search);
        search = next;
    }
    
    free(board);
    
}

/*
 *  Get a tile's height.
 *
 *  Returns a tile's height.
 */
int getTileHeight(tile_t *tile){
    assert(tile != NULL);
    return tile.height;
}

/*
 *  Get a board's dimensions.
 *
 *  Returns      a      corresponding
 *  dimensions object.
 */
dimensions_t getBoardDimensions(board_t *board){
    
    double minX = 0.0, maxX = 0.0, minY = 0.0, maxY = 0.0;
    int minZ = 0, maxZ = 0;
    tile_t *search;
    dimensions_t *ret;
    
    assert(board != NULL);
    
    search = board.begin;
    
    while (search != NULL) {
        if (search == board.begin) {
            minX = search.x;
            maxX = search.x;
            minY = search.y;
            maxY = search.y;
            minZ = search.height;
            maxZ = search.height;
        }else{
            if (search.x < minX) {
                minX = search.x;
            }
            if (search.x > maxX) {
                maxX = search.x;
            }
            if (search.y < minY) {
                minY = search.y;
            }
            if (search.y > maxY) {
                maxY = search.y;
            }
            if (search.height < minZ) {
                minZ = search.height;
            }
            if (search.height > maxZ) {
                maxZ = search.height;
            }
        }
        search = search.next;
    }
    
    assert(minX >= 0.0);
    assert(minY >= 0.0);
    assert(minZ >= 0);
    
    ret = malloc(1 * sizeof(dimensions_t));
    assert(ret != NULL);
    
    ret.minX = minX;
    ret.maxX = maxX;
    ret.minY = minY;
    ret.maxY = maxY;
    ret.minZ = minZ;
    ret.maxZ = maxZ;
    
    return ret;
    
}