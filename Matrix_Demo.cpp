//compile with $ g++ -o Matrix_Demo Matrix_Demo.cpp Matrix.cpp

#include "Matrix.h"
#include <iostream>
#include <vector>

using namespace std;

int main(){
    //Matrix matrix1=Matrix("example/testMatrixTwobyFour.txt");
    //smatrix1.printMatrix();
    vector<vector<double>> aVect={
        {1,2},
        {1,1},
        {1,1}
    };

    vector<vector<double>> bVect={
        {1,0,0},
        {0,1,0}
    };

    Matrix AMatrix=Matrix(aVect);
    AMatrix.printMatrix();
    Matrix BMatrix=Matrix(bVect);
    BMatrix.printMatrix();
    Matrix product=AMatrix.multiply(BMatrix);

    product.printMatrix();
    return 0;
}