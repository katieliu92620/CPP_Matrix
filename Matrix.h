#include <vector>
#include <iostream>
using namespace std;

class Matrix{

    private:
    unsigned int numRows;
    unsigned int numColumns;
    vector<vector<double>> entries;


    /**
    * @brief Construct a new default Matrix object. Creates an empty matrix of size 0 x 0.
    * 
    */
    Matrix();
    

    public:
    /**
     * @brief Construct a new Matrix object from a formatted csv file. Tthe file contains the elements of the matrix, 
     * with each element being separated by a comma and each row beginning with a new line. 
     * 
     * @param matrix_csv: name of the csv file containing the matrix
     */
    Matrix(const char* const &matrix_csv);

    /**
     * @brief Construct a new Matrix object from a 2D vector of doubles. Each element of the 2D vector must contain the
     * same number of elements. 
     * 
     * @param inputEntries The 2D double vector that contains the elements for the new Matrix. 
     */
    Matrix(vector<vector<double>> inputEntries);

    /**
     * @brief Construct a new Matrix object which is the identity matrix of size size.
     * 
     * @param size: size of the identity Matrix to be constructed
     */
    Matrix(unsigned int size);

    /**
     * @brief Prints out the elements of a the matrix.
     * 
     */
    void printMatrix() const;

    /**
     * @brief Overloads + operator with Matrix addition
     * 
     * @param Other: matrix to be added to this matrix
     * @return Matrix: the sum of this matrix and other. Returns NULL if such a sum does not exist
     */
    Matrix operator+(Matrix const &Other);

    /**
     * @brief Overloads - operator with Matrix subtraction
     * 
     * @param Other: matrix to be subtracted from this matrix
     * @return Matrix: the difference that results from subtracting Other from this matrix. Returns NULL
     * is such a difference does not exist. 
     */
    Matrix operator-(Matrix const &Other);

    /**
     * @brief Overloads * operator with Matrix multiplication
     * 
     * @param Other: matrix to be multiplied with this matrix
     * @return Matrix: the product (this Matrix)(Other). Returns NULL if such a product does not exist
     */
    Matrix operator*(Matrix const &Other);

    /**
     * @brief Overloads == operator to check if two matrices are equal
     * 
     * @param Other: Matrix to be compared with this matrix
     * @return true: if the two matrices are equal
     * @return false: if the two matrices are not equal
     */
    bool operator==(Matrix const &Other);

    /**
     * @brief Overloads != opertor to check if two matrices are not equal
     * 
     * @param Other: Matrix to be compared with thsi matrix
     * @return true: if the two matrices are equal
     * @return false: if the two matrices are not equal
     */
    bool operator!=(Matrix const &Other);

    /**
     * @brief Calcuates the determnant of the matrix this function is being called on. 
     * 
     * @return double: the determinant of this matrix
     */
    double determinant() const;

    /**
     * @brief returns the inverse matrix of this Matrix
     * 
     * @return Matrix: inverse of this Matrix, returns NULL if inverse does not exist
     */
    Matrix inverse() const;

    /**
     * @brief Get the number of rows in this Matrix.
     * 
     * @return unsigned int: number of rows in this Matrix.
     */
    unsigned int getNumRows() const;

    /**
     * @brief Get the number of columns in this Matrix.
     * 
     * @return unsigned int: numberfof columns in this Matrix.
     */
    unsigned int getNumColumns() const;

    /**
     * @brief gets the entry of the Matrix located at row i and column j.
     * 
     * @param i: row index of the entry to be retrieved
     * @param j: column index of the entry to be retrieved
     * @return double: entry of Matrix retrieved by row i and column j
     */
    double getElementAtIndex(int i, int j) const;

    /**
     * @brief Generates a submatrix of this matrix that excludes row i and column j of the original matrix.
     * 
     * @param i: row to be excluded in submatrix
     * @param j: column to be excluded in the submatrix
     * @return Matrix: submatrix of the original matrix where row i and column j has been deleted
     */
    Matrix subMatrix(int i, int j) const;

    /**
     * @brief Generates the ajoint matrix of this matrix
     * 
     * @return Matrix: adjoint matrix of this matrix, returns NULL if such a matrix does not exist
     */
    Matrix adjoint() const;

};