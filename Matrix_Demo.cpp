#include "Matrix.h"
#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char** argv){
    if(argc!=2&&argc!=4){
        cerr << "USAGE: " << argv[0] << " <matrix_csv>" <<endl; 
        cerr << "USAGE: " << argv[0] << " <matrix_csv_1> <operation_name> <mastrix_csv_2>" <<endl; exit(1);
    }

    string add="add";
    string sub="subtract";
    string mult="multiply";
   

    if(argc==2){
        
        cout<<endl;
        cout<<endl;
        Matrix curr=Matrix(argv[1]);
        cout<<"Matrix is from: "<<argv[1]<<endl;
        curr.printMatrix();
        printf("\n\n");
        cout<<"determinant: "<<endl;
        try{
            printf("\n%.3f\n\n",curr.determinant());
        }
        catch(domain_error){
            cout<<"Determinant does not exist"<<endl;
        }
        printf("\nadjoint matrix: \n");
        try{
            Matrix adj=curr.adjoint();
            adj.printMatrix();
            printf("\n");
        }
        catch(domain_error){
            cout<<"adjoint matrix does not exist"<<endl;
        }
        
        cout<<endl;
        printf("\nInverse: \n");
        try{
            Matrix inv=curr.inverse();
            inv.printMatrix();
            printf("\n");
        }
        catch(domain_error){
            cout<<"inverse matrix does not exist"<<endl;
        }
        
    }
    else{
        Matrix first=Matrix(argv[1]);
        printf("\n");
        cout<<"First Matrix from: "<<argv[1]<<endl;
        first.printMatrix();
        printf("\n");
        printf("\n");
        Matrix second=Matrix(argv[3]);
        cout<<"Second Matrix from: "<<argv[3]<<endl;
        second.printMatrix();
        printf("\n");
        if(argv[2]==add){
            try{
                printf("\nSum:\n");
                Matrix sum=first+second;
                sum.printMatrix();
            }
            catch(invalid_argument){
                printf("\nSum does not exist because dimensions do not match.\n");
            }
        }
        else if(argv[2]==sub){
            try{
                printf("\nDifference:\n");
                Matrix difference=first-second;
                difference.printMatrix();
            }
            catch(invalid_argument){
                printf("\nDifference does not exist because dimensions do not match.\n");
            }
        }
        else if(argv[2]==mult){
            try{
                printf("\nProduct:\n");
                Matrix product=first*second;
                product.printMatrix();
            }
            catch(invalid_argument){
                printf("\nProduct does not exist because dimensions do not match.\n");
            }
        }
        else{
            cout<<"Please input a valid operator name, valid operator names are: "<<add<<", "<<sub<<", "<<mult<<"."<<endl;
            exit(1);
        }
        
    }
    

    return 0;
}