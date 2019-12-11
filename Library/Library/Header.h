#pragma once
#ifndef HEADER_
#include <string>

struct Library {
	string ukdNumber;
	string fullName;
	string bookName;
	int publishYear;
	int amountInstances;

	Library * left;
	Library * right;
	Library * parent;
};

Library* root;
#endif // !HEADER_
