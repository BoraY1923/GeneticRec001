#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "maps.h"

#include "Textures/T_1.h"
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

int mapX=8,mapY=8,mapS=64;


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
	
	for (r=0;r<105;r++) //60 rays, value can be increased or decreased !!!!!!!!!
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
		while(dof<8) //I forgot what dof means, distance of focus? 
		{
			mx=(int)(rx)>>6;
			my=(int)(ry)>>6;
			mp=my*mapX+mx;
			if(mp>0 && mp<mapX*mapY && currentMapW[mp]>0){ hmt=currentMapW[mp]-1; hx=rx; hy=ry; disH=dist(px,py,hx,hy,ra); dof=8;} //hit vall.
			else{ rx+=xo; ry+= yo; dof+=1;}
		}

		//VERTICAL RAYS
		float disV=1000000, vx=px,vy=py;
		dof=0;
		float nTan=-tan(ra);
		if(ra>P2 && ra<P3){ rx=(((int)px>>6)<<6)-0.0001; ry=(px-rx)*nTan+py; xo=-64; yo=-xo*nTan; } //looking up
		if(ra<P2 || ra>P3){ rx=(((int)px>>6)<<6)+64    ; ry=(px-rx)*nTan+py; xo= 64; yo=-xo*nTan; }
		if (ra==0 || ra==PI) { rx=px; ry=py; dof=8;}
		while(dof<8)
		{
			mx=(int)(rx)>>6;
			my=(int)(ry)>>6;
			mp=my*mapX+mx;
			if(mp>0 && mp<mapX*mapY && currentMapW[mp]>0){ vmt=currentMapW[mp]-1; vx=rx; vy=ry; disV=dist(px,py,vx,vy,ra); dof=8;} //hit wall.
			else{ rx+=xo; ry+= yo; dof+=1;}
		}
		float shade=1;
		glColor3f(0,0.8,0);
		if(disV<disH){  hmt=vmt; shade=0.6; rx=vx; ry=vy; disT=disV; glColor3f(0.9,0,0);}
		if(disH<disV){rx=hx; ry=hy;disT=disH; glColor3f(0.6,0,0);}
		
/* This draws the rays on the 2D map	
	
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex2i(px,py);
		glVertex2i(rx,ry);
		glEnd();
*/	
		//--------3D WALLS--------
		
		float ca=pa-ra; if(ra<0){ra+=2*PI;} if(ra>2*PI){ra-=2*PI;} disT=disT*cos(ca);
		float lineH=(mapS*640)/disT;
		float ty_step=32.0/(float)lineH;
		float ty_off=0;
		if(lineH>640){ ty_off=(lineH-640)/2.0; lineH=640;}
		float lineO=320-lineH/2;  //line Offset
		
		int y;
		float ty=ty_off*ty_step; //+hmt*32;
		float tx;
  		if(shade==1){ tx=(int)(rx/2.0)%32; if(ra>180){ tx=31-tx;}}  
  		else        { tx=(int)(ry/2.0)%32; if(ra>90 && ra<270){ tx=31-tx;}}
		for(y=0;y<lineH;y++){
		
		/*	
			float c = All_Textures[(int)(ty)*32 + (int)(tx)]*shade;
			if(hmt==0) {glColor3f(c     ,c/2.0,c/2.0);}
			if(hmt==1) {glColor3f(c     ,c    ,c/2.0);}
			if(hmt==2) {glColor3f(c/2.0 ,c/2.0,c    );}
			if(hmt==3) {glColor3f(c/2.0 ,c    ,c/2.0);}
			if(hmt==4) {glColor3f(c,c,c);}
			
			glPointSize(8);
			glBegin(GL_POINTS);
			glVertex2i(r*8+530,y+lineO);
			glEnd();
		*/	
			int pixel =((int)ty*32+(int)tx)*3;
			int red   = T_1[pixel+0]*shade;
			int green = T_1[pixel+1]*shade;
			int blue  = T_1[pixel+2]*shade;
			
			glPointSize(16); glColor3ub(red,green,blue); glBegin(GL_POINTS); glVertex2i(r*16,y+lineO); glEnd();
			ty+=ty_step;
		}

		          											//----------DRAW FLOORS currentMapF & CEILING mapC--------
		//once per ray
		float raFix = cos(pa - ra); // fisheye
		float cosRa = cos(ra);
		float sinRa = sin(ra);

		for(y = lineO + lineH; y < 640; y++)
		{
    			float dy = y - 324.0; 
    			float weight = (320.0 * 32.0) / (dy * raFix);
    			float tx = px/2.0 + cosRa * weight;
    			float ty = py/2.0 + sinRa * weight;

    			int mapPos = ((int)(ty/32.0) * mapX) + (int)(tx/32.0);
    			int pixelX = (int)(tx) & 31;
    			int pixelY = (int)(ty) & 31;

    														// --- DRAW FLOOR ---
    		int floorTex = currentMapF[mapPos] * 1024; // 32*32 = 1024
    		float cF = All_Textures[pixelY * 32 + pixelX + floorTex] * 0.7;
    		glColor3f(cF/1.3, cF/1.3, cF); 
    		glPointSize(16); glBegin(GL_POINTS); glVertex2i(r*16, y); glEnd();

    														// --- DRAW CEILING ---
    		int ceilTex = currentMapC[mapPos] * 1024;
    		float cC = All_Textures[pixelY * 32 + pixelX + ceilTex] * 0.7;
    		glColor3f(cC/2.0, cC/1.2, cC/2.0);
   		glPointSize(16); glBegin(GL_POINTS); glVertex2i(r*16, 639-y); glEnd();
}
		
		
		
		
		ra+=DR;
		if(ra<0){ra+= 2*PI;}
		if(ra>2*PI){ra-=2*PI;}
	}	
	
	
	
}




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
    // Note: glReadPixels uses unsigned char, so you might need to adjust meltBuffer type
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
        			saveGame();                                 // Auto-save, you are welcome... Ill get rid of this actually
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
	
	if(gameState == 0){                  //init game
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
	
	if(gameState == 3){          //this is the melting state
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
	
	if(gameState == 2) {         //gaemplay state          
		
			
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
		if(currentMapW[ipy*mapX        + ipx_add_xo] == 0) { px+=pdx*0.06*fps;}
		if(currentMapW[ipy_add_yo*mapX + ipx       ] == 0) { py+=pdy*0.06*fps;}
	}
	
	if(Keys.s==1){ 
		if(currentMapW[ipy*mapX        + ipx_sub_xo] == 0) { px-=pdx*0.02*fps;}
		if(currentMapW[ipy_sub_yo*mapX + ipx       ] == 0) { py-=pdy*0.02*fps;}
	}
	
//	drawMap2D();
//	drawPlayer();
	drawRays3D();

	
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
