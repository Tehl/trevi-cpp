/*
	Spot Light Data Type (Implimentation)
	Matt Howe	E5034116
	Dec 06 (Updated Apr 06)
*/

#include "lightspot.h"
#include "intersection.h"
#include "raytrace.h"
#include <math.h>

//-----------------------------------------------------------------------------
// clamp function
//-----------------------------------------------------------------------------
double clamp(double dArg);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Spot Light Data Type
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Spot Light Data Type - Constructor
//-----------------------------------------------------------------------------
LightSpot::LightSpot ( Vector vecPosition, Colour clrIntensity, Vector vecDirection, double dCutoff, double dSpread )
	: m_vecDirection ( vecDirection ), m_dCutoff ( dCutoff ), m_dSpread ( dSpread ), Light ( vecPosition, clrIntensity )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// Spot Light Data Type - Destructor
//-----------------------------------------------------------------------------
LightSpot::~LightSpot ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Spot Light Data Type - Access Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Spot Light Data Type - Cutoff Access
//-----------------------------------------------------------------------------
double LightSpot::cutoff ( void ) const
{
	return m_dCutoff;
}

void LightSpot::cutoff ( double dCutoff )
{
	m_dCutoff = dCutoff;
}

//-----------------------------------------------------------------------------
// Spot Light Data Type - Spread Access
//-----------------------------------------------------------------------------
double LightSpot::spread ( void ) const
{
	return m_dSpread;
}

void LightSpot::spread ( double dSpread )
{
	m_dSpread = dSpread;
}

//-----------------------------------------------------------------------------
// Spot Light Data Type - Direction Access
//-----------------------------------------------------------------------------
Vector LightSpot::direction ( void ) const
{
	return m_vecDirection;
}

void LightSpot::direction ( Vector vecNewDirection )
{
	m_vecDirection = vecNewDirection;
}

void LightSpot::direction ( double dPosX, double dPosY, double dPosZ )
{
	m_vecDirection.i = dPosX;
	m_vecDirection.j = dPosY;
	m_vecDirection.k = dPosZ;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Spot Light Data Type - Light Command Call
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Colour LightSpot::light ( const Vector& vecPoint, const Scene& scnScene ) const
{
	// are we inside the cone?
	Vector v = (vecPoint - m_vecPosition).unit();
	double vd = Vector::dot(v, m_vecDirection);
	double costheta = cos(m_dSpread * 0.0174532925); // convert to radians
	if (vd > costheta)
	{
		// we're inside
		// shadow check
		Intersection shadowTest = Raytrace::Trace ( Ray ( m_vecPosition, (vecPoint - m_vecPosition).unit() ), scnScene );
		if ( shadowTest.intersects() == false
			|| ( shadowTest.intersects() == true
			&& shadowTest.tval() >= (vecPoint - m_vecPosition).mod() - 0.01 /* fix for self shadowing */ ) )
		{
			// not in shadow
			return m_clrIntensity * ((vd - costheta) / (1 - costheta));
		} else {
			// shadowed
			return Colour(0, 0, 0);
		}
	} else {
		// no light
		return Colour(0, 0, 0);
	}
}