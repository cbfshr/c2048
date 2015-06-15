/*
 * 2048_utils.c
 * Written in C using ncurses Library
 *
 * Author: Cal Fisher
 * Last Updated: 6/15/2015
*/

#include "2048.h"

void updateGrid(int grid[4][4], boolean hasMoved)
{
	if(hasMoved)
    {
		updateAllTiles(grid);
        //Places a new tile on the grid
		createRandomTile(grid);
	}
}

void createRandomTile(int grid[4][4]) {
	boolean validPlacement = FALSE;
    int xTileCoordinate = 0, yTileCoordinate = 0;
	while(!validPlacement) {
		xTileCoordinate = rand() % 4;
		yTileCoordinate = rand() % 4;

		//Coordinates must be an empty tile
		if(grid[xTileCoordinate][yTileCoordinate] == EMPTY) {
			validPlacement = TRUE;
		}
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
	attron(COLOR_PAIR(returnColor(grid, m, n)));
	drawTile(grid, m, n);
	attroff(COLOR_PAIR(returnColor(grid, m, n)));
}

void drawTile(int grid[4][4], int i, int j) {
	int actualXCoordinate = (i * TILE_WIDTH) + 2 + i + 1;
	int actualYCoordinate = (j * TILE_HEIGHT) + 2 + j;

	drawContainer(actualXCoordinate, actualYCoordinate, TILE_WIDTH, TILE_HEIGHT);

	if(grid[i][j] > 0) {
		mvprintw((actualYCoordinate + 5), (actualXCoordinate + 6), "%3d", grid[i][j]);
	}
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

    //        #     Text Color      Background Color
	init_pair(1,    COLOR_WHITE,    COLOR_BLACK);		//Other
	init_pair(2,    COLOR_WHITE,    COLOR_RED);		//2
	init_pair(3,    COLOR_WHITE,    COLOR_GREEN);		//4
	init_pair(4,    COLOR_WHITE,    COLOR_BLUE);		//8
	init_pair(5,    COLOR_WHITE,    COLOR_MAGENTA);	//16
	init_pair(6,    COLOR_BLACK,    COLOR_CYAN);		//32
	init_pair(7,    COLOR_BLACK,    COLOR_YELLOW);	//64
	init_pair(8,    COLOR_BLACK,    COLOR_WHITE);		//128
	init_pair(9,    COLOR_RED,      COLOR_WHITE);		//256
	init_pair(10,   COLOR_GREEN,    COLOR_WHITE);	//512
	init_pair(11,   COLOR_BLUE,     COLOR_WHITE);		//1024
	init_pair(12,   COLOR_MAGENTA,  COLOR_WHITE);	//2048
	init_pair(13,   COLOR_CYAN,     COLOR_WHITE);		//4096
	init_pair(14,   COLOR_YELLOW,   COLOR_WHITE);	//8192
}

void init_grid(int grid[4][4]) {
	int i, j;

	for(i = 0; i < 4; i++) {
		for(j =0; j < 4; j++) {
			grid[i][j] = EMPTY;
		}
	}

	//Draws container
	drawContainer(1, 1, CONTAINER_WIDTH, CONTAINER_HEIGHT);
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			// Draws 16 tiles within container
			drawTile(grid, i, j);
		}
	}
	refresh();
}

//Find some way to combine Left/Right and Up/Down moveTiles logic
//Rewrite this function to be more efficient and easier to understand
void moveTilesLeftRight(int direction, int grid[4][4], boolean *hasMoved) {
	boolean alreadyCombined = FALSE;
    boolean updated = FALSE;
	int i, j, f, k;
	if (direction == LEFT) {
		direction = 1;
	} else if (direction == RIGHT) {
		direction = -1;
	} else {
		return;
	}

	for(j = 0; j < 4; j++) {
        //These need to be reset every time for combination to work
		if (direction == 1) {
			i = 1;
			f = -1;
		} else if (direction == -1) {
			i = 2;
			f = 4;
		}

		for( ; (direction == -1 && (i > -1)) || (direction == 1 && (i < 4)); i += direction) {
			k = i;
			while(((direction == 1) && (k > (f + direction))) || ((direction == -1) && (k < (f + direction)))) {
				if(grid[k][j] > 0) {
					if(grid[k-direction][j] == EMPTY) {
						grid[k-direction][j] = grid[k][j];
						grid[k][j] = EMPTY;

						updated = TRUE;
					} else if(grid[k-direction][j] == grid[k][j]) {
						if(!alreadyCombined) {
							grid[(k)-direction][j] += grid[k][j];
							grid[k][j] = EMPTY;

							f = k - direction;

							alreadyCombined = TRUE;
						} else {
							grid[k-direction][j] += grid[k][j];
							grid[k][j] = EMPTY;
						}

						updated = TRUE;
					}
				}
				if(updated) {
					*hasMoved = TRUE;
				}
				updated = FALSE;
				k -= direction;
			}
		}
	}
}

//Rewrite this function to be more efficient and easier to understand
void moveTilesUpDown(int direction, int grid[4][4], boolean *hasMoved) {
	boolean alreadyCombined = FALSE;
    boolean updated = FALSE;
    int i, j, f, k;
	if (direction == UP) {
		direction = 1;
	} else if (direction == DOWN) {
		direction = -1;
	} else {
		return;
	}

	for(i = 0; i < 4; i++) {
        //These need to be reset every time for combination to work
		if (direction == 1) {
			j = 1;
			f = -1;
		} else if (direction == -1) {
			j = 2;
			f = 4;
		}

		for( ; (direction == -1 && (j > -1)) || (direction == 1 && (j < 4)); j += direction) {
			k = j;
			while((direction == 1 && ((k) > (f) + direction)) || (direction == -1 && (k < (f + direction)))) {
				if(grid[i][k] > 0) {	//This block has a direction, else ignore
					if(grid[i][k-direction] == EMPTY) {
						grid[i][k-direction] = grid[i][k];
						grid[i][k] = EMPTY;

						updated = TRUE;
					//Are two blocks with the same direction adjacent?
					} else if(grid[i][k-direction] == grid[i][k]) {
						if(!alreadyCombined) {
							//assign block below/above to current block's direction
							grid[i][k-direction] += grid[i][k];
							//assign old block to EMPTY
							grid[i][k] = EMPTY;

							f = k - direction;

							alreadyCombined = TRUE;
						} else {
							grid[i][k-direction] += grid[i][k];
							grid[i][k] = EMPTY;
						}

						updated = TRUE;
					}
				}
				if(updated) {
					//refresh the screen only when a tile has moved
					*hasMoved = TRUE;
				}
				updated = FALSE;
                k -= direction;
			}
		}
	}
}

int returnColor(int grid[4][4], int m, int n) {
	int i;
	if (grid[m][n] > 0) {
        //14 (8192) is highest value with color
		for(i = 1; (log10(grid[m][n])/log10(2) != i) && (i < 14); i++);
        return i + 1;
	}
	return 1;
}

//Maybe also have a menu file for starting the application and calling each of these files
int won(int grid[4][4]) {
	int i, j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			if(grid[i][j] == 2048) {
				// Call winning animation
				usleep(500000);
				wonAnimation(grid, i, j);
				return 1;
			}
		}
	}
	return 0;
}

void wonAnimation(int grid[4][4], int i, int j) {
	//final coordinates:
	//width: 24, height: 15
	int finalX = ((1 * TILE_WIDTH) + 2 + 1 + 1 + 6);
	int finalY = ((0 * TILE_HEIGHT) + 2 + 0 + 5);

	erase();
	drawContainer(1, 1, CONTAINER_WIDTH, CONTAINER_HEIGHT);
	updateTile(grid, i, j);
	//drawContainer(finalX, finalY, 24, 15);
	refresh();
	usleep(1000000);

	signed int currentX = (i * TILE_WIDTH) + 2 + i + 1;
	int currentY = (j * TILE_HEIGHT) + 2 + j;

	int fiX = 0;
	int fiY = 0;

	if(finalX > currentX) {
		fiX = 1;
	} else {
		fiX = -1;
	}

	if(finalY > currentY) {
		fiY = 1;
	} else {
		fiY = -1;
	}

	while(currentX != finalX || currentY != finalY) {
		erase();
		drawContainer(1, 1, CONTAINER_WIDTH, CONTAINER_HEIGHT);
		drawContainer(finalX, finalY, 24, 15);

		if(abs(finalX - currentX) > abs(finalY - currentY)) {
			if(currentX != finalX) {
				if(currentY != finalY) {
					currentX += fiX*(abs(finalX - currentX) / abs(finalY - currentY));
				} else {
					currentX += fiX;
				}
			}
			if(currentY != finalY) {
				currentY += fiY;
			}
		} else {
			if(currentX != finalX) {
				currentX += fiX;
			}
			if(currentY != finalY) {
				if(currentY != finalY) {
					currentY += fiY*(abs(finalY - currentY) / abs(finalX - currentX));
				} else {
					currentY += fiY;
				}
			}
		}

		if(((currentX > finalX) && (fiX == 1)) || ((currentX < finalX) && (fiX == -1))) {
			currentX = finalX;
		}
		if(((currentY > finalY) && (fiY == 1)) || ((currentY < finalY) && (fiY == -1))) {
			currentY = finalY;
		}

		attron(COLOR_PAIR(returnColor(grid, i, j)));

		drawContainer(currentX, currentY, 24 - 8*abs(finalX - currentX)/finalX, 15 - 5*abs(finalY - currentY)/finalY);
		if(grid[i][j] > 0) {
			mvprintw((currentY + 7), (currentX + 8), "%6d", 2048);
		}
		refresh();

		attroff(COLOR_PAIR(returnColor(grid, i, j)));

		refresh();
        usleep(100000);
	}
    mvprintw(25,35,"You won!");
}
