			/*for(i = 0; i < 4; i++) {
				if (value == 1) { f = -1; j = 1; }
				else if (Value == -1) { f = 4; j = 2; }
//				f = 4;
				for( ; (value == -1 && (j > -1)) && (value == 1 && (j < 4)); j += value) {
//				for(j = 2; j > -1; j--) {
				
					k = j;
//					while(k < f - 1) {
						if(grid[i][k] > 0) {
//							if(grid[i][k+1] == -1) {
//								grid[i][k+1] = grid[i][k];
								grid[i][k] = -1;
								
								updated = 1;
//							} else if(grid[i][k+1] == grid[i][k]) {
								if(!alreadyCombined) {
//									grid[i][k+1] += grid[i][k];
									grid[i][k] = -1;
									
//									f = k+1;
								
									alreadyCombined = 1;
								} else {
//									grid[i][k+value] += grid[i][k];
									grid[i][k] = -1;
								}
								
								updated = 1;
							}
						}
						if(updated) {
							hasMoved = 1;
						}
						updated = 0;
//						k++;
					}
				}
				alreadyCombined = 0;
			}*/