#ifndef _type_h
#define _type_h
/* Tile and Board Types */
typedef struct tile_s tile_t;
typedef struct board_s board_t;

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
 *	The function returns 1 if they are
 *	of the same type, or 0 otherwise.
 */
int tilesMatch(board_t *board, tile_t *a, tile_t *b);

/*
 *	Add a tile to the specified board.
 *
 *  This function  returns  the  newly
 *  added tile.
 */
tile_t *addTile(board_t *board, tile_t *tile);

/*
 *	Remove a tile from a board.
 */
void rmTile(board_t *b, tile_t *tile);

/*
 *	Get  the  tile  at  the  specified
 *	position in the board.
 *
 *	This function returns the tile, or
 *	NULL if it doesn't exist.
 */
tile_t *getTileAt(board_t *board, double x, double y);

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
 *
 *  Returns the tile's value.
 */
char *getTileName(tile_t *tile);

/*
 *  Get  the  highest  tile  in   this
 *  position.
 *
 *  Returns the highest tile.
 */
tile_t *getHighestTileInPosition(board_t *board, double x, double y);

/*
 *  Create a new tile from an existing
 *  with the same properties.
 *
 *  Returns the new tile.
 */
tile_t *copyTile(tile_t *tile);

/*
 *  Remove a board and delete all its
 *  elements.
 */
void deleteBoard(board_t *board);

#endif
