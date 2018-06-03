#include "Board.h"

#include <iostream>
#include <string>
using namespace std;

int main() {
	cout << "starting main..." << endl;
	Board board;
	cin >> board;
	//cout << board;
	string filename = board.draw(600);
	cout << filename << endl;
}