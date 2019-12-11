#include "Header.h"
#include <iostream>


/*
	Функция проверяет символ - буква это или нет.
	Входные параметры:
		1)const char sym - проверяемый символ
	Возвращает:
		false - если символ не буква
		true - если символ буква
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
	Функция проверяет строку, чтобы в ней были только цифры.
	Входные параметры:
		1)string str - проверяемая строка
	Возвращает:
		1, если все символы - цифры
		0, если найден другой символ
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

/*  Функция проверки строки на наличие других символов кроме букв.
	Входные параметры:
		1)string str - проверяемая строка
	Возвращает:
		0 - если найдена не буква
		1 если в строке все символы - буквы
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
	Функция проверяет символ - это цифра, или нет.
	Возвращает:
		true, если символ цифра;
		false - если символ не цифра.
	Входные параметры:
		1) const char sym - проверяемый символ
*/
bool IsDigit(const char sym)
{
	int KeyCode = sym;
	if (KeyCode >= 48 && KeyCode < 58)
		return true;
	else return false;
}

/*
	Функция преобразования строки в число целочисленного типа.
	Входные параметры:
		1) string str - преобразовываемая строка
	Возвращает:
		1)число типа int.
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
	Функция проверяет строку, чтобы в ней не было никаких букв и цифр.
	Входные параметры:
		1) string str - проверяемая строка.
	Возвращает:
		1 - если все символы строки буквы или цифры
		0 - если какой-то символ строки не буквы и не цифра
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
	Функция считывания символа с клавиши:
	Входные параметры отсутствуют.
	Возвращает:
		символ char 'д' или 'н';
*/
char GetKey()
{
	char Answer;
	Answer = _getch();
	switch (Answer) {
	case 'д':
		return Answer;
		break;
	case 'н':
		return Answer;
		break;
	case 'l':
		Answer = 'д';
		return Answer;
		break;
	case 'y':
		Answer = 'н';
		return Answer;
		break;
	case 'Д':
		Answer = 'д';
		return Answer;
		break;
	case 'Н':
		Answer = 'н';
		return Answer;
		break;
	case 'Y':
		Answer = 'н';
		return Answer;
		break;
	case 'L':
		Answer = 'д';
		return Answer;
		break;
	default:
		cout << endl << "Нажмите 'Д' или 'Н' !";
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
	Функция проверяет присутствие данных в дереве. Если данных нет, возвращает в главное меню.
	Входные параметры отсутствуют.
	Ничего не возвращает.
*/
void DataAvailibility() {
	if (root == NULL) {
		cout << endl << endl << "\tВ БАЗЕ НЕТ ДАННЫХ! ПОВТОРИТЕ ПОПЫТКУ ПОЗЖЕ!" << endl << endl;
		_getch();
		PrintMainMenu();
	}
}