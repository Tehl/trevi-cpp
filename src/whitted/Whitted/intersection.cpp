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
Intersection::Intersection ( bool bIntersects, double dTval, Vector vecPosition, Vector vecNormal, Surface* surSurface )
	: m_bIntersects ( bIntersects ), m_dTval ( dTval ), m_vecPosition ( vecPosition ), m_vecNormal ( vecNormal ), m_surSurface ( surSurface )
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
Surface& Intersection::surface ( void )
{
	assert(m_bIntersects);
	return *m_surSurface;
}

Surface& Intersection::surface ( void ) const
{
	assert(m_bIntersects);
	return *m_surSurface;
}
