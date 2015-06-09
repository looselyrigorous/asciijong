#include "type.h"

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

struct board_s{
	tile_t *begin;			/* The first tile in the board */
};
