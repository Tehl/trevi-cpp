/*
	Spot Light Data Type (Header)
	Matt Howe	E5034116
	Dec 06 (Updated Apr 06)
*/

#pragma once;
#include "light.h"

//-----------------------------------------------------------------------------
// Spot Light Data Type
//-----------------------------------------------------------------------------
class LightSpot : public Light
{
	public:
		// constructor
		LightSpot ( Vector vecPosition = Vector(), Colour clrIntensity = Colour(), Vector vecDirection = Vector(), double dCutoff = 0, double dSpread = 0 );
		// destructor
		~LightSpot ( void );

		// access functions
		double cutoff ( void ) const;
		void cutoff ( double );

		double spread ( void ) const;
		void spread ( double );

		Vector direction ( void ) const;
		void direction ( Vector );
		void direction ( double, double, double );

		// light command call
		Colour light ( const Vector&, const Scene& ) const;

	private:
		// attenuation
		double m_dCutoff, m_dSpread;
		Vector m_vecDirection;
};

