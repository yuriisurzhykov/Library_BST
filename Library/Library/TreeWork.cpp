#include "Header.h"
#include <iostream>
#include <Windows.h>
#include <string>

#pragma region Add Node
Library addNode(Library** node, Library* parent, Library data) {
	//Если узел пустой, то заносим туда данные
	if ((*node) == NULL) {
		(*node) = new Library;
		(*node)->bookName = data.bookName;
		(*node)->amountInstances = data.amountInstances;
		(*node)->publishingYear = data.publishingYear;
		(*node)->fullName = data.fullName;
		(*node)->ukdNumber = data.ukdNumber;
		(*node)->Left = (*node)->right = NULL;
		(*node)->Parent = parent;
		return *(*node);
	}
	else { // Если не пустой, то сравниваем с текущим узлом
		if (data.publishingYear >= (*node)->publishingYear) //Вносимое значение больше текущего, идем вправо
			return addNode(&(*node)->right, (*node), data);
		else  //Вносимое значение меньше текущего, идем влево
			return addNode(&(*node)->Left, (*node), data);
	}
}
#pragma endregion

#pragma region Delete And Search Node

//Функция удаления нужного узла дерева
int DeleteData(string Search) {
	Library** NeededElem = new Library*;
	*NeededElem = SearchName(root, Search);

	//Если указатель на найденый адрес памяти равен нуль, значит элемент найти не удалось,
	//поэтому возвращаем 0
	if (*NeededElem == NULL)
		return 0;
	//У найденого элемента нет потомков - Самый простой случай.
	if ((*NeededElem)->right == NULL && (*NeededElem)->Left == NULL) {
		if ((*NeededElem) == root) {
			root = NULL;
		}
		else if ((*NeededElem)->Parent->right == (*NeededElem)) {//Выясняем каким потомком - правым или левым, является найденый элемент
			(*NeededElem)->Parent->right = NULL; //Говорим родителю, что теперь у него нет потомка.
		}
		else (*NeededElem)->Parent->Left = NULL; //Говорим родителю, что теперь у него нет потомка.
	}

	//У найденого элемента есть правый потомок
	else if ((*NeededElem)->Left == NULL) {
		if ((*NeededElem) == root) {
			root = root->right;
		}
		else {
			if ((*NeededElem)->Parent->right == (*NeededElem)) { //Выясняем каким потомком - правым или левым, является найденый элемент
				(*NeededElem)->right->Parent = (*NeededElem)->Parent; //Говорим потомку найденого элемента, что теперь его родитель - это родитель найденого элемента.
				(*NeededElem)->Parent->right = (*NeededElem)->right; //Говорим родителю, что теперь его потомок, это потомок потомка элемента
			}
			else {
				(*NeededElem)->right->Parent = (*NeededElem)->Parent;
				(*NeededElem)->Parent->Left = (*NeededElem)->right;
			}
		}
	}

	//У найденого элемента есть левый потомок
	else if ((*NeededElem)->right == NULL) {
		if ((*NeededElem) == root) {
			root = root->Left;
		}
		else {
			if ((*NeededElem)->Parent->right == (*NeededElem)) {  //Выясняем каким потомком - правым или левым, является найденый элемент
				(*NeededElem)->Parent->right = (*NeededElem)->Left; //Говорим родителю, что теперь его потомок, это потомок потомка элемента
				(*NeededElem)->Left->Parent = (*NeededElem)->Parent; //Говорим потомку найденого элемента, что теперь его родитель - это родитель найденого элемента.
			}
			else {
				(*NeededElem)->Parent->Left = (*NeededElem)->Left;  //Говорим родителю, что теперь его потомок, это потомок потомка элемента
				(*NeededElem)->Left->Parent = (*NeededElem)->Parent;  //Говорим потомку найденого элемента, что теперь его родитель - это родитель найденого элемента
			}
		}
	}

	//Самый сложный случай. У найденого элемента 2 потомка.
	else {
		Library* MinRightElem = (*NeededElem)->right; //Объявляем указатель на минимальный элемент правого поддерева
		while (MinRightElem->Left) {
			MinRightElem = MinRightElem->Left; //Ищем этот самый минимальный элемент
		}
		if (!MinRightElem->right) { //Если у мин.элемента нет правого потомка
			if ((*NeededElem) == root) {  // Если удаляемый элемент - корень дерева
				if (MinRightElem == (*NeededElem)->right) { // Если минимальный элемент правого поддерева, это правый ребенок удаляемого элемента
					root->Left->Parent = MinRightElem;  //Говорим потомку удаляемого элемента, что его родитель - это только что найденный мин.элемент
					MinRightElem->Left = root->Left; //Делаем мин.эл-нт нашим корнем. Говорим, что левый потомок мин.эл-та, это левый потомок удаляемого элемента
					MinRightElem->right = NULL;  //Говорим, что у нового корня нет правых детей, так как был новый элемен был единственным потомком
					MinRightElem->Parent = NULL; //Говорим, что родителя у него нет
					root = MinRightElem; //И присваиваем указателю на корень адрес нового элемента
				}
				else { //Если мин.элемент не является правым потомком удаляемого элемента
					root->Left->Parent = MinRightElem; //Говорим левому ребенку удаляемого элемента что его родитель - это мин.элемент, правого поддерева 
					root->right->Parent = MinRightElem;//Говорим правому ребенку удаляемого элемента что его родитель - это мин.элемент, правого поддерева 
					//Говорим родителю мин.элемента, что теперь у него нет потомка
					MinRightElem->Parent->Left = NULL;
					//Сообщаем мин.элменту адреса его новых детей
					MinRightElem->Left = root->Left;
					MinRightElem->right = root->right;
					//Говорим мин.элементу, что у него нет родителей
					MinRightElem->Parent = NULL;
					//Присваиваем указателю на корень дерева новый адрес
					root = MinRightElem;
				}
			}
			else { //Если удаляемый элемент не корень, и мин.элемента правого поддерева нет правого потомка
				if (MinRightElem == (*NeededElem)->right) {
					//Говорим потомку удаляемого элемента, что его родитель - это только что найденный мин.элемент
					(*NeededElem)->Left->Parent = MinRightElem;
					//Говорим, что левый потомок мин.эл-та, это левый потомок удаляемого элемента
					MinRightElem->Left = (*NeededElem)->Left;
					//Говорим, что правых потомков у мин.элемента теперь нет
					MinRightElem->right = NULL;
					MinRightElem->Parent = (*NeededElem)->Parent;

					if ((*NeededElem)->Parent->right == (*NeededElem)) {
						(*NeededElem)->Parent->right = MinRightElem;
					}
					else {
						(*NeededElem)->Parent->Left = MinRightElem;
					}
				}
				else {
					MinRightElem->Parent->Left = NULL; //Говорим родителю минимального элемента, что у него теперь нет потомка
					//Говорим левому потомку удаляемого элемента адрес нового родителя
					(*NeededElem)->Left->Parent = MinRightElem;
					//Говорим правому потомку удаляемого элемента адрес нового родителя
					(*NeededElem)->right->Parent = MinRightElem;
					//Присваиваем мин.элементу адреса его новых потомков
					MinRightElem->Left = (*NeededElem)->Left;
					MinRightElem->right = (*NeededElem)->right;
					//Говрим мин.элементу адрес его нового родителя
					MinRightElem->Parent = (*NeededElem)->Parent;

					if ((*NeededElem)->Parent->right == (*NeededElem)) {
						//Если удаляемый элемент - правый потомок, то говорим родителю, что его правый потомок, это теперь мин.элемент
						(*NeededElem)->Parent->right = MinRightElem;
					}
					else {
						//Если удаляемый элемент - левый потомок, то говорим родителю, что его левый  потомок, это теперь мин.элемент
						(*NeededElem)->Parent->Left = MinRightElem;
					}
				}
			}
		}
		else {  //Если у мин элменета есть правый потомок
			if ((*NeededElem) == root) { // Если удаляемый элемент - это корень всего дерева
				if (MinRightElem == (*NeededElem)->right) { // Если мин.элемент правого поддерева, это правый потомок, удаляемого элемента.
					//Сообщаем мин.элементу его адреса новых потомков
					MinRightElem->Left = root->Left;
					//Говорим, мин.элементу что у него нет родителя
					MinRightElem->Parent = NULL;
					//Связываем левый элемент с новым корнем
					root->Left->Parent = MinRightElem;
					//Присваиваем указателю не корень дерева новый адрес
					root = MinRightElem;
				}
				else { //Если мин.элемент правого поддерева, не является правым потомком, удаляемого элемента.
					//Связываем правого потомка мин.элемента с родителем этого мин.элемента
					MinRightElem->right->Parent = MinRightElem->Parent;
					//Связываем родителя мин.элемента с правым потомком этого мин.элемента
					MinRightElem->Parent->Left = MinRightElem->right;
					//Сообщаем мин.элементу адреса его новых потомков
					MinRightElem->Left = root->Left;
					MinRightElem->right = root->right;
					//Говорим, что родителя у него нет
					MinRightElem->Parent = NULL;
					//Связываем потомков корня дерева с новым элементом
					root->Left->Parent = MinRightElem;
					root->right->Parent = MinRightElem;
					//Присваиваем указателю не корень дерева новый адрес
					root = MinRightElem;
				}
			}
			else {
				//По аналогии с предыдущим случаем делаем почти все тоже самое
				if (MinRightElem == (*NeededElem)->right) {
					(*NeededElem)->Left->Parent = MinRightElem;
					MinRightElem->Parent = (*NeededElem)->Parent;
					MinRightElem->Left = (*NeededElem)->Left;
					if ((*NeededElem)->Parent->right == (*NeededElem)) {
						(*NeededElem)->Parent->right = MinRightElem;
					}
					else {
						(*NeededElem)->Parent->Left = MinRightElem;
					}
				}
				else {
					MinRightElem->right->Parent = MinRightElem->Parent;
					MinRightElem->Parent->Left = MinRightElem->right;
					MinRightElem->Left = (*NeededElem)->Left;
					MinRightElem->right = (*NeededElem)->right;
					MinRightElem->Parent = (*NeededElem)->Parent;
					(*NeededElem)->Left->Parent = MinRightElem;
					(*NeededElem)->right->Parent = MinRightElem;
					if ((*NeededElem)->Parent->right == (*NeededElem)) {
						(*NeededElem)->Parent->right = MinRightElem;
					}
					else {
						(*NeededElem)->Parent->Left = MinRightElem;
					}
				}
			}
		}
	}
	//Удаляем нужный элемент
	delete (*NeededElem);
	(*NeededElem) = NULL;
	delete NeededElem;
	return 1;
}

//Функция поиска нужного узла дерева
//Для понимания работы функции, смотреть функцию добавления узла в дерево.
Library* SearchName(Library* node, string SearchData) {
	if (node == NULL || node->ukdNumber == SearchData)
		return node;
	else if (SearchData > node->ukdNumber)
		return SearchName(node->right, SearchData);
	else 
		return SearchName(node->Left, SearchData);
}

#pragma endregion

#pragma region Print Tree Functions

void PrintTree(Library* Branch) {
	if (Branch == NULL) return;
	else {
		PrintTree(Branch->Left);
		cout << "\t" << "|" << setw(4) << right << ++Position;
		cout << "|";
		cout << setw(33) << left << Branch->fullName << " | ";
		cout << setw(12) << right << Branch->ukdNumber;
		cout << "|";
		cout << setw(18) << right << Branch->bookName;
		cout << "|";
		cout << setw(11) << right << Branch->amountInstances;
		cout << "|";
		cout << setw(11) << right << Branch->publishingYear;
		cout << "|" << endl;
		cout << "\t" << "+----+------------------------------------------------+------------------------------------------+" << endl;
		PrintTree(Branch->right);
	}
}

#pragma endregion

#pragma region Entered Data Functions

void InputData() {
	Library* inputable = new Library;
	cout << "Введіть ПІБ автора: ";
	cin >> inputable->fullName;
	cin.clear();
	cout << "Введіть УКД номер книги: ";
	cin >> inputable->ukdNumber;
	cin.clear();
	cout << "Введіть назву книги: ";
	cin >> inputable->bookName;
	cin.clear();
	string temp;
	cout << "Введіть рік видання: ";
	cin >> temp;
	cin.clear();
	/*while (!CheckStringToNumb(temp)) {
		cout << "Неможливо ввести букву!" << endl;
		cin >> temp;
		cin.clear();
	}*/
	inputable->publishingYear = StringToInt(temp);
	cout << "Введіть кількість примірників: ";
	cin >> temp;
	cin.clear();
	/*while (!CheckStringToNumb(temp)) {
		cout << "Неможливо ввести букву!" << endl;
		cout << "Спробуйте ще раз!" << endl;
		cin >> temp;
		cin.clear();
	}*/
	inputable->amountInstances = StringToInt(temp);
	addNode(&root, NULL, *inputable);
	system("cls");
}

#pragma endregion


