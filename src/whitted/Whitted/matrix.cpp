/*
	Matrix Library (Implementation)
	Matt Howe	(E5034116)
	Nov 06 (Updated Nov 07)
*/

#include "matrix.h"
#include "die.h"
#include <assert.h>
#include <math.h>

//-----------------------------------------------------------------------------
// Matrix Datatype - Constructor
//-----------------------------------------------------------------------------
Matrix::Matrix ( int iRows, int iCols )
	: m_iRows ( iRows ), m_iCols ( iCols )
{
	m_dData = new double [m_iRows * m_iCols];
	for (int i = 0; i < (m_iRows * m_iCols); i++)
	{
		m_dData[i] = 0;
	}
}

//-----------------------------------------------------------------------------
// Matrix Datatype - Copy Constructor
//-----------------------------------------------------------------------------
Matrix::Matrix ( const Matrix& matTmp )
{
	m_iRows = matTmp.m_iRows;
	m_iCols = matTmp.m_iCols;
	m_dData = new double[m_iRows * m_iCols];
	for (int i = 0; i < (m_iRows * m_iCols); i++)
	{
		m_dData[i] = matTmp.m_dData[i];
	}
}

//-----------------------------------------------------------------------------
// Matrix Datatype - Destructor
//-----------------------------------------------------------------------------
Matrix::~Matrix ( void )
{
	delete [] m_dData;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Matrix Datatype - Operator Overloads
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Matrix Datatype - Copy operator
//-----------------------------------------------------------------------------
const Matrix& Matrix::operator = ( const Matrix& matTmp )
{
	m_iRows = matTmp.m_iRows;
	m_iCols = matTmp.m_iCols;
	if (m_dData) {
		delete [] m_dData;
		m_dData = new double[m_iRows * m_iCols];
	}
	for (int i = 0; i < (m_iRows * m_iCols); i++)
	{
		m_dData[i] = matTmp.m_dData[i];
	}
	return *this;
}

//-----------------------------------------------------------------------------
// Matrix Datatype - Addition operator
//-----------------------------------------------------------------------------
Matrix Matrix::operator + ( const Matrix& matTmp ) const
{
	assert(m_iRows == matTmp.m_iRows);
	assert(m_iCols == matTmp.m_iCols);
	Matrix matReturn(m_iRows,m_iCols);
	for (int i = 0; i < (m_iRows * m_iCols); i++)
	{
		matReturn.m_dData[i] = m_dData[i] + matTmp.m_dData[i];
	}
	return matReturn;
}

const Matrix& Matrix::operator += ( const Matrix& matTmp )
{
	assert(m_iRows == matTmp.m_iRows);
	assert(m_iCols == matTmp.m_iCols);
	for (int i = 0; i < (m_iRows * m_iCols); i++)
	{
		m_dData[i] += matTmp.m_dData[i];
	}
	return *this;
}

//-----------------------------------------------------------------------------
// Matrix Datatype - Subtraction operator
//-----------------------------------------------------------------------------
Matrix Matrix::operator - ( const Matrix& matTmp ) const
{
	assert(m_iRows == matTmp.m_iRows);
	assert(m_iCols == matTmp.m_iCols);
	Matrix matReturn(m_iRows,m_iCols);
	for (int i = 0; i < (m_iRows * m_iCols); i++)
	{
		matReturn.m_dData[i] = m_dData[i] - matTmp.m_dData[i];
	}
	return matReturn;
}

const Matrix& Matrix::operator -= ( const Matrix& matTmp )
{
	assert(m_iRows == matTmp.m_iRows);
	assert(m_iCols == matTmp.m_iCols);
	for (int i = 0; i < (m_iRows * m_iCols); i++)
	{
		m_dData[i] -= matTmp.m_dData[i];
	}
	return *this;
}

//-----------------------------------------------------------------------------
// Matrix Datatype - Scalar multiplication operator
//-----------------------------------------------------------------------------
Matrix Matrix::operator * ( double dTmp ) const
{
	Matrix matReturn(m_iRows,m_iCols);
	for (int i = 0; i < (m_iRows * m_iCols); i++)
	{
		matReturn.m_dData[i] = m_dData[i] * dTmp;
	}
	return matReturn;
}

const Matrix& Matrix::operator *= ( double dTmp )
{
	for (int i = 0; i < (m_iRows * m_iCols); i++)
	{
		m_dData[i] *= dTmp;
	}
	return *this;
}

//-----------------------------------------------------------------------------
// Matrix Datatype - Scalar division operator
//-----------------------------------------------------------------------------
Matrix Matrix::operator / ( double dTmp ) const
{
	Matrix matReturn(m_iRows,m_iCols);
	for (int i = 0; i < (m_iRows * m_iCols); i++)
	{
		matReturn.m_dData[i] = m_dData[i] / dTmp;
	}
	return matReturn;
}

const Matrix& Matrix::operator /= ( double dTmp )
{
	for (int i = 0; i < (m_iRows * m_iCols); i++)
	{
		m_dData[i] /= dTmp;
	}
	return *this;
}

//-----------------------------------------------------------------------------
// Matrix Datatype - Matrix multiplication operator
//					http://mathworld.wolfram.com/MatrixMultiplication.html
//-----------------------------------------------------------------------------
Matrix Matrix::operator * ( const Matrix& matTmp ) const
{
	assert(m_iCols == matTmp.m_iRows);
	Matrix matReturn(m_iRows,m_iCols);
	for (int i = 0; i < m_iRows; i++)
	{
		for (int j = 0; j < m_iCols; j++)
		{
			matReturn(i,j) = 0;
			for (int k = 0; k < m_iCols; k++)
			{
				matReturn(i,j) += m(i,k) * matTmp(k,j);
			}
		}
	}
	return matReturn;
} 

const Matrix& Matrix::operator *= ( const Matrix& matTmp )
{
	assert(m_iCols == matTmp.m_iRows);
	Matrix matReturn(m_iRows,m_iCols);
	for (int i = 0; i < m_iRows; i++)
	{
		for (int j = 0; j < m_iCols; j++)
		{
			matReturn(i,j) = 0;
			for (int k = 0; k < m_iCols; k++)
			{
				matReturn(i,j) += m(i,k) * matTmp(k,j);
			}
		}
	}
	m_iRows = matReturn.m_iRows;
	m_iCols = matReturn.m_iCols;
	delete [] m_dData;
	m_dData = new double[m_iRows * m_iCols];
	for (int i = 0; i < (m_iRows * m_iCols); i++)
	{
		m_dData[i] = matReturn.m_dData[i];
	}
	return *this;
}

//-----------------------------------------------------------------------------
// Matrix Datatype - Element access overload
//-----------------------------------------------------------------------------
double& Matrix::operator () ( int iRow, int iCol )
{
	assert(iRow >= 0);
	assert(iRow < m_iRows);
	assert(iCol >= 0);
	assert(iCol < m_iCols);
	return m_dData[iRow * m_iCols + iCol];
}

double& Matrix::operator () ( int iRow, int iCol ) const
{
	assert(iRow >= 0);
	assert(iRow < m_iRows);
	assert(iCol >= 0);
	assert(iCol < m_iCols);
	return m_dData[iRow * m_iCols + iCol];
}

//-----------------------------------------------------------------------------
// Matrix Datatype - Row access overload
//-----------------------------------------------------------------------------
Vector Matrix::operator () ( int iRow )
{
	assert(iRow >= 0);
	assert(iRow < m_iRows);
	return Vector(m(iRow, 0), m(iRow, 1), m(iRow, 2), m(iRow, 3));
}

Vector Matrix::operator () ( int iRow ) const
{
	assert(iRow >= 0);
	assert(iRow < m_iRows);
	return Vector(m(iRow, 0), m(iRow, 1), m(iRow, 2), m(iRow, 3));
}

//-----------------------------------------------------------------------------
// Matrix Datatype - Equality test overload
//-----------------------------------------------------------------------------
bool Matrix::operator == ( const Matrix& matTmp ) const
{
	if (m_iRows == matTmp.m_iRows && m_iCols == matTmp.m_iCols)
	{
		for (int i = 0; i < (m_iRows * m_iCols); i++)
		{
			if (m_dData[i] != matTmp.m_dData[i])
			{
				return false;
			}
		}
	} else {
		return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
// Matrix Datatype - Inequality test overload
//-----------------------------------------------------------------------------
bool Matrix::operator != ( const Matrix& matTmp ) const
{
	if (m_iRows == matTmp.m_iRows && m_iCols == matTmp.m_iCols)
	{
		for (int i = 0; i < (m_iRows * m_iCols); i++)
		{
			if (m_dData[i] != matTmp.m_dData[i])
			{
				return true;
			}
		}
	} else {
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Matrix Datatype - Member Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Matrix Datatype - insert the contents of a vector into a specified row
//-----------------------------------------------------------------------------
void Matrix::insert ( int iRow, const Vector& vecIns )
{
	assert(m_iCols == 4);
	assert(iRow < m_iRows);
	assert(iRow >= 0);
	m(iRow,0) = vecIns.i;
	m(iRow,1) = vecIns.j;
	m(iRow,2) = vecIns.k;
	m(iRow,3) = vecIns.h;
}

//-----------------------------------------------------------------------------
// Matrix Datatype - insert a list of doubles into a specified row
//-----------------------------------------------------------------------------
void Matrix::insert ( int iRow, double dA, double dB, double dC, double dD )
{	
	assert(m_iCols == 4);
	assert(iRow < m_iRows);
	assert(iRow >= 0);
	m(iRow,0) = dA;
	m(iRow,1) = dB;
	m(iRow,2) = dC;
	m(iRow,3) = dD;
}

//-----------------------------------------------------------------------------
// Matrix Datatype - calculate the transpose of the matrix
//-----------------------------------------------------------------------------
Matrix Matrix::transpose ( void ) const
{
	Matrix matReturn(m_iRows,m_iCols);
	for (int i = 0; i < m_iCols; i++)
	{
		for (int j = 0; j < m_iRows; j++)
		{
			matReturn(i,j) = m(j,i);
		}
	}
	return matReturn;
}

//-----------------------------------------------------------------------------
// Matrix Datatype - calculate the inverse of the matrix
//                  http://en.wikipedia.org/wiki/Invertible_matrix
//-----------------------------------------------------------------------------
Matrix Matrix::inverse ( void ) const
{
	if ( m_iRows != m_iCols )
		die("Cannot invert non-square matrix"); // matrix must be square
	
	if ( m_iRows == 2 )
	{
		// easy inversion
		Matrix result (2, 2);
		
		result(0,0) = m(1,1);
		result(0,1) = -m(0,1);
		result(1,0) = -m(1,0);
		result(1,1) = m(0,0);
		
		result /= m(0,0) * m(1,1) - m(0,1) * m(1,0);

		return result;
	} else if (m_iRows == 4 ) {
		// blockwise inversion
		Matrix result (4, 4);

		// sub-matrices
		Matrix A ( 2, 2 );
		A(0,0) = m(0, 0); A(0,1) = m(0, 1);
		A(1,0) = m(1, 0); A(1,1) = m(1, 1);
		Matrix B ( 2, 2 );
		B(0,0) = m(0, 2); B(0,1) = m(0, 3);
		B(1,0) = m(1, 2); B(1,1) = m(1, 3);
		Matrix C ( 2, 2 );
		C(0,0) = m(2, 0); C(0,1) = m(2, 1);
		C(1,0) = m(3, 0); C(1,1) = m(3, 1);
		Matrix D ( 2, 2 );
		D(0,0) = m(2, 2); D(0,1) = m(2, 3);
		D(1,0) = m(3, 2); D(1,1) = m(3, 3);

		// calculations
		Matrix W = (A - B * D.inverse() * C).inverse();
		Matrix X = A.inverse() * B * (D - C * A.inverse() * B).inverse() * -1;
		Matrix Y = D.inverse() * C * (A - B * D.inverse() * C).inverse() * -1;
		Matrix Z = (D - C * A.inverse() * B).inverse();

		// composit
		result(0,0) = W(0,0);	result(0,1) = W(0,1);	result(0,2) = X(0,0);	result(0,3) = X(0,1);
		result(1,0) = W(1,0);	result(1,1) = W(1,1);	result(1,2) = X(1,0);	result(1,3) = X(1,1);
		result(2,0) = Y(0,0);	result(2,1) = Y(0,1);	result(2,2) = Z(0,0);	result(2,3) = Z(0,1);
		result(3,0) = Y(1,0);	result(3,1) = Y(1,1);	result(3,2) = Z(1,0);	result(3,3) = Z(1,1);

		return result;
	} else {
		// needs to be 2x2 or 4x4
		die("Cannot invert a matrix of this size");
	}

	// null return
	return Matrix();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Matrix Datatype - Static member functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Matrix Datatype - create a transformation matrix to translate points
//-----------------------------------------------------------------------------
Matrix Matrix::translate ( double dX, double dY, double dZ )
{
	Matrix matReturn(4,4);
	matReturn.insert(0,Vector(1,0,0,0));
	matReturn.insert(1,Vector(0,1,0,0));
	matReturn.insert(2,Vector(0,0,1,0));
	matReturn.insert(3,Vector(dX,dY,dZ,1));
	return matReturn;
}

//-----------------------------------------------------------------------------
// Matrix Datatype - create a transformation matrix to rotate points around
//					a vector
//-----------------------------------------------------------------------------
Matrix Matrix::rotate(double fAngle, const Vector& vecDir)
{
	double cosA = cos ( fAngle * 0.0174532925 );
	double sinA = sin ( fAngle * 0.0174532925 );

	Matrix matReturn(4,4);

	matReturn(0,0) = cosA + (1 - cosA) * vecDir.i * vecDir.i;
	matReturn(1,0) = (1 - cosA) * vecDir.i * vecDir.j - sinA * vecDir.k;
	matReturn(2,0) = (1 - cosA) * vecDir.i * vecDir.k + sinA * vecDir.j;

	matReturn(0,1) = (1 - cosA) * vecDir.j * vecDir.i + sinA * vecDir.k;
	matReturn(1,1) = cosA + (1 - cosA) * vecDir.j * vecDir.j;
	matReturn(2,1) = (1 - cosA) * vecDir.j * vecDir.k - sinA * vecDir.i;
	
	matReturn(0,2) = (1 - cosA) * vecDir.k * vecDir.i - sinA * vecDir.j;
	matReturn(1,2) = (1 - cosA) * vecDir.k * vecDir.j + sinA * vecDir.i;
	matReturn(2,2) = cosA + (1 - cosA) * vecDir.k * vecDir.k;

	matReturn(3,3) = 1;

	return matReturn;
}

//-----------------------------------------------------------------------------
// Matrix Datatype - create a transformation matrix to scale points
//-----------------------------------------------------------------------------
Matrix Matrix::scale ( double dX, double dY, double dZ )
{
	Matrix matReturn(4,4);
	matReturn.insert(0,Vector(dX,0,0,0));
	matReturn.insert(1,Vector(0,dY,0,0));
	matReturn.insert(2,Vector(0,0,dZ,0));
	matReturn.insert(3,Vector(0,0,0,1));
	return matReturn;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Matrix Datatype - Private access functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Matrix Datatype - private element access overload, mimics operator ()
//-----------------------------------------------------------------------------
double& Matrix::m ( int iRow, int iCol )
{
	assert(iRow >= 0);
	assert(iRow < m_iRows);
	assert(iCol >= 0);
	assert(iRow < m_iRows);
	return m_dData[iRow * m_iCols + iCol];
}

double& Matrix::m ( int iRow, int iCol ) const
{
	assert(iRow >= 0);
	assert(iRow < m_iRows);
	assert(iCol >= 0);
	assert(iRow < m_iRows);
	return m_dData[iRow * m_iCols + iCol];
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Matrix Datatype - global ostream overload
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::ostream& operator << ( std::ostream& oStream, const Matrix& matTmp )
{
	oStream << std::endl;
	for (int i = 0; i < matTmp.rows(); i++)
	{
		oStream << "[";
		for (int j = 0; j < matTmp.cols(); j++)
		{
			oStream << matTmp(i,j) << " ";
		}
		oStream << "]" << std::endl;
	}
	return oStream;
}