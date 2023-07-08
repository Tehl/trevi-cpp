/*
	Intersection Data Type (Header)
	Matt Howe	E5034116
	Nov 07
*/

#pragma once
#include "vector.h"

class Triangle;

//-----------------------------------------------------------------------------
// Intersection Data Type
//-----------------------------------------------------------------------------
class Intersection
{
	public:
		Intersection ( bool bIntersects = false, double dTval = 0.0, Vector vecPosition = Vector(), Vector verNormal = Vector(), const Triangle* triTriangle = 0, double dWeightA = 1, double dWeightB = 0, double dWeightC = 0 );
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

		const Triangle& triangle ( void );
		const Triangle& triangle ( void ) const;

		double weightA ( void );
		double weightA ( void ) const;

		double weightB ( void );
		double weightB ( void ) const;

		double weightC ( void );
		double weightC ( void ) const;

	private:
		bool m_bIntersects;
		Vector m_vecNormal, m_vecPosition;
		double m_dTval;
		const Triangle* m_triTriangle;
		double m_dWeightA, m_dWeightB, m_dWeightC;
};
