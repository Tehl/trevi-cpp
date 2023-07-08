/*
	Ray Data Type (Header)
	Matt Howe	E5034116
	Oct 07
*/

#pragma once
#include "vector.h"
#include "intersection.h"

//-----------------------------------------------------------------------------
// Ray Data Type
//-----------------------------------------------------------------------------
class Ray
{
	public:
		Ray ( const Vector&, const Vector& );
		Ray ( void );
		Ray ( const Ray& );
		~Ray ( void );

		// operators
		const Ray& operator = ( const Ray& );

		// access functions
		const Vector& position ( void );
		const Vector& position ( void ) const;
		void position ( const Vector& );

		const Vector& direction ( void );
		const Vector& direction ( void ) const;
		void direction ( const Vector& );

		// member functions
		Ray reflect ( const Intersection& );
		Ray refract ( const Intersection& , double, double );

	private:
		Vector *m_vecPosition, *m_vecDirection;
};
