/*
	Point Light Data Type (Header)
	Matt Howe	E5034116
	Dec 06 (Updated Apr 06)
*/

#pragma once;
#include "light.h"

//-----------------------------------------------------------------------------
// Point Light Data Type
//-----------------------------------------------------------------------------
class LightPoint : public Light
{
	public:
		// constructor
		LightPoint ( Vector vecPosition = Vector(), Colour clrIntensity = Colour(), double dRadius = 0, double dFalloff = 0 );
		// destructor
		~LightPoint ( void );

		// access functions
		double falloff ( void ) const;
		void falloff ( double );

		// light command call
		Colour light ( const Vector&, const Scene& ) const;

	private:
		// attenuation
		double m_dFalloff;
};