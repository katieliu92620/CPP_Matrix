//compile with $ g++ -o Matrix_Demo Matrix_Demo.cpp Matrix.cpp

#include "Matrix.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <assert.h>

using namespace std;

int main(){

    vector<vector<double>> vector1={
        {1,3.14,1},
        {3,4, 2},
        {2, 2, 2}
    };
    Matrix matrix1=Matrix(vector1);

    printf("\nTesting determinants.\n");
    double determinant=matrix1.determinant();
    assert(abs(determinant-(-4.28))<0.001);

    vector<vector<double>> vector2={
        {4,0,7,4},
        {0,5,0,0},
        {0,5,22.5,34},
        {8,1,0,0}
    };

    Matrix matrix2=Matrix(vector2);
    determinant=matrix2.determinant();
    assert(abs(determinant-5920)<0.001);


    vector<vector<double>> vector3={
        {4,0,7,4, 5.1},
        {0,5,0,0,10},
        {0,5,22.5,34,3},
        {8,1,0,0,0.7},
        {1,1,4.4,1.1,1}
    };

    Matrix matrix3=Matrix(vector3);
    determinant=matrix3.determinant();
    assert(abs(determinant-(-36445.5))<0.001);

    vector<vector<double>> vector4={
        {1, -2 , 4, 7},
        {1, 0, 1, 3},
        {-3.5, 1, 5, 0},
        {3, -1, -9, 4}
    };

    Matrix matrix4=Matrix(vector4);

    Matrix zeroByZero=Matrix("example/zeroByZero.csv");
    assert(zeroByZero.determinant()==1);

    vector<vector<double>> vector5={
        {-16, 84, -67, -35},
        {-83.5, 191.5, 33, 2.5},
        {5.5, 20.5, -14, -25},
        {3.5, 31, 27, 20}
    };

    Matrix matrix5=Matrix(vector5);
    Matrix matrix6=matrix4.adjoint();

    printf("\nTesting adjoints.\n");
    
    assert(matrix6==matrix5);

    Matrix matrix11=Matrix("example/oneByOne.csv");
    matrix11=matrix11.adjoint();
    Matrix matrix12=Matrix("solutions/oneByOneAdjoint.csv");
    assert(matrix11==matrix12);

    printf("\nTesting inverses.\n");
    matrix11=Matrix("example/oneByOne.csv");
    vector<vector<double>> inverse11=vector<vector<double>>(1,vector<double>(1,0.5));
    assert(matrix11.inverse()==Matrix(inverse11));
    matrix11=Matrix("example/twoByTwo.csv");
    assert(matrix11.inverse()==Matrix("solutions/twoByTwoInv.csv"));

    printf("\nTesting operations.\n");
    Matrix matrix7=Matrix("example/fourByFour.csv");
    matrix7=matrix7*matrix7;
    Matrix matrix8=Matrix("solutions/fourByFourMultFourByFour.csv");
    assert (matrix7==matrix8);

    Matrix matrix9=Matrix(6);
    Matrix matrix10=Matrix("solutions/identitySix.csv");
    assert(matrix9==matrix10);

    matrix9=matrix9*matrix9;
    assert(matrix9==matrix10);

    matrix9=Matrix("example/fourByFour.csv");
    matrix10=Matrix("example/fourByTwo.csv");
    matrix8=Matrix("solutions/fourByFourMultFourByTwo.csv");
    assert((matrix9*matrix10)==matrix8);

    


    printf("\nAll tests have passed.\n");
    return 0;
}