//	File: twenty.cpp
//	Connor Lucier, June 2017

#include "twenty.h"
#include <cassert>

twenty::twenty() {

	for(int r = 0; r < twenty::board_size; r++) {
		for(int c = 0; c < twenty::board_size; c++) {
			board[r][c] = 0;
		}
	}

	srand(time(NULL));
	game_score = 0;
	generate();
}

void twenty::generate() {
	int r = rand() % twenty::board_size;
	int c = rand() % twenty::board_size;

	while(used(r,c)) {
		r = rand() % twenty::board_size;
		c = rand() % twenty::board_size;
	}

	// P(2) = 0.75, P(4) = 0.25
	if(rand() % 4 == 0) {
		board[r][c] = 4;
		game_score += 4;
	}
	else {
		board[r][c] = 2;
		game_score += 2;
	}
}

bool twenty::combine(const int& r1, const int& c1, const int& r2, const int& c2) {

	assert(r1 >= 0 && c1 >= 0 && r2 >= 0 && c2 >= 0);
	assert(r1 < board_size && c1 < board_size && r2 < board_size && c2 < board_size);
	bool result = false;

	if(r1 == r2 && c1 == c2) {
		return result;
	}

	if(used(r1,c1) && board[r1][c1] == board[r2][c2]) {
		board[r1][c1] *= 2;
		board[r2][c2] = 0;

		game_score += board[r1][c1];
		result = true;
	}
	else if(!used(r1,c1) && used(r2,c2)) {
		board[r1][c1] = board[r2][c2];
		board[r2][c2] = 0;
		result = true;
	}

	return result;
}

// TODO: Handle weird shift cases.
	//	1) Four of same number in same row/col.
	//			i.e. [2][ ][ ][ ] -- shift_up() -->	[4][ ][ ][ ] & new num
	//				 [2][ ][ ][ ]					[4][ ][ ][ ] generated
	//				 [2][ ][ ][ ]					[ ][ ][ ][ ]
	//				 [2][ ][ ][ ]					[ ][ ][ ][ ]
	//	2) Two nonadjacent numbers need to be combined then shifted.
	//			i.e. [ ][ ][ ][ ] -- shift_up() -->	[4][ ][ ][ ] & new num
	//				 [2][ ][ ][ ]					[ ][ ][ ][ ] generated
	//				 [ ][ ][ ][ ]					[ ][ ][ ][ ]
	//				 [2][ ][ ][ ]					[ ][ ][ ][ ]


/*	NOTES ON SHIFT OPERATIONS LOGIC:
*		All shift_x() functions follow roughly the same logic. The only differences lie in the
*	order and direction of combinations, listed below.
*
*		- shift_up():
*			-> Loop through columns in any order; picked left to right for simplicity.
*				--> Within each column, loop through rows incrementing from zero.
*
*		- shift_down():
*			-> Loop through columns in any order; picked left to right for simplicity.
*				--> Within each column, loop through rows, decrementing from board_size - 1.
*
*		- shift_left():
*			-> Same as shift_up(), except rows and columns are switched. Outer loop for rows, inner loop for columns.
*
*		- shift_right():
*			-> Same as shift_down(), except rows and columns are switched. Outer loop for rows, inner loop for columns.
*
*
*	>>> NOTE: Using shift_up() to explain the general shift functionality simply. <<<
*	
*		SHIFT LOGIC:
*		
*		Loop through columns {
*			Loop through rows {
*				
*				If the current space is used, look downward and try to find the next used space.
*					- If this space is valid has the same value as the current space, combine them.
*					- Otherwise, move the next non-zero value up as far as possible.
*
*			}
*		}
*
*		If the board changed at all, generate a new number.
*
*/


void twenty::shift_up() {

	bool changed = false;

	for(int c = 0; c < twenty::board_size; c++) {
		for(int r = 0; r < twenty::board_size - 1; r++) {
				
			int cur = r+1;
			while(cur < twenty::board_size && !used(cur,c)) {
				cur++;
			}
			
			if(cur < twenty::board_size) {

				if(!used(r,c) || board[r][c] == board[cur][c]) {
					changed = combine(r,c,cur,c);
				}
				else {
					changed = combine(r+1,c,cur,c);
				}
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
				
			int cur = r-1;
			while(cur >= 0 && !used(cur,c)) {
				cur--;
			}
			
			if(cur >= 0) {
				
				if(!used(r,c) || board[r][c] == board[cur][c]) {
					changed = combine(r,c,cur,c);
				}
				else {
					changed = combine(r-1,c,cur,c);
				}
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
				
			int cur = c+1;
			while(cur < twenty::board_size && !used(r,cur)) {
				cur++;
			}
			
			if(cur < twenty::board_size) {

				if(!used(r,c) || board[r][c] == board[r][cur]) {
					changed = combine(r,c,r,cur);
				}
				else {
					changed = combine(r,c+1,r,cur);
				}
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
				
			int cur = c-1;
			while(cur >= 0 && !used(r,cur)) {
				cur--;
			}
			
			if(cur >= 0) {
				
				if(!used(r,c) || board[r][c] == board[r][cur]) {
					changed = combine(r,c,r,cur);
				}
				else {
					changed = combine(r,c-1,r,cur);
				}
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
			if(!used(r,c)) {
				return false;
			}
		}
	}

	return true;
}

bool twenty::used(const int& r, const int& c) const {
	
	assert(r >= 0 && c >= 0);
	assert(r < twenty::board_size && c < twenty::board_size);

	return (board[r][c] > 0);
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

			if(t.used(r,c)) {
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
