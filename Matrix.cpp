#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <optional>

using namespace std;

Matrix::Matrix(){
    this->numRows=0;
    this->numColumns=0;
    this->entries=vector<vector<double>>(0,vector<double>(0,0));
}


Matrix::Matrix(const char* const &matrix_csv){
    //first initialize all fields to default values;
    this->numRows=0;
    this->numColumns=0;
    this->entries=vector<vector<double>>(0,vector<double>(0,0));
    ifstream my_file(matrix_csv);
    if(!my_file.is_open()){
        cerr<<"file open failed."<<endl;
        exit(1);
    }

    string line;
    string value;

    //if file is not empty, iterates through entire file to fill up entries vector
    while(getline (my_file, line)){
        vector<double> curr;
        stringstream s (line);
        while (getline (s, value, ',')){
            curr.push_back (stod (value));
        }
        this->entries.push_back(curr);
        this->numRows=this->entries.size();
        if(this->numRows!=0){
            this->numColumns=this->entries.at(0).size();
        }
        else{
            this->numColumns=0;
        }
            
    }
}

Matrix::Matrix(vector<vector<double>> inputEntries){
    this->numRows=inputEntries.size();
    if(this->numRows==0){
        this->numColumns=0;
    }
    else{
        this->numColumns=inputEntries[0].size();
    }
    this->entries=inputEntries;
}

void Matrix::printMatrix() const{
    if(this->numRows==0||this->numColumns==0){
        cout<<"[]"<<endl;
        return;
    }
    cout<<endl;
    unsigned int rowCount=this->numRows;
    unsigned int colCount=this->numColumns;
    for(unsigned int i=0;i<numRows;i++){
        for(unsigned int j=0;j<numColumns;j++){
            printf("%7.3f  ", this->entries[i][j]);;
        }
        cout<<endl;
    }
}

Matrix::Matrix(unsigned int size){
    vector<vector<double>> idEntries=vector<vector<double>>(size,vector<double>(size,0));
    for(unsigned int i=0;i<size;i++){
        idEntries[i][i]=1;
    }
    this->entries=idEntries;
    this->numRows=size;
    this->numColumns=size;
}


Matrix Matrix::operator+(Matrix const &Other){
    if(this->numRows!=Other.getNumRows()||this->numColumns!=Other.getNumColumns()){
        throw invalid_argument("Matrix dimensions do not match");
    }
    vector<vector<double>> answer= this->entries;
    unsigned int numRows=this->numRows;
    unsigned int numCols=this->numColumns;
    for(unsigned int i=0;i<numRows;i++){
        for(unsigned int j=0;j<numColumns;j++){
            answer[i][j]=answer[i][j]+Other.getElementAtIndex(i,j);
        }
    }

    return Matrix(answer);
}


Matrix Matrix::operator-(Matrix const &Other){
    if(this->numRows!=Other.getNumRows()||this->numColumns!=Other.getNumColumns()){
        throw invalid_argument("Matrix dimensions do not match");
    }
    vector<vector<double>> answer= this->entries;
    unsigned int numRows=this->numRows;
    unsigned int numCols=this->numColumns;
    for(unsigned int i=0;i<numRows;i++){
        for(unsigned int j=0;j<numColumns;j++){
            answer[i][j]=answer[i][j]-Other.getElementAtIndex(i,j);
        }
    }

    return Matrix(answer);
}


Matrix Matrix::operator*(Matrix const &Other){
    if(this->numColumns!=Other.getNumRows()){
       throw invalid_argument("Matrix dimensions do not match");
    }

    unsigned int thisRowLength=this->numColumns;
    unsigned int otherRowLength=Other.getNumColumns();
    unsigned int otherColumnLength=Other.getNumRows();
    vector<vector<double>> answer=vector<vector<double>>(this->numRows,vector<double>(Other.getNumColumns(),0));
    double currEntry;

    //three nested loops for iterating over matrix for matrix multiplication
    for(unsigned int i=0;i<this->numRows;i++){
        vector<double> currRow=this->entries[i];
        for(unsigned int j=0;j<otherRowLength;j++){
            currEntry=0;
            for(unsigned int k=0;k<otherColumnLength;k++){
                currEntry=currEntry+this->getElementAtIndex(i,k)*Other.getElementAtIndex(k,j);
            }
            answer[i][j]=currEntry;
            
        }

    }
        return Matrix(answer);
}



bool Matrix::operator==(Matrix const &Other){
    if(this->numRows!=Other.getNumRows()||this->numColumns!=Other.getNumColumns()){
        cout<<"dimentions not equal"<<endl;
        return false;
    }
    unsigned int numRows=this->numRows;
    unsigned int numColumns=this->numColumns;
    for(unsigned int i=0;i<numRows;i++){
        for(unsigned int j=0;j<numColumns;j++){
            //comparison accounts for rounding errors in floating point arithmetic
            if(abs(this->entries[i][j]-Other.getElementAtIndex(i,j))>0.001){
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(Matrix const &Other){
    return !(*this==Other);
}


Matrix Matrix::inverse() const{
    //check if this matrix is square
    if(this->numRows!=this->numColumns){
        throw domain_error("Not a square matrix");
    }

    //check if inverse exists
    double determinant=this->determinant();
    if(determinant==0){
        throw domain_error("Matrix determinant is 0");
    }

    unsigned int size=this->numRows;
    vector<vector<double>> inverseVector=vector<vector<double>>(size,vector<double>(size,0));
    Matrix adj=this->adjoint();

    for(unsigned int i=0;i<size;i++){
        for(unsigned int j=0;j<size;j++){
            inverseVector[i][j]=adj.getElementAtIndex(i,j)/determinant;
        }
    }

    return Matrix(inverseVector);
    
}


double Matrix::determinant() const{
    if(this->numRows!=this->numColumns){
        throw domain_error("Not a square matrix.");
    }

    //base case size=0
    if(this->numRows==0){
        return 1;
    }

    //base case size = 1
    if(this->numRows==1){
        return this->entries[0][0];
    }

    //base case size=2
    if(this->numRows==2){
        double determinant=this->entries[0][0]*this->entries[1][1]-this->entries[0][1]*this->entries[1][0];
        return determinant;
    }
    int index=-1;
    unsigned int rowLength=this->numColumns;
    double determinant=0;
    Matrix submatrix;

    //if matrix dimensions larget than 2x2 does confactor expansion along first row with recursive calls to determinant()
    for(unsigned int i=0;i<rowLength;i++){
        index=index*(-1);
        submatrix=this->subMatrix(0,i);
        determinant=determinant+(index*this->entries[0][i]*submatrix.determinant());
    }
    
    return determinant;
}


unsigned int Matrix::getNumRows() const{
    return this->numRows;
}


unsigned int Matrix::getNumColumns() const{
    return this->numColumns;
}


double Matrix::getElementAtIndex(int i, int j) const{
    return (this->entries.at(i)).at(j);
}


Matrix Matrix::subMatrix(int i, int j) const{
    unsigned int numRows=this->numRows;
    unsigned int numColumns=this->numColumns;
    vector<vector<double>> subMatrixVector=vector<vector<double>>(numRows-1,vector<double>(numColumns-1,0));
    int subRow=0;
    int subCol=0;
    for(unsigned int rowCounter=0;rowCounter<numRows;rowCounter++){
        subCol=0;
        if(rowCounter==i){
            continue;
        }
        for(unsigned int colCounter=0;colCounter<numColumns;colCounter++){
            if(colCounter==j){
                continue;
            }
            subMatrixVector[subRow][subCol]=this->entries[rowCounter][colCounter];
            subCol++;
        }
        subRow++;
    }
    Matrix subMatrix=Matrix(subMatrixVector);
    return subMatrix;
}


Matrix Matrix::adjoint() const{
    if(this->numRows!=this->numColumns){
        throw domain_error("Not a square matrix");
    }

    vector<vector<double>> adjVector=vector<vector<double>>(this->numRows, vector<double>(this->numColumns,0));
    unsigned int size=this->numRows;
    double cofactor=0;
    int index;
    for(unsigned int i=0;i<size;i++){
        for(unsigned int j=0;j<size;j++){
            Matrix submatrix=this->subMatrix(i,j);
            cofactor=submatrix.determinant();
            if((i+j)%2==0){
                index=1;
            }
            else{
                index=-1;
            }
            cofactor=cofactor*index;
            adjVector[j][i]=cofactor;
        }
    }
    
    return Matrix(adjVector);
}

