/*
 * 2048.c
 * Written in C using ncurses Library
 *
 * Author: Cal Fisher
 * Last Updated: 6/15/2015
*/

#include "2048.h"

void main(int argc, char* argv[])
{
	int keyPressed = 0;
	boolean alreadyCombined;
	boolean hasMoved = FALSE;
	boolean updated = 0;

	srand(time(NULL));

	// Initialize ncurses, keypad (no echo), color, and color pairs
	init_ncurses();

	int grid[4][4];
	init_grid(grid);

	createRandomTile(grid);
	createRandomTile(grid);
	do {
		keyPressed = getch();
		if(keyPressed == KEY_LEFT) {
			moveTilesLeftRight(LEFT, grid, &hasMoved);
		} else if(keyPressed == KEY_UP) {
			moveTilesUpDown(UP, grid, &hasMoved);
		} else if(keyPressed == KEY_RIGHT) {
			moveTilesLeftRight(RIGHT, grid, &hasMoved);
		} else if(keyPressed == KEY_DOWN) {
			moveTilesUpDown(DOWN, grid, &hasMoved);
		}

		updateGrid(grid, hasMoved);
		hasMoved = FALSE;
		refresh();
	} while(!won(grid));
	usleep(500000);

/*---END---*/
	int exitKey = 0;
	do {
		mvprintw(26,17,"Press [Enter] to return to the main menu.");
		mvprintw(27,22,"Press [Esc] to exit the game.");
		refresh();
		exitKey = getch();
	} while(exitKey != ENTER && exitKey != ESC);	//Enter or Escape
	//Add functionality to return to a main menu

	usleep(100000);
	erase();
	endwin();
/*---END---*/
}
