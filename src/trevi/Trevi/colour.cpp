/*
	Colour Storage (Implimentation)
	Matt Howe	E5034116
	Dec 06
*/

#include "colour.h"

//-----------------------------------------------------------------------------
// Colour Datatype - Constructor
//-----------------------------------------------------------------------------
Colour::Colour ( double dRed, double dGreen, double dBlue, double dAlpha )
	: r ( dRed ), g ( dGreen ) , b ( dBlue ), a ( dAlpha )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// Colour Datatype - Destructor
//-----------------------------------------------------------------------------
Colour::~Colour ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Colour Datatype - Operator Overloads
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Colour Datatype - Addition
//-----------------------------------------------------------------------------
Colour Colour::operator + ( const Colour& colArg ) const
{
	return Colour ( r + colArg.r, g + colArg.g, b + colArg.b, a + colArg.a );
}

const Colour& Colour::operator += ( const Colour& colArg )
{
	r += colArg.r;
	g += colArg.g;
	b += colArg.b;
	a += colArg.a;
	return *this;
}


//-----------------------------------------------------------------------------
// Colour Datatype - Subtraction
//-----------------------------------------------------------------------------
Colour Colour::operator - ( const Colour& colArg ) const
{
	return Colour ( r - colArg.r, g - colArg.g, b - colArg.b, a + colArg.a );
}

const Colour& Colour::operator -= ( const Colour& colArg )
{
	r -= colArg.r;
	g -= colArg.g;
	b -= colArg.b;
	a -= colArg.a;
	return *this;
}

//-----------------------------------------------------------------------------
// Colour Datatype - Multiplication
//-----------------------------------------------------------------------------
Colour Colour::operator * ( const Colour& colArg ) const
{
	return Colour ( r * colArg.r, g * colArg.g, b * colArg.b, a + colArg.a );
}

const Colour& Colour::operator *= ( const Colour& colArg )
{
	r *= colArg.r;
	g *= colArg.g;
	b *= colArg.b;
	a *= colArg.a;
	return *this;
}

//-----------------------------------------------------------------------------
// Colour Datatype - Division
//-----------------------------------------------------------------------------
Colour Colour::operator / ( const Colour& colArg ) const
{
	return Colour ( r / colArg.r, g / colArg.g, b / colArg.b, a + colArg.a );
}

const Colour& Colour::operator /= ( const Colour& colArg )
{
	r /= colArg.r;
	g /= colArg.g;
	b /= colArg.b;
	a /= colArg.a;
	return *this;
}


//-----------------------------------------------------------------------------
// Colour Datatype - Scalar Multiplication
//-----------------------------------------------------------------------------
Colour Colour::operator * ( double dArg ) const
{
	return Colour ( r * dArg, g * dArg, b * dArg, a * dArg );
}

const Colour& Colour::operator *= ( double dArg )
{
	r *= dArg;
	g *= dArg;
	b *= dArg;
	a *= dArg;
	return *this;
}

//-----------------------------------------------------------------------------
// Colour Datatype - Scalar Division
//-----------------------------------------------------------------------------
Colour Colour::operator / ( double dArg ) const
{
	return Colour( r / dArg, g / dArg, b / dArg, a * dArg );
}

const Colour& Colour::operator /= ( double dArg )
{
	r /= dArg;
	g /= dArg;
	b /= dArg;
	a /= dArg;
	return *this;
}
