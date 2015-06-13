/*
 * 2048, Written in C using ncurses Library
 *
 * Author: Cal Fisher
 * Last Updated: 10/18/2014
*/

// ON WINDOWS (Unix-Like Terminal environment that can compile and run C programs. Must also support ncurses.):
// *NOTE: a.) Windows must be running a Unix-like command-line environment.
//        b.) It must be able to compile and run C.
//        c.) It must support the ncurses and Math library.
// One such environment is Cygwin. Download it here: http://cygwin.com/install.html
// On install, be sure to install the ncurses and math packages.
//
// 1. Compile in Cygwin Terminal using the following command:
// gcc -o filename filename.c -lncurses
// *Note: In some cases, you will need to link the Math library as well
//        Cygwin normally does this automatically;
//        however, if it does not, compile using the following command:
//        gcc -o filename filename.c -lm -lncurses
// 2. Run the program using the following command:
// ./filename

// ON MAC OS X:
// 1. Comment out this line:
#include <ncurses/ncurses.h>
// 2. Uncomment this line:
//#include <curses.h>
// 3. Compile in Terminal using the following command:
// gcc -o filename filename.c -lcurses
// 4. Run the program using the following command:
// ./filename


#include <stdio.h>
#include <math.h>
#include <string.h>
#include "tfe_utils.h"


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

void createRandomTile(int grid[4][4]);
void drawTile(int grid[4][4], int i, int j);
void drawContainer(int a, int b, int width, int height);
void updateTile(int grid[4][4], int a, int b);
void updateAllTiles(int grid[4][4]);
void moveTilesUpDown(int value, int grid[4][4], int *f, int *k, int *alreadyCombined, int *updated, int *hasMoved);
void moveTilesLeftRight(int value, int grid[4][4], int *f, int *k, int *alreadyCombined, int *updated, int *hasMoved);

int won(int grid[4][4]);

int returnColor(int grid[4][4], int m, int n){
	int i;
	if (grid[m][n] > 0) {
		for(i = 1; (log10(grid[m][n])/log10(2) != i) && (i < 15); i++);	//14:8192 is highest value with color
	}
	
	if (i != 14) {
		return i + 1;
	}
	
	return 1;
}


int main(int argc, char* argv[]) {
	int a, b ,i, j, k;
	int alreadyCombined, f;
	int keyPressed = 0;
	int hasMoved = 0;
	int updated = 0;
	
	srand(time(NULL));
	
	init_ncurses();	// Initialize ncurses, keypad (no echo), color, and color pairs
	
	int grid[4][4];
	init_grid(grid);
	
	
	createRandomTile(grid);
	createRandomTile(grid);
	do {		
		keyPressed = getch();
		
		if(keyPressed == KEY_LEFT) {
			moveTilesLeftRight(LEFT, grid, &f, &k, &alreadyCombined, &updated, &hasMoved);
		} else if(keyPressed == KEY_UP) {
			moveTilesUpDown(UP, grid, &f, &k, &alreadyCombined, &updated, &hasMoved);
		} else if(keyPressed == KEY_RIGHT) {
			moveTilesLeftRight(RIGHT, grid, &f, &k, &alreadyCombined, &updated, &hasMoved);
		} else if(keyPressed == KEY_DOWN) {
			moveTilesUpDown(DOWN, grid, &f, &k, &alreadyCombined, &updated, &hasMoved);
		}
		
		
		//---UPDATE GRID
		if(hasMoved) {
			updateAllTiles(grid);
			createRandomTile(grid);	//Places a new tile on the grid
		}
		//--------------------------------[
	
		hasMoved = 0;	
		refresh();
	} while(!won(grid));
	usleep(500000);
	
	
/*---END---*/
	//erase();
	mvprintw(25,35,"You won!");
	refresh();
	usleep(1000000);
	
	int exitKey = 0;
	do {
		mvprintw(26,17,"Press [Enter] to return to the main menu.");
		mvprintw(27,22,"Press [Esc] to exit the game.");
		refresh();
		exitKey = getch();
	} while(exitKey != 10 && exitKey != 27);	//Enter or Escape
	
	
	usleep(100000);
	erase();
	endwin();
/*---END---*/
	
	return 0;
}

















/*--------FUNCTIONS--------*/

void createRandomTile(int grid[4][4]) {
	int validPlacement = 0, xTileCoordinate = 0, yTileCoordinate = 0;
	while(!validPlacement) {
		xTileCoordinate = rand() % 4;	// Gets an x coordinate between 0 and 3
		yTileCoordinate = rand() % 4;	// Gets a y coordinate between 0 and 3
		if(grid[xTileCoordinate][yTileCoordinate] == EMPTY)	//Coordinates must be an empty tile
			validPlacement = 1;
	}
	
	grid[xTileCoordinate][yTileCoordinate] = ((rand() % 2) + 1) * 2;	//2 or 4
	updateTile(grid, xTileCoordinate, yTileCoordinate);
	refresh();
}

void updateAllTiles(int grid[4][4]) {
	int x, y;
	for(x = 0; x < 4; x++) {
		for(y = 0; y < 4; y++) {
			updateTile(grid, x, y);
		}
	}
}

void updateTile(int grid[4][4], int m, int n) {
	//color of the text/border will depend on the current number.
	int c = 1;
	int i = 14;
	
	if (grid[m][n] > 0) {
		for(i = 1; (log10(grid[m][n])/log10(2) != i) && (i < 15); i++);	//14:8192 is highest value with color
	}
	
	if (i != 14) {
		c = i + 1;
	}
	
	attron(COLOR_PAIR(c));
	drawTile(grid, m, n);
	attroff(COLOR_PAIR(c));
}

void drawTile(int grid[4][4], int i, int j) {
	int actualXCoordinate = (i * TILE_WIDTH) + 2 + i + 1;
	int actualYCoordinate = (j * TILE_HEIGHT) + 2 + j;
	
	drawContainer(actualXCoordinate, actualYCoordinate, TILE_WIDTH, TILE_HEIGHT);
	
	if(grid[i][j] > 0)
		mvprintw((actualYCoordinate + 5), (actualXCoordinate + 6), "%3d", grid[i][j]);
}

void drawContainer(int a, int b, int width, int height) {
	int i = a;
	int j = b;
	
	// [ Upper Left Corner to Upper Right Corner )
	mvaddch(j, i++, ACS_ULCORNER);
	for( ; i < width + a; i++) {
		mvaddch(j,i,ACS_HLINE);
	}
	
	// [ Upper Right Corner to Lower Right Corner )
	mvaddch(j++, i, ACS_URCORNER);
	for( ; j < height + b; j++) {
		mvaddch(j, i, ACS_VLINE);
	}
	
	// [ Lower Right Corner to Lower Left Corner )
	mvaddch(j, i--, ACS_LRCORNER);
	for( ; i > a; i--) {
		mvaddch(j, i, ACS_HLINE);
	}
	
	// [ Lower Left Corner to Upper Left Corner )
	mvaddch(j--,i,ACS_LLCORNER);
	for( ; j > b; j--) {
		mvaddch(j,i,ACS_VLINE);
	}
	
	// Fill in center of tile with color
	for(i = a + 1; i < a + width; i++) {
		for(j = b + 1; j < b + height; j++) {
			mvaddch(j, i, ' ');
		}
	}
}

void init_ncurses() {
	initscr();
	cbreak();
	keypad(stdscr, true);
	noecho();
	refresh();
	start_color();
	
	init_pair(1, COLOR_WHITE, COLOR_BLACK);		//Other
	init_pair(2, COLOR_WHITE, COLOR_RED);		//2
	init_pair(3, COLOR_WHITE, COLOR_GREEN);		//4
	init_pair(4, COLOR_WHITE, COLOR_BLUE);		//8
	init_pair(5, COLOR_WHITE, COLOR_MAGENTA);	//16
	init_pair(6, COLOR_BLACK, COLOR_CYAN);		//32
	init_pair(7, COLOR_BLACK, COLOR_YELLOW);	//64
	init_pair(8, COLOR_BLACK, COLOR_WHITE);		//128
	init_pair(9, COLOR_RED, COLOR_WHITE);		//256
	init_pair(10, COLOR_GREEN, COLOR_WHITE);	//512
	init_pair(11, COLOR_BLUE, COLOR_WHITE);		//1024
	init_pair(12, COLOR_MAGENTA, COLOR_WHITE);	//2048
	init_pair(13, COLOR_CYAN, COLOR_WHITE);		//4096
	init_pair(14, COLOR_YELLOW, COLOR_WHITE);	//8192
}

void init_grid(int grid[4][4]) {
	int i, j;

	for(i = 0; i < 4; i++) {
		for(j =0; j < 4; j++) {
			grid[i][j] = EMPTY;
		}
	}
	
	drawContainer(1, 1, CONTAINER_WIDTH, CONTAINER_HEIGHT);	//Draws container
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			drawTile(grid, i, j);	// Draws 16 tiles within container
		}
	}
	refresh();
}

void moveTilesLeftRight(int value, int grid[4][4], int *f, int *k, int *alreadyCombined, int *updated, int *hasMoved) {
	int i, j;
	if (value == LEFT) {
		value = 1;
	} else if (value == RIGHT) {
		value = -1;
	} else {
		return;
	}
	
	for(j = 0; j < 4; j++) {
		if (value == 1) {
			i = 1;
			*f = -1;
		} else if (value == -1) {
			i = 2;
			*f = 4;
		}
		
		for( ; (value == -1 && (i > -1)) || (value == 1 && (i < 4)); i += value) {
			(*k) = i;
			while(((value == 1) && ((*k) > (*f) + value)) || ((value == -1) && ((*k) < (*f) + value))) {
				if(grid[*k][j] > 0) {
					if(grid[(*k)-value][j] == EMPTY) {
						grid[(*k)-value][j] = grid[*k][j];
						grid[(*k)][j] = EMPTY;
						
						(*updated) = 1;
					} else if(grid[(*k)-value][j] == grid[*k][j]) {
						if(!(*alreadyCombined)) {
							grid[(*k)-value][j] += grid[*k][j];
							grid[*k][j] = EMPTY;
							
							(*f) = (*k) - value;
						
							(*alreadyCombined) = 1;
						} else {
							grid[(*k)-value][j] += grid[*k][j];
							grid[*k][j] = EMPTY;
						}
						
						(*updated) = 1;
					}
				}
				if(*updated) {
					(*hasMoved) = 1;
				}
				(*updated) = 0;
				(*k) -= value;
			}
		}
		(*alreadyCombined) = 0;
	}
}

void moveTilesUpDown(int value, int grid[4][4], int *f, int *k, int *alreadyCombined, int *updated, int *hasMoved) {
	int i, j;
	if (value == UP) {
		value = 1;
	} else if (value == DOWN) {
		value = -1;
	} else {
		return;
	}
	
	for(i = 0; i < 4; i++) {
		if (value == 1) {
			j = 1;
			*f = -1;
		} else if (value == -1) {
			j = 2;
			*f = 4;
		}

		for( ; (value == -1 && (j > -1)) || (value == 1 && (j < 4)); j += value) {
			*k = j;
			while((value == 1 && ((*k) > (*f) + value)) || (value == -1 && ((*k) < (*f) + value))) {
				if(grid[i][*k] > 0) {	//This block has a value, else ignore
					if(grid[i][(*k)-value] == EMPTY) { 
						grid[i][(*k)-value] = grid[i][*k];
						grid[i][*k] = EMPTY;
							
						*updated = 1;
					} else if(grid[i][(*k)-value] == grid[i][*k]) {	//Are two blocks with the same value adjacent?
						if(!(*alreadyCombined)) {
							grid[i][(*k)-value] += grid[i][*k];	//assign block below/above to current block's value
							grid[i][*k] = EMPTY;	//assign old block to EMPTY
							
							*f = (*k)-value;
						
							*alreadyCombined = 1;
						} else {
							grid[i][(*k)-value] += grid[i][*k];
							grid[i][*k] = EMPTY;
						}
						
						(*updated) = 1;
					}
				}
				if(*updated) {
					(*hasMoved) = 1;	//refresh the screen only when a tile has moved
				}
				(*updated) = 0;
				(*k) -= value;
			}
		}
		(*alreadyCombined) = 0;
	}
}

int won(int grid[4][4]) {
	int i, j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			if(grid[i][j] == 32) {
				// Call winning animation
				usleep(500000);
				wonAnimation(grid, i, j);
				return 1;
			}
		}
	}
	return 0;
}

