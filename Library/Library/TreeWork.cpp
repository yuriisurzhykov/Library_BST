#include "Header.h"
#include <iostream>
#include <Windows.h>
#include <string>

#pragma region Add Node
Library addNode(Library** node, Library* parent, Library data) {
	//���� ���� ������, �� ������� ���� ������
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
	else { // ���� �� ������, �� ���������� � ������� �����
		if (data.publishingYear >= (*node)->publishingYear) //�������� �������� ������ ��������, ���� ������
			return addNode(&(*node)->right, (*node), data);
		else  //�������� �������� ������ ��������, ���� �����
			return addNode(&(*node)->Left, (*node), data);
	}
}
#pragma endregion

#pragma region Delete And Search Node

//������� �������� ������� ���� ������
int DeleteData(string Search) {
	Library** NeededElem = new Library*;
	*NeededElem = SearchName(root, Search);

	//���� ��������� �� �������� ����� ������ ����� ����, ������ ������� ����� �� �������,
	//������� ���������� 0
	if (*NeededElem == NULL)
		return 0;
	//� ��������� �������� ��� �������� - ����� ������� ������.
	if ((*NeededElem)->right == NULL && (*NeededElem)->Left == NULL) {
		if ((*NeededElem) == root) {
			root = NULL;
		}
		else if ((*NeededElem)->Parent->right == (*NeededElem)) {//�������� ����� �������� - ������ ��� �����, �������� �������� �������
			(*NeededElem)->Parent->right = NULL; //������� ��������, ��� ������ � ���� ��� �������.
		}
		else (*NeededElem)->Parent->Left = NULL; //������� ��������, ��� ������ � ���� ��� �������.
	}

	//� ��������� �������� ���� ������ �������
	else if ((*NeededElem)->Left == NULL) {
		if ((*NeededElem) == root) {
			root = root->right;
		}
		else {
			if ((*NeededElem)->Parent->right == (*NeededElem)) { //�������� ����� �������� - ������ ��� �����, �������� �������� �������
				(*NeededElem)->right->Parent = (*NeededElem)->Parent; //������� ������� ��������� ��������, ��� ������ ��� �������� - ��� �������� ��������� ��������.
				(*NeededElem)->Parent->right = (*NeededElem)->right; //������� ��������, ��� ������ ��� �������, ��� ������� ������� ��������
			}
			else {
				(*NeededElem)->right->Parent = (*NeededElem)->Parent;
				(*NeededElem)->Parent->Left = (*NeededElem)->right;
			}
		}
	}

	//� ��������� �������� ���� ����� �������
	else if ((*NeededElem)->right == NULL) {
		if ((*NeededElem) == root) {
			root = root->Left;
		}
		else {
			if ((*NeededElem)->Parent->right == (*NeededElem)) {  //�������� ����� �������� - ������ ��� �����, �������� �������� �������
				(*NeededElem)->Parent->right = (*NeededElem)->Left; //������� ��������, ��� ������ ��� �������, ��� ������� ������� ��������
				(*NeededElem)->Left->Parent = (*NeededElem)->Parent; //������� ������� ��������� ��������, ��� ������ ��� �������� - ��� �������� ��������� ��������.
			}
			else {
				(*NeededElem)->Parent->Left = (*NeededElem)->Left;  //������� ��������, ��� ������ ��� �������, ��� ������� ������� ��������
				(*NeededElem)->Left->Parent = (*NeededElem)->Parent;  //������� ������� ��������� ��������, ��� ������ ��� �������� - ��� �������� ��������� ��������
			}
		}
	}

	//����� ������� ������. � ��������� �������� 2 �������.
	else {
		Library* MinRightElem = (*NeededElem)->right; //��������� ��������� �� ����������� ������� ������� ���������
		while (MinRightElem->Left) {
			MinRightElem = MinRightElem->Left; //���� ���� ����� ����������� �������
		}
		if (!MinRightElem->right) { //���� � ���.�������� ��� ������� �������
			if ((*NeededElem) == root) {  // ���� ��������� ������� - ������ ������
				if (MinRightElem == (*NeededElem)->right) { // ���� ����������� ������� ������� ���������, ��� ������ ������� ���������� ��������
					root->Left->Parent = MinRightElem;  //������� ������� ���������� ��������, ��� ��� �������� - ��� ������ ��� ��������� ���.�������
					MinRightElem->Left = root->Left; //������ ���.��-�� ����� ������. �������, ��� ����� ������� ���.��-��, ��� ����� ������� ���������� ��������
					MinRightElem->right = NULL;  //�������, ��� � ������ ����� ��� ������ �����, ��� ��� ��� ����� ������ ��� ������������ ��������
					MinRightElem->Parent = NULL; //�������, ��� �������� � ���� ���
					root = MinRightElem; //� ����������� ��������� �� ������ ����� ������ ��������
				}
				else { //���� ���.������� �� �������� ������ �������� ���������� ��������
					root->Left->Parent = MinRightElem; //������� ������ ������� ���������� �������� ��� ��� �������� - ��� ���.�������, ������� ��������� 
					root->right->Parent = MinRightElem;//������� ������� ������� ���������� �������� ��� ��� �������� - ��� ���.�������, ������� ��������� 
					//������� �������� ���.��������, ��� ������ � ���� ��� �������
					MinRightElem->Parent->Left = NULL;
					//�������� ���.������� ������ ��� ����� �����
					MinRightElem->Left = root->Left;
					MinRightElem->right = root->right;
					//������� ���.��������, ��� � ���� ��� ���������
					MinRightElem->Parent = NULL;
					//����������� ��������� �� ������ ������ ����� �����
					root = MinRightElem;
				}
			}
			else { //���� ��������� ������� �� ������, � ���.�������� ������� ��������� ��� ������� �������
				if (MinRightElem == (*NeededElem)->right) {
					//������� ������� ���������� ��������, ��� ��� �������� - ��� ������ ��� ��������� ���.�������
					(*NeededElem)->Left->Parent = MinRightElem;
					//�������, ��� ����� ������� ���.��-��, ��� ����� ������� ���������� ��������
					MinRightElem->Left = (*NeededElem)->Left;
					//�������, ��� ������ �������� � ���.�������� ������ ���
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
					MinRightElem->Parent->Left = NULL; //������� �������� ������������ ��������, ��� � ���� ������ ��� �������
					//������� ������ ������� ���������� �������� ����� ������ ��������
					(*NeededElem)->Left->Parent = MinRightElem;
					//������� ������� ������� ���������� �������� ����� ������ ��������
					(*NeededElem)->right->Parent = MinRightElem;
					//����������� ���.�������� ������ ��� ����� ��������
					MinRightElem->Left = (*NeededElem)->Left;
					MinRightElem->right = (*NeededElem)->right;
					//������ ���.�������� ����� ��� ������ ��������
					MinRightElem->Parent = (*NeededElem)->Parent;

					if ((*NeededElem)->Parent->right == (*NeededElem)) {
						//���� ��������� ������� - ������ �������, �� ������� ��������, ��� ��� ������ �������, ��� ������ ���.�������
						(*NeededElem)->Parent->right = MinRightElem;
					}
					else {
						//���� ��������� ������� - ����� �������, �� ������� ��������, ��� ��� �����  �������, ��� ������ ���.�������
						(*NeededElem)->Parent->Left = MinRightElem;
					}
				}
			}
		}
		else {  //���� � ��� �������� ���� ������ �������
			if ((*NeededElem) == root) { // ���� ��������� ������� - ��� ������ ����� ������
				if (MinRightElem == (*NeededElem)->right) { // ���� ���.������� ������� ���������, ��� ������ �������, ���������� ��������.
					//�������� ���.�������� ��� ������ ����� ��������
					MinRightElem->Left = root->Left;
					//�������, ���.�������� ��� � ���� ��� ��������
					MinRightElem->Parent = NULL;
					//��������� ����� ������� � ����� ������
					root->Left->Parent = MinRightElem;
					//����������� ��������� �� ������ ������ ����� �����
					root = MinRightElem;
				}
				else { //���� ���.������� ������� ���������, �� �������� ������ ��������, ���������� ��������.
					//��������� ������� ������� ���.�������� � ��������� ����� ���.��������
					MinRightElem->right->Parent = MinRightElem->Parent;
					//��������� �������� ���.�������� � ������ �������� ����� ���.��������
					MinRightElem->Parent->Left = MinRightElem->right;
					//�������� ���.�������� ������ ��� ����� ��������
					MinRightElem->Left = root->Left;
					MinRightElem->right = root->right;
					//�������, ��� �������� � ���� ���
					MinRightElem->Parent = NULL;
					//��������� �������� ����� ������ � ����� ���������
					root->Left->Parent = MinRightElem;
					root->right->Parent = MinRightElem;
					//����������� ��������� �� ������ ������ ����� �����
					root = MinRightElem;
				}
			}
			else {
				//�� �������� � ���������� ������� ������ ����� ��� ���� �����
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
	//������� ������ �������
	delete (*NeededElem);
	(*NeededElem) = NULL;
	delete NeededElem;
	return 1;
}

//������� ������ ������� ���� ������
//��� ��������� ������ �������, �������� ������� ���������� ���� � ������.
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
	cout << "������ ϲ� ������: ";
	cin >> inputable->fullName;
	cin.clear();
	cout << "������ ��� ����� �����: ";
	cin >> inputable->ukdNumber;
	cin.clear();
	cout << "������ ����� �����: ";
	cin >> inputable->bookName;
	cin.clear();
	string temp;
	cout << "������ �� �������: ";
	cin >> temp;
	cin.clear();
	/*while (!CheckStringToNumb(temp)) {
		cout << "��������� ������ �����!" << endl;
		cin >> temp;
		cin.clear();
	}*/
	inputable->publishingYear = StringToInt(temp);
	cout << "������ ������� ���������: ";
	cin >> temp;
	cin.clear();
	/*while (!CheckStringToNumb(temp)) {
		cout << "��������� ������ �����!" << endl;
		cout << "��������� �� ���!" << endl;
		cin >> temp;
		cin.clear();
	}*/
	inputable->amountInstances = StringToInt(temp);
	addNode(&root, NULL, *inputable);
	system("cls");
}

#pragma endregion


