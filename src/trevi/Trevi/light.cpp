/*
	Light Data Type Virtual Parent (Implementation)
	Matt Howe	E5034116
	Dec 06 (Updated Apr 07)
*/

#include "light.h"
#include "die.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Light Data Type Virtual Parent
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Light Data Type Virtual Parent - Constructor
//-----------------------------------------------------------------------------
Light::Light ( Vector vecPosition, Colour clrIntensity, double dRadius )
	: m_vecPosition(vecPosition), m_clrIntensity(clrIntensity), m_dRadius ( dRadius )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
// Light Data Type Virtual Parent - Destructor
//-----------------------------------------------------------------------------
Light::~Light ( void )
{
	// nothing to do here
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Light Data Type Virtual Parent - Access Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Light Data Type Virtual Parent - Position access
//-----------------------------------------------------------------------------
Vector Light::position ( void ) const
{
	return m_vecPosition;
}

void Light::position ( Vector vecNewPosition )
{
	m_vecPosition = vecNewPosition;
}

void Light::position ( double dPosX, double dPosY, double dPosZ )
{
	m_vecPosition.i = dPosX;
	m_vecPosition.j = dPosY;
	m_vecPosition.k = dPosZ;
}

//-----------------------------------------------------------------------------
// Light Data Type Virtual Parent - Intensity access
//-----------------------------------------------------------------------------
Colour Light::intensity ( void ) const
{
	return m_clrIntensity;
}

void Light::intensity ( Colour clrNewIntensity )
{
	m_clrIntensity = clrNewIntensity;
}

void Light::intensity ( double dR, double dG, double dB )
{
	m_clrIntensity.r = dR;
	m_clrIntensity.g = dG;
	m_clrIntensity.b = dB;
}

//-----------------------------------------------------------------------------
// Light Data Type Virtual Parent - Radius access
//-----------------------------------------------------------------------------
double Light::radius ( void ) const
{
	return m_dRadius;
}

double Light::radius ( void )
{
	return m_dRadius;
}

void Light::radius ( double dNewRadius )
{
	m_dRadius = dNewRadius;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Light Data Type Virtual Parent - for LightPoint
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
double Light::falloff ( void ) const
{
	// this should never be called
	die("Light::falloff() should not be called");
	return 0;
}

void Light::falloff ( double dFalloff )
{
	// this should never be called
	die("Light::falloff() should not be called");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Light Data Type Virtual Parent - for LightSpot
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
double Light::cutoff ( void ) const
{
	// this should never be called
	die("Light::cutoff() should not be called");
	return 0;
}

void Light::cutoff ( double dCutoff )
{
	// this should never be called
	die("Light::cutoff() should not be called");
}

double Light::spread ( void ) const
{
	// this should never be called
	die("Light::spread() should not be called");
	return 0;
}

void Light::spread ( double dSpread )
{
	// this should never be called
	die("Light::spread() should not be called");
}

Vector Light::direction ( void ) const
{
	// this should never be called
	die("Light::direction() should not be called");
	return Vector();
}

void Light::direction ( Vector vecNewPosition )
{
	// this should never be called
	die("Light::direction() should not be called");
}

void Light::direction ( double dPosX, double dPosY, double dPosZ )
{
	// this should never be called
	die("Light::direction() should not be called");
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Light Data Type Virtual Parent - Light command call
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Colour Light::light ( const Vector& vecPoint, const Scene& scnScene ) const
{
	// this should never be called
	die("Light::light() should not be called");
	return Colour(1,1,1);
}