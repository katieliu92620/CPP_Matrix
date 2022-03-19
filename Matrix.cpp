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
            cout<<(this->entries)[i][j];
        }
        cout<<endl;
    }
}

int Matrix::determinant(){
    return 0;
}

Matrix Matrix::multiply(Matrix Other){
    if(this->numColumns!=Other.getNumRows()){
        cerr<<"Matrix Dimensions do not match. "<<endl;
        return NULL;
    }

    unsigned int thisRowLength=this->numColumns;
    unsigned int otherRowLength=Other.getNumColumns();
    unsigned int otherColumnLength=Other.getNumRows();
    vector<vector<double>> answer=vector<vector<double>>(this->numRows,vector<double>(Other.getNumColumns(),0));
    double currEntry;

    for(unsigned int i=0;i<this->numRows;i++){
        vector<double> currRow=this->entries[i];

        for(unsigned int j=0;j<otherRowLength;j++){
            currEntry=0;
            vector<double> currCol;
            for(unsigned int k=0;k<otherColumnLength;k++){
                currCol.push_back(Other.getElementAtIndex(k,j));
            }

            for(unsigned int l=0;l<thisRowLength;l++){
                currEntry=currEntry+currRow[l]*currCol[l];
                answer[i][j]=currEntry;
            }
            
        }

    }

    return Matrix(answer);
}

unsigned int Matrix::getNumRows(){
    return this->numRows;
}

unsigned int Matrix::getNumColumns(){
    return this->numColumns;
}

double Matrix::getElementAtIndex(int a, int b){
    return (this->entries.at(a)).at(b);
}

