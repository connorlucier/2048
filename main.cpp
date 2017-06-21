//	File: main.cpp
//	Connor Lucier, June 2017

#include <iostream>
#include <stdio.h>
#include "twenty.h"

using namespace std;

int main() {

	cout << "_______________      _____   ______\n";  
	cout << "\\_____  \\   _  \\    /  |  | /  __  \\ \n";
	cout << " /  ____/  /_\\  \\  /   |  |_>      < \n";
	cout << "/       \\  \\_/   \\/    ^   /   --   \\\n";
	cout << "\\_______ \\_____  /\\____   |\\______  /\n";
	cout << "        \\/     \\/      |__|       \\/ \n\n";

	cout << "\t~ Press Enter/Return ~\n\n";
	getchar();

	cout << "Instructions: Enter w, a, s, or d to indicate direction. Press Enter/Return to finalize a move.\nEntering an invalid move will end the game.\n";

	twenty t;
	cout << t;
	cout << "Score: " << t.score() << "\n";

	char input;
	while(cin >> input) {

		if(input == 'w') {
			t.shift_up();
		}
		else if(input == 'a') {
			t.shift_left();
		}
		else if(input == 's') {
			t.shift_down();
		}
		else if(input == 'd') {
			t.shift_right();
		}
		else {
			break;
		}

		cout << t << "Score: " << t.score() << "\nInput: ";
		cin.clear();

	}

	return 0;
}