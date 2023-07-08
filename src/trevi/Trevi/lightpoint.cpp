/*
	Point Light Data Type (Header)
	Matt Howe	E5034116
	Dec 06 (Updated Apr 06)
*/

#include "lightpoint.h"
#include "intersection.h"
#include "raytrace.h"

//-----------------------------------------------------------------------------
// clamp function
//-----------------------------------------------------------------------------
double clamp(double dArg);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Point Light Data Type
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Point Light Data Type - Constructor
//-----------------------------------------------------------------------------
LightPoint::LightPoint ( Vector vecPosition, Colour clrIntensity, double dRadius, double dFalloff )
	: m_dFalloff ( dFalloff ), Light ( vecPosition, clrIntensity, dRadius )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// Point Light Data Type - Destructor
//-----------------------------------------------------------------------------
LightPoint::~LightPoint ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Point Light Data Type - Access functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Point Light Data Type - Falloff Access
//-----------------------------------------------------------------------------
double LightPoint::falloff ( void ) const
{
	return m_dFalloff;
}

void LightPoint::falloff ( double dFalloff )
{
	m_dFalloff = dFalloff;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Point Light Data Type - Light Command Call
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Colour LightPoint::light ( const Vector& vecPoint, const Scene& scnScene ) const
{
	// coordinate axes
	Vector vecW = (vecPoint - m_vecPosition).unit();
	Vector vecU;
	if (vecW != Vector(0,1,0) && vecW != Vector(0,-1,0))
		vecU = Vector::cross ( vecW, Vector(0,1,0) ).unit();
	else
		vecU = Vector::cross ( vecW, Vector(0,0,1) ).unit();
	Vector vecV = Vector::cross ( vecU, vecW ).unit();

	// jitter position
	Vector position = m_vecPosition;
	position += vecU * ( (double)(rand() % 100) / 100.0 - 0.5 ) * m_dRadius;
	position += vecV * ( (double)(rand() % 100) / 100.0 - 0.5 ) * m_dRadius;

	// shadow check
	Intersection shadowTest = Raytrace::Trace ( Ray ( position, (vecPoint - position).unit() ), scnScene );
	if ( shadowTest.intersects() == false
		|| ( shadowTest.intersects() == true
		&& shadowTest.tval() >= (vecPoint - position).mod() - 0.01 /* fix for self shadowing */ ) ) 
	{
		// not in shadow
		if (m_dFalloff == 0)
		{
			// no falloff
			return m_clrIntensity;
		} else {
			// falloff
			double distance = (position - vecPoint).mod();
			return m_clrIntensity * clamp(m_dFalloff - distance);
		}
	} else {
		// shadowed
		return Colour(0, 0, 0);
	}
}