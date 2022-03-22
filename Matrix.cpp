#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

Matrix::Matrix(){
    this->numRows=0;
    this->numColumns=0;
    this->entries=vector<vector<double>>(0,vector<double>(0,0));
}


Matrix::Matrix(const char* const &matrix_csv){
    this->entries=vector<vector<double>>(0,vector<double>(0,0));
    ifstream my_file(matrix_csv);
    string line;

    //reading in row and column count of matrix
    //checking that file is not empty
    if(!getline(my_file,line)){
        cerr<<"Please do not input an empty file."<<endl;
        return;
    }
    istringstream ss(line);
    string rowCount;
    string columnCount;

    getline(ss, rowCount, ',');
    getline(ss, columnCount,',');
    this->numRows=stoi(rowCount);
    this->numColumns=stoi(columnCount);

    this->entries=vector<vector<double>>(numRows,vector<double>(numColumns,0));

    //Reading in the entries of this matrix from the csv file
    for(unsigned int i=0;i<this->numRows;i++){
         getline(my_file,line);
         istringstream ss(line);
         for(unsigned int j=0;j<this->numColumns;j++){
             string currNumString;
             getline(ss,currNumString,',');
             this->entries[i][j]=stod(currNumString);
             
         }
    }
}

Matrix::Matrix(vector<vector<double>> inputEntries){
    this->numRows=inputEntries.size();
    this->numColumns=inputEntries[0].size();
    this->entries=inputEntries;
}

void Matrix::printMatrix(){
    cout<<endl;
    unsigned int rowCount=this->numRows;
    unsigned int colCount=this->numColumns;
    for(unsigned int i=0;i<numRows;i++){
        for(unsigned int j=0;j<numColumns;j++){
            printf("%6.3f  ", this->entries[i][j]);;
        }
        cout<<endl;
    }
}


Matrix Matrix::operator+(Matrix const &Other){
    if(this->numRows!=Other.getNumRows()||this->numColumns!=Other.getNumColumns()){
        cerr<<"Dimensions do not match."<<endl;
        return NULL;
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
        cerr<<"Dimensions do not match."<<endl;
        return NULL;
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
    {
        if(this->numColumns!=Other.getNumRows()){
        cerr<<"Matrix Dimensions do not match. "<<endl;
        Matrix dummy=Matrix();
        return NULL;
    }

    unsigned int thisRowLength=this->numColumns;
    unsigned int otherRowLength=Other.getNumColumns();
    unsigned int otherColumnLength=Other.getNumRows();
    vector<vector<double>> answer=vector<vector<double>>(this->numRows,vector<double>(Other.getNumColumns(),0));
    double currEntry;

    for(unsigned int i=0;i<this->numRows;i++){
        //getting the curent row to be multiplied with a corresponding column of the other matrixs
        vector<double> currRow=this->entries[i];

        for(unsigned int j=0;j<otherRowLength;j++){
            currEntry=0;
            vector<double> currCol;
            //getting the current column in the other matrix to be multiplied with a row of this matrix
            for(unsigned int k=0;k<otherColumnLength;k++){
                currCol.push_back(Other.getElementAtIndex(k,j));
            }

            //multiplying corresponding entries from the two matrices
            for(unsigned int l=0;l<thisRowLength;l++){
                currEntry=currEntry+currRow[l]*currCol[l];
                answer[i][j]=currEntry;
            }
            
        }

    }
        return Matrix(answer);
    }
}

Matrix Matrix::inverse(){
    //check if determinant exists
    if(this->determinant()==0){
        return NULL;
    }

    return Matrix();
    
}


double Matrix::determinant(){
    if(this->numRows!=this->numColumns){
        throw invalid_argument("Not a square matrix");
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


Matrix Matrix::subMatrix(int i, int j){
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


Matrix Matrix::adjoint(){
    if(this->numRows!=this->numColumns){
        return NULL;
    }
    vector<vector<double>> adjVector=vector<vector<double>>(this->numRows, vector<double>(this->numColumns,0));
    return Matrix(adjVector);
}

