/*
 * 2048_utils.h
 * Written in C using ncurses Library
 *
 * Author: Cal Fisher
 * Last Updated: 6/15/2015
*/

// ON WINDOWS (Unix-Like Terminal environment that can compile and run C programs. Must also support ncurses.):
// *NOTE: a.) Windows must be running a Unix-like command-line environment.
//        b.) It must be able to compile and run C.
//        c.) It must support the ncurses and Math library.
// One such environment is Cygwin. Download it here: http://cygwin.com/install.html
// On install, be sure to include the ncurses and math packages.
//
// 1. Compile in Cygwin Terminal using the following command:
// gcc -o 2048 2048.c 2048_utils.c -lncurses
// *Note: In some cases, you will need to link the Math library as well
//        Cygwin normally does this automatically;
//        however, if it does not, compile using the following command:
//        gcc -o 2048 2048.c 2048_utils.c -lm -lncurses
// 2. Run the program using the following command:
// ./2048

// ON MAC OS X:
// 1. Comment out this line:
#include <ncurses/ncurses.h>
// 2. Uncomment this line:
//#include <curses.h>
// 3. Compile in Terminal using the following command:
// gcc -o 2048 2048.c 2048_utils.cc -lcurses
// 4. Run the program using the following command:
// ./2048

#include <stdio.h>
#include <math.h>
#include <string.h>


#define uchar int
#define boolean int
#define TRUE 1
#define FALSE 0
#define ENTER 10
#define ESC 17

#define CONTAINER_WIDTH 71
#define CONTAINER_HEIGHT 45
#define TILE_WIDTH 16
#define TILE_HEIGHT 10

#define EMPTY -1
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4


void init_ncurses();
void init_grid(int grid[4][4]);
int returnColor(int grid[4][4], int m, int n);

void createRandomTile(int grid[4][4]);
void drawTile(int grid[4][4], int i, int j);
void drawContainer(int a, int b, int width, int height);
void updateGrid(int grid[4][4], boolean hasMoved);
void updateTile(int grid[4][4], int a, int b);
void updateAllTiles(int grid[4][4]);
void moveTilesUpDown(int value, int grid[4][4], boolean *hasMoved);
void moveTilesLeftRight(int value, int grid[4][4], boolean *hasMoved);

int won(int grid[4][4]);
void wonAnimation(int grid[4][4], int i, int j);
