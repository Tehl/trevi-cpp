/*
	Vector Library (Header)
	Matt Howe	(E5034116)
	Oct 06
*/
#pragma once
#include <iostream>

//-----------------------------------------------------------------------------
// Fake class header
//-----------------------------------------------------------------------------
class Matrix;

//-----------------------------------------------------------------------------
// Vector Data Type
//-----------------------------------------------------------------------------
class Vector
{
	public:
		// constructor wi/default values
		Vector ( double dX = 0, double dY = 0, double dZ = 0, double dW = 1 );

		// destructor
		~Vector ( void );
		
		// overloading operators for basic functions
		const Vector& operator = ( const Vector& );
		Vector operator + ( const Vector& ) const;
		Vector operator - ( const Vector& ) const;
		Vector operator - ( void ) const;
		Vector operator * ( double ) const;
		Vector operator * ( const Matrix& ) const;
		Vector operator / ( double ) const;
		const Vector& operator += ( const Vector& );
		const Vector& operator -= ( const Vector& );
		const Vector& operator *= ( const Vector& );
		const Vector& operator *= ( const Matrix& );
		const Vector& operator /= ( const Vector& );
		bool operator == ( const Vector& ) const;
		bool operator != ( const Vector& ) const;

		// non-operator member functions
		double mod ( void ) const;
		Vector unit ( void ) const;
		void homogenise ( void );

		// static operations functions
		static double dot ( const Vector&, const Vector& );
		static Vector cross ( const Vector&, const Vector& );
	
		// data variables; should be private & encapsulated, but left public due to heavy access needs
		double i, j, k, h;		// non-Hungarian notation as meaning is explicit in a vector context; saves typing during access
};

//-----------------------------------------------------------------------------
// ostream overload
//-----------------------------------------------------------------------------
std::ostream& operator << (std::ostream& oStream, const Vector& vecTmp);