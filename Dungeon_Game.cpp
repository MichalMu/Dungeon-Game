#include<iostream>
#include<string>
#include<ctime>
#include<conio.h>
#include<vector>
#include <stdlib.h>
using std::cout;
using std::endl;

//Global Variables
const int x_dim = 8;
const int y_dim = 10;


class Dungeon {
public:
	void buildboard();
	void initialize();
	int playermove();
	void settrap();
	bool checkwin(int krow, int kcol);
	bool checklose(int krow, int kcol);
	char userinput;
protected:
	std::vector<std::vector<char>> board;
};

void Dungeon::initialize()
{
	int kcol{ 0 }, krow{ 0 };
	std::vector<char> help;
	for (int i = 0; i < x_dim; ++i)
	{
		for (int j = 0; j < y_dim; ++j)
		{
			help.push_back('.');
		}
		board.push_back(help);
		help.clear();
	}
	//Random treasure
	while (kcol + krow == 0) {

		kcol = rand() % 10;
		krow = rand() % 8;
		board[krow][kcol] = 'X';
	}

	//player start at 0,0.
	board[0][0] = 'P';

}

void Dungeon::settrap() {
	//random trap
	int kcol, krow;
	bool ok = false;
	while (ok == false) {
		kcol = rand() % 10;
		krow = rand() % 8;
		if (board[krow][kcol] == '.') {
			board[krow][kcol] = 'T';
			ok = true;
		}

	}
}

void Dungeon::buildboard() {

	system("CLS");
	cout << "Welcom in Dungeon Game \n";
	cout << "Your goal is to find the treasuer[X], but You have to be careful," << endl;
	cout << "if you step on a trap[T] you lose \n";
	cout << "Good Luck \n";

	for (auto& row : board) {
		for (auto& col : row) {
			cout << col;
		}
		cout << '\n';
	}




}

bool Dungeon::checkwin(int krow, int kcol)
{
	//if player P find treasure X
	if (board[krow][kcol] == 'X') {
		return true;
		//buildboard();
	}
	else
	{
		return false;
	}
}

int Dungeon::playermove() {
	int kcol, krow;
	for (int i{ 0 }; i < 10; i++) {
		for (int j{ 0 }; j < 8; j++) {
			if (board[j][i] == 'P') {
				kcol = i;
				krow = j;
				break;
			}
		}
	}

	//do not let player move off board
	board[krow][kcol] = '.';
	if (userinput == 'w' && krow != 0) {
		krow--;
	}
	else if (userinput == 's' && krow != 7) {
		krow++;
	}
	else if (userinput == 'a' && kcol != 0) {
		kcol--;
	}
	else if (userinput == 'd' && kcol != 9) {
		kcol++;
	}
	//if win
	if (checkwin(krow, kcol) == true)
	{
		cout << "\n YOU WIN \n";
	}
	//if lose
	else if (checklose(krow, kcol) == true)
	{
		cout << "\n YOU LOSE \n";
		return true;
	}
	else {
		board[krow][kcol] = 'P';
		return false;
	}
}


bool Dungeon::checklose(int krow, int kcol)
{
	//if player P find trap:
	if (board[krow][kcol] == 'T') {
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	srand((unsigned)time(0));
	Dungeon x;
	x.initialize();
	x.settrap();
	bool stop = false;
	//Do while winner or loser
	while (stop == false) {
		x.buildboard();
		x.settrap();
		cout << "player {P} can move up, down, left, right (w,s,a,d)" << endl;
		//cout <<" ";
		x.userinput = _getch();
		bool quit = false;

		while (!quit) {
			switch (x.userinput) {
			case 'w':
			case 's':
			case 'a':
			case 'd':
				quit = true;
				break;
			default:
				cout << "Invalid move, try again! You can only use w,a,s,d" << endl;
				//cout<<" ";
				x.userinput = _getch();
			}

		}
		stop = x.playermove();
		x.userinput = '.'; //reset

	}
}







