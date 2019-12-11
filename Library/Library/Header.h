#pragma once
#ifndef HEADER_
#include <string>
#include <Windows.h>
#include <iomanip>
#include <conio.h>

using namespace std;

struct Library {

	string ukdNumber;
	string fullName;
	string bookName;
	int publishingYear;
	int amountInstances;

	Library* Left = NULL;
	Library* right = NULL;
	Library* Parent = NULL;
};

__declspec(selectany) Library* root = NULL;
__declspec(selectany) int Position = 0;

void HeadTable();
void PrintMainMenu();
void InputData();
void PrintTree(Library* Branch);


int CheckForNotLetter(string str);
int StringToInt(string str);
char GetKey();
bool IsLetter(const char sym);
int CheckStringToNumb(string str);
int CheckInt(string str);
void StringToCharArray(string NameFileStr, char* NameFileChar);
bool IsDigit(const char sym);
#endif // !HEADER_
