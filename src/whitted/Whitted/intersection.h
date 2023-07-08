/*
	Intersection Data Type (Header)
	Matt Howe	E5034116
	Nov 07
*/

#pragma once
#include "vector.h"
#include "surface.h"

//-----------------------------------------------------------------------------
// Intersection Data Type
//-----------------------------------------------------------------------------
class Intersection
{
	public:
		Intersection ( bool bIntersects = false, double dTval = 0.0, Vector vecPosition = Vector(), Vector verNormal = Vector(), Surface* surSurface = 0 );
		~Intersection ( void );

		// access functions
		bool intersects ( void );
		bool intersects ( void ) const;

		double tval ( void );
		double tval ( void ) const;

		const Vector& position ( void );
		const Vector& position ( void ) const;

		const Vector& normal ( void );
		const Vector& normal ( void ) const;

		Surface& surface ( void );
		Surface& surface ( void ) const;

	private:
		bool m_bIntersects;
		Vector m_vecNormal, m_vecPosition;
		double m_dTval;
		Surface* m_surSurface;
};
