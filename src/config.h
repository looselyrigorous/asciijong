#ifndef _config_h
#define _config_h

#include <string.h>

/*
 *	Array with all values returned to the UI 
 */
char TileValues = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/*
 *	Array length (max available tile types)
 */
size_t TotalTileValues = strlen(TileValues);

#endif
