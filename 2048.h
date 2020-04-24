/*
 * 2048_utils.h
 * Written in C using ncurses Library
 *
 * Author: Cal Fisher
 * Last Updated: 6/15/2015
*/

// Windows
// #include <ncurses/ncurses.h>
// MacOS
#include <curses.h>

// #define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define uchar int
#define boolean int
#define TRUE 1
#define FALSE 0
#define ENTER 10
#define ESC 27

//For now, assume it must be a square
#define NUM_TILES 4
#define TILE_WIDTH 16
#define TILE_HEIGHT 10
#define CONTAINER_WIDTH (NUM_TILES*TILE_WIDTH)+4
#define CONTAINER_HEIGHT (NUM_TILES*TILE_HEIGHT)+2
#define WIN_NUMBER 2048

#define EMPTY -1
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4

void init_ncurses();
void init_grid(int grid[NUM_TILES][NUM_TILES]);
int returnColor(int grid[NUM_TILES][NUM_TILES], int m, int n);

void createRandomTile(int grid[NUM_TILES][NUM_TILES]);
void drawTile(int grid[NUM_TILES][NUM_TILES], int i, int j);
void drawContainer(int a, int b, int width, int height);
void updateGrid(int grid[NUM_TILES][NUM_TILES], boolean hasMoved);
void updateTile(int grid[NUM_TILES][NUM_TILES], int a, int b);
void updateAllTiles(int grid[NUM_TILES][NUM_TILES]);
void moveTilesUpDown(int value, int grid[NUM_TILES][NUM_TILES], boolean *hasMoved);
void moveTilesLeftRight(int value, int grid[NUM_TILES][NUM_TILES], boolean *hasMoved);

boolean won(int grid[NUM_TILES][NUM_TILES]);
boolean lost(int grid[NUM_TILES][NUM_TILES]);
