#include "Header.h"
#include <iostream>

using namespace std;

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	for (int i = 0; i < 3; i++)
		InputData();
	PrintTree(root);

	return 0;
}