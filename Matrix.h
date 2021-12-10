#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include "Vector.h"

class Matrix {

public:
    double** matrix;

    Matrix() {
        matrix = new double* [3];
        for (int i = 0; i < 3; i++) {
            matrix[i] = new double[3];
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                matrix[i][j] = 0;
            }
        }
    }
    Matrix(const Matrix& other) {
        matrix = new double* [3];
        for (int i = 0; i < 3; i++) {
            matrix[i] = new double[3];
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                matrix[i][j] = other.matrix[i][j];
            }
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            for (size_t i = 0; i < 3; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;

            matrix = new double* [3];
            for (int i = 0; i < 3; i++) {
                matrix[i] = new double[3];
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    matrix[i][j] = other.matrix[i][j];
                }
            }
        }
        return *this;
    }

    friend Vector operator *(Matrix a, Vector vec) {
        Vector m;
        m.x = a.matrix[0][0] * vec.x + a.matrix[0][1] * vec.y + a.matrix[0][2] * vec.z;
        m.y = a.matrix[1][0] * vec.x + a.matrix[1][1] * vec.y + a.matrix[1][2] * vec.z;
        m.z = a.matrix[2][0] * vec.x + a.matrix[2][1] * vec.y + a.matrix[2][2] * vec.z;
        return m;
    }

    friend Matrix operator *(Matrix a, Matrix b) {

        Matrix c = Matrix();
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++)
                    c.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];

        return c;
    }

    friend Matrix operator *(Matrix a, double k) {

        Matrix c = Matrix();
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                c.matrix[i][j] = a.matrix[i][j] * k;
        return c;

    }

    friend Matrix operator +(Matrix a, Matrix b) {

        Matrix c = Matrix();
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                c.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
        return c;
    }

    Matrix TransponateMatrix(Matrix& a)
    {
        Matrix c = Matrix();
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                c.matrix[j][i] = a.matrix[i][j];
        return c;
    }

    Matrix BackMatrix(Matrix& a) {
        Matrix c = Matrix();

        for (int i = 0; i < 3; i++) {
            c.matrix[i][i] = 1 / a.matrix[i][i];
        }
        return c;
    }

    Vector vectorProduct(Vector a, Vector b) {
        Vector c;
        c.x = a.y * b.z - a.z * b.y;
        c.y = a.z * b.x - a.x * b.z;
        c.z = a.x * b.y - a.y * b.x;
        return c;
    }

    Matrix skewMatrix(Vector& vec) {
        Matrix c = Matrix();
        c.matrix[0][0] = 0;
        c.matrix[0][1] = -vec.z;
        c.matrix[0][2] = vec.y;

        c.matrix[1][0] = vec.z;
        c.matrix[1][1] = 0;
        c.matrix[1][2] = -vec.x;

        c.matrix[2][0] = -vec.y;
        c.matrix[2][1] = vec.x;
        c.matrix[2][2] = 0;
        return c;
    }

    double scalarProduct(Vector a, Vector b) {
        double res1 = double(a.x) * double(b.x);
        double res2 = double(a.y) * double(b.y);
        double res3 = double(a.z) * double(b.z);
        double res = res1 + res2 + res3;
        return res;
    }

    Matrix ortGramSchmidt(Matrix& a) {
        Vector f1 = { a.matrix[0][0], a.matrix[1][0] , a.matrix[2][0] };
        Vector f2 = { a.matrix[0][1], a.matrix[1][1] , a.matrix[2][1] };
        Vector f3 = { a.matrix[0][2], a.matrix[1][2] , a.matrix[2][2] };

        Vector e1, e2, e3;
        double g12, g13, g23;
        e1 = f1;
        g12 = scalarProduct(f2, e1) / scalarProduct(e1, e1);
        e2 = f2 - g12 * e1;
        g13 = scalarProduct(f3, e1) / scalarProduct(e1, e1);
        g23 = scalarProduct(f3, e2) / scalarProduct(e2, e2);
        e3 = f3 - g13 * e1 - g23 * e2;

        e1 = e1 / sqrt(scalarProduct(e1, e1));
        e2 = e2 / sqrt(scalarProduct(e2, e2));
        e3 = e3 / sqrt(scalarProduct(e3, e3));

        Matrix m;
        m.matrix[0][0] = e1.x; m.matrix[0][1] = e2.x; m.matrix[0][2] = e3.x;
        m.matrix[1][0] = e1.y; m.matrix[1][1] = e2.y; m.matrix[1][2] = e3.y;
        m.matrix[2][0] = e1.z; m.matrix[2][1] = e2.z; m.matrix[2][2] = e3.z;
        return m;
    }

    void printMatrix(Matrix& a)
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
                std::cout << a.matrix[i][j] << " ";
            std::cout << std::endl;
        }
    }

    ~Matrix() {
        for (size_t i = 0; i < 3; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

};