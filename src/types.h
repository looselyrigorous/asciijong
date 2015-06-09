typedef struct tile_s tile_t;

struct board_t{
    tile_t *begin;
}

board_t readBoardFromFile(FILE *f);

/* Check surrounding tiles to see if we can remove it*/
int canRemoveTile(tile_t *tile, board_t *board);
tile_t *getLeftTile(board_t *board, tile_t *tile);
tile_t *getRightTile(board_t *board, tile_t *tile);
tile_t *getTopTile(board_t *board, tile_t *tile);

/* Return 1 if two tiles are of same type, 0 otherwise */
int tilesMatch(tile_t *a, tile_t *b);

void addTile(board_t *b, tile_t *tile);
void rmTile(board_t *b, tile_t *tile);

tile_t *getTileAt(double x, double y);
tile_t *getTilesOfType(unsigned int ttype);
/* If the user gave valid coordinates return the tile, NULL otherwise */
tile_t *validateTileFromUser(double x, double y);
