//	File: twenty.h
//	Connor Lucier, June 2017

/*	Class implemented: twenty
*	
*	Private member variables:
*
*		1) static const int board_size
*			- Defines board size. Can be adjusted for bigger/smaller board.
*		2) int[][] board
*			- Size: board_size * board_size
*			- Contains actual values in each space of the board.
*			- Entries initialized to 0.
*
*/

#ifndef TWENTY_H
#define TWENTY_H

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

class twenty {

private:

	static const int board_size = 4;

	int board[board_size][board_size];
	int game_score;

public:

	// CONSTRUCTOR
	
	twenty();

	// MODIFIER FUNCTIONS

	void generate();
	void combine(const int& r1, const int& c1, const int& r2, const int& c2);

	void shift_up();
	void shift_down();
	void shift_left();
	void shift_right();

	// CONSTANT FUNCTIONS

	int score() const { return game_score; }
	int size() const { return board_size; }
	
	bool full() const;
	bool used(const int& r, const int& c) const { return (board[r][c] != 0); }

	// FRIEND FUNCTIONS

	friend std::ostream& operator<<(std::ostream& outs, const twenty& game);

};

#endif