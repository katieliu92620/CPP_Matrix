//compile with $ g++ -o Matrix_Demo Matrix_Demo.cpp Matrix.cpp

#include "Matrix.h"
#include <iostream>
#include <vector>

using namespace std;

int main(){

    vector<vector<double>> vector1={
        {1,3.14,1},
        {3,4, 2},
        {2, 2, 2}
    };
    Matrix matrix1=Matrix(vector1);

    cout<<"Testing determinants: "<<endl;
    matrix1.printMatrix();
    double determinant=matrix1.determinant();
    cout<<endl;
    cout<<"determinant: "<<determinant<<endl;
    if(determinant!=-4.28){
        cout<<"determinant was incorrect"<<endl;
        return -1;
    }

    vector<vector<double>> vector2={
        {4,0,7,4},
        {0,5,0,0},
        {0,5,22.5,34},
        {8,1,0,0}
    };

    Matrix matrix2=Matrix(vector2);
    cout<<endl;
    matrix2.printMatrix();
    determinant=matrix2.determinant();
    cout<<endl;
    cout<<"determinant: "<<determinant<<endl;
    if(determinant!=5920){
        cout<<"determinant was incorrect"<<endl;
        return -1;
    }


    vector<vector<double>> vector3={
        {4,0,7,4, 5.1},
        {0,5,0,0,10},
        {0,5,22.5,34,3},
        {8,1,0,0,0.7},
        {1,1,4.4,1.1,1}
    };

    Matrix matrix3=Matrix(vector3);
    cout<<endl;
    matrix3.printMatrix();
    determinant=matrix3.determinant();
    cout<<endl;
    cout<<"determinant: "<<determinant<<endl;
    if(determinant!=-36445.5){
        cout<<"determinant was incorrect"<<endl;
        return -1;
    }

    
    


    return 0;
}