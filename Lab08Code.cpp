#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

class Matrix {
private:
    int size;
    std::vector<std::vector<int>> data;

public:
    // Constructor to initialize matrix with a given size
    Matrix(int n) : size(n), data(n, std::vector<int>(n, 0)) {}

    // Function to load matrix from a file
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    file >> data[i][j];
                }
            }
            file.close();
        } else {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }

    // Function to display the matrix
    void display() const {
        for (const auto& row : data) {
            for (int element : row) {
                std::cout << std::setw(4) << element;
            }
            std::cout << std::endl;
        }
    }

    // Operator overloading for matrix addition
    Matrix operator+(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Operator overloading for matrix multiplication
    Matrix operator*(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < size; ++k) {
                    result.data[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Function to calculate the sum of diagonal elements
    int diagonalSum() const {
        int mainDiagonalSum = 0, secondaryDiagonalSum = 0;
        for (int i = 0; i < size; ++i) {
            mainDiagonalSum += data[i][i];
            secondaryDiagonalSum += data[i][size - i - 1];
        }
        return mainDiagonalSum + secondaryDiagonalSum;
    }

    // Function to swap two rows
    void swapRows(int row1, int row2) {
        if (row1 >= 0 && row1 < size && row2 >= 0 && row2 < size) {
            std::swap(data[row1], data[row2]);
        } else {
            std::cerr << "Invalid row indices." << std::endl;
        }
    }
};

// Main function to demonstrate matrix operations
int main() {
    int size;
    std::cout << "Enter the matrix size: ";
    std::cin >> size;

    // Initialize two matrices
    Matrix matrixA(size);
    Matrix matrixB(size);

    // Prompt the user to enter file names
    std::string fileA, fileB;
    std::cout << "Enter the filename for Matrix A: ";
    std::cin >> fileA;
    std::cout << "Enter the filename for Matrix B: ";
    std::cin >> fileB;

    // Load data from files
    matrixA.loadFromFile(fileA);
    matrixB.loadFromFile(fileB);

    std::cout << "\nMatrix A:" << std::endl;
    matrixA.display();
    std::cout << "\nMatrix B:" << std::endl;
    matrixB.display();

    // Matrix addition
    Matrix additionResult = matrixA + matrixB;
    std::cout << "\nA + B:" << std::endl;
    additionResult.display();

    // Matrix multiplication
    Matrix multiplicationResult = matrixA * matrixB;
    std::cout << "\nA * B:" << std::endl;
    multiplicationResult.display();

    // Diagonal sum
    int diagSum = matrixA.diagonalSum();
    std::cout << "\nSum of main and secondary diagonal elements of A: " << diagSum << std::endl;

    // Row swapping
    int row1, row2;
    std::cout << "Enter two row indices to swap in Matrix A: ";
    std::cin >> row1 >> row2;
    matrixA.swapRows(row1, row2);
    std::cout << "\nMatrix A after swapping rows " << row1 << " and " << row2 << ":" << std::endl;
    matrixA.display();

    return 0;
}
