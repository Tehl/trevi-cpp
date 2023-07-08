/*
	Ray Data Type (Implimentation)
	Matt Howe	E5034116
	Oct 07
*/

#include "ray.h"
#include <math.h>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Ray Data Type
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Ray Data Type - Constructor
//-----------------------------------------------------------------------------
Ray::Ray ( const Vector& vecPosition, const Vector& vecDirection )
{
	m_vecPosition = new Vector(vecPosition);
	m_vecDirection = new Vector(vecDirection);
}

//-----------------------------------------------------------------------------
// Ray Data Type - Default Constructor
//-----------------------------------------------------------------------------
Ray::Ray ( void )
{
	m_vecPosition = new Vector(0, 0, 0);
	m_vecDirection = new Vector(0, 0, 1);
}

//-----------------------------------------------------------------------------
// Ray Data Type - Copy Constructor
//-----------------------------------------------------------------------------
Ray::Ray ( const Ray& rayOriginal )
{
	m_vecPosition = new Vector(rayOriginal.position());
	m_vecDirection = new Vector(rayOriginal.direction());
}

//-----------------------------------------------------------------------------
// Ray Data Type - Destructor
//-----------------------------------------------------------------------------
Ray::~Ray ( void )
{
	delete m_vecPosition;
	delete m_vecDirection;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Ray Data Type - Operator Overloads
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Ray Data Type - Assignment Operator
//-----------------------------------------------------------------------------
const Ray& Ray::operator = ( const Ray& rayOriginal )
{
	*m_vecPosition = rayOriginal.position();
	*m_vecDirection = rayOriginal.direction();

	return *this;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Ray Data Type - Access Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Ray Data Type - Position Vector Access
//-----------------------------------------------------------------------------
const Vector& Ray::position ( void )
{
	return *m_vecPosition;
}

const Vector& Ray::position ( void ) const
{
	return *m_vecPosition;
}

void Ray::position ( const Vector& vecNewPosition )
{
	*m_vecPosition = vecNewPosition;
}

//-----------------------------------------------------------------------------
// Ray Data Type - Direction Vector Access
//-----------------------------------------------------------------------------
const Vector& Ray::direction ( void )
{
	return *m_vecDirection;
}

const Vector& Ray::direction ( void ) const
{
	return *m_vecDirection;
}

void Ray::direction ( const Vector& vecNewDirection )
{
	*m_vecDirection = vecNewDirection;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Ray Data Type - Member Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Ray Data Type - Reflect the ray from an intersection
//				Formula: Shirley, P174
//				intersection normal vector must be unit ( set elsewhere )
//-----------------------------------------------------------------------------
Ray Ray::reflect ( const Intersection& itsIntersection )
{
	return Ray(
		itsIntersection.position() - itsIntersection.normal() * 0.001, // fix for self-shadowing
		( *m_vecDirection - itsIntersection.normal() * 2 * Vector::dot ( *m_vecDirection, itsIntersection.normal() ) ).unit()
		);
}

//-----------------------------------------------------------------------------
// Ray Data Type - Refract the ray through an intersection
//				Formula: Shirley, P177, eq 12.7
//				ray direction, intersection normal vectors must be unit
//				 ( set elsewhere to save repeat calculations )
//-----------------------------------------------------------------------------
Ray Ray::refract ( const Intersection& itsIntersection, double dIndexSource, double dIndexDestination )
{
	double dDdotN = Vector::dot(*m_vecDirection, itsIntersection.normal());
	double dN1overN2 = dN1overN2 = dIndexSource / dIndexDestination;
	return Ray (
		itsIntersection.position() - itsIntersection.normal() * 0.001, // fix for self-shadowing
		( ( *m_vecDirection - itsIntersection.normal() * dDdotN ) * dN1overN2
			- itsIntersection.normal() * sqrt ( 1 - ( dN1overN2 * dN1overN2 * ( 1 - ( dDdotN * dDdotN ) ) ) ) ).unit()
		);
}