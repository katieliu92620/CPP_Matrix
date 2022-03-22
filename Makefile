all: Matrix_Demo Matrix_Test

Matrix_Demo: Matrix_Demo.cpp Matrix.cpp Matrix.h
	g++ -o Matrix_Demo Matrix_Demo.cpp Matrix.cpp

Matrix_Test: Matrix_Test.cpp Matrix.cpp Matrix.h
	g++ -o Matrix_Test Matrix_Test.cpp Matrix.cpp