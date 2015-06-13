// ON MAC OS X:
// Comment out this line:
#include <ncurses/ncurses.h>
// Uncomment the line below:
//#include <curses.h>
// Compile in Terminal using the following command:
// gcc -o filename filename.c -lcurses

#include <stdio.h>
#include <math.h>
#include <string.h>
//#include <windows.h>


#define CONTAINER_WIDTH 75
#define CONTAINER_HEIGHT 48

//#define O 'o'
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4

void generateContainer(int a, int b, int width, int height);
void updateContainer(int a, int b, int num);
void updateAllContainers(int arr[4][4]);

int main(int argc, char* argv[]) {
	//printf("%c", O);	//THIS WORKS
	int a,b ,i, j, k;
	//int pox = 20, poy = 20;
	//int direction = DOWN;
	
	srand(time(NULL));
	
	initscr();
	cbreak();
	keypad(stdscr, true);
	noecho();
	refresh();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	init_pair(3, COLOR_WHITE, COLOR_GREEN);
	init_pair(4, COLOR_WHITE, COLOR_YELLOW);
	init_pair(5, COLOR_WHITE, COLOR_BLUE);
	init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(7, COLOR_WHITE, COLOR_CYAN);
	
	init_pair(8, COLOR_BLACK, COLOR_WHITE);
	init_pair(9, COLOR_RED, COLOR_WHITE);
	init_pair(10, COLOR_GREEN, COLOR_WHITE);
	init_pair(11, COLOR_YELLOW, COLOR_WHITE);
	init_pair(12, COLOR_BLUE, COLOR_WHITE);
	init_pair(13, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(14, COLOR_CYAN, COLOR_WHITE);
	
	//mvaddch(y,x,c);
	//generateContainer(a, b, width, height);
	generateContainer(1, 1, 71, 45);
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			generateContainer((i * 16) + 2 + i + 1, (j * 10) + 2 + j, 16, 10);
			//generateContainer(i, j, 16, 10);
		}
	}
	refresh();
	
	int w, z, validPlacement, won, alreadyCombined, f;
	int grid[4][4];
	for(i = 0; i < 4; i++)
		for(j =0; j < 4; j++)
			grid[i][j] = -1;
			
	/*grid[0][0] = 2;
	grid[0][1] = 1;	
	grid[0][2] = 1;
	grid[0][3] = 2;*/
		
	//--------------------------------[
	//BEGIN
	int ch;
	int hasMoved;
	int canMoveUp = 1;
	int updated;
	
	while(!validPlacement) {
		w = rand()%4;
		z = rand()%4;
	
		if(grid[w][z] == -1)
			validPlacement = 1;
	}
		
	grid[w][z] = 2;
	updateContainer(w,z,grid[w][z]);
	refresh();
	
	do {		
		ch = getch();
		
		hasMoved = 0;
		if(ch == KEY_LEFT) {
			for(j = 0; j < 4; j++) {
				f = -1;
				for(i = 1; i < 4; i++) {
					k = i;
					while(k > f + 1) {
						if(grid[k][j] > 0) {
							if(grid[k-1][j] == -1) {
								grid[k-1][j] = grid[k][j];
								grid[k][j] = -1;
								
								updated = 1;
							} else if(grid[k-1][j] == grid[k][j]) {
								if(!alreadyCombined) {
									grid[k-1][j] += grid[k][j];
									grid[k][j] = -1;
									
									f = k-1;
								
									alreadyCombined = 1;
								} else {
									grid[k-1][j] += grid[k][j];
									grid[k][j] = -1;
								}
								
								updated = 1;
							}
						}
						//updateAllContainers(grid);
						if(updated) {
							//updateContainer(i, k, grid[i][k]);
							//updateContainer(i, k-1, grid[i][k-1]);
							//refresh();
							//usleep(10000);
							hasMoved = 1;
						} else {
							//hasMoved = 0;
						}
						updated = 0;
						k--;
					}
				}
				alreadyCombined = 0;
			}
		} else if(ch == KEY_UP) {
			for(i = 0; i < 4; i++) {
				f = -1;
				for(j = 1; j < 4; j++) {
					k = j;
					while(k > f + 1) {
						if(grid[i][k] > 0) {
							if(grid[i][k-1] == -1) {
								grid[i][k-1] = grid[i][k];
								grid[i][k] = -1;
								
								updated = 1;
							} else if(grid[i][k-1] == grid[i][k]) {
								if(!alreadyCombined) {
									grid[i][k-1] += grid[i][k];
									grid[i][k] = -1;
									
									f = k-1;
								
									alreadyCombined = 1;
								} else {
									grid[i][k-1] += grid[i][k];
									grid[i][k] = -1;
								}
								
								updated = 1;
							}
						}
						//updateAllContainers(grid);
						if(updated) {
							//updateContainer(i, k, grid[i][k]);
							//updateContainer(i, k-1, grid[i][k-1]);
							//refresh();
							//usleep(10000);
							hasMoved = 1;
						} else {
							//hasMoved = 0;
						}
						updated = 0;
						k--;
					}
				}
				alreadyCombined = 0;
			}
		} else if(ch == KEY_RIGHT) {
			for(j = 0; j < 4; j++) {
				f = 4;
				for(i = 2; i > -1; i--) {
					k = i;
					while(k < f - 1) {
						if(grid[k][j] > 0) {
							if(grid[k+1][j] == -1) {
								grid[k+1][j] = grid[k][j];
								grid[k][j] = -1;
								
								updated = 1;
							} else if(grid[k+1][j] == grid[k][j]) {
								if(!alreadyCombined) {
									grid[k+1][j] += grid[k][j];
									grid[k][j] = -1;
									
									f = i+1;
								
									alreadyCombined = 1;
								} else {
									grid[k+1][j] += grid[k][j];
									grid[k][j] = -1;
								}
								
								updated = 1;
							}
						}
						//updateAllContainers(grid);
						if(updated) {
							//updateContainer(i, k, grid[i][k]);
							//updateContainer(i, k+1, grid[i][k+1]);
							//refresh();
							//usleep(10000);
							hasMoved = 1;
						}
						updated = 0;
						k++;
					}
				}
				alreadyCombined = 0;
			}
		} else if(ch == KEY_DOWN) {
			for(i = 0; i < 4; i++) {
				f = 4;
				for(j = 2; j > -1; j--) {
					k = j;
					while(k < f - 1) {
						if(grid[i][k] > 0) {
							if(grid[i][k+1] == -1) {
								grid[i][k+1] = grid[i][k];
								grid[i][k] = -1;
								
								updated = 1;
							} else if(grid[i][k+1] == grid[i][k]) {
								if(!alreadyCombined) {
									grid[i][k+1] += grid[i][k];
									grid[i][k] = -1;
									
									f = k+1;
								
									alreadyCombined = 1;
								} else {
									grid[i][k+1] += grid[i][k];
									grid[i][k] = -1;
								}
								
								updated = 1;
							}
						}
						//updateAllContainers(grid);
						if(updated) {
							//updateContainer(i, k, grid[i][k]);
							//updateContainer(i, k+1, grid[i][k+1]);
							//refresh();
							//usleep(10000);
							hasMoved = 1;
						}
						updated = 0;
						k++;
					}
				}
				alreadyCombined = 0;
			}
		}
		
		
		
		
		//---UPDATE GRID
	
		//updateAllContainers(grid);
		if(hasMoved) {
			updateAllContainers(grid);
		
			while(!validPlacement) {
				w = rand()%4;
				z = rand()%4;
			
				if(grid[w][z] == -1)
					validPlacement = 1;
			}
			
			grid[w][z] = 2;
			updateContainer(w,z,grid[w][z]);		
		}
		//--------------------------------[
	
		/*for(i = 0; i < 4; i++)
			for(j =0; j < 4; j++)
				if(grid[i][j] == 7)
					won = 1;*/
		validPlacement = 0;		

		//mvprintw(0,0,"Input is: %d, KEY_UP is %d ",ch, KEY_UP);
		refresh();
	} while(1);
	
		
	//while(1);
	erase();
	mvprintw(25,35,"You won!");
	refresh();
	usleep(1000000);
	endwin();
	return 0;
}

void updateAllContainers(int arr[4][4]) {
	int m, n;
	for(m = 0; m < 4; m++)
		for(n =0; n < 4; n++)
			updateContainer(m, n, arr[m][n]);
	return;
}

void updateContainer(int m, int n, int num) {
	//color of the text/border will depend on the current number.
	int a = (m * 16) + 2 + m + 1;
	int b = (n * 10) + 2 + n;
	
	int c;
	if(num == -1 || num == 0) {
		c = 1;
	} else if(num == 2) {
		c = 2;
	} else if(num == 4) {
		c = 3;
	} else if(num == 8) {
		c = 4;
	} else if(num == 16) {
		c = 5;
	} else if(num == 32) {
		c = 6;
	} else if(num == 64) {
		c = 7;
	} else if(num == 128) {
		c = 8;
	} else if(num == 256) {
		c = 9;
	} else if(num == 512) {
		c = 10;
	} else if(num == 1024) {
		c = 11;
	} else if(num == 2048) {
		c = 12;
	} else if(num == 4096) {
		c = 13;
	} else {
		c = 1;
	}
	
	attron(COLOR_PAIR(c));
	
	generateContainer(a, b, 16, 10);
	
	if(num > 0)
		mvprintw(b + 5, a + 6, "%3d", num);

	attroff(COLOR_PAIR(c));
	return;
}

void generateContainer(int a, int b, int width, int height) {
	//int i = (a * 16) + 2 + a + 1;
	//int	j = (b * 10) + 2 + b;
	int i = a;
	int j = b;
	
	mvaddch(j,i++,ACS_ULCORNER);
	for( ; i < width+a; i++)
		mvaddch(j,i,ACS_HLINE);
		
	mvaddch(j++,i,ACS_URCORNER);
	for( ; j < height+b; j++)
		mvaddch(j,i,ACS_VLINE);
		
	mvaddch(j,i--,ACS_LRCORNER);
	for( ; i > a; i--)
		mvaddch(j,i,ACS_HLINE);
		
	mvaddch(j--,i,ACS_LLCORNER);
	for( ; j > b; j--)
		mvaddch(j,i,ACS_VLINE);
	
	for(i = a + 1; i < a + width; i++) {
		for(j = b + 1; j < b + height; j++) {
			mvaddch(j, i, ' ');
		}
	}
	
	return;
}
