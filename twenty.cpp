//	File: twenty.cpp
//	Connor Lucier, June 2017

#include "twenty.h"

twenty::twenty() {

	for(int i = 0; i < twenty::board_size; i++) {
		for(int j = 0; j < twenty::board_size; j++) {
			used[i][j] = false;
			board[i][j] = 0;
		}
	}

	srand(time(NULL));
	score = 0;
	generate();
}

void twenty::generate() {
	int r = rand() % twenty::board_size;
	int c = rand() % twenty::board_size;

	while(used[r][c]) {
		r = rand() % twenty::board_size;
		c = rand() % twenty::board_size;
	}

	// P(2) = 0.75, P(4) = 0.25
	if(rand() % 4 == 0) {
		board[r][c] = 4;
		score += 4;
	}
	else {
		board[r][c] = 2;
		score += 2;
	}

	used[r][c] = true;
}

void twenty::combine(const int& r1, const int& c1, const int& r2, const int& c2) {

	if(used[r1][c1] && board[r1][c1] == board[r2][c2]) {
		board[r1][c1] *= 2;
		board[r2][c2] = 0;
		used[r2][c2] = false;

		score += (board[r1][c1] * 2);
	}
	else if(!used[r1][c1] && used[r2][c2]) {
		board[r1][c1] = board[r2][c2];
		used[r1][c1] = true;
		board[r2][c2] = 0;
		used[r2][c2] = false;
	}
}

// TODO: Handle weird cases.
	//	1) 4 of same number in same row/col.
	//	2) 2 non-adjacent same numbers need to be combined & moved.
	//			i.e. [ ][ ][ ][ ] -- shift_up() -->	[4][ ][ ][ ] & new num
	//				 [2][ ][ ][ ]					[ ][ ][ ][ ] generated
	//				 [ ][ ][ ][ ]					[ ][ ][ ][ ]
	//				 [2][ ][ ][ ]					[ ][ ][ ][ ]

void twenty::shift_up() {

	bool changed = false;

	for(int c = 0; c < twenty::board_size; c++) {
		for(int r = 0; r < twenty::board_size - 1; r++) {

			if(used[r][c]) {
				int temp = r+1;
				while(temp < twenty::board_size - 1 && !used[temp][c]) {
					temp++;
				}

				if(board[r][c] == board[temp][c]) {
					combine(r,c,temp,c);
					changed = true;
				}
			}

			if(!used[r][c] && used[r+1][c]) {

				if(r < twenty::board_size - 2 && board[r+1][c] == board[r+2][c]) {
					combine(r+1,c,r+2,c);
				}

				int temp = r;
				while(temp > 0 && !used[temp-1][c]) {
					temp--;
				}

				combine(temp,c,r+1,c);
				changed = true;
			}
		}
	}

	if(changed) {
		generate();
	}
}

void twenty::shift_down() {

	bool changed = false;

	for(int c = 0; c < twenty::board_size; c++) {
		for(int r = twenty::board_size - 1; r > 0; r--) {

			if(used[r][c]) {
				int temp = r-1;
				while(temp > 0 && !used[temp][c]) {
					temp--;
				}

				if(board[r][c] == board[temp][c]) {
					combine(r,c,temp,c);
					changed = true;
				}
			}

			if(!used[r][c] && used[r-1][c]) {
				
				if(r > 1 && board[r-1][c] == board[r-2][c]) {
					combine(r-1,c,r-2,c);
				}

				int temp = r;
				while(temp < twenty::board_size - 1 && !used[temp+1][c]) {
					temp++;
				}

				combine(temp,c,r-1,c);
				changed = true;
			}
		}
	}

	if(changed) {
		generate();
	}
}

void twenty::shift_left() {

	bool changed = false;

	for(int r = 0; r < twenty::board_size; r++) {
		for(int c = 0; c < twenty::board_size - 1; c++) {

			if(used[r][c]) {
				int temp = c+1;
				while(temp < twenty::board_size - 1 && !used[r][temp]) {
					temp++;
				}

				if(board[r][c] == board[r][temp]) {
					combine(r,c,r,temp);
					changed = true;
				}
			}

			if(!used[r][c] && used[r][c+1]) {
				
				if(c < twenty::board_size - 2 && board[r][c+1] == board[r][c+2]) {
					combine(r,c+1,r,c+2);
				}

				int temp = c;
				while(temp > 0 && !used[r][temp-1]) {
					temp--;
				}

				combine(r,temp,r,c+1);
				changed = true;
			}
		}
	}

	if(changed) {
		generate();
	}
}

void twenty::shift_right() {

	bool changed = false;

	for(int r = 0; r < twenty::board_size; r++) {
		for(int c = twenty::board_size - 1; c > 0; c--) {

			if(used[r][c]) {
				int temp = c-1;
				while(temp > 0 && !used[r][temp]) {
					temp--;
				}

				if(board[r][c] == board[r][temp]) {
					combine(r,c,r,temp);
					changed = true;
				}
			}

			if(!used[r][c] && used[r][c-1]) {
				
				if(c > 1 && board[r][c-1] == board[r][c-2]) {
					combine(r,c-1,r,c-2);
				}

				int temp = c;
				while(temp < twenty::board_size - 1 && !used[r][temp+1]) {
					temp++;
				}

				combine(r,temp,r,c-1);
				changed = true;
			}
		}
	}

	if(changed) {
		generate();
	}
}

bool twenty::full() const {
	
	for(int r = 0; r < twenty::board_size; r++) {
		for(int c = 0; c < twenty::board_size; c++) {
			if(!used[r][c]) {
				return false;
			}
		}
	}

	return true;
}

std::ostream& operator<<(std::ostream& outs, const twenty& t) {

	int len = twenty::board_size * twenty::board_size;
	int i;
	for(i = 0; i <= len; i++) {
		outs << "_";
	}

	outs << "\n";

	for(int r = 0; r < twenty::board_size; r++) {
		
		outs << "| ";
		for(int c = 0; c < twenty::board_size; c++) {

			if(t.used[r][c]) {
				outs << t.board[r][c] << " | ";
			}
			else {
				outs << "  | ";
			}
		}

		outs << "\n";	
	}

	for(i = 0; i <= len; i++) {
		outs << "_";
	}

	outs << "\n";

	return outs;
}
