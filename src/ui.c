/*
 * file: ui.c
 * author: looselyrigorous
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "ui.h"
#include "types.h"

void showErrorMessageToUser(const char *errormsg) {
	fprintf(stderr, "%s\n", errormsg);
	return;
}

tile_t *getTileFromUser(board_t *b) {
	coordt_t x=0.0, y=0.0;
	tile_t *tile;
	while(1) {
		printf("\nEnter tile coordinates separated by comma: ");
		scanf("%lf,%lf", &x, &y);
		tile = validateTileFromUser(b,x,y);
		if(tile != NULL) return tile;
		showErrorMessageToUser("Invalid coordinates.");
	}
}

void refreshBoard(board_t *b, tile_t *hl) {
	coordt_t x=0.0, y=0.0;
	int tmp=0, i=0;
	dimensions_t *dim;
	tile_t *tile, *tile_up, *tile_down;
	char **l;

	dim = getBoardDimensions(b);

	/* Memory allocation */
	tmp = (int) getMaximumX(dim);
	l = malloc(sizeof(char*) * 5);
	for(i=0; i<5; i++)
		l[i] = malloc(sizeof(char) * tmp);
	assert(l && l[0] && l[1] && l[2] && l[3] && l[4]);


	/* Refresh sequence */
	printf("\e[1;1H\e[2J"); /* Clears screen */
	for(y=getMinimumY(dim); y<getMaximumY(dim); y+=0.5) {
		for(x=getMinimumX(dim); x<getMaximumX(dim); x+=0.5) {
			tile = getTileAt(b,x,y);
			if(fmod(y, 1.0) == 0.0) {
				if(y-0.5>getMinimumY(dim)) tile_up = getTileAt(b,x,y-0.5);
				if(y+0.5<getMaximumY(dim)) tile_down = getTileAt(b,x,y+0.5);
			}

			if(tile != NULL) {
				l[0] = strcat(l[0], "+---+");
				l[1] = strcat(l[1], "|   |");

				l[2] = strcat(l[2], "| ");
				l[2] = strcat(l[2], getTileName(tile));
				l[2] = strcat(l[2], " |");

				l[3] = strcat(l[3], "|   |");
				l[4] = strcat(l[4], "+---+");
			} else {
				if(tile_up != NULL) {
					l[0] = strcat(l[0], "| ");
					l[0] = strcat(l[0], getTileName(tile_up));
					l[0] = strcat(l[0], " |");
					l[1] = strcat(l[1], "|   |");
					l[2] = strcat(l[2], "+---+");
				} else {
					l[0] = strcat(l[0], "     ");
					l[1] = strcat(l[1], "     ");
					l[2] = strcat(l[2], "     ");
				}

				if(tile_down != NULL) {
					l[3] = strcat(l[3], "+---+");
					l[4] = strcat(l[4], "|   |");
				} else {
					l[3] = strcat(l[3], "     ");
					l[4] = strcat(l[4], "     ");
				}
			}
		}
		for(i=0; i<5; i++)
			printf("%s\n",l[i]);
	}
	for(i=0; i<5; i++)
		free(l[i]);
	free(l);
	return;
}
