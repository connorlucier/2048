//	File: main.cpp
//	Connor Lucier, June 2017

#include "twenty.h"
#include <iostream>

using namespace std;

int main() {

	cout << "  _____    ______   _    _      ______\n";
	cout << " / __  \\  |  __  | | |  | |    |  __  |\n";
	cout << "|_/  |  | | |  | | | |  | |    | |__| |\n";
	cout << "    /  /  | |  | | | |__| |__  |      |\n";
	cout << "   /  /   | |  | | |____   __| |  __  |\n";
	cout << "  /  /__  | |__| |      | |    | |__| |\n";
	cout << " |______| |______|      |_|    |______|\n\n";

	cout << "\t~ Press Enter/Return ~\n\n";

	char input;
	getchar();

	cout << "Instructions: Enter w, a, s, or d to indicate direction. Press Enter/Return to finalize a move.\n";

	twenty t;
	cout << t;

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

		cout << t;
		cout << "Score: " << t.score() << "\n";
		cin.clear();

	}

	return 0;
}