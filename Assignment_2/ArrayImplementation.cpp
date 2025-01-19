#include <iostream>
#include <vector>
using namespace std;

class SparseMatrix {
private:
    struct Element {
        int row;
        int col;
        int value;
    };

    int rows, cols;
    vector<Element> elements;

public:
    SparseMatrix(int rows, int cols) : rows(rows), cols(cols) {}

    void addElement(int row, int col, int value) {
        if (value != 0) {
            elements.push_back({row, col, value});
        }
    }

    void display() const {
        cout << "Sparse Matrix (Row, Column, Value):\n";
        for (const auto& element : elements) {
            cout << element.row << " " << element.col << " " << element.value << endl;
        }
    }

    void displayFullMatrix() const {
        cout << "Full Matrix:\n";
        size_t currentIndex = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (currentIndex < elements.size() && elements[currentIndex].row == i && elements[currentIndex].col == j) {
                    cout << elements[currentIndex].value << " ";
                    ++currentIndex;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    int noOfRows, noOfColumns;

    cout << "Enter the number of rows: ";
    cin >> noOfRows;

    cout << "Enter the number of columns: ";
    cin >> noOfColumns;

    SparseMatrix matrix(noOfRows, noOfColumns);

    int numberOfElements;
    cout << "Enter the number of non-zero elements: ";
    cin >> numberOfElements;

    for (int i = 0; i < numberOfElements; ++i) {
        int row, col, value;
        cout << "Enter row index: ";
        cin >> row;
        cout << "Enter column index: ";
        cin >> col;
        cout << "Enter value: ";
        cin >> value;
        matrix.addElement(row, col, value);
    }

    matrix.display();
    matrix.displayFullMatrix();

    return 0;
}
