#ifndef MAPS_H
#define MAPS_H
#include <stdbool.h>

typedef struct {
	float x;
	float y;
	int textureID;
	int active;
	float dist;
	bool solid; // true = solid, false = ghost
} Sprite;

extern int *currentMapW;
extern int *currentMapF;
extern int *currentMapC;

extern Sprite *currentSprites;
extern int currentSpriteCount;


//function to swap them
void loadLevel(int levelNum);

#endif
