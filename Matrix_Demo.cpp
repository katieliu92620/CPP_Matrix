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
        {1,3.14},
        {3,4}
    };
    Matrix matrix2=Matrix(vector1);


    vector<vector<double>> vector2={
        {1,2},
        {0.5,5}
    };
    Matrix matrix3=Matrix(vector2);

    cout<<"Matrix A: "<<endl;
    matrix2.printMatrix();
    cout<<"Matrix B: "<<endl;
    matrix3.printMatrix();
    cout<<"A+B:" <<endl;
    Matrix sum=matrix2+matrix3;
    sum.printMatrix();
    cout<<"A-B: "<<endl;
    Matrix difference=matrix2-matrix3;
    difference.printMatrix();
    cout<<"A*B: "<<endl;
    Matrix product=matrix2*matrix3;
    product.printMatrix();

    return 0;
}