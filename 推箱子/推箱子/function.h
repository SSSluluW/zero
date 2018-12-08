#include<stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<string.h>

#define maps_num 35

typedef struct Map {

	char map[50][50];
	int level;
	int h;

	int x;
	int y;

	int aim_count;
	int aimx[50];
	int aimy[50];

}Map;
void init();
void mainloop();
int gameloop(int level);
Map* LoadMap(int level);

