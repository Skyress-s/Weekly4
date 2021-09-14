#include <iostream>
#include <vector>
#include <conio.h>
#include <random>

//using this little trick to not use std:: on these specific functions
using std::cout;
using std::cin;
using std::endl;
using std::vector;

void ClearCin();
std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

//calulator prototypes
void Calculator();
void GridGame();

int main() {
	
	
		
		

		 
	

	while (true)
	{
		system("cls");
		cout << "Main Menu" << endl;
		cout << "1. Calculator" << endl;
		cout << "2. 10x10 grid" << endl;
		cout << "3. Acocunts" << endl;
		cout << "q. Exit" << endl;

		char input{};
		cin >> input;
		ClearCin();

		switch (tolower(input))
		{
		case '1':
			Calculator();
			break;

		case '2':
			GridGame();
			break;

		case '3':
			break;

		case'q':
			exit(0);
			break;

		default:
			break;
		}


	}
	return 0;
}

void ClearCin() {
	std::cin.clear();				//Clears eventual errors from buffer
	std::cin.ignore(32767, '\n');	//clears the buffer if anything is there
}



void Calculator() {
	bool exit = false;
	while (exit == false)
	{
		system("cls");
		cout << "Calculator" << endl;
		int input1{};
		int input2{};

		cout << "Please input a number" << endl;
		cout << " Number 1 : ";
		cin >> input1;

		cout << "Please input a second number" << endl;
		cout << " Number 2 : ";
		cin >> input2;

		
		cout << "What operation do you want to do?" << endl;
		cout << "a. Addition" << endl;
		cout << "s. Subtract" << endl;
		cout << "m. Multiply" << endl;
		cout << "d. Divide" << endl;

		char operation{};
		cin >> operation;
		ClearCin();

		int answer{};
		switch (operation)
		{
		case 'a':
			answer = input1 + input2;
			break;

		case 's':
			answer = input1 - input2;
			break;

		case 'm':
			answer = input1 * input2;
			break;
		case 'd':
			answer = input1 / input2;
			break;


		default:
			break;
		}

		cout << endl << "Result : " << answer << endl;
		system("pause");

		while (true)
		{
			system("cls");
			cout << "Return to meny? y/n" << endl;
			char ans{};
			cin >> ans;
			ClearCin();
			if ('y' == tolower(ans))
			{
				exit = true;
				break;
			}
			else if ('n' == tolower(ans))
			{
				break;
			}
		}
	}
}

int GenerateRandomInt() {
	std::uniform_int_distribution<> die{ 0, 9 };
	return die(mersenne);
}
vector<int> StartPos() {
	while (true) // runs until i break it
	{
		system("cls");
		cout << "Do you want a random staring position? (defualt (0, 0))" << endl;
		cout << "input y/n : ";
		char input{};
		cin >> input;
		ClearCin();
		if (tolower(input) == 'y')
		{
			int x = GenerateRandomInt();
			int y = GenerateRandomInt();

			return { y,x };
			
		}
		else if (tolower(input) == 'n')
		{
			return { 0,0 };
			
		}
	}
}
void Input(vector<int>& a_move, char a_activeTile) {
	bool exit = false;
	while (exit == false)
	{
		exit = true;

		if (a_activeTile == '/')
		{
			a_move = { -1, 0 };
			break;
		}
		else if (a_activeTile == '\\')
		{
			a_move = { 1, 0 };
			break;
		}

		//move logic if no special tiles active
		char ans = _getch();
		a_move = { 0,0 };
		switch (ans)
		{
		case 'w':
			a_move[0] = 1;
			break;

		case 's':
			a_move[0] = -1;
			break;

		case 'd':
			a_move[1] = 1;
			break;

		case 'a':
			a_move[1] = -1;
			break;
		default:
			exit = false;
			break;
		}
	}
}
void DrawBoard(vector<vector<char>> a_grid) {
	cout << "______________________" << endl;
	for (int i = 0; i < a_grid.size(); i++)
	{
		cout << "| ";
		for (int j = 0; j < a_grid[0].size(); j++)
		{
			if (j <= 8)
			{
				cout << a_grid[a_grid.size() - 1 - i][j] << ' ';
			}
			else
			{
				cout << a_grid[a_grid.size() - 1 - i][j];
			}
		}

		cout << " |" << endl;
	}
	cout << "|_____________________|" << endl;
}
void GridGame() {
	int size = 10;
	vector<int> startPos = StartPos(); 
	vector<int> pos = { 0,0 };	// y, x 
	pos = startPos;
	vector<int> move = { 1,0 };

	char activeTile{};

	//init grid
	system("cls");
	vector<vector<char>> grid;
	for (int i = 0; i < size; i++)
	{
		grid.push_back(vector<char>{});
		for (int j = 0; j < size; j++)
		{
			grid[i].push_back('-');
		}
	}

	//places spacialTiles
	//go down tile
	grid[3][2] = '/';

	//go up tile
	grid[7][8] = '\\';

	grid[5][9] = 'G';




	//sets the active tile
	activeTile = grid[pos[0]][pos[1]];

	//starting pos
	grid[ pos[0] ][ pos[1] ] = 'x';

	//gameloop
	while (true)
	{
		system("cls");
		DrawBoard(grid);
		cout << endl << activeTile;





		//removes last space
		grid[pos[0]] [pos[1]] = activeTile;

		Input(move, activeTile);

		//checks if its out of bounds of the grid
		if (pos[0] + move[0] <= size - 1 && pos[0] + move[0]>=0){
			pos[0] = pos[0] + move[0];
		}
		if (pos[1] + move[1] <= size - 1 && pos[1] + move[1] >= 0){
			pos[1] = pos[1] + move[1];
		}
		
		activeTile = grid[pos[0]][pos[1]];
		grid[pos[0]][pos[1]] = 'x';


		//checks if victory condition is met
		if (activeTile == 'G')
		{
			system("cls");
			DrawBoard(grid);
			cout << endl << "Game Finished!";
			exit(0);
		}
	}

}
