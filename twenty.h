//	File: twenty.h
//	Connor Lucier, June 2017

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
	bool used[board_size][board_size];

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

	int size() const { return board_size; }
	int score() const { return game_score; }
	bool full() const;

	// FRIEND FUNCTIONS

	friend std::ostream& operator<<(std::ostream& outs, const twenty& game);

};

#endif