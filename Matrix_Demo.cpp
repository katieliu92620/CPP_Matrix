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
    return 0;
}