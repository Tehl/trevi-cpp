/*
	Colour Data Type (Header)
	Matt Howe	E5034116
	Dec 06 (Updated Nov 07)
*/

#pragma once

//-----------------------------------------------------------------------------
// Colour Data Type
//-----------------------------------------------------------------------------
class Colour
{
	public:
		// constructor
		Colour ( double dRed = 0.0, double dGreen = 0.0, double dBlue = 0.0, double dAlpha = 0.0 );
		// destructor
		~Colour ( void );

		// operator overloads
		Colour operator + ( const Colour& ) const;
		Colour operator - ( const Colour& ) const;
		Colour operator * ( const Colour& ) const;
		Colour operator / ( const Colour& ) const;
		Colour operator * ( double ) const;
		Colour operator / ( double ) const;
		const Colour& operator += ( const Colour& );
		const Colour& operator -= ( const Colour& );
		const Colour& operator *= ( const Colour& );
		const Colour& operator /= ( const Colour& );
		const Colour& operator *= ( double );
		const Colour& operator /= ( double );
		
		// data storage
		double r, g, b, a;
};
