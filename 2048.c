/*
 * 2048.c
 * Written in C using ncurses Library
 *
 * Author: Cal Fisher
 * Last Updated: 6/15/2015
*/

#include "2048.h"

int main(int argc, char* argv[])
{
	//		   HEIGHT	  WIDTH
	int grid[NUM_TILES][NUM_TILES];
	uchar keyPressed = NULL;
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

	erase();
	mvprintw(0, 0, "You won!");
	//mvprintw(26, 17, "Press [Enter] to return to the main menu.");
	mvprintw(1, 0, "Press [Esc] to exit the game.");
	refresh();
	do
	{
		keyPressed = getch();
	} while(keyPressed != ENTER && keyPressed != ESC);	//Enter or Escape
	//Add functionality to return to a main menu

	endwin();
}
