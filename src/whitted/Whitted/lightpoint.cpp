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
LightPoint::LightPoint ( Vector vecPosition, Colour clrIntensity, double dFalloff )
	: m_dFalloff ( dFalloff ), Light ( vecPosition, clrIntensity )
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
	// shadow check
	Intersection shadowTest = Raytrace::Trace ( Ray ( m_vecPosition, (vecPoint - m_vecPosition).unit() ), scnScene );
	if ( shadowTest.intersects() == false
		|| ( shadowTest.intersects() == true
		&& shadowTest.tval() >= (vecPoint - m_vecPosition).mod() - 0.01 /* fix for self shadowing */ ) ) 
	{
		// not in shadow
		if (m_dFalloff == 0)
		{
			// no falloff
			return m_clrIntensity;
		} else {
			// falloff
			double distance = (position() - vecPoint).mod();
			return m_clrIntensity * clamp(m_dFalloff - distance);
		}
	} else {
		// shadowed
		return Colour(0, 0, 0);
	}
}