/*
	Vector Library (Implementation)
	Matt Howe	(E5034116)
	Oct 06
*/
/*
	Notes:
		This version of the library has certain functionality stripped out for use with the PCGAPI, specifically that dealing with the homogeneous component.
		No checks are done on the 'h' variable; thus, care should be taken to ensure that vectors retain the same value for this when performing calculations on them.
*/
#include <math.h>
#include "vector.h"
#include "matrix.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Vector Data Type
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Vector Data Type - Constructor
//-----------------------------------------------------------------------------
Vector::Vector(double dX, double dY, double dZ, double dW)
	: i ( dX ), j ( dY ), k ( dZ ), h ( dW )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// Vector Data Type - Destructor
//-----------------------------------------------------------------------------
Vector::~Vector ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Vector Data Type - Operator Overloads
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Vector Data Type - Assignment Operator
//-----------------------------------------------------------------------------
const Vector& Vector::operator = ( const Vector& vecTmp )
{
	i = vecTmp.i;
	j = vecTmp.j;
	k = vecTmp.k;
	h = vecTmp.h;
	return *this;
}

//-----------------------------------------------------------------------------
// Vector Data Type - Vector Addition
//-----------------------------------------------------------------------------
Vector Vector::operator + ( const Vector& vecTmp ) const
{
	return Vector(i + vecTmp.i, j + vecTmp.j, k + vecTmp.k, h);
}

const Vector& Vector::operator += ( const Vector& vecTmp )
{
	i += vecTmp.i;
	j += vecTmp.j;
	k += vecTmp.k;
	return *this;
}

//-----------------------------------------------------------------------------
// Vector Data Type - Vector Subtraction
//-----------------------------------------------------------------------------
Vector Vector::operator - ( const Vector& vecTmp ) const
{
	return Vector(i - vecTmp.i, j - vecTmp.j, k - vecTmp.k, h);
}

const Vector& Vector::operator -= ( const Vector& vecTmp )
{
	i -= vecTmp.i;
	j -= vecTmp.j;
	k -= vecTmp.k;
	return *this;
}

//-----------------------------------------------------------------------------
// Vector Data Type - Negative Overload
//-----------------------------------------------------------------------------
Vector Vector::operator - ( void ) const
{
	return Vector(-i, -j, -k, h);
}

//-----------------------------------------------------------------------------
// Vector Data Type - Vector by Scalar multiplication
//-----------------------------------------------------------------------------
Vector Vector::operator * ( double dTmp ) const
{
	return Vector(dTmp * i, dTmp * j, dTmp * k, h);
}

const Vector& Vector::operator *= ( const Vector& vecTmp )
{
	i *= vecTmp.i;
	j *= vecTmp.j;
	k *= vecTmp.k;
	return *this;
}

//-----------------------------------------------------------------------------
// Vector Data Type - Vector by Matrix multiplication
//-----------------------------------------------------------------------------
Vector Vector::operator * ( const Matrix& matTmp ) const
{
	Matrix matThisVector(1);
	matThisVector.insert(0,i,j,k,h);
	matThisVector *= matTmp;
	return Vector(matThisVector(0,0), matThisVector(0,1), matThisVector(0,2), matThisVector(0,3));
}

const Vector& Vector::operator *= ( const Matrix& matTmp )
{
	Matrix matThisVector(1);
	matThisVector.insert(0,i,j,k,h);
	matThisVector *= matTmp;
	i = matThisVector(0,0);
	j = matThisVector(0,1);
	k = matThisVector(0,2);
	h = matThisVector(0,3);
	return *this;
}

//-----------------------------------------------------------------------------
// Vector Data Type - Vector by Scalar division
//-----------------------------------------------------------------------------
Vector Vector::operator / ( double dTmp ) const
{
	return Vector(i / dTmp, j / dTmp, k / dTmp, h);
}

const Vector& Vector::operator /= ( const Vector& vecTmp )
{
	i /= vecTmp.i;
	j /= vecTmp.j;
	k /= vecTmp.k;
	return *this;
}

//-----------------------------------------------------------------------------
// Vector Data Type - Equality
//-----------------------------------------------------------------------------
bool Vector::operator == ( const Vector& vecTmp ) const
{
	// compare individual components
	if (i == vecTmp.i && j == vecTmp.j && k == vecTmp.k && h == vecTmp.h)
	{
		// the vectors are equal
		return true;
	} else {
		// they aren't
		return false;
	}
}

//-----------------------------------------------------------------------------
// Vector Data Type - Inequality
//-----------------------------------------------------------------------------
bool Vector::operator != ( const Vector& vecTmp ) const
{
	// compare individual components
	if (i == vecTmp.i && j == vecTmp.j && k == vecTmp.k && h == vecTmp.h)
	{
		// the vectors are equal
		return false;
	} else {
		// they aren't
		return true;
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Vector Data Type - Member Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Vector Data Type - Modulus / Length
//-----------------------------------------------------------------------------
double Vector::mod ( void ) const
{
	return sqrt(i*i + j*j + k*k);
}

//-----------------------------------------------------------------------------
// Vector Data Type - Unit Direciton Vector
//-----------------------------------------------------------------------------
Vector Vector::unit ( void ) const
{
	double dMod = mod();	// call the mod() function to ascertain the length of the vector
	return Vector(i / dMod, j / dMod, k / dMod, h);	// do the maths and return the result
}

//-----------------------------------------------------------------------------
// Vector Data Type - Homogenise the vector - [i j k 1]
//-----------------------------------------------------------------------------
void Vector::homogenise ( void )
{
	i /= h;
	j /= h;
	k /= h;
	h = 1;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Vector Data Type - Static Member Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Vector Data Type - Dot Product of two vectors
//-----------------------------------------------------------------------------
double Vector::dot ( const Vector& vecA, const Vector& vecB )
{
	return ( vecA.i * vecB.i + vecA.j * vecB.j + vecA.k * vecB.k );
}

//-----------------------------------------------------------------------------
// Vector Data Type - Cross Product of two vectors
//-----------------------------------------------------------------------------
Vector Vector::cross ( const Vector& vecA, const Vector& vecB )
{
	return Vector ( vecA.j * vecB.k - vecA.k * vecB.j, vecA.k * vecB.i - vecA.i * vecB.k, vecA.i * vecB.j - vecA.j * vecB.i, vecA.h );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// global overload for cout access
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::ostream& operator << ( std::ostream& oStream, const Vector& vecTmp )
{
	oStream << "[" << vecTmp.i << " " << vecTmp.j << " " << vecTmp.k << " " << vecTmp.h << "]";
	return oStream;
}