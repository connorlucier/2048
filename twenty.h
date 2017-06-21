//	FILE: twenty.h
//	Connor Lucier, June 2017

/*	CLASS IMPLEMENTED: twenty
*	
*	PRIVATE MEMBER VARIABLES:
*
*		1) static const int board_size
*			- Defines board size. Can be adjusted for bigger/smaller board.
*		2) int[][] board
*			- Size: board_size * board_size
*			- Contains actual values in each space of the board.
*			- Entries initialized to 0.
*		3) int game_score
*			- Tracks score throughout game.
*			- Initialized to zero. Score increased by each number created.
*
*	DEFAULT CONSTRUCTOR:
*		- Initializes board to all zeroes.
*		- Sets game_score to 0.
*		- Initializes rand() seed.
*
*	PUBLIC MEMBER FUNCTIONS:
*
*		MODIFIER FUNCTIONS:
*			- void generate()
*				-> Generates a new number in an unused spot on the board.
*				-> Increases game_score by the value of this new number.
*			
*			- void combine(r1,c1,r2,c2)
*			  PRECONDITION: all passed row/column values are positive and less than board_size.
*				-> If the numbers in board[r1][c1] and board[r2][c2] are greater than 0 and equal, combine them and add the result to game_score.
*				-> Otherwise, copy board[r2][c2] to board[r1][c1]
*				-> In either case, board[r2][c2] is reset to 0.
*
*			- void shift_up()
*				-> Shifts and combines numbers upward. If the board changes in this process, a new number is generated.
*
*			- void shift_down()
*				-> Shifts and combines numbers downward. If the board changes in this process, a new number is generated.
*
*			- void shift_left()
*				-> Shifts and combines numbers to the left. If the board changes in this process, a new number is generated.
*
*			- void shift_right()
*				-> Shifts and combines numbers to the right. If the board changes in this process, a new number is generated.
*
*		CONSTANT FUNCTIONS:
*			- int score()
*				-> Returns the current value of game_score
*
*			- int size()
*				-> Returns the value of board_size
*
*			- bool full()
*				-> Returns true if all spaces in board[][] are used, and false otherwise.
*
*			- bool used(r,c)
*				-> Returns true if the value in board[r][c] is greater than 0.
*
*		OPERATOR OVERLOADS:
*
*			- friend std::ostream& operator<<(outs, game)
*				-> Prints the current state of the board to outs.
*
*	VALUE SEMANTICS:
*		The default copy constructor and assignment operators can be used with the 'twenty' class.
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
	bool used(const int& r, const int& c) const { return (board[r][c] > 0); }

	// FRIEND FUNCTIONS

	friend std::ostream& operator<<(std::ostream& outs, const twenty& game);

};

#endif