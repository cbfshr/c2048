#include <ncurses/ncurses.h>
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

//Use for general functions of the tfe program.
//These functions include:
// - generateContainer(int a, int b, int width, int height);
// - updateContainer(int a, int b, int num);
// - updateAllContainers(int arr[4][4]);
// - init_ncurses();

//These are not necessarily specific to the game logic of the program


//Maybe also have a menu file for starting the application and calling each of these files




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
}