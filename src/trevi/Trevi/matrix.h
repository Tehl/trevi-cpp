/*
	Matrix Library (Header)
	Matt Howe	(E5034116)
	Nov 06 (Updated Nov 07)
*/

#pragma once
#include "vector.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Matrix Datatype - global ostream overload
//-----------------------------------------------------------------------------
std::ostream& operator << (std::ostream&, const Matrix&);

//-----------------------------------------------------------------------------
// Matrix Datatype
//-----------------------------------------------------------------------------
class Matrix
{
	public:
		// constructor wi/default values
		Matrix ( int iRows = 4, int iCols = 4 );
		// copy constructor
		Matrix ( const Matrix& matArg );
		// destructor
		~Matrix ( void );

		// operator overloads
		const Matrix& operator = ( const Matrix& );
		Matrix operator + ( const Matrix& ) const;
		Matrix operator - ( const Matrix& ) const;
		Matrix operator * ( double ) const;
		Matrix operator / ( double ) const;
		Matrix operator * ( const Matrix& ) const;
		const Matrix& operator += ( const Matrix& );
		const Matrix& operator -= ( const Matrix& );
		const Matrix& operator *= ( double );
		const Matrix& operator /= ( double );
		const Matrix& operator *= ( const Matrix& );
		double& operator () ( int, int );
		double& operator () ( int, int ) const;
		Vector operator () ( int );
		Vector operator () ( int ) const;
		bool operator == ( const Matrix& ) const;
		bool operator != ( const Matrix& ) const;

		// non-operator member functions
		void insert ( int, const Vector& );
		void insert ( int, double, double, double, double );
		Matrix transpose ( void ) const;
		Matrix inverse ( void ) const;
		int rows ( void ) const { return m_iRows; }
		int cols ( void ) const { return m_iCols; }

		// static member functions
		static Matrix translate ( double, double, double );
		static Matrix rotate ( double, const Vector& );
		static Matrix scale ( double, double, double );

	private:
		// private access function, mimics 'operator ()'
		double& m ( int iRow = 0, int iCol = 0 );
		double& m ( int iRow = 0, int iCol = 0 ) const;
		// header for dynamic array data
		double* m_dData;
		// size of the matrix
		int m_iRows, m_iCols;
};


// http://www.parashift.com/c++-faq-lite/operator-overloading.html
