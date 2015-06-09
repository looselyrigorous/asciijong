/*
 * file: ui.c
 * author: looselyrigorous
 */
#include <stdio.h>
#include "types.h"

tile_t *getTileFromUser(void) {
	double x,y;
	tile_t tile;

	printf("Enter two doubles separated by comma: ");
	scanf("%lf,%lf", &x, &y);

	tile = getTileAt(x,y);
	return tile;
}

void refreshBoard(board_t *b, tile_t hl) {
	
}
