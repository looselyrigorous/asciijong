/*
 * file: ui.h
 * author: looselyrigorous
 */
#include "types.h"

/* Asks the user to select a valid tile, then returns it.
 * Always returns valid tile from board *b */
tile_t *getTileFromUser(board_t *b);

/* Refreshes board *b, and highlights tile *hl
 * Called after the program has received input
 * and acted according to it*/
void refreshBoard(board_t *b, tile_t *hl);

/* Shows an error message to the user.
 * Should be used for errors related to the game itself. */
void showErrorMessageToUser(const char *errormsg);
