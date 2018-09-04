#pragma once
class Matrix
{
private:
	int size;
	int** values;
	void CopyMatrix(const Matrix&);
	void DeleteMatrix();
public:
	Matrix(const int =0);
	Matrix(const Matrix&);
	~Matrix();
	Matrix& operator=(const Matrix&);
	void InitialiazeMatrix();
	Matrix A11() const;
	Matrix A12() const;
	Matrix A21() const;
	Matrix A22() const;
	void Display() const;
	void Combine(const Matrix&, const Matrix&, const Matrix&, const Matrix&);
	Matrix operator+(const Matrix&) const;
	Matrix operator-(const Matrix&) const;
	int GetSize() const;
	friend Matrix SquareMatrixMult(const Matrix&, const Matrix&);
};
Matrix StrassenMethod(const Matrix&, const Matrix&);