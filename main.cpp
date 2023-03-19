#include<iostream>
#include"Matrix.h"

using namespace std;

int main() {
	int arrayValue = 0;
	int** mat = new int* [3];
	for (int i = 0; i < 3; i++) {
		mat[i] = new int[3];
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mat[i][j] = ++arrayValue;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << mat[i][j];
		}
		cout << endl;
	}
	int ma[3][MAX_COL] = { {1,2,3}, {3,4,4}, {5,6,6} };
	/*for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << ma[i][j];
		}
		cout << endl;
	}*/

	cout << "Create new matrix from 2d array (parameterized constructor):\n" << endl;
	Matrix<int>a(mat, 3, 3);
	cout << a << endl;
	
	cout << "Copy last created matrix to new array (copy assignment operator):\n" << endl;
	Matrix<int>b; 
	b = a;
	cout << b << endl;

	cout << "Create new matrix from last created matrix (copy constructor):\n" << endl;
	Matrix<int>c(b);
	cout << c << endl;

	cout << "Get element (1,2) from matrix:\n" << endl;
	cout << c.getElement(1, 2) << endl;
	
	cout << "Get row 1 of Matrix:\n" << endl;
	cout << c.getRow(1) << endl;
	cout << "Get col 3 of Matrix:\n" << endl;
	cout << b.getCol(3) << endl;
	
	cout << "Add two matrixes together:\n" << endl;
	cout << a + b;

	cout << "Create new matrix and assign the two added matrixes to it:\n" << endl;
	Matrix<int> d;
	d = a + b;
	cout << d;

	cout << "Create new matrix from col 2 of last matrix:\n" << endl;
	Matrix<int> e = d.getCol(2);
	cout << e;
	
	//cout<<d.front->nextInColumn->nextInRow->nextInColumn->value << endl;
	//cout<<d.front->nextInRow->nextInColumn->nextInRow->nextInColumn->value << endl;

	return 0;
}



/*	row = obj.row;
		col = obj.col;
		T** tempArr = new T * [row];
		for (int i = 0; i < row; i++) {
			tempArr[i] = new T[col];
		}

		Node<T>* objTemp = obj.front;
		for (int i = 0; i < row; i++) {
			objTemp = obj.front;
			for (int k = i; k > 0; k--) {
				objTemp = objTemp->nextInRow;
			}
			for (int j = 1; j < col; j++) {
				tempArr[i][j] = objTemp->value;
				objTemp = objTemp->nextInColumn;
			}
		}

		Node<T>* temp = front;
		Node<T>* tempPivot = front;
		for (int i = 0; i < row; i++) {
			Node<T>* pivot = new Node<T>(tempArr[i][0]);
			if (i == 0) {
				front = pivot;
				temp = front;
				tempPivot = front;
			}
			else {
				tempPivot->nextInRow = pivot;
				tempPivot = tempPivot->nextInRow;
				temp = pivot;
			}
			for (int j = 1; j < col; j++) {
				Node<T>* node = new Node<T>(tempArr[i][j]);
				temp->nextInColumn = node;
				temp = temp->nextInColumn;
			}
		}

		temp = front;
		int count = 0;

		for (int i = 1; i < row; i++) {
			for (int j = 1; j < col; j++) {
				temp->nextInColumn->nextInRow = temp->nextInRow->nextInColumn;
				temp = temp->nextInRow;
				if (temp->nextInRow == nullptr) {
					temp = front;
					for (int i = 0; i <= count; i++) {
						temp = temp->nextInColumn;
					}
					count++;
				}
			}
		}

		for (int i = 0; i < row; i++) {
			delete[] tempArr[i];
		}
		delete[] tempArr;
		*/