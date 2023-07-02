#include "hw1.h"

namespace algebra {
    // Error handling functions
    static inline void check_empty(size_t n, size_t m, std::string msg) {
        if (n == 0 || m == 0) {
            throw std::logic_error(msg + ": Size of the matrix must be non-zero.");
        }
    }
    static inline void check_valid(const Matrix& matrix, std::string msg) {
        size_t n = matrix.size();
        if (n == 0) { return; }
        size_t m = matrix[0].size();
        for (size_t i = 1; i < n; ++i) {
            if (m != matrix[i].size()) {
                throw std::logic_error(msg + ": Not a matrix at all.");
            }
        }
    }
    static inline void check_square(const Matrix& matrix, std::string msg) {
        if (matrix.size() != matrix[0].size()) {
            throw std::logic_error(msg + ": Matrix must be square.");
        }
    }

    bool equal_to_zero(double n) {
        if (abs(n) < 1e-5) {
            return true;
        }
        return false;
    }
    // Here it's worth of thinking
    // We allow the user to create a Matrix with size(10, 0)
    // But a Matrix with size(0, 10) is considered to be an empty matrix
    Matrix zeros(size_t n, size_t m) {
        if (n == 0) {
            return Matrix{};
        }
        return Matrix(n, std::vector<double>(m, 0));
    }
    Matrix ones(size_t n, size_t m) {
        if (n == 0) {
            return Matrix{};
        }
        return Matrix(n, std::vector<double>(m, 1));
    }
    Matrix random(size_t n, size_t m, double min, double max) {
        if (n == 0) {
            return Matrix{};
        }
        if (min > max) {
            throw std::logic_error("Min must be greater than max.");
        }
        Matrix res = zeros(n, m);
        std::default_random_engine e;
        std::uniform_real_distribution<double> u(min, max);
        for (auto& row : res) {
            for (auto& column : row) {
                column = u(e);
            }
        }
        return res;
    }

    void show(const Matrix& matrix) {
        check_valid(matrix, "Show");
        for (auto& row : matrix) {
            for (auto column : row) {
                std::cout << column << "  ";
            }
            std::cout << std::endl << std::endl;
        }
    }

    Matrix multiply(const Matrix& matrix, double c) {
        check_valid(matrix, "Multiply");
        Matrix res = matrix;
        for (auto& row : res) {
            for (auto& column : row) {
                column *= c;
            }
        }
        return res;
    }
    // This function don't need to check_valid
    // Cause it will trigger an error: out_of_range when multiplying
    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
        if (matrix1.size() == 0 || matrix2.size() == 0) { return Matrix{}; }
        if (matrix1[0].size() != matrix2.size()) {
            throw std::logic_error("Multiply: Dimensions are incoherent.");
        }
        size_t n = matrix1.size(), m = matrix2[0].size(), t = matrix2.size();
        Matrix res = zeros(n, m);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                // for optimizing the cache, use sum instead of res[i][j]
                double sum = 0;
                for (size_t k = 0; k < t; ++k) {
                    sum += matrix1[i][k] * matrix2[k][j];
                }
                res[i][j] = sum;
            }
        }
        return res;
    }
    Matrix sum(const Matrix& matrix, double c) {
        check_valid(matrix, "Sum");
        Matrix res = matrix;
        for (auto& row : res) {
            for (auto& column : row) {
                column += c;
            }
        }
        return res;
    }
    Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
        size_t n = matrix1.size();
        if (n == 0 && matrix2.size() == 0) { return matrix1; }
        if (n != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
            throw std::logic_error("Sum: Dimensions are incoherent.");
        }
        size_t m = matrix1[0].size();
        Matrix res = matrix1;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                res[i][j] += matrix2[i][j];
            }
        }
        return res;
    }

    Matrix transpose(const Matrix& matrix) {
        size_t n = matrix.size();
        if (n == 0) { return matrix; }
        size_t m = matrix[0].size();
        Matrix res = zeros(m, n);
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                res[i][j] = matrix[j][i];
            }
        }
        return res;
    }

    // size(0, *) or (*, 0) is not allowed.
    Matrix minor(const Matrix& matrix, size_t n, size_t m) {
        size_t nn = matrix.size();
        check_empty(nn, nn, "Minor");
        check_square(matrix, "Minor");
        if (n >= nn || m >= nn) {
            throw std::logic_error("Minor: n or m too greate.");
        }
        size_t i, j;
        Matrix res = zeros(nn - 1, nn - 1);
        for (i = 0; i < n; ++i) {
            for (j = 0; j < m; ++j) {
                res[i][j] = matrix[i][j];
            }
        }
        for (i = n + 1; i < nn; ++i) {
            for (j = 0; j < m; ++j) {
                res[i - 1][j] = matrix[i][j];
            }
        }
        for (i = 0; i < n; ++i) {
            for (j = m + 1; j < nn; ++j) {
                res[i][j - 1] = matrix[i][j];
            }
        }
        for (i = n + 1; i < nn; ++i) {
            for (j = m + 1; j < nn; ++j) {
                res[i - 1][j - 1] = matrix[i][j];
            }
        }
        return res;
    }
    // 3  2
    // 4  1
    // det = 1 * 3 * 1 + -1 * 2 * 4
    double determinant(const Matrix& matrix) {
        if (matrix.size() == 0) {
            return 1;
        }
        check_square(matrix, "Determinant");
        if (matrix.size() == 1) {
            return matrix[0][0];
        }
        size_t n = matrix.size();
        double sum = 0;
        for (size_t j = 0; j < n; ++j) {
            if ((j & 1) == 0) {
                sum += matrix[0][j] * determinant(minor(matrix, 0, j));
            } else {
                sum -= matrix[0][j] * determinant(minor(matrix, 0, j));
            }
        }
        return sum;
    }

    Matrix inverse(const Matrix& matrix) {
        if (matrix.size() == 0) {
            return Matrix{};
        }
        double det = determinant(matrix);
        if (equal_to_zero(det)) {
            throw std::logic_error("Inverse: det(matrix) = 0.");
        }
        size_t n = matrix.size();
        Matrix res = zeros(n, n);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (((i + j) & 1) == 0) {
                    res[i][j] = determinant(minor(matrix, j, i)) / det;
                } else {
                    res[i][j] = -determinant(minor(matrix, j, i)) / det;
                }
            }
        }
        return res;
    }

    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis) {
        size_t n1 = matrix1.size();
        size_t n2 = matrix2.size();
        if (n1 == 0) { return matrix2; }
        if (n2 == 0) { return matrix1; }
        check_valid(matrix1, "Concatenate: ");
        check_valid(matrix2, "Concatenate: ");

        size_t m1 = matrix1[0].size();
        size_t m2 = matrix2[0].size();
        size_t i;
        if (axis == 0) {
            if (m1 != m2) {
                throw std::logic_error("Concatenate: Dimensions are incoherent.");
            }
            Matrix res(n1 + n2);
            for (i = 0; i < n1; ++i) {
                res[i] = matrix1[i];
            }
            for (i = 0; i < n2; ++i) {
                res[i + n1] = matrix2[i];
            }
            return res;
        } else if (axis == 1) {
            if (n1 != n2) {
                throw std::logic_error("Concatenate: Dimensions are incoherent.");
            }
            Matrix res(n1);
            for (i = 0; i < n1; ++i) {
                res[i].insert(res[i].end(), matrix1[i].begin(), matrix1[i].end());
                res[i].insert(res[i].end(), matrix2[i].begin(), matrix2[i].end());
            }
            return res;
        } else {
            throw std::logic_error("Concatenate: Axis must be 0 or 1.");
        }
        return Matrix{};
    }

    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2) {
        size_t n = matrix.size();
        check_valid(matrix, "Ero_swap");
        if (r1 >= n || r2 >= n) {
            throw std::logic_error("Ero_swap: it doesn't exist r1th or r2th row.");
        }
        Matrix res = matrix;
        swap(res[r1], res[r2]);
        return res;
    }
    Matrix ero_multiply(const Matrix& matrix, size_t r, double c) {
        size_t n = matrix.size();
        check_valid(matrix, "Ero_multiply");
        if (r >= n) {
            throw std::logic_error("Ero_multiply: it doesn't exist rth row.");
        }
        Matrix res = matrix;
        for (auto& column : res[r]) {
            column *= c;
        }
        return res;
    }
    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2) {
        size_t n = matrix.size();
        check_valid(matrix, "Ero_sum");
        if (r1 >= n || r2 >= n) {
            throw std::logic_error("Ero_sum: it doesn't exist r1th or r2th row.");
        }
        Matrix res = matrix;
        size_t m = matrix[0].size();
        for (size_t i = 0; i < m; ++i) {
            res[r2][i] += c * res[r1][i];
        }
        return res;
    }
    Matrix upper_triangular(const Matrix& matrix) {
        size_t n = matrix.size();
        if (n == 0) { return matrix; }
        check_square(matrix, "Upper_triangular");
        Matrix res = matrix;
        for (size_t j = 0; j < n; ++j) {
            if (equal_to_zero(res[j][j])) {
                for (size_t i = j + 1; i < n; ++i) {
                    if (!equal_to_zero(res[i][j])) {
                        res = ero_sum(res, i, 1, j);
                        break;
                    }
                }
            }
            // All elements below are zero.
            if (equal_to_zero(res[j][j])) { continue; }

            for (size_t i = j + 1; i < n; ++i) {
                if (!equal_to_zero(res[i][j])) {
                    res = ero_sum(res, j, -res[i][j] / res[j][j], i);
                }
            }
        }
        return res;
    }
}