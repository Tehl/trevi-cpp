/*
	Light Data Type Virtual Parent (Header)
	Matt Howe	E5034116
	Dec 06 (Updated Apr 06)
*/

#pragma once;
#include "vector.h"
#include "colour.h"

class Scene;

//-----------------------------------------------------------------------------
// Light Data Type Virtual Parent
//-----------------------------------------------------------------------------
class Light
{
	public:
		// constructor; this class should never be instantiated
		Light ( Vector vecPosition = Vector(), Colour clrIntensity = Colour() );
		// destructor
		virtual ~Light ( void );

		// access functions
		Vector position ( void ) const;
		void position ( Vector );
		void position ( double, double, double );

		Colour intensity ( void ) const;
		void intensity ( Colour );
		void intensity ( double, double, double );

		// for LightPoint
		virtual double falloff ( void ) const;
		virtual void falloff ( double );
		// for LightSpot
		virtual double cutoff ( void ) const;
		virtual void cutoff ( double );
		virtual double spread ( void ) const;
		virtual void spread ( double );
		virtual Vector direction ( void ) const;
		virtual void direction ( Vector );
		virtual void direction ( double, double, double );

		// light command call
		virtual Colour light ( const Vector&, const Scene& ) const;

	protected:
		// light location
		Vector m_vecPosition;
		// intensity
		Colour m_clrIntensity;
};