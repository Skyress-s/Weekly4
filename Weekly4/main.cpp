#include <iostream>
#include <vector>
#include <conio.h>
#include <random>

//using this little trick to not use std:: on these specific functions
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

//classes
struct Account {
	string name{};
	int number{};
};

struct Dice {
	int value{};
	bool isHeld{ false };

	void ToogleIsHeld() {
		if (isHeld) {
			isHeld = false;
		}
		else {
			isHeld = true;
		}
	}
};



void ClearCin();
void Spacing(int pos, int);
std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

//calulator prototypes
void Calculator();

//Grid game
void DrawBoard(vector<vector<char>>);
void Input(vector<int>&, char);
vector<int> StartPos();
int GenerateRandomInt(int from, int to);
void GridGame();

//accounts task
void AccountTask();

//Dice task
vector<Dice> Roll(vector<Dice>);
void PrintDices(vector<Dice>);
int FromCharToInt(char);
int HowMany6Dice(vector<Dice>);
void NumOfPairs(vector<Dice>);
void DiceTask();


//main
int main() {
	while (true)
	{
		system("cls");
		cout << "Main Menu" << endl;
		cout << "1. Calculator" << endl;
		cout << "2. 10x10 grid" << endl;
		cout << "3. Acocunts" << endl;
		cout << "4. Dice" << endl;
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
			AccountTask();
			break;

		case '4':
			DiceTask();
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

void Spacing(int pos, int spaceTaken) {
	for (int i = 0; i < pos - spaceTaken; i++)
	{
		cout << ' ';
	}
}


//task 1 --------------------------------------------------------------------
void Calculator() {
	bool returnToMenu = false;
	while (returnToMenu == false)
	{
		int answer{};
		bool acceptedAns{ false };

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

		while (!acceptedAns) {
			system("cls");
			cout << "input 1 : " << input1 << endl;
			cout << "input 2 : " << input2 << endl << endl;
			cout << "What operation do you want to do?" << endl;
			cout << "a. Addition" << endl;
			cout << "s. Subtract" << endl;
			cout << "m. Multiply" << endl;
			cout << "d. Divide" << endl;

			char operation{};
			cin >> operation;
			ClearCin();

			acceptedAns = true;

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

				acceptedAns = false;
				break;
			}
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
				returnToMenu = true;
				break;
			}
			else if ('n' == tolower(ans))
			{
				break;
			}
		}
	}
}


//task 2 --------------------------------------------------------------------
int GenerateRandomInt(int from, int to) {
	std::uniform_int_distribution<> die{ from, to };
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
			int x = GenerateRandomInt(0, 9);
			int y = GenerateRandomInt(0, 9);

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


//task 3 --------------------------------------------------------------------
void AccountTask() {
	int maxPersons = 10;
	vector<Account> accounts{};
	//input accounts
	while (true)
	{
		system("cls");
		Account temp{};
		cout << "Name : ";
		cin >> temp.name;
		ClearCin();
		cout << "Number : ";
		cin >> temp.number;
		ClearCin();

		accounts.push_back(temp);

		

		//ensures that the loop exits if the vector has 10 elements
		if (accounts.size() >= 10 ) {
			break;
		}

		//ask if you want to add another account
		cout << "add new account y/n : ";
		char ans{};
		cin >> ans;
		ClearCin();

		
		if (ans == 'n') {
			break;
		}
	}

	//print
	system("cls");
	cout << "Accounts added : " << endl;
	for (int i = 0; i < accounts.size(); i++) {

		cout << " | name : " << accounts[i].name;
		Spacing(12, accounts[i].name.size());
		cout << " | Number : " << accounts[i].number << endl;
	}

	system("pause");
}


//task 4 / dice task --------------------------------------------------------

vector<Dice> Roll(vector<Dice> a_dices) {
	for (int i = 0; i < a_dices.size(); i++)
	{
		if (!a_dices[i].isHeld)
		{
			a_dices[i].value = GenerateRandomInt(1, 6);
		}
	}
	return a_dices;
}

void PrintDices(vector<Dice> a_dices) {
	for (int i = 0; i < a_dices.size(); i++)
	{
		cout << "dice " << i + 1 << " : " << a_dices[i].value;
		if (a_dices[i].isHeld)
		{
			cout << " *HELD";
		}
		cout << endl;
	}
}

int FromCharToInt(char ch) {
	int result = ch - '0';
	return result;
}

int HowMany6Dice(vector<Dice> a_dice) {
	int result{};
	for (int i = 0; i < a_dice.size(); i++)
	{
		if (a_dice[i].value == 6)
		{
			result++;
		}
	}
	return result;
}

void NumOfPairs(vector<Dice> a_dices) {
	for (int i = 0; i < 6; i++)
	{
		int pair{};
		for (int j = 0; j < a_dices.size(); j++)
		{
			if (a_dices[j].value == i + 1)
			{
				pair++;
			}
		}
		if (pair%2 == 0 && pair > 0) // the task asked for ONLY pairs so we only print if there is exaclty two equal dice
		{
			cout << "There are : " << pair/2 << " " << i + 1 << "pairs" << endl;

		}

	}
}

void DiceTask() {
	vector<Dice> dices(5);
	PrintDices(dices);
	bool finished{};
	while (!finished)
	{
		
		system("cls");
		dices = Roll(dices);
		PrintDices(dices);
		cout << endl << HowMany6Dice(dices) << " | 6 sides have been rolled. " << endl;
		cout << endl;
		NumOfPairs(dices);
		cout << endl;
		cout << endl;


		cout << "1-6. Which dice to hold?" << endl;
		cout << "h. to stop rolling" << endl;
		cout << "g. continue" << endl;
		char ans{};
		cin >> ans;
		ClearCin();
		int intAns = FromCharToInt(ans);

		if (intAns >= 1 && intAns <= 5)
		{
			dices[intAns - 1].ToogleIsHeld();
		}
		else if (ans == 'h')
		{
			finished = true;
			break;
		}
		else if (ans == 'g')
		{
			
		}
		else
		{
			system("cls");
			cout << "Invalid answer, please choose again!"<< endl;
			system("pause");
		}
		
		
		

	}
}
