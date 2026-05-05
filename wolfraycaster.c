#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "maps.h"
#include "config.h"

#include "Textures/T_1.h"
#include "Textures/TS_1.h"
#include "Textures/end.h"
#include "Textures/start.h"
#include "Textures/Maintitle.h"
#include "Textures/hold.h"
#include "Textures/press.h"

typedef struct {
	int w,a,d,s,p,l;
}ButtonKeys; ButtonKeys Keys;

typedef struct {
    int x, y, w, h;       //
    int *tex_normal;      // to the "Press" 
    int *tex_hold;        // to the "Hold" 
    int state;            // 0 = Normal ----- 1 = Hover/Pressed
    void (*action)();     // a function pointer i forgot 
} MenuButton;



int All_Textures[] = {
//32x32 size
// Bricks
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
1,1,1,0,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
1,1,1,0,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
1,1,1,0,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
1,1,1,1,0,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 
1,1,1,1,0,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 
1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

//Texture 2

1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

//Texture Wall 3

1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

//Wall 4, doors I mean

1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 

1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

//ceiling/"skybox"

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

};

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533 //one degree in radian

float degToRad(float a) { return a*M_PI/180.0;}
float FixAng(float a) { if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}
float depthBuffer[150]; // 105 matches your maximum ray count

float px,py,pdx,pdy,pa; //player position

void drawPlayer()
{
	glColor3d(1,1,0);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(px,py);
	glEnd();
	
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2i(px,py);
	glVertex2i(px+pdx*5, py+pdy*5);
	glEnd();
}

int mapX=20,mapY=20,mapS=64;


/*
void drawMap2D()
{
	int x,y,xo,yo;
	for(y=0;y<mapY;y++)
	{
		for(x=0;x<mapX;x++)
		{
			if(currentMapW[y*mapX+x]>0) {glColor3f(0,0,1);} 
			else{glColor3f(1,1,1);}
			xo=x*mapS;
			yo=y*mapS;
			glBegin(GL_QUADS);
			glVertex2i(xo     +1, yo     +1);
			glVertex2i(xo     +1, yo+mapS-1);
			glVertex2i(xo+mapS-1, yo+mapS-1);
			glVertex2i(xo+mapS-1, yo+1     );
			glEnd();
		}
	}
}
*/

float dist(float ax, float ay, float bx, float by, float ang)
 {
 	return (sqrt((bx-ax)*(bx-ax)+(by-ay)*(by-ay)));                        //distance between two points
 }

void drawRays3D()
{
	int r,mx,my,mp,dof;
	float rx,ry,ra,xo,yo,disT;
	ra=pa-DR*30;
	if(ra<0){
		 ra+= 2*PI;
	}
	if(ra>2*PI) {
		 ra-=2*PI;
	}
	
	for (r=0;r<105;r++) //105 rays, value can be increased or decreased !!!!!!!!!
	{
		//Vertical and horizontal map texture numbers 
		int vmt=0;
		int hmt=0;
		
		
		
		//HORIZONTAL RAYS
		float disH=1000000,hx=px,hy=py;
		dof=0;
		float aTan=-1/tan(ra);
		if(ra>PI){ ry=(((int)py>>6)<<6)-0.0001; rx=(py-ry)*aTan+px; yo=-64; xo=-yo*aTan; } //looking up
		if(ra<PI){ ry=(((int)py>>6)<<6)+64    ; rx=(py-ry)*aTan+px; yo= 64; xo=-yo*aTan; }
		if (ra==0 || ra==PI) { rx=px; ry=py; dof=8;}
		while(dof < 40) 
		{
    			mx=(int)(rx)>>6;
   			my=(int)(ry)>>6;
    			mp=my*mapX+mx;
    											// Safety check
    			if(mx >= 0 && mx < mapX && my >= 0 && my < mapY && currentMapW[mp] > 0) 
    			{ 
        			hmt=currentMapW[mp]-1; hx=rx; hy=ry; disH=dist(px,py,hx,hy,ra); dof=40;
    			} 
    			else { rx+=xo; ry+=yo; dof+=1; }
		}

		//VERTICAL RAYS
		float disV=1000000, vx=px,vy=py;
		dof=0;
		float nTan=-tan(ra);
		if(ra>P2 && ra<P3){ rx=(((int)px>>6)<<6)-0.0001; ry=(px-rx)*nTan+py; xo=-64; yo=-xo*nTan; } //looking up
		if(ra<P2 || ra>P3){ rx=(((int)px>>6)<<6)+64    ; ry=(px-rx)*nTan+py; xo= 64; yo=-xo*nTan; }
		if (ra==0 || ra==PI) { rx=px; ry=py; dof=8;}
		
		while(dof < 40) 
		{
    		mx=(int)(rx)>>6;
    		my=(int)(ry)>>6;
    		mp=my*mapX+mx;
    
    		if(mx >= 0 && mx < mapX && my >= 0 && my < mapY && currentMapW[mp] > 0) 
    		{ 
        		vmt=currentMapW[mp]-1; //vmt for vertical
        		vx=rx; vy=ry; 
        		disV=dist(px,py,vx,vy,ra); 
        		dof=40;
    		} 
    		else { rx+=xo; ry+=yo; dof+=1; }
		}
		
		/*
		while(dof < 40) 
		{
    			mx=(int)(rx)>>6;
   			my=(int)(ry)>>6;
    			mp=my*mapX+mx;
    											// Safety check
    			if(mx >= 0 && mx < mapX && my >= 0 && my < mapY && currentMapW[mp] > 0) 
    			{ 
        			hmt=currentMapW[mp]-1; hx=rx; hy=ry; disH=dist(px,py,hx,hy,ra); dof=40;
    			} 
    			else { rx+=xo; ry+=yo; dof+=1; }
		}
		*/
		float shade=1;
		glColor3f(0,0.8,0);
		if(disV<disH){  hmt=vmt; shade=0.6; rx=vx; ry=vy; disT=disV; glColor3f(0.9,0,0);}
		if(disH<disV){rx=hx; ry=hy;disT=disH; glColor3f(0.6,0,0);}
		
		/* This draws the rays on the 2D map which is no longer needed	
	
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex2i(px,py);
		glVertex2i(rx,ry);
		glEnd();
		*/	
		//--------3D WALLS--------
		
		float ca=pa-ra; if(ra<0){ra+=2*PI;} if(ra>2*PI){ra-=2*PI;} disT=disT*cos(ca);
		depthBuffer[r] = disT;
		float lineH=(mapS*640)/disT;
		float ty_step=64.0/(float)lineH;
		float ty_off=0;
		int texIdx = (disV < disH) ? vmt : hmt;
		int texOffset = texIdx * 4096; // 64x64=4096
		
		float tx;
		if(disV < disH){tx = (int)(ry)%64;}
		else           {tx = (int)(rx)%64;}
		
		if(lineH>640){ ty_off=(lineH-640)/2.0; lineH=640;}
		float lineO=320-lineH/2;  //line Offset
		
		int y;
		float ty=ty_off*ty_step; //+hmt*32;
		if(shade==1){ tx=(int)(rx)%64; if(ra>180){ tx=63-tx;}}  
  		else        { tx=(int)(ry)%64; if(ra>90 && ra<270){ tx=63-tx;}}
		for(y=0;y<lineH;y++){
			int pixel =((texIdx * 64 + (int)ty) * 64) + (int)tx*3;
			//float c = T_1[pixel]*shade;
			
			
			int red   = T_1[pixel+0]*shade;
			int green = T_1[pixel+1]*shade;
			int blue  = T_1[pixel+2]*shade;
			
			// glPointSize(16); 
			glColor3ub(red,green,blue); glBegin(GL_POINTS); glVertex2i(r*16,y+lineO); glEnd();
			ty+=ty_step;
		}

		          											//----------DRAW FLOORS currentMapF & CEILING mapC--------
		//once per ray
		float raFix = cos(pa - ra); // fisheye
		float cosRa = cos(ra);
		float sinRa = sin(ra);

		for(y = lineO + lineH; y < 640; y++)
		{
    			float dy = y - 320.0; 
    			float weight = (320.0) / (dy * raFix);
    			float tx = px + cosRa * weight;
    			float ty = py + sinRa * weight;

    			int mapPos = ((int)(ty/64.0) * mapX) + (int)(tx/64.0);
    			int pixelX = (int)(tx) & 63;
    			int pixelY = (int)(ty) & 63;

    														// --- DRAW FLOOR ---
    		
		if(mapPos < 0) mapPos = 0;
		if(mapPos >= mapX*mapY)mapPos = mapX*mapY-1;
		int floorIdx = currentMapF[mapPos] - 1;
		if(floorIdx < 0) floorIdx = 0;
		int floorTex = floorIdx * 4096; // 64*64 
		//if(mapPos >= 400) mapPos = 399;
    		float cF = T_1[pixelY * 64 + pixelX + floorTex] * 0.7;
    		glColor3f(0.5, 0.5, 0.5); 
    		glPointSize(16); glBegin(GL_POINTS); glVertex2i(r*16, y); glEnd();

    		if(mapPos < 0) mapPos = 0;									// --- DRAW CEILING ---
    		int ceilIdx = currentMapC[mapPos] - 1;
		if(ceilIdx < 0) ceilIdx = 0;
		int ceilTex = ceilIdx * 4096;
    		if(mapPos >= mapX*mapY)mapPos = mapX*mapY-1;
		//if(mapPos >= 400) mapPos = 399;
    		float cC = T_1[pixelY * 64 + pixelX + ceilTex] * 0.7;
    		glColor3f(0.3, 0.3, 0.3);
   		glPointSize(16); glBegin(GL_POINTS); glVertex2i(r*16, 639-y); glEnd();
}
		
		
		
		
		ra+=DR;
		if(ra<0){ra+= 2*PI;}
		if(ra>2*PI){ra-=2*PI;}
	}	
	
	
	
}



//                                                                                     SPRITES



void sortSprites(Sprite* sprites, int count) {
    int i, j;
    for(i = 0; i < count - 1; i++) {
        for(j = 0; j < count - i - 1; j++) {
            if(sprites[j].dist < sprites[j+1].dist) {
                Sprite temp = sprites[j];
                sprites[j] = sprites[j+1];
                sprites[j+1] = temp;
            }
        }
    }
}

void drawSprite(float sx, float sy, int textureID)
{
    float dx = sx - px;
    float dy = sy - py;
    float spriteDist = sqrt(dx * dx + dy * dy);
    float spriteAngle = atan2(dy, dx);
    float angleDiff = spriteAngle - pa;

    while (angleDiff < -PI) angleDiff += 2 * PI;
    while (angleDiff >  PI) angleDiff -= 2 * PI;

    //Only draw if its in front of player
    if (cos(angleDiff) <= 0.2) return;

    float correctedDist = spriteDist * cos(angleDiff);
    float spriteH = (mapS * 640.0) / correctedDist;
    float spriteTop    = 320.0 - spriteH / 2.0;
    float spriteBottom = 320.0 + spriteH / 2.0;

    float rayIndex = (angleDiff + (30.0 * DR)) / DR;
    //spriteW in rays
    float halfW = spriteH / 2.0 / 16.0;       //each ray is 16px wide

    int startRay = (int)(rayIndex - halfW);
    int endRay   = (int)(rayIndex + halfW);
    int totalRays = endRay - startRay + 1;

    int r;
    for (r = startRay; r <= endRay; r++)
    {
        if (r < 0 || r >= 105) continue;
        if (correctedDist >= depthBuffer[r]) continue; // behind a wall
        
        //how far 
        float u = (float)(r - startRay) / (float)(totalRays);
        int tx = (int)(u * 32);   // 32 (width)
        if (tx < 0)  tx = 0;
        if (tx > 31) tx = 31;

        glPointSize(16);
        glBegin(GL_POINTS);
        int y;
        for (y = (int)spriteTop; y < (int)spriteBottom; y++)
        {
            if (y < 0 || y >= 640) continue;

            
            float v = (float)(y - spriteTop) / spriteH;
            int ty = (int)(v * 32);
            if (ty < 0)  ty = 0;
            if (ty > 31) ty = 31;

            int pixel = ((textureID*32 + ty)*32+tx)*3;
            int red   = S_1[pixel + 0];
            int green = S_1[pixel + 1];
            int blue  = S_1[pixel + 2];

            if (red == 255 && green == 0 && blue == 255) continue; //The purple wont be rendered, very oldschool i know B)

            glColor3ub(red, green, blue);
            glVertex2i(r * 16, y);
            depthBuffer[r] = correctedDist;  //fixes the see through sprites
        }
        glEnd();
    }
}

int spriteBlocking(float newX, float newY) {
    int i;
    for (i = 0; i < currentSpriteCount; i++) {
        if(!currentSprites[i].active) continue;
        if(currentSprites[i].solid == true ) continue; //if it isnt solid then skip this function
        float sx = currentSprites[i].x * 64.0;
        float sy = currentSprites[i].y * 64.0;
        float dx = newX - sx;
        float dy = newY - sy;
        float dist = sqrt(dx*dx + dy*dy);
        if (dist < 30.0) return 1;  // 30px radius, works nicely but can be adjudted if you want to become one with the wall...
    }
    return 0;
}
   
   
   
   
   
//                                                                                WIPING SCREEN
 

int meltOffsets[960];
int isMelting = 0;
int *meltBuffer = NULL; //store the screenshot

void startMelt() {
	int i;
    for(i=0; i<960; i++) {
        // random delay/offset
        meltOffsets[i] = -(rand() % 100); 
    }
    isMelting = 1;
}

void drawMelt() {
    int x, y;
    glBegin(GL_POINTS); // Set point size to 1 before the loop
    for(x=0; x<960; x++) {
        if (meltOffsets[x] >= 640) continue; 

        for(y=0; y<640; y++) {
            int targetY = y + meltOffsets[x];
            if(targetY >= 0 && targetY < 640) {
                int pixel = (y * 960 + x) * 3;
                glColor3ub(meltBuffer[pixel], meltBuffer[pixel+1], meltBuffer[pixel+2]);
                glVertex2i(x, targetY);
            }
        }
        // the speed of the wiping, i cant do it i just cant
        meltOffsets[x] += (rand() % 5) + 5; 
    }
    glEnd();
}

/*
void captureScreen() {
    if(meltBuffer == NULL) {
        meltBuffer = malloc(960 * 640 * 3 * sizeof(int));
    }
    // This reads the actual rendered screen into your buffer
    glReadPixels(0, 0, 960, 640, GL_RGB, GL_UNSIGNED_BYTE, meltBuffer);
}
*/

void captureScreen() {
    if(meltBuffer == NULL) {
        meltBuffer = malloc(960 * 640 * 3 * sizeof(int));
    }
    
    int i;
    //copy
    for(i = 0; i < 960 * 640 * 3; i++) {
        meltBuffer[i] = Maintitle[i];
    }
}











//                                                                       BUTTONS INITIALIZE



int gameState = 0;
int timer = 0;

void startGame()  { gameState = 2;}
void quitGame()   { exit(0);      }
void openOptions(){}

void triggerMelt() {
    captureScreen();
    startMelt();
    gameState = 3; // Change to the melting state
}
MenuButton buttons[3];

void initButtons(){
	//Start
	buttons[0] = (MenuButton){400, 200, 160, 70, press, hold, 0, triggerMelt};
	
	buttons[1] = (MenuButton){400, 300, 160, 70, press, hold, 0, openOptions};
	
	//buttons[1] = (MenuButton){400, 300, 160, 70, opt_press, opt_hold, 0, openOptions};
	
	//buttons[2] = (MenuButton){400, 400, 160, 70, quit_press, quit_hold, 0, quitGame};
	
	buttons[2] = (MenuButton){400, 400, 160, 70, press, hold, 0, quitGame};
}


void ButtonDown(unsigned char key, int x, int y){
	if (key =='a') { Keys.a=1;}
	if (key =='d') { Keys.d=1;}
	if (key =='w') { Keys.w=1;}
	if (key =='s') { Keys.s=1;}
	if (key =='e') {            //Interact with doors
		int xo = 0; if(pdx<0) {xo=-25;} else{ xo=25;}
		int yo = 0; if(pdy<0) {yo=-25;} else{ yo=25;}
		
		
		int ipx=px/64.0;
		int ipx_add_xo = (px+xo)/64.0; 
	
		int ipy=py/64.0;
		int ipy_add_yo = (py+yo)/64.0;
		
		if(currentMapW[ipy_add_yo*mapX+ipx_add_xo]==4) {
			currentMapW[ipy_add_yo*mapX+ipx_add_xo] = 0;
		}
	}
	if (key == 'p'){saveGame();}
	if (key == 'l'){loadGame();}
	
	
	/*if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		
		int fixedY = 640 - y;
		
		if(gameState == 1) {
			if(x > 400 && x < 560 && y > 300 && y < 350){
				
				gameState = 2;
			}
		}
	}*/
	
	glutPostRedisplay();
}

void ButtonUp(unsigned char key, int x, int y){
	if (key =='a') { Keys.a=0;}
	if (key =='d') { Keys.d=0;}
	if (key =='w') { Keys.w=0;}
	if (key =='s') { Keys.s=0;}
	glutPostRedisplay();
}

int mouseState = 1;
int mouseX;
int mouseY;

void mouseClick(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON) {
		mouseState = state;                     //update global state
		mouseX = x;
		mouseY = y;
		int i;
		printf("Mouse Click: x=%d y=%d\n", x, y);
		
		if(state == GLUT_UP && gameState == 1){
			for(i=0;i<3;i++){
				if(x > buttons[i].x && x < buttons[i].x + buttons[i].w 
				&& y > buttons[i].y && y < buttons[i].y + buttons[i].h){
					buttons[i].action();
				}
			}
		}
		
	}
glutPostRedisplay();
}

void mousePassive(int x, int y){
	mouseX = x;
	mouseY = y;
	glutPostRedisplay();
}

void drawButtonTexture(int x, int y, int *texture){
	glPointSize(1);
	glBegin(GL_POINTS);
	int tx;
	int ty;
	for(ty=0;ty<70;ty++){
		for(tx=0;tx<160;tx++){
			int pixel = (ty *160 + tx)*3;
			glColor3ub(texture[pixel], texture[pixel+1], texture[pixel+2]);
			glVertex2i(x + tx, y + ty);
		}
	}
	glEnd();
}




                                               // I CANT FUCKING DO THIS OH MY GOD FUCK MY LIFE WHY CANT I DO IT I TRIED  EVERYTHING A IFFUCK IM GONNA KILL MYSELF












void screen(int v) {
	int x,y;
	int *T;
	if(v==1) {T=Maintitle;} //Get Psyched!
	if(v==2) {T=end;} //losing screen
	//if(v==3) {}
	for(y=0;y<640;y++){
		for(x=0;x<960;x++){
			int pixel =(y*960+x)*3;
			int red   = T[pixel+0];
			int green = T[pixel+1];
			int blue  = T[pixel+2];
			glPointSize(1); glColor3ub(red,green,blue); glBegin(GL_POINTS); glVertex2i(x,y); glEnd();
			
		}
	}
}

void init()
{
	glClearColor(0.3,0.3,0.3,0);
	
	px=300;
	py=300;
	pdx=cos(pa)*5;
	pdy=sin(pa)*5;
}




void drawButton(float x, float y, float w, float h, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2i(x, y);         // Top Left
    glVertex2i(x + w, y);     // Top Right
    glVertex2i(x + w, y + h); // Bottom Right
    glVertex2i(x, y + h);     // Bottom Left
    glEnd();
}


float frame1,frame2,fps; 








//                                                                               SAVE-LOAD SYSTEM

int currentLevel = 0;
void saveGame() {
    FILE *f = fopen("save.dat", "w");
    if (f == NULL) {
        printf("Error: Could not create save file!\n");
        return;
    }
    fprintf(f, "%d %f %f %f", currentLevel, px, py, pa);
    fclose(f);
    printf("Game Saved.\n");
}

void loadGame() {
    FILE *f = fopen("save.dat", "r");
    if (f == NULL) {
        printf("No save file found.\n");
        return;
    }
    float tempX, tempY, tempA;
    int tempL;

    if (fscanf(f, "%d %f %f %f", &tempL, &tempX, &tempY, &tempA) == 4) {
        currentLevel = tempL;
        px = tempX;
        py = tempY;
        pa = tempA;
        
        // uppdate the pointers to the correct level data
        loadLevel(currentLevel);
        
        //direction vectors
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
        
        gameState = 2; // gameplay
    }
    fclose(f);
    printf("Game Loaded.\n");
}












void display()
{
	int i;
	for(i = 0; i < currentSpriteCount; i++) {
    		float dx = currentSprites[i].x - px;
    		float dy = currentSprites[i].y - py;
    		currentSprites[i].dist = (dx * dx) + (dy * dy); 
	}
	
	
	
	int mapX_pos = (int)px >> 6;
	int mapY_pos = (int)py >> 6;

	int currentLevel = 0;
	if(currentMapW[mapY_pos * mapX + mapX_pos] == 2) {
    	currentLevel++; 
    	loadLevel(currentLevel);                             //updates the pointers in maps.c
    
    
    	px = 300; 
    	py = 300; 
    
    
    	triggerMelt(); 
}
	
	if(currentMapW[mapY_pos * mapX + mapX_pos] == 2) {
    		currentLevel++; 
    		if(currentLevel > 2) {
        			gameState = 4;                                  //intermission from doom
    		} else {
        			loadLevel(currentLevel);
        			px = 300;                                    //reset player position for new level
        			py = 300;
        			//saveGame();  No auto-save because fuck you!
        			triggerMelt(); 
    		}
}
	
	//frames per second(FPS)
	frame2=glutGet(GLUT_ELAPSED_TIME);
	fps = (frame2-frame1);
	frame1 = glutGet(GLUT_ELAPSED_TIME);
	glClear (GL_COLOR_BUFFER_BIT);
	
	//Frame time cap, just in case
	if(fps > 100) {
		fps = 100;
	}
	
	//gameState
	
	if(gameState == 0){                  					//init game
		init();
		timer = 0;
		gameState = 1;
	};
			                					//start the game
	if(gameState == 1){
		screen(1);
		// int buttonX = 400, buttonY = 300, buttonW = 160, buttonH = 70;// x position, y position, width of the button, height, and 3f colors
		
		int i;
		for(i=0;i<3;i++){
			if(mouseX > buttons[i].x && mouseX < buttons[i].x + buttons[i].w
			&& mouseY > buttons[i].y && mouseY < buttons[i].y + buttons[i].h){
			
				if(mouseState == GLUT_DOWN){
					drawButtonTexture(buttons[i].x, buttons[i].y, buttons[i].tex_hold);
				}
				else {
					drawButtonTexture(buttons[i].x, buttons[i].y, buttons[i].tex_normal);
				}	
			}
			else {
				drawButtonTexture(buttons[i].x, buttons[i].y, buttons[i].tex_normal);
			}		
		}

		/*
		timer+=1*fps;
		if(timer>3000){
			timer = 0; 
			gameState = 2;
		}
		*/
	}
	
	if(gameState == 3){          							//this is the melting state
		drawRays3D();
		drawMelt();
		
		int finished = 1;
		int i;
		for(i=0;i<960;i++){
			if(meltOffsets[i]<640){
				finished = 0;
				break;
			}
		}
		
		if(finished){
			gameState = 2;
		}
	}
	
	if(gameState == 2) {         								//gaemplay state          
		
			
	// || Buttons ||
	//The sensitivity is a bit of a mess but works well
	if(Keys.a==1) { pa-=0.003*fps; if(pa<   0){ pa+=2*PI;} pdx=cos(pa) *5; pdy=sin(pa)*5;}
	if(Keys.d==1) { pa+=0.003*fps; if(pa>2*PI){ pa-=2*PI;} pdx=cos(pa) *5; pdy=sin(pa)*5;}
	
	int xo = 0; if(pdx<0) {xo=-20;} else{ xo=20;}
	int yo = 0; if(pdy<0) {yo=-20;} else{ yo=20;}
	
	int ipx=px/64.0;
	int ipx_add_xo = (px+xo)/64.0; 
	int ipx_sub_xo = (px-xo)/64.0;
	
	int ipy=py/64.0;
	int ipy_add_yo = (py+yo)/64.0;
	int ipy_sub_yo = (py-yo)/64.0;
	
	
	
	if(Keys.w==1){ 
		float newX = px + pdx*0.06*fps;
		float newY = py + pdy*0.06*fps;
		if(currentMapW[ipy*mapX + ipx_add_xo] == 0 && !spriteBlocking(newX, py)) { px = newX; }
    		if(currentMapW[ipy_add_yo*mapX + ipx] == 0 && !spriteBlocking(px, newY)) { py = newY; }
		//if(currentMapW[ipy*mapX        + ipx_add_xo] == 0) { px+=pdx*0.06*fps;}
		//if(currentMapW[ipy_add_yo*mapX + ipx       ] == 0) { py+=pdy*0.06*fps;}
	}
	
	if(Keys.s==1){ 
		float newX = px - pdx*0.06*fps;
		float newY = py - pdy*0.06*fps;
		if(currentMapW[ipy*mapX + ipx_sub_xo] == 0 && !spriteBlocking(newX, py)) { px = newX; }
    		if(currentMapW[ipy_sub_yo*mapX + ipx] == 0 && !spriteBlocking(px, newY)) { py = newY; }
		//if(currentMapW[ipy*mapX        + ipx_sub_xo] == 0) { px-=pdx*0.02*fps;}
		//if(currentMapW[ipy_sub_yo*mapX + ipx       ] == 0) { py-=pdy*0.02*fps;}
	}
	
//	drawMap2D();
//	drawPlayer();
	drawRays3D();
	sortSprites(currentSprites, currentSpriteCount);
int i;
for (i = 0; i < currentSpriteCount; i++) {
    if (currentSprites[i].active) {
        drawSprite(currentSprites[i].x * 64.0,   // convert map coords to world coords
                   currentSprites[i].y * 64.0,
                   currentSprites[i].textureID);
    }
}
	}
	
	
	
	glutPostRedisplay();
	glutSwapBuffers();

	
}




void resize(int w, int h) {
	glutReshapeWindow(960,640);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(960, 640);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)/2-960/2, glutGet(GLUT_SCREEN_HEIGHT)/2-640/2);
	glutCreateWindow("Wolfenstein");
	gluOrtho2D(0,960,640,0);
	init();
	initButtons();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(ButtonDown);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(mousePassive);
	glutKeyboardUpFunc(ButtonUp);
	glutMainLoop();
}

