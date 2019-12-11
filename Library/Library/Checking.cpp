#include "Header.h"
#include <iostream>


/*
	������� ��������� ������ - ����� ��� ��� ���.
	������� ���������:
		1)const char sym - ����������� ������
	����������:
		false - ���� ������ �� �����
		true - ���� ������ �����
*/
bool IsLetter(const char sym) {
	int KeyCode = sym;
	if (KeyCode >= 65 && KeyCode < 91)
		return true;
	else if (KeyCode == 32)
		return true;
	else if (KeyCode >= 97 && KeyCode < 123)
		return true;
	else if (KeyCode == (127 - 168))
		return true;
	else if (KeyCode == (127 - 184))
		return true;
	else if (KeyCode <= -1 && KeyCode > -65)
		return true;
	else if (sym == '.')
		return true;
	else return false;
}

/*
	������� ��������� ������, ����� � ��� ���� ������ �����.
	������� ���������:
		1)string str - ����������� ������
	����������:
		1, ���� ��� ������� - �����
		0, ���� ������ ������ ������
*/
int CheckInt(string str) {
	int size = str.size();
	for (int i = 0; i < size; i++) {
		if (IsDigit(str[i]))
			continue;
		else return 0;
	}
	return 1;
}

/*  ������� �������� ������ �� ������� ������ �������� ����� ����.
	������� ���������:
		1)string str - ����������� ������
	����������:
		0 - ���� ������� �� �����
		1 ���� � ������ ��� ������� - �����
*/
int CheckStringToNumb(string str)
{
	int size = str.size();
	for (int i = 0; i < size; i++) {
		if (!IsLetter(str[i]))
			return 0;
	}
	return 1;
}

/*
	������� ��������� ������ - ��� �����, ��� ���.
	����������:
		true, ���� ������ �����;
		false - ���� ������ �� �����.
	������� ���������:
		1) const char sym - ����������� ������
*/
bool IsDigit(const char sym)
{
	int KeyCode = sym;
	if (KeyCode >= 48 && KeyCode < 58)
		return true;
	else return false;
}

/*
	������� �������������� ������ � ����� �������������� ����.
	������� ���������:
		1) string str - ����������������� ������
	����������:
		1)����� ���� int.
*/
int StringToInt(string str) {
	int Value = 0;
	int size = str.size();
	if (size == 1 && str[0] == '-') return -1;
	else if (size == 1 && str[0] == '0') return 0;
	for (int i = size - 1, pow = 1; i >= 0; i--, pow *= 10) {
		Value += (str[i] - '0') * pow;
	}
	return Value;
}

/*
	������� ��������� ������, ����� � ��� �� ���� ������� ���� � ����.
	������� ���������:
		1) string str - ����������� ������.
	����������:
		1 - ���� ��� ������� ������ ����� ��� �����
		0 - ���� �����-�� ������ ������ �� ����� � �� �����
*/
int CheckForNotLetter(string str) {
	int size = str.size();
	for (int i = 0; i < size; i++) {
		if (!IsLetter(str[i]) && !IsDigit(str[i]))
			return 0;
		else continue;
	}
	return 1;
}

/*
	������� ���������� ������� � �������:
	������� ��������� �����������.
	����������:
		������ char '�' ��� '�';
*/
char GetKey()
{
	char Answer;
	Answer = _getch();
	switch (Answer) {
	case '�':
		return Answer;
		break;
	case '�':
		return Answer;
		break;
	case 'l':
		Answer = '�';
		return Answer;
		break;
	case 'y':
		Answer = '�';
		return Answer;
		break;
	case '�':
		Answer = '�';
		return Answer;
		break;
	case '�':
		Answer = '�';
		return Answer;
		break;
	case 'Y':
		Answer = '�';
		return Answer;
		break;
	case 'L':
		Answer = '�';
		return Answer;
		break;
	default:
		cout << endl << "������� '�' ��� '�' !";
		return GetKey();
	}
}


void StringToCharArray(string NameFileStr, char* NameFileChar) {
	int i, j;
	for (i = 0, j = NameFileStr.size(); i < j; i++) {
		NameFileChar[i] = NameFileStr[i];
	}
	NameFileChar[i] = '.';
	NameFileChar[++i] = 't';
	NameFileChar[++i] = 'x';
	NameFileChar[++i] = 't';
}

/*
	������� ��������� ����������� ������ � ������. ���� ������ ���, ���������� � ������� ����.
	������� ��������� �����������.
	������ �� ����������.
*/
void DataAvailibility() {
	if (root == NULL) {
		cout << endl << endl << "\t� ���� ��� ������! ��������� ������� �����!" << endl << endl;
		_getch();
		PrintMainMenu();
	}
}