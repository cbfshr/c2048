/*
 * 2048_utils.h
 * Written in C using ncurses Library
 *
 * Author: Cal Fisher
 * Last Updated: 6/13/2015
*/

#define CONTAINER_WIDTH 71
#define CONTAINER_HEIGHT 45
#define TILE_WIDTH 16
#define TILE_HEIGHT 10
#define EMPTY -1
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4

#define boolean int
#define TRUE 1
#define FALSE 0

int won(int grid[4][4]);
void wonAnimation(int grid[4][4], int i, int j);

