#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>

using namespace std;

template<typename T>
class Node {
public:
	Node() {
		nextInRow = nextInColumn = nullptr;
	}
	Node(T& v) {
		nextInRow = nextInColumn = nullptr;
		value = v;
	}
	
	T value;
	Node<T>* nextInRow, * nextInColumn;
};

const int MAX_COL = 100;

template<typename T>
class Matrix {
public:
	Matrix() : row(0), col(0) {
		front = nullptr;
	}

	Matrix(T** m, int row, int col) : row(row), col(col) {
		if (row < 0 || col < 0) {
			throw runtime_error("Row and Column can't be negative");
		}

		Node<T>* temp = front;
		Node<T>* tempPivot = front;
		for (int i = 0; i < row; i++) {
			Node<T>* pivot = new Node<T>(m[i][0]);
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
				Node<T>* node = new Node<T>(m[i][j]);
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
					for (int k = 0; k <= count; k++) {
						temp = temp->nextInColumn;
					}
					count++;
				}
			}
		}

	}
	Matrix(const Matrix& obj) : col(obj.col), row(obj.row) {
		Node<T>* tempObj = obj.front;
		Node<T>* temp = front;
		Node<T>* tempPivot = front;
		int count = 0;
		for (int i = 0; i < row; i++) {
			Node<T>* pivot = new Node<T>(tempObj->value);
			if (i == 0) {
				front = pivot;
				temp = front;
				tempPivot = front;
			}
			else {
				tempPivot->nextInRow = pivot;
				tempPivot = tempPivot->nextInRow;
				temp = tempPivot;
			}
			for (int j = 1; j < col; j++) {
				tempObj = tempObj->nextInColumn;

				Node<T>* node = new Node<T>(tempObj->value);
				temp->nextInColumn = node;
				temp = temp->nextInColumn;
			}
			tempObj = obj.front;
			for (int k = 0; k <= count; k++) {
				tempObj = tempObj->nextInRow;
			}
			count++;
		}

		count = 0;
		temp = front;

		for (int i = 1; i < row; i++) {
			for (int j = 1; j < col; j++) {
				temp->nextInColumn->nextInRow = temp->nextInRow->nextInColumn;
				temp = temp->nextInRow;
				if (temp->nextInRow == nullptr) {
					temp = front;
					for (int k = 0; k <= count; k++) {
						temp = temp->nextInColumn;
					}
					count++;
				}
			}
		}
	}
	Matrix& operator=(const Matrix& obj){
		if (this != &obj) {
			row = obj.row;
			col = obj.col;
			
			Node<T>* tempObj = obj.front;
			Node<T>* temp = front;
			Node<T>* tempPivot = front;
			int count = 0;
			for (int i = 0; i < row; i++) {
				Node<T>* pivot = new Node<T>(tempObj->value);
				if (i == 0) {
					front = pivot;
					temp = front;
					tempPivot = front;
				}
				else {		
					tempPivot->nextInRow = pivot;
					tempPivot = tempPivot->nextInRow;
					temp = tempPivot;
				}
				for (int j = 1; j < col; j++) {
					tempObj = tempObj->nextInColumn;

					Node<T>* node = new Node<T>(tempObj->value);
					temp->nextInColumn = node;
					temp = temp->nextInColumn;
				}
				tempObj = obj.front;
				for (int k = 0; k <= count; k++) {
					tempObj = tempObj->nextInRow;
				}
				count++;
			}

			count = 0;
			temp = front;

			for (int i = 1; i < row; i++) {
				for (int j = 1; j < col; j++) {
					temp->nextInColumn->nextInRow = temp->nextInRow->nextInColumn;
					temp = temp->nextInRow;
					if (temp->nextInRow == nullptr) {
						temp = front;
						for (int k = 0; k <= count; k++) {
							temp = temp->nextInColumn;
						}
						count++;
					}
				}
			}
		}

		return *this;
	}
	Matrix(Matrix&& obj): row(obj.row), col(obj.col) {
		front = obj.front;
		obj.front = nullptr;
	}
	
	Matrix& operator=(Matrix&& obj) {
		
		if (this != &obj) {
			front = obj.front;
			col = obj.col;
			row = obj.row;

			obj.front = nullptr;
		}
		return *this;
	}

	~Matrix() {	
		
		if (front != nullptr) {
			Node <T>* temp = front, * nextRow = front->nextInRow;
			for (int i = 1; i < row; i++) {
				for (int j = 1; j < col; j++, nextRow = temp->nextInRow) {
					Node<T>* nodeToDelete = temp;
					temp = temp->nextInColumn;
					delete nodeToDelete;
				}
				temp = nextRow;
			}
			delete nextRow;
			delete temp;
		}		
	}

	Matrix<T> getRow(int r) {
		if (r > row || r <= 0) {
			throw("Out of range row");
		}

		Matrix result;
		result.row = 1;
		result.col = col;

		Node<T>* tempResult = result.front;
		Node<T>* temp = front;
		for (int i = 0; i < r - 1; i++) {
			temp = temp->nextInRow;
		}

		for (int i = 0; i < col; i++) {
			Node<T>* node = new Node<T>(temp->value);
			if (i == 0) {
				result.front = node;
				tempResult = result.front;
			}
			else {
				tempResult->nextInColumn = node;
				tempResult = tempResult->nextInColumn;
			}
			temp = temp->nextInColumn;
		}

		return result;
	}
	Matrix<T> getCol(int c) {
		if (c > col || c <= 0) {
			throw("out of range column");
		}
		Matrix result;
		result.row = row;
		result.col = 1;
		
		Node<T>* tempResult = result.front;
		Node<T>* temp = front;
		for (int i = 0; i < c - 1; i++) {
			temp = temp->nextInColumn;
		}

		for (int i = 0; i < row; i++) {
			Node<T>* node = new Node<T>(temp->value);
			if (i == 0) {
				result.front = node;
				tempResult = result.front;
			}
			else {
				tempResult->nextInRow = node;
				tempResult = tempResult->nextInRow;
			}
			temp = temp->nextInRow;
		}

		return result;
	}
	T& getElement(int row, int col) {
		if (row < 0 || col < 0 || row > this->row || col > this->col) {
			throw runtime_error("Out of Node!");
		}
		Node<T>* temp = front;
		for (int i = 1; i < row; i++) {
			temp = temp->nextInRow;
		}
		for (int i = 1; i < col; i++) {
			temp = temp->nextInColumn;
		}
		return temp->value;
	}
	Matrix<T> transpose(const Matrix& obj) {
		/*Matrix<T> result = obj;
		
		Node<T>* tempToSwap = front;
		Node<T>* temp = front;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				temp->nextInColumn 
			}
		}*/
	}
	Matrix operator+(const Matrix& obj) {
		if (obj.col != col && obj.row != row) {
			throw ("Both Matrix must have same size to add.");
		}

		T** thisArr = new T * [row];
		for (int i = 0; i < row; i++) {
			thisArr[i] = new T[col];
		}

		Node<T>* temp = front;
		for (int i = 0; i < row; i++) {
			temp = front;
			for (int k = i; k > 0; k--) {
				temp = temp->nextInRow;
			}
			for (int j = 0; j < col; j++) {
				thisArr[i][j] = temp->value;
				temp = temp->nextInColumn;
			}
		}

		T** objArr = new T * [row];
		for (int i = 0; i < row; i++) {
			objArr[i] = new T[col];
		}

		temp = obj.front;
		for (int i = 0; i < row; i++) {
			temp = obj.front;
			for (int k = i; k > 0; k--) {
				temp = temp->nextInRow;
			}
			for (int j = 0; j < col; j++) {
				objArr[i][j] = temp->value;
				temp = temp->nextInColumn;
			}
		}

		T** resultArr = new T * [row];
		for (int i = 0; i < row; i++) {
			resultArr[i] = new T[col];
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				resultArr[i][j] = thisArr[i][j] + objArr[i][j];
			}
		}

		for (int i = 0; i < row; i++) {
			delete[] thisArr[i];
			delete[] objArr[i];
		}
		delete[] thisArr;
		delete[] objArr;

		Matrix result(resultArr, row, col);
		return result;
	}

	Matrix& operator*(const Matrix& obj) {}

	template<typename T>
	friend ostream& operator<<(ostream& out, const Matrix<T>& m) {
		Node<T>* temp = m.front;
		int count = 0;

		for (int i = 0; i < m.row; i++) {
			if (i > 0) {
				temp = m.front;
				for (int k = 0; k <= count; k++) {
					temp = temp->nextInRow;
				}
				count++;
			}

			out << temp->value << '\t';

			for (int j = 1; j < m.col; j++) {
				temp = temp->nextInColumn;
				out << temp->value << '\t';
			}

			cout << endl;
		}

		return out;
	}
private:
	Node<T>* front;
	int row, col;
};

template<typename T>
ostream& operator<<(ostream& out, const Matrix<T>& m);

#endif
/*
template<typename T>
Node<T>* copy(Node<T>* m) {
	Node<T>* pointerToReturn = nullptr;
	Node<T>* preRow = nullptr;
	
	while (m != nullptr) {
		Node <T>* currentRow = copyRow(m);
		
		m = m->nextInColumn;
		
		if (pointerToReturn == nullptr) {
			pointerToReturn = currentRow;
		}


		if (prevRow != nullptr) {
			for (Node<T>* prevTemp = PrevRow, *currTemp = currentRow; prevTemp->nextInRow != nullptr; prevTemp = ptrvTemp->nextInRow, currTemp = currTemp->nextInRpw) {
				prevTemp->nextInColumn = currTemp;
			}
		}
		prevRow = currRow;

	}
	return pointerToReturn;
}

template<typename T>
Node<T>* copytRow(Node<T>* r) {
	if (r == nullptr) {
		return r;
	}
	
	Node<T>* front = new Node<T>(r->value);
	front -> nexInRow = copyRow(r->nextInRow);

	return front;
}*/