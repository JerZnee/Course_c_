#include <iostream>
#include <vector>

using namespace std;

class Matrix {
public:
    //default constructor
    Matrix() {
        num_cols = 0;
        num_rows = 0;
    }

    Matrix(int new_rows, int new_cols) {
        Reset(new_rows, new_cols);
    }

    void Reset(int new_rows, int new_cols) {
        if (new_rows >= 0 && new_cols >= 0) {
            num_rows = new_rows;
            num_cols = new_cols;
            data.resize(num_rows, vector<int>(num_cols, 0));
        } else {
            throw out_of_range("Negative size");
        }
    }

    [[nodiscard]] int At(int row, int col) const {
        if (row >= 0 && col >= 0 && num_rows > row && num_cols > col) {
            return data[row][col];
        } else {
            throw out_of_range("Negative size");
        }
    }

    int &At(int row, int col) {
        if (row >= 0 && col >= 0 && num_rows > row && num_cols > col) {
            return data[row][col];
        } else {
            throw out_of_range("Negative size");
        }
    }

    int GetNumRows() const {
        return num_rows;
    }

    int GetNumColumns() const {
        return num_cols;
    }

    //operators overloading
    friend istream &operator>>(istream &in, Matrix &matrix);

    friend ostream &operator<<(ostream &out, const Matrix &matrix);

    bool operator==(const Matrix &other) const {
        return data == other.data;
    }

    Matrix &operator+=(const Matrix &other) {
        if (!check_size(*this, other)) {
            throw invalid_argument("Incompatible sizes of matrices ");
        }
        for (int i = 0; i < num_rows; ++i) {
            for (int j = 0; j < num_cols; ++j) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    Matrix operator+(const Matrix &other) const {
        Matrix mat = *this;
        mat += other;
        return mat;
    }

private:
    static bool check_size(const Matrix &lhs, const Matrix &rhs) {
        return lhs.num_cols == rhs.num_cols && lhs.num_rows == rhs.num_rows;
    }

    int num_rows{0}, num_cols{0};
    vector<vector<int>> data;
};

istream &operator>>(istream &in, Matrix &matrix) {
    int num_rows, num_cols;
    in >> num_rows >> num_cols;
    matrix.Reset(num_rows, num_cols);
    for (auto &row: matrix.data) {
        for (auto &el: row) {
            in >> el;
        }
    }
    return in;
}

ostream &operator<<(ostream &out, const Matrix &matrix) {
    out << matrix.num_rows << " " << matrix.num_cols << endl;
    for (auto &row: matrix.data) {
        for (auto &el: row) {
            out << el << " ";
        }
        out << endl;
    }
    return out;
}

int main() {
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;
    return 0;
}