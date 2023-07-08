/*
	Intersection Data Type (Header)
	Matt Howe	E5034116
	Nov 07
*/

#include "intersection.h"
#include <assert.h>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Intersection Data Type
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Intersection Data Type - Constructor
//-----------------------------------------------------------------------------
Intersection::Intersection ( bool bIntersects, double dTval, Vector vecPosition, Vector vecNormal, const Triangle* triTriangle, double dWeightA, double dWeightB, double dWeightC )
	: m_bIntersects ( bIntersects ), m_dTval ( dTval ), m_vecPosition ( vecPosition ), m_vecNormal ( vecNormal ), m_triTriangle ( triTriangle ), m_dWeightA ( dWeightA ), m_dWeightB ( dWeightB ), m_dWeightC ( dWeightC )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// Intersection Data Type - Destructor
//-----------------------------------------------------------------------------
Intersection::~Intersection ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Intersection Data Type - Access Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Intersection Data Type - Returns whether an intersection has occured
//-----------------------------------------------------------------------------
bool Intersection::intersects ( void )
{
	return m_bIntersects;
}

bool Intersection::intersects ( void ) const
{
	return m_bIntersects;
}

//-----------------------------------------------------------------------------
// Intersection Data Type - Returns the T value
//-----------------------------------------------------------------------------
double Intersection::tval ( void )
{
	return m_dTval;
}

double Intersection::tval ( void ) const
{
	return m_dTval;
}

//-----------------------------------------------------------------------------
// Intersection Data Type - Returns the intersection position
//-----------------------------------------------------------------------------
const Vector& Intersection::position ( void )
{
	assert(m_bIntersects);
	return m_vecPosition;
}

const Vector& Intersection::position ( void ) const
{
	assert(m_bIntersects);
	return m_vecPosition;
}

//-----------------------------------------------------------------------------
// Intersection Data Type - Returns the intersection normal
//-----------------------------------------------------------------------------
const Vector& Intersection::normal ( void )
{
	assert(m_bIntersects);
	return m_vecNormal;
}

const Vector& Intersection::normal ( void ) const
{
	assert(m_bIntersects);
	return m_vecNormal;
}

//-----------------------------------------------------------------------------
// Intersection Data Type - Returns the intersecting surface
//-----------------------------------------------------------------------------
const Triangle& Intersection::triangle ( void )
{
	assert(m_bIntersects);
	return *m_triTriangle;
}

const Triangle& Intersection::triangle ( void ) const
{
	assert(m_bIntersects);
	return *m_triTriangle;
}

//-----------------------------------------------------------------------------
// Intersection Data Type - Returns the intersection weights
//-----------------------------------------------------------------------------
double Intersection::weightA ( void )
{
	assert(m_bIntersects);
	return m_dWeightA;
}
double Intersection::weightA ( void ) const
{
	assert(m_bIntersects);
	return m_dWeightA;
}

double Intersection::weightB ( void )
{
	assert(m_bIntersects);
	return m_dWeightB;
}
double Intersection::weightB ( void ) const
{
	assert(m_bIntersects);
	return m_dWeightB;
}

double Intersection::weightC ( void )
{
	assert(m_bIntersects);
	return m_dWeightC;
}
double Intersection::weightC ( void ) const
{
	assert(m_bIntersects);
	return m_dWeightC;
}
