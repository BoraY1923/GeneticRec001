#include "maps.h"
									// Level 1 Data
int mapW_1[] = { 
	1,1,1,1,1,2,2,2,
	1,0,0,0,0,0,0,2,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1};
int mapF_1[] = { 
	1,1,1,1,1,1,1,1,
	1,0,0,1,0,0,0,1,
	1,0,0,1,0,0,0,1,
	1,1,1,1,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,1,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1};
int mapC_1[] = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0};
Sprite sprites_1[] = 
{
{2.5, 3.5, 0, 1},
{5.5, 1.5, 0, 1},
{4.5, 6.5, 0, 1,}
};

int spriteCount_1 = sizeof(sprites_1)/sizeof(sprites_1[0]);


									// Level 2 Data
int mapW_2[] = { 
	1,1,1,1,1,2,2,2,
	1,0,0,0,0,0,0,2,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,2,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1};
int mapF_2[] = { 
	1,1,1,1,1,1,1,1,
	1,0,0,1,0,0,0,1,
	1,0,0,1,0,0,0,1,
	1,1,1,1,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,1,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1};
int mapC_2[] = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0};
	

//active pointers

int *currentMapW = mapW_1;
int *currentMapF = mapF_1;
int *currentMapC = mapC_1;
Sprite *currentSprites = sprites_1;
int currentSpriteCount = 3;

void loadLevel(int levelNum) {
    if(levelNum == 1) {
        currentMapW = mapW_1;
        currentMapF = mapF_1;
        currentMapC = mapC_1;
        currentSprites = sprites_1;
        currentSpriteCount = spriteCount_1;
    } else if(levelNum == 2) {
        currentMapW = mapW_2;
        currentMapF = mapF_2;
        currentMapC = mapC_2;
    }
}
