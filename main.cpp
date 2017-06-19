#include "twenty.h"
#include <iostream>

using namespace std;

int main() {

	twenty t;

	cout << t;

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

		cout << t;
		cin.clear();

	}

	return 0;
}