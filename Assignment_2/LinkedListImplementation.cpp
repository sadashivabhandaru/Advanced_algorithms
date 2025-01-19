#include <iostream>
using namespace std;

struct Node {
    int row, col, value;
    Node* next;
    Node(int r, int c, int v) : row(r), col(c), value(v), next(nullptr) {}
};

class SparseMatrix {
private:
    Node* head;

    void insertNodeSorted(Node* newNode) {
        if (!head || (newNode->row < head->row) || (newNode->row == head->row && newNode->col < head->col)) {
            newNode->next = head;
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next && (current->next->row < newNode->row || (current->next->row == newNode->row && current->next->col < newNode->col))) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

public:
    SparseMatrix() : head(nullptr) {}

    void insert(int row, int col, int value) {
        if (value != 0) {
            Node* newNode = new Node(row, col, value);
            insertNodeSorted(newNode);
        }
    }

    void display() const {
        Node* current = head;
        if (!current) {
            cout << "The sparse matrix is empty." << endl;
            return;
        }
        cout << "Sparse Matrix (Row, Column, Value):" << endl;
        while (current) {
            cout << current->row << " " << current->col << " " << current->value << endl;
            current = current->next;
        }
    }

    void displayFullMatrix(int rows, int cols) const {
        Node* current = head;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (current && current->row == i && current->col == j) {
                    cout << current->value << " ";
                    current = current->next;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }

    ~SparseMatrix() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    int noOfRows, noOfColumns;

    cout << "Enter the number of rows: ";
    cin >> noOfRows;

    cout << "Enter the number of columns: ";
    cin >> noOfColumns;

    SparseMatrix matrix;

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
        matrix.insert(row, col, value);
    }

    matrix.display();
    cout << "Full Matrix:" << endl;
    matrix.displayFullMatrix(noOfRows, noOfColumns);

    return 0;
}