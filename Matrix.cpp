#include "Matrix.h"

Matrix::Matrix()
{

}

Matrix::~Matrix()
{

}

/*
  构造函数：复制构造函数
*/
Matrix::Matrix(Matrix &m)
{
    this->columns = m.columns;
    this->rows = m.rows;
    this->matrixs= m.matrixs;

}

/*
 *构造函数：数组构造矩阵
*/
Matrix::Matrix(double **arr,int row,int col)
{
    this->rows = row;
    this->columns = col;
    QVector<double>  vec;
    for(int ii=0;ii<row;ii++)
    {
        for(int jj=0;jj<col;jj++)
            vec.push_back(   *(((double*)arr+ii*col)+jj));
        this->matrixs.push_back(vec);
        vec.clear();
    }

}


Matrix::Matrix(double *arr, int row, int col)
{
    this->rows = row;
    this->columns = col;
    QVector<double>  vec;
    for(int ii=0;ii<row;ii++)
    {
        for(int jj=0;jj<col;jj++)
            vec.push_back(   *(((double*)arr+ii*col)+jj));
        this->matrixs.push_back(vec);
        vec.clear();
    }
}



Matrix::Matrix(int row, int col)
{
    this->columns = col;
    this->rows = row;
    QVector<double>  vect;
    for(int ii=0;ii<row;ii++)
    {
       for(int jj=0;jj<col;jj++)
       {
           if(ii==jj)
             vect.push_back(1);
           else
                vect.push_back(0);

       }
       this->matrixs.push_back(vect);
       vect.clear();


    }


}

/*
 *
 *  求转置矩阵
 *
 **/

Matrix Matrix::Transpose()
{

        Matrix result;
        result.rows = this->columns;
        result.columns = this->rows;
        QVector<double> rowData;
        for (int ii = 0; ii < this->columns; ii++)
        {
            for (int jj = 0; jj < this->rows; jj++)
            {
                rowData.push_back((this->matrixs)[jj][ii]);
            }
            (result.matrixs).push_back(rowData);
            rowData.clear();
        }
        return result;
}

/*
  逆矩阵
*/
Matrix Matrix::Inverse()
{
    Matrix result;

    if (this->rows != this->columns)
    {
        qDebug() << "矩阵不是方阵，不能求逆矩阵！";
    }
    else{
        int i = 0, j = 0, k = 0, M = this->columns, N = 2 * this->columns;
        double b[15][30];  //存储矩阵的扩展矩阵，根据实际需要修改大小
        for (i = 0; i < M; i++)     //赋值
        {
            for (j = 0; j < M; j++)
                b[i][j] = (this->matrixs)[i][j];
        }
        for (i = 0; i < M; i++)    //扩展
        for (j = M; j < N; j++)
        {
            if (i == (j - M))
                b[i][j] = 1;
            else
                b[i][j] = 0;
        }
        for (i = 0; i < M; i++)
        {
            if (b[i][i] == 0)
            {
                for (k = i; k < M; k++)
                {
                    if (b[k][i] != 0)
                    {
                        for (int j = 0; j < N; j++)
                        {
                            double temp;
                            temp = b[i][j];
                            b[i][j] = b[k][j];
                            b[k][j] = temp;
                        }
                        break;
                    }
                }
                if (k == M)
                {
                    qDebug() << "该矩阵不可逆！\n";

                }
            }
            for (j = N - 1; j >= i; j--)
                b[i][j] /= b[i][i];

            for (k = 0; k < M; k++)
            {
                if (k != i)
                {
                    double temp = b[k][i];
                    for (j = 0; j < N; j++)
                        b[k][j] -= temp*b[i][j];
                }
            }
        }
        result.columns = this->columns;
        result.rows = this->rows;//行列数设置好
        result.matrixs.clear();
        QVector <double> t;
        for (int i = 0; i < M; i++)
        {
            for (int j = M; j < N; j++)
            {
                //cout<<b[i][j]<<endl;
                t.push_back(b[i][j]);
            }
            result.matrixs.push_back(t);//数据输入matrixs量中
            t.clear();
        }


    }
    return  result;
}

//   单位矩阵
Matrix Matrix::ones(int row, int col)
{
    Matrix result;
    result.rows = row;
    result.columns = col;
    QVector<double>  vect;
    for(int ii=0;ii<row;ii++)
    {
       for(int jj=0;jj<col;jj++)
       {
           if(ii==jj)
             vect.push_back(1);
           else
                vect.push_back(0);

       }
       result.matrixs.push_back(vect);
       vect.clear();


    }

    return result;
}
//零矩阵
Matrix Matrix::zeros(int row, int col)
{
    Matrix result;
    QVector<double>  vect;
    for(int ii=0;ii<row;ii++)
    {
       for(int jj=0;jj<col;jj++)
              vect.push_back(0);

       result.matrixs.push_back(vect);
       vect.clear();
    }

    return result;
}

/*
  赋值操作符
*/
void  Matrix::operator =(const Matrix &m)
{
    this->rows = m.rows;
    this->columns =m.columns;
    this->matrixs = m.matrixs;
}
Matrix Matrix::operator +(const Matrix &m)
{
      Matrix result;
      QVector<double>  vect;
    if(this->rows!=m.rows || this->columns !=m.columns)
    {
        qDebug()<<"不能做加法运算";
       exit(0);
    }else
    {
        result.columns = this->columns;
        result.rows = this->rows;
        for (int ii = 0; ii < result.rows; ii++)
        {
            for (int jj = 0; jj < result.columns; jj++)
            {
               vect.push_back(this->matrixs[ii][jj] + m.matrixs[ii][jj]);
            }
             result.matrixs.push_back(vect);
             vect.clear();
        }

    }

    return  result;

}
Matrix Matrix::operator -(const Matrix &m)
{
    Matrix result;
    QVector<double>  vect;
  if(this->rows!=m.rows || this->columns !=m.columns)
  {
      qDebug()<<"不能做减法运算";
     exit(0);
  }else
  {
      result.columns = this->columns;
      result.rows = this->rows;
      for (int ii = 0; ii < result.rows; ii++)
      {
          for (int jj = 0; jj < result.columns; jj++)
          {
             vect.push_back(this->matrixs[ii][jj] - m.matrixs[ii][jj]);
          }
           result.matrixs.push_back(vect);
           vect.clear();
      }

  }

  return  result;

}

Matrix Matrix::operator *(const Matrix &m)
{
        Matrix result;
        if (this->columns != m.rows){
            qDebug() << "矩阵无法做乘法运算";
        }
        else{

            result.rows = this->rows;
            result.columns = m.columns;

            QVector<double>  rowData;
            double temp=0;

            for (int ii = 0; ii < result.rows;ii++)
            {
                for (int jj = 0; jj < result.columns;jj++)
                {
                    for (int kk = 0; kk < this->columns;kk++)
                    {
                        temp += this->matrixs[ii][kk] * m.matrixs[kk][jj];
                    }
                    rowData.push_back(temp);
                    temp = 0;
                }
                result.matrixs.push_back(rowData);
                rowData.clear();
            }

        }
        return result;
}

Matrix Matrix::operator *(const double &m)
{
    Matrix result;
    result.columns = this->columns;
    result.rows = this->rows;
    QVector<double>  vect;
    for(int ii=0;ii<this->rows;ii++)
    {
       for(int jj=0;jj<this->columns;jj++)
              vect.push_back((this->matrixs)[ii][jj]*m);

       result.matrixs.push_back(vect);
       vect.clear();
    }

    return result;
}

void Matrix::ShowMatrix()
{
    for(int ii=0;ii<this->rows;ii++)
    {
        for(int jj=0;jj<this->columns;jj++)
            qDebug()<<(this->matrixs)[ii][jj] <<"  ";
    }

}
