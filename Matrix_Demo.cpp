#include "Matrix.h"
#include <iostream>

int main(int argc, char** argv){
    if(argc<2){
        cerr << "USAGE: " << argv[0] << " <matrix_csv_1> ... <matrix_csv_n>" <<endl; exit(1);
    }

    vector<Matrix> matrixVector;

    for(int i=1;i<argc;i++){
        Matrix curr=Matrix(argv[i]);
        matrixVector.push_back(curr);
    }

    unsigned int numMatrices=matrixVector.size();
    for(unsigned int j=0;j<numMatrices;j++){
        cout<<endl;
        cout<<endl;
        cout<<"Curr Matrix from: "<<argv[j+1]<<endl;
        Matrix curr=matrixVector.at(j);
        curr.printMatrix();
        cout<<endl;
        cout<<"determinant: "<<endl;
        try{
            cout<<curr.determinant()<<endl;
        }
        catch(domain_error){
            cout<<"Determinant does not exist"<<endl;
        }
        cout<<endl;
        cout<<"adjoint matrix:"<<endl;
        try{
            Matrix adj=curr.adjoint();
            adj.printMatrix();
        }
        catch(domain_error){
            cout<<"adjoint matrix does not exist"<<endl;
        }
        
        cout<<endl;
        cout<<"Inverse: "<<endl;
        try{
            Matrix inv=curr.inverse();
            inv.printMatrix();
        }
        catch(domain_error){
            cout<<"inverse matrix does not exist"<<endl;
        }
        
    }

    return 0;
}