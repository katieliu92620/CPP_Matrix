//compile with $ g++ -o Matrix_Demo Matrix_Demo.cpp Matrix.cpp

#include "Matrix.h"
#include <iostream>
#include <vector>

using namespace std;

int main(){
    Matrix matrix1=Matrix("example/fourByFour.txt");
    matrix1.printMatrix();
    Matrix submatrix=matrix1.subMatrix(3,0);
    submatrix.printMatrix();

    vector<vector<double>> vector1={
        {1,2},
        {3,4}
    };
    Matrix matrix2=Matrix(vector1);


    vector<vector<double>> vector2={
        {1,2},
        {3,4}
    };
    Matrix matrix3=Matrix(vector2);

    matrix2.printMatrix();
    matrix3.printMatrix();
    Matrix product=matrix2*matrix3;
    product.printMatrix();

    return 0;
}