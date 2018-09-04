#include "Matrix.h"
#include <iostream>
Matrix::Matrix(const int s):size(s)
{
	if (size != 0)
	{
		values = new int*[size];
		for (int i = 0; i < size; i++)
		{
			values[i] = new int[size];
			for (int j = 0; j < size; j++)
			{
				//std::cin >> values[i][j];
				values[i][j] = 0;
			}
		}
	}
	else
	{
		values = nullptr;
	}
}
Matrix::Matrix(const Matrix&A)
{
	CopyMatrix(A);
}
Matrix::~Matrix()
{
	DeleteMatrix();
}
Matrix& Matrix::operator=(const Matrix&A)
{
	if (this != &A)
	{
		DeleteMatrix();
		CopyMatrix(A);
	}
	return *this;
}
void Matrix::CopyMatrix(const Matrix&A)
{
	size = A.size;
	values = new int*[size];
	for (int i = 0; i < size; i++)
	{
		values[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			values[i][j] = A.values[i][j];
		}
	}
}
void Matrix::DeleteMatrix()
{
	for (int i = 0; i < size; i++)
	{
		delete[] values[i];
	}
	delete[] values;
}
Matrix Matrix::A11() const
{
	//std::cout << "A11 begin" << std::endl;
	if (size < 1)
	{
		return Matrix(0);
	}
	Matrix a11(size / 2);
	for (int i = 0; i < a11.size; i++)
	{
		for (int j = 0; j < a11.size; j++)
		{
			a11.values[i][j] = values[i][j];
		}
	}
	//std::cout << "A11 end" << std::endl;
	return a11;
}
Matrix Matrix::A12() const
{
	//std::cout << "A12 begin" << std::endl;
	if (size <= 1)
	{
		return Matrix(0);
	}
	/*
	int temp = 0;
	if (size % 2 == 0)
	{
		temp=size / 2;
	}
	else
	{
		temp = size / 2 + 1;
	}
	*/
	Matrix a12(size/2);
	for (int i = 0 ; i < a12.size;i++)
	{
		for (int j = a12.size; j < size; j++)
		{
			a12.values[i][j-a12.size] = values[i][j];
		}
	}
	//std::cout << "A12 end" << std::endl;
	return a12;
}
Matrix Matrix::A21() const
{
	//std::cout << "A21 begin" << std::endl;
	if (size <= 1)
	{
		return Matrix(0);
	}
	/*
	int temp = 0;
	if (size % 2 == 0)
	{
		temp = size / 2;
	}
	else
	{
		temp = size / 2 + 1;
	}
	*/
	Matrix a21(size/2);
	for (int i = a21.size; i < size; i++)
	{
		for (int j = 0; j < a21.size; j++)
		{
			a21.values[i-a21.size][j] = values[i][j];
		}
	}
//	std::cout << "A21 end" << std::endl;
	return a21;
}
Matrix Matrix::A22() const
{
	//std::cout << "A22 begin" << std::endl;
	if (size <= 1)
	{
		return Matrix(0);
	}
	/*
	int temp = 0;
	if (size % 2 == 0)
	{
		temp = size / 2;
	}
	else
	{
		temp = size / 2 + 1;
	}
	*/
	Matrix a22(size/2);
	for (int i = a22.size; i < size; i++)
	{
		for (int j = a22.size; j < size; j++)
		{
			a22.values[i-a22.size][j-a22.size] = values[i][j];
		}
	}
	//std::cout << "A22 end" << std::endl;
	return a22;
}
void Matrix::Display() const
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << values[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
void Matrix::InitialiazeMatrix()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cin >> values[i][j];
		}
	}
}
void Matrix::Combine(const Matrix&A11, const Matrix&A12, const Matrix&A21, const Matrix&A22)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i < size / 2 && j < size / 2&&A11.size!=0)
			{
				values[i][j] = A11.values[i][j];
			}
			else if (i < size / 2 && j >= size / 2&&A12.size!=0)
			{
				values[i][j] = A12.values[i][j - A12.size];
			}
			else if (i >= size / 2 && j < size / 2&&A21.size!=0)
			{
				values[i][j] = A21.values[i - A21.size][j];
			}
			else if (i >= size / 2 && j >= size / 2&&A22.size!=0)
			{
				values[i][j] = A22.values[i - A22.size][j - A22.size];
			}
		}
	}
}
Matrix Matrix::operator+(const Matrix&A) const
{
	Matrix sum(A.size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			sum.values[i][j] = values[i][j] + A.values[i][j];
		}
	}
	return sum;
}
Matrix Matrix::operator-(const Matrix&A) const
{
	Matrix diff(A.size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			diff.values[i][j] = values[i][j] - A.values[i][j];
		}
	}
	return diff;
}
int Matrix::GetSize() const
{
	return size;
}
//Despite the fact that we use recursion through the master theorem we find out that the time is also etha n^3
Matrix SquareMatrixMult(const Matrix&A, const Matrix&B)
{
	int n = A.GetSize();
	Matrix C(n);
	if (n == 1)
	{
		C.values[0][0] = A.values[0][0] *B.values[0][0];
	}
	else
	{
		Matrix C11 = SquareMatrixMult(A.A11(), B.A11()) + SquareMatrixMult(A.A12(), B.A21());
		Matrix C12= SquareMatrixMult(A.A11(), B.A12()) + SquareMatrixMult(A.A12(), B.A22());
		Matrix C21 = SquareMatrixMult(A.A21(), B.A11()) + SquareMatrixMult(A.A22(), B.A21());
		Matrix C22 = SquareMatrixMult(A.A21(), B.A12()) + SquareMatrixMult(A.A22(), B.A22());
		C.Combine(C11, C12, C21, C22);
	}
	return C;
}
//Gonna use Strassen's method which is infact  approximately etha(n^2.81)
Matrix StrassenMethod(const Matrix&A, const Matrix&B)
{
	Matrix S1 = B.A12() - B.A22();
	Matrix S2 = A.A11() + A.A12();
	Matrix S3 = A.A21() + A.A22();
	Matrix S4 = B.A21() - B.A11();
	Matrix S5 = A.A11() + A.A22();
	Matrix S6 = B.A11() + B.A22();
	Matrix S7 = A.A12() - A.A22();
	Matrix S8 = B.A21() + B.A22();
	Matrix S9 = A.A11() - A.A21();
	Matrix S10 = B.A11() + B.A12();
	Matrix P1 = SquareMatrixMult(A.A11(), S1);
	Matrix P2 = SquareMatrixMult(S2, B.A22());
	Matrix P3 = SquareMatrixMult(S3, B.A11());
	Matrix P4 = SquareMatrixMult(A.A22(),S4);
	Matrix P5 = SquareMatrixMult(S5, S6);
	Matrix P6 = SquareMatrixMult(S7, S8);
	Matrix P7 = SquareMatrixMult(S9, S10);
	Matrix C11 = P5 + P4 - P2 + P6;
	Matrix C12 = P1 + P2;
	Matrix C21 = P3 + P4;
	Matrix C22 = P5 + P1 - P3 - P7;
	Matrix C(A.GetSize());
	C.Combine(C11, C12, C21, C22);
	return C;
}