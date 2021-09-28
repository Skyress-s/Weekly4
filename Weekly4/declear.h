#pragma once
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


