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
	printf("%s\n", errormsg);
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
	int tmp=0;
	dimensions_t *dim;
	tile_t *tile, *tile_up, *tile_down;
	char *l1=NULL, *l2=NULL, *l3=NULL,
		 *l4=NULL, *l5=NULL;

	dim = getBoardDimensions(b);
	
	/* Memory allocation */
	tmp = (int) getMaximumX(dim);
	l1 = malloc(sizeof(char) * tmp);
	l2 = malloc(sizeof(char) * tmp);
	l3 = malloc(sizeof(char) * tmp);
	l4 = malloc(sizeof(char) * tmp);
	l5 = malloc(sizeof(char) * tmp);
	assert(l1 && l2 && l3 && l4 && l5);


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
				l1 = strcat(l1, "+---+");
				l2 = strcat(l2, "|   |");

				l3 = strcat(l3, "| ");
				l3 = strcat(l3, getTileName(tile));
				l3 = strcat(l3, " |");
				
				l4 = strcat(l4, "|   |");
				l5 = strcat(l5, "+---+");
			} else {
				if(tile_up != NULL) {
					l1 = strcat(l1, "| ");
					l1 = strcat(l1, getTileName(tile_up));
					l1 = strcat(l1, " |");
					l2 = strcat(l2, "|   |");
					l3 = strcat(l3, "+---+");
				} else {
					l1 = strcat(l1, "     ");
					l2 = strcat(l2, "     ");
					l3 = strcat(l3, "     ");
				}

				if(tile_down != NULL) {
					l4 = strcat(l4, "+---+");
					l5 = strcat(l5, "|   |");
				} else {
					l4 = strcat(l4, "     ");
					l5 = strcat(l5, "     ");
				}
			}
		}
		printf("%s\n",l1);
		printf("%s\n",l2);
		printf("%s\n",l3);
		printf("%s\n",l4);
		printf("%s\n",l5);
	}
}
