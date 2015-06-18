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
    //         HEIGHT       WIDTH
	int grid[NUM_TILES][NUM_TILES];
	uchar keyPressed = NULL;
	uchar exitKey = NULL;
	boolean hasMoved = FALSE;

    srand(time(NULL));
    init_ncurses();

    init_grid(grid);
	do
    {
		keyPressed = getch();
		if(keyPressed == KEY_LEFT)
        {
			moveTilesLeftRight(LEFT, grid, &hasMoved);
		}
        else if(keyPressed == KEY_UP)
        {
			moveTilesUpDown(UP, grid, &hasMoved);
		}
        else if(keyPressed == KEY_RIGHT)
        {
			moveTilesLeftRight(RIGHT, grid, &hasMoved);
		}
        else if(keyPressed == KEY_DOWN)
        {
			moveTilesUpDown(DOWN, grid, &hasMoved);
		}

		updateGrid(grid, hasMoved);
		hasMoved = FALSE;
		refresh();
	} while(!won(grid));
	usleep(500000);

	mvprintw(28,17,"Press [Enter] to return to the main menu.");
	mvprintw(29,22,"Press [Esc] to exit the game.");
	refresh();
	do
    {
		exitKey = getch();
	} while(exitKey != ENTER && exitKey != ESC);	//Enter or Escape
	//Add functionality to return to a main menu

	erase();
	endwin();
}
