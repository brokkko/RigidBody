#include <iostream>
#include <algorithm>
#include <vector>
#include "Vector.h"

class Matrixx{

public:
    int columns = 3;
    int rows = 3;
    double** matrix;
    Matrixx() {
        matrix = new double*[rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new double[columns];
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                matrix[i][j] = 0;
            }
        }
    }


    Matrixx(int column, int row) {
        matrix = new double* [row];
        //std::cout << "state1" << std::endl;
        for (int i = 0; i < row; i++) {
            matrix[i] = new double[column];
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                matrix[i][j] = 0;
            }
        }
    }

    void setElement(int row, int column, double value) {
        matrix[row][column] = value;
    }

    double getElement(int row, int column) {
        return matrix[row][column];
    }

    friend Vector operator *(Matrixx a, Vector vec) {
        // Matrix m(a.rows, 1);
        Vector m;
        m.x = a.matrix[0][0] * vec.x + a.matrix[0][1] * vec.y + a.matrix[0][2] * vec.z;
        m.y = a.matrix[1][0] * vec.x + a.matrix[1][1] * vec.y + a.matrix[1][2] * vec.z;
        m.z = a.matrix[2][0] * vec.x + a.matrix[2][1] * vec.y + a.matrix[2][2] * vec.z;
        return m;
    }

    friend Matrixx operator *(Matrixx a, Matrixx b) {

        a.printMatrix(a);
        std::cout << std::endl;
        b.printMatrix(b);
        std::cout << std::endl;

        Matrixx c = Matrixx(a.columns, b.rows);
        for (int i = 0; i < a.columns; ++i)
            for (int j = 0; j < b.rows; ++j) 
                for (int k = 0; k < a.rows; ++k)
                    c.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];

        c.printMatrix(c);
        std::cout << "+++++++++++++++++++++++" << std::endl;
        return c;
    }

    friend Matrixx operator *(Matrixx a, float k) {

        Matrixx c = Matrixx(a.columns, a.rows);
        for (int i = 0; i < a.columns; ++i)
            for (int j = 0; j < a.rows; ++j)
                c.matrix[i][j] = c.matrix[i][j] * k;
        return c;

    }

    friend Matrixx operator +(Matrixx a, Matrixx b) {

        Matrixx c = Matrixx(a.columns, b.rows);
        for (int i = 0; i < a.columns; ++i)
            for (int j = 0; j < a.rows; ++j)
                c.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
        return c;
    }

    Matrixx TransponateMatrix(Matrixx& a)
    {
        Matrixx c = Matrixx(a.rows, a.columns);
        for (int i = 0; i < a.columns; ++i)
            for (int j = 0; j < a.rows; ++j)
                c.matrix[j][i] = a.matrix[i][j];
        return c;
    }

    Matrixx BackMatrix(Matrixx& a) {
        Matrixx c(a.rows, a.columns);
        
        for (int i = 0; i < c.rows; i++) {
            c.matrix[i][i] = 1 / a.matrix[i][i];
        }
        return c;
    }

    Matrixx skewMatrix(Vector& vec) {
        Matrixx c = Matrixx(rows, columns);
        c.matrix[0][1] = -vec.z;
        c.matrix[0][2] = vec.y;

        c.matrix[1][0] = vec.z;
        c.matrix[1][2] = -vec.x;

        c.matrix[2][0] = -vec.y;
        c.matrix[2][1] = vec.x;
        return c;
    }

    void printMatrix(Matrixx& a)
    {
        for (int i = 0; i < a.columns; ++i)
        {
            for (int j = 0; j < a.rows; ++j)
                std::cout << a.matrix[i][j] << " ";
            std::cout << std::endl;
        }
    }

    //// сложить две матрицы
    //Matrix SumMatrix(Matrix& a, Matrix& b)
    //{
    //    if (a.Columns() != b.Columns() || a.Rows() != b.Rows())
    //        return Matrix();
    //    Matrix c = Matrix(a.Columns(), b.Rows());
    //    for (int i = 0; i < a.Columns(); ++i)
    //        for (int j = 0; j < a.Rows(); ++j)
    //            c[i][j] = a[i][j] + b[i][j];
    //    return c;
    //}

    //// умножение матрицы на число
    //Matrix MultiplyrMatrixOnDigit(Matrix& a, double k)
    //{
    //    Matrix c = Matrix(a.Columns(), a.Rows());
    //    for (int i = 0; i < a.Columns(); ++i)
    //        for (int j = 0; j < a.Rows(); ++j)
    //            c[i][j] = a[i][j] * k;
    //    return c;
    //}

    //// умножение двух матриц
    //Matrix MultiplyMatrix(Matrix& a, Matrix& b)
    //{
    //    if (a.Rows() != b.Columns())
    //        return Matrix();
    //    Matrix c = Matrix(a.Columns(), b.Rows());
    //    for (int i = 0; i < a.Columns(); ++i)
    //        for (int j = 0; j < b.Rows(); ++j)
    //            for (int k = 0; k < a.Rows(); ++k)
    //                c[i][j] += a[i][k] * b[k][j];
    //    return c;
    //}

    //// транспонирование матрицы
    //Matrix TransponateMatrix(Matrix& a)
    //{
    //    Matrix c = Matrix(a.Rows(), a.Columns());
    //    for (int i = 0; i < a.Columns(); ++i)
    //        for (int j = 0; j < a.Rows(); ++j)
    //            c[j][i] = a[i][j];
    //    return c;
    //}

    //// матрица без элементов
    //Matrix()
    //{
    //    MatrixArray = 0;
    //    columns = 0;
    //    rows = 0;
    //}



    /////////////////////////////////////////////////////////////////////////////////////////////////////////


    //// матрица NxM, если E, то единичная, иначе нулевая
    //Matrix(int N, int M, bool E = 0)
    //{
    //    columns = N;
    //    rows = M;
    //    MatrixArray = new double* [columns];
    //    for (int i = 0; i < columns; ++i)
    //    {
    //        MatrixArray[i] = new double[rows];
    //        for (int j = 0; j < rows; ++j)
    //            MatrixArray[i][j] = (i == j) * E;
    //    }
    //}
    //// матрица из элементов array, если horizontal, то  горизонтальная, иначе вертикальная
    //Matrix(double array[], int N, bool horizontal)
    //{
    //    if (horizontal)
    //    {
    //        columns = 1;
    //        rows = N;
    //        MatrixArray = new double* [1];
    //        MatrixArray[0] = new double[rows];
    //        for (int i = 0; i < rows; ++i)
    //            MatrixArray[0][i] = array[i];
    //    }
    //    else
    //    {
    //        columns = N;
    //        rows = 1;
    //        MatrixArray = new double* [columns];
    //        for (int i = 0; i < columns; ++i)
    //        {
    //            MatrixArray[i] = new double[1];
    //            MatrixArray[i][0] = array[i];
    //        }
    //    }
    //}

    //double* operator [] (int index)
    //{
    //    return getRow(index);
    //}
    //// получить строку матрицы
    //double* getRow(int index)
    //{
    //    if (index >= 0 && index < columns)
    //        return MatrixArray[index];
    //    return 0;
    //}

};

// вывести матрицу на консоль
//void printMatrix(Matrix& a)
//{
//    for (int i = 0; i < a.Columns(); ++i)
//    {
//        for (int j = 0; j < a.Rows(); ++j)
//            std::cout <<  a[i][j];
//        puts("");
//    }
//}