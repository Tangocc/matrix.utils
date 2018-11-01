```
#ifndef Matrix_H
#define Matrix_H
#include "QVector"
#include "QDebug"

class Matrix
{
public:
    Matrix();
    ~Matrix();
    Matrix(Matrix &m);//复制构造函数
    Matrix(double** arr,int row,int col);//利用数组构造矩阵构造函数
    Matrix(int row,int col);//利用数组构造矩阵构造函数
    Matrix(double* arr,int row,int col);//利用数组构造矩阵构造函数
public:
    int rows;
    int columns;
    QVector<QVector<double>> matrixs;
public:

    //静态成员，通过类名引用，返回矩阵，方便链式编程
     Matrix Transpose();//转置矩阵

     Matrix Inverse();//逆矩阵
   static   Matrix ones(int row,int col);//生成单位阵
     static Matrix zeros(int row,int col);//零矩阵


    void  operator =(Matrix const &m);
    Matrix operator +(Matrix const &m);
    Matrix operator -(Matrix const &m);
    Matrix operator *(Matrix const &m);
    Matrix operator *(double const &m);
    //显示矩阵
    void ShowMatrix();
};


```
